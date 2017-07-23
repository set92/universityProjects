#version 120

uniform mat4 modelToCameraMatrix;
uniform mat4 cameraToClipMatrix;
uniform mat4 modelToWorldMatrix;
uniform mat4 modelToClipMatrix;

attribute vec3 v_position;

varying vec3 f_texCoord;

void main() {

	gl_Position = modelToClipMatrix * vec4(v_position, 1.0);
	//f_texCoord = (modelToWorldMatrix * vec4(v_position, 1.0)).xyz;
	f_texCoord = v_position;
}
