uniform mat4 projMat;
uniform mat4 MVMat;

attribute vec4 vPosition;

void main(){
	gl_Position = projMat * MVMat * vPosition;
}
