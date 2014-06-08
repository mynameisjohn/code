#version 130

uniform mat4 projMat;
uniform mat4 MVMat;

attribute vec4 vPosition;
attribute vec2 a_TexCoord;
varying vec2 v_TexCoord;

void main(){
	v_TexCoord = a_TexCoord;
	gl_Position = projMat * MVMat * vPosition;
}
