#version 120
#extension GL_ARB_shading_language_420pack : require

// Bump mapping with many lights.
//
// All computations are performed in the tangent space; therefore, we need to
// convert all light (and spot) directions and view directions to tangent space
// and pass them the fragment shader.

varying vec2 f_texCoord;
varying vec3 f_viewDirection;     // tangent space
varying vec3 f_lightDirection[4]; // tangent space
varying vec3 f_spotDirection[4];  // tangent space

// all attributes in model space
attribute vec3 v_position;
attribute vec3 v_normal;
attribute vec2 v_texCoord;
attribute vec3 v_TBN_t;//tangent space matrix (TBN) tangente
attribute vec3 v_TBN_b;//binormal
// La normal es la misma, asi que usamos la v_normal

uniform mat4 modelToCameraMatrix;
uniform mat4 modelToWorldMatrix;
uniform mat4 cameraToClipMatrix;
uniform mat4 modelToClipMatrix;

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

void main() {

	mat3 MV3x3 = mat3(modelToCameraMatrix); // 3x3 modelview matrix

    vec3 n = normalize( MV3x3 * v_normal);
    vec3 t = normalize( MV3x3 * v_TBN_t );
    vec3 b = normalize( MV3x3 * v_TBN_b ); // No hace falta calcular la bitg, ya la tenemos
    //vec3 b = normalize( MV3x3 * ( cross( v_normal, v_TBN_t ) * 1 ) );

    vec3 vertexView = (modelToCameraMatrix * vec4(v_position,1) ).xyz ;

    //vec3 temp = ( modelToCameraMatrix * vec4( v_position, 1.0 ) ).xyz - vertexView;

    mat3 tbn = transpose(mat3( t, b, n ) );

    f_viewDirection = (tbn * (-vertexView));

    for(int i=0; i < active_lights_n; i++) {
        //lightDirection = lightPosition - vertexView;
        f_lightDirection[i] =  (theLights[i].position.xyz - vertexView);
    }

    f_texCoord = v_texCoord;
	gl_Position = modelToClipMatrix * vec4(v_position, 1.0);
}
