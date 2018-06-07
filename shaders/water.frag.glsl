#version 400

in vec2 frag_TextureCoords;


// Output from Fragment Shader RGBA colour
out vec4 pixel_Color;


void main(void) {

	pixel_Color = vec4(0.0, 0.0, 1.0, 1.0);

}