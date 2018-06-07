#version 400

in vec4 vert_Position;

out vec2 frag_TextureCoords;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Transformation;


void main(void) {

	gl_Position = u_Projection * u_View * u_Transformation * vert_Position;
	frag_TextureCoords = vec2(vert_Position.x/2.0 + 0.5, vert_Position.z/2.0 + 0.5);

}