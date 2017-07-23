#version 120

uniform mat4 modelToCameraMatrix; //RenderState::modelview
uniform mat4 cameraToClipMatrix; //RenderState::projection
uniform mat4 modelToWorldMatrix; //RenderState::model
uniform mat4 modelToClipMatrix; //RenderState::modelview_projection

uniform int active_lights_n; // Number of active lights (< MG_MAX_LIGHT)

uniform struct light_t {
    vec4 position;    // Camera space
    vec3 ambient;     // rgb
    vec3 diffuse;     // rgb
    vec3 specular;    // rgb
    vec3 attenuation; // (constant, lineal, quadratic)
    vec3 spotDir;     // Camera space
    float cosCutOff;  // cutOff cosine
    float exponent;
} theLights[4];     // MG_MAX_LIGHTS

uniform struct material_t {
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    float alpha;
    float shininess;
} theMaterial;

attribute vec3 v_position; // Model space
attribute vec3 v_normal;   // Model space
attribute vec2 v_texCoord;

varying vec4 f_color; // Varying: Forma de comunicacion entre vertex y fragment
varying vec2 f_texCoord; // De salida(escritura) en vertex, de entrada(lectura) en el fragment shader

float diffuse_channel(const vec4 n,
					  const vec4 l) {
    //Solo se devuelve el prod vectorial si es > 0
    return max(0, dot(n,l) );
}

// r = 2(nl)n - l -> r es el vector del reflejo de la luz, vamos el rebote de l
// (r*v)^m -> v es el vector que va del vertice a la camara
// max(0, (r*v)^m ) -> intensidad especular
float specular_channel(const vec4 n,
					   const vec4 l,
					   const vec4 v,
					   float m) {
    vec4 r = 2 * diffuse_channel(n,l) * n - l;
    float aux = dot(r,v);
    if(aux > 0) return pow(aux,m);
    return 0.0;
}

// att = 1/(Ac + Al (Spos - p) + Aq (Spos - p)²)
// Ac es att constante // Al es la lineal // Aq es la cuadratica
// Si un valor de att es 1 entonces no existe atenuacion, mucha att es 0.999
float attenuation(const in int i, const in vec4 posicion){
    // attCte + attLineal * distance(lightPos-pos) + attCuadratica * distance(lightPos-pos)²

    if (theLights[i].attenuation[0] + theLights[i].attenuation[1] + theLights[i].attenuation[2] <= 1){
        float d = distance(theLights[i].position, posicion);
        vec3 att = theLights[i].attenuation;
        float denom = att[0] + att[1] * d + att[2] * pow(d, 2);
        if(denom > 0) return (1/denom);
    }

	return 1.0;
}

void direction_light(const in int i, const in vec4 lightDirection, const in vec4 viewDirection, const in vec4 normal,
					 inout vec3 ambient, inout vec3 diffuse, inout vec3 specular) {
	ambient += theLights[i].ambient * theMaterial.ambient;

    if(diffuse_channel(normal,lightDirection) > 0){
        diffuse += theLights[i].diffuse *
                    diffuse_channel(normal, lightDirection) *
                    theMaterial.diffuse;
        specular += theLights[i].specular *
                    specular_channel(normal,lightDirection, viewDirection, theMaterial.shininess) *
                    theMaterial.specular;
    }
}

void point_light(const in int i, const in vec4 lightDirection, const in vec4 viewDirection, const in vec4 normal,
				 inout vec3 ambient, inout vec3 diffuse, inout vec3 specular) {
    ambient += theLights[i].ambient * theMaterial.ambient;

    if(diffuse_channel(normal, lightDirection) > 0){
        diffuse += theLights[i].diffuse *
                    diffuse_channel(normal, lightDirection) *
                    attenuation(i, modelToCameraMatrix * vec4(v_position,1)) *
                    theMaterial.diffuse;

        specular += theLights[i].specular *
                    specular_channel(normal,lightDirection, viewDirection, theMaterial.shininess) *
                    attenuation(i, modelToCameraMatrix * vec4(v_position,1)) *
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
        if(d > 0) {//Podria ser negativo, y no queremos eso
            diffuse += theLights[i].diffuse *
                       d *
                       cSpot *
                       theMaterial.diffuse *
                       attenuation(i, modelToCameraMatrix * vec4(v_position,1));

            specular += theLights[i].specular *
                        specular_channel(normal,lightDirection, viewDirection, theMaterial.shininess) *
                        cSpot *
                        attenuation(i, modelToCameraMatrix * vec4(v_position,1)) *
                        theMaterial.specular;

        }
    }
}

void main() {

    f_color = vec4(0,0,0,1);
    // Eye significa que esta en coords de la camara
    vec4 positionEye = modelToCameraMatrix * vec4(v_position, 1);// 1 x ser pto
    vec4 normalEye = modelToCameraMatrix * vec4(v_normal,0);// 0 por vector
    vec3 ambient = vec3(0);
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);
    vec4 direccionLuz;
    vec4 direccionVista;
    //N o NormalEye = normal del vertice en el sistema de coords de la camara

	direccionVista = normalize(-positionEye);

	for(int i = 0; i < active_lights_n; ++i) {
	 	if(theLights[i].position.w == 0.0) {
	 	    //Direccional
	 	    direccionLuz = normalize(-theLights[i].position);
            direction_light(i,
                            direccionLuz,
                            direccionVista,
                            normalEye,
                            ambient,
                            diffuse,
                            specular);
	 	} else {
	 	    direccionLuz = normalize(theLights[i].position - positionEye);//Si no normalizamos
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
    f_color = vec4(ambient + diffuse + specular,1);

	gl_Position = modelToClipMatrix * vec4(v_position, 1);
	f_texCoord = v_texCoord;
}
