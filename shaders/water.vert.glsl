#version 400

in vec4 vert_Position;

out vec4 frag_ClipSpace;
out vec2 frag_TextureCoordinates;
out vec3 frag_TowardsCamera;
out vec3 frag_FromLight;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Transformation;
uniform vec3 u_CameraPosition;
uniform vec3 u_LightPosition;

const float tiling = 1.0f;

void main(void) {
    vec4 worldPosition = u_Transformation * vert_Position;
    frag_ClipSpace = u_Projection * u_View * worldPosition;
	gl_Position = frag_ClipSpace;
    frag_TextureCoordinates = vec2(vert_Position.x/ 2.0f + 0.5f, vert_Position.z/ 2.0f + 0.5f) * tiling;
    frag_TowardsCamera = u_CameraPosition - worldPosition.xyz;
    // Point light
    frag_FromLight = worldPosition.xyz - u_LightPosition;

    //Dirctional light;
//    frag_FromLight = vec3(0.0f, 1.0f, 0.0f);
}