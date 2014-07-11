#version 130

precision mediump float;

varying vec2 v_TexCoord;
uniform sampler2D u_Texture;

uniform vec4 fColor;

void main(){
	//Should multiply by black and white texture
	gl_FragColor = fColor * texture2D(u_Texture, v_TexCoord);
}
