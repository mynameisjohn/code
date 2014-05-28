#version 130

uniform mat4 MVMat;
uniform mat4 projMat;

in vec2 vPosition;

void main() { 
	gl_Position = projMat * MVMat * vec4( vPosition.x, vPosition.y, 0, 1 ); 
}
