#version 400

in vec2 frag_TextureCoords;


uniform sampler2D u_GuiTexture;

// Output from Fragment Shader RGBA colour
out vec4 pixel_Color;


void main(void) {

	pixel_Color = texture(u_GuiTexture, frag_TextureCoords);

}