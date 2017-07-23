#version 120

uniform int active_lights_n; // Number of active lights (< MG_MAX_LIGHT)

struct material_t {
	vec3  ambient;
	vec3  diffuse;
	vec3  specular;
	float alpha;
	float shininess;
};

struct light_t {
	vec4 position;    // Camera space
	vec3 ambient;     // rgb
	vec3 diffuse;     // rgb
	vec3 specular;    // rgb
	vec3 attenuation; // (constant, lineal, quadratic)
	vec3 spotDir;     // Camera space
	float cosCutOff;  // cutOff cosine
	float exponent;
};

uniform light_t theLights[4];
uniform material_t theMaterial;

uniform sampler2D texture0;
uniform sampler2D bumpmap;

varying vec2 f_texCoord;
varying vec3 f_viewDirection;     // tangent space
varying vec3 f_lightDirection[4]; // tangent space
varying vec3 f_spotDirection[4];  // tangent space

float diffuse_channel(const vec4 n,
					  const vec4 l) {
	return max(0, dot(n,l) );
}

float specular_channel(const vec4 n,
					   const vec4 l,
					   const vec4 v,
					   float m) {
    vec4 r = 2 * diffuse_channel(n,l) * n - l;
    float aux = dot(r,v);
    if(aux > 0) return pow(aux,m);
    return 0.0;
}

void direction_light(const in int i, const in vec4 lightDirection, const in vec4 viewDirection, const in vec4 normal,
					 inout vec3 ambient, inout vec3 diffuse, inout vec3 specular) {
    ambient += theLights[i].ambient * theMaterial.ambient;

    if(diffuse_channel(normal,lightDirection) > 0){
        diffuse += theLights[i].diffuse * diffuse_channel(normal, lightDirection) * theMaterial.diffuse;
        specular += theLights[i].specular *
                    specular_channel(normal,lightDirection, viewDirection, theMaterial.shininess) *
                    theMaterial.specular;
    }
}

void point_light(const in int i, const in vec4 lightDirection, const in vec4 viewDirection, const in vec4 normal,
				 inout vec3 ambient, inout vec3 diffuse, inout vec3 specular) {

    ambient += theLights[i].ambient * theMaterial.ambient;

    if(diffuse_channel(normal, lightDirection) > 0){
        diffuse += theLights[i].diffuse * diffuse_channel(normal, lightDirection) * theMaterial.diffuse ;
        specular += theLights[i].specular *
                    specular_channel(normal,lightDirection, viewDirection, theMaterial.shininess) *
                    theMaterial.specular;
    }

}

void spot_light(const in int i,	const in vec4 lightDirection, const in vec4 viewDirection,	const in vec4 normal,
				inout vec3 ambient, inout vec3 diffuse, inout vec3 specular) {

    float aux = dot(theLights[i].spotDir, -lightDirection.xyz);
    float cSpot = aux; // Coeficiente de la spotlight
    if(aux > 0) cSpot = pow(aux, theLights[i].exponent);
    else cSpot = 0.0;

    if(aux > theLights[i].cosCutOff){ // Solo se tiene en cuenta la parte positiva porque si es negativo estariamos restando luz
        ambient += theLights[i].ambient * theMaterial.ambient;

        float d = diffuse_channel(normal,lightDirection);//si dot(n,l) = 0 no hay reflejo especular
        if(d > 0) {
            diffuse += theLights[i].diffuse *
                       d *
                       cSpot *
                       theMaterial.diffuse;

            specular += theLights[i].specular *
                        specular_channel(normal,lightDirection, viewDirection, theMaterial.shininess) *
                        cSpot *
                        theMaterial.specular;

        }
    }
}


void main() {

    //https://www.opengl.org/sdk/docs/tutorials/TyphoonLabs/Chapter_4.pdf
    //http://www.fabiensanglard.net/bumpMapping/index.php
    //http://www.opengl-tutorial.org/es/intermediate-tutorials/tutorial-13-normal-mapping/
    //https://learnopengl.com/#!Advanced-Lighting/Normal-Mapping
    //http://www.gamasutra.com/blogs/RobertBasler/20131122/205462/Three_Normal_Mapping_Techniques_Explained_For_the_Mathematically_Uninclined.php?print=1


    //TODO http://www.swiftless.com/tutorials/glsl/8_bump_mapping.html
    vec4 normalEye = normalize(texture2D(bumpmap,f_texCoord)*2.0 - 1.0);
    vec3 ambient = vec3(0);
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);
    vec4 direccionLuz;
    vec4 direccionVista;
    //N o NormalEye = normal del vertice en el sistema de coords de la camara

	direccionVista = vec4(normalize(f_viewDirection),0); // punto es 1, vector es 0
	for(int i = 0; i < active_lights_n; ++i) {

	 	direccionLuz = vec4(normalize(f_lightDirection[i]),1);
	 	if(theLights[i].position.w == 0.0) {
	 	    //Direccional

            direction_light(i,
                            direccionLuz,
                            direccionVista,
                            normalEye,
                            ambient,
                            diffuse,
                            specular);
	 	} else {

	 		if (theLights[i].cosCutOff == 0.0) {
	 		    //Sol
	 		    point_light(i,
	 		                direccionLuz,
	 		                direccionVista,
	 		                normalEye,
	 		                ambient,
	 		                diffuse,
	 		                specular);
	 	  	} else {
	 	  	    //Foco
                spot_light(i,
                            direccionLuz,
                            direccionVista,
                            normalEye,
                            ambient,
                            diffuse,
                            specular);
	 	 	}
	 	}
	}

	//Iremos acumulando en f_color, ya que el resultado es la unificacion de todas las luces
    gl_FragColor = vec4(ambient + diffuse + specular,1) * texture2D(texture0, f_texCoord);
}
