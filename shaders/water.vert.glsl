#version 400

in vec4 vert_Position;

out vec4 frag_ClipSpace;
out vec2 frag_TextureCoordinates;
out vec3 frag_TowardsCamera;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Transformation;
uniform vec3 u_CameraPosition;

const float tiling = 6.0f;

void main(void) {
    vec4 worldPosition = u_Transformation * vert_Position;
    frag_ClipSpace = u_Projection * u_View * worldPosition;
	gl_Position = frag_ClipSpace;
	// TODO: Should use the terrain texture parameter here, but so far the water looks ok
    frag_TextureCoordinates = vec2(vert_Position.x/ 2.0f + 0.5f, vert_Position.z/ 2.0f + 0.5f);
    frag_TowardsCamera = u_CameraPosition - worldPosition.xyz;
}