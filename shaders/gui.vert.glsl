#version 400

in vec4 vert_Position;

out vec2 frag_TextureCoords;

uniform mat4 u_Transformation;


void main(void) {

	gl_Position = u_Transformation * vert_Position;
	frag_TextureCoords = vec2((vert_Position.x + 1.0f)/2.0f, 1.0f - (vert_Position.y + 1.0f)/2.0f);

}