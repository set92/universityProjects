#version 120

attribute vec3 v_position;
attribute vec3 v_normal;
attribute vec2 v_texCoord;

uniform int active_lights_n; // Number of active lights (< MG_MAX_LIGHT)

uniform mat4 modelToCameraMatrix;
uniform mat4 cameraToClipMatrix;
uniform mat4 modelToWorldMatrix;
uniform mat4 modelToClipMatrix;

varying vec4 f_positionEye;
varying vec4 f_viewDirection;
varying vec4 f_normal;
varying vec2 f_texCoord;

void main() {

	f_positionEye = modelToCameraMatrix * vec4(v_position, 1);
	f_viewDirection = normalize(-f_positionEye);
	f_normal = normalize(modelToCameraMatrix * vec4(v_normal, 0));
	f_texCoord = v_texCoord;

	gl_Position = modelToClipMatrix * vec4(v_position, 1.0);
}
