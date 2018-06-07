// OpenGL 3.3
#version 330

// Input to Vertex Shader
in vec4 vert_Position;
in vec4 vert_UV;
in vec4 vert_Normal;

// Transform Matrices
uniform mat4 u_Translation;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform vec3 u_lightPosition;

// Output to Fragment Shader
out vec4 frag_UV;
out vec4 frag_Normal;
out vec3 frag_TowardsLight;
out vec3 frag_towardsCamera;

void main() {
    vec4 worldPosition = u_Translation * vert_Position;

    frag_UV = vert_UV * 40;
    frag_Normal = u_Translation * vert_Normal;
    frag_TowardsLight = u_lightPosition - worldPosition.xyz;
    // "(inverse(u_View) * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz" this gives us camera position
    frag_towardsCamera = (inverse(u_View) * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz - worldPosition.xyz;

	//----------------------------------------------
	// Vertex Position
	//----------------------------------------------
	gl_Position = u_Projection * u_View * u_Translation * vert_Position;

}