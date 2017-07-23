#version 120

varying vec4 f_color;
varying vec2 f_texCoord;

uniform sampler2D texture0;

void main() {

  //gl_FragColor = f_color;
  gl_FragColor = texture2D(texture0, f_texCoord).rgba * f_color;
}
