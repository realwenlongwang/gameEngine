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

// Horizontal plane, (A, B, C, D) "A, B ,C is the normal of plane" "D is the height of plane"
uniform vec4 u_plane;

void main() {
    vec4 worldPosition = u_Translation * vert_Position;

    // Distance of the vertex from the plane
    gl_ClipDistance[0] = dot(worldPosition, u_plane);

    frag_UV = vert_UV;
    frag_Normal = u_Translation * vert_Normal;
    // Point light
    frag_TowardsLight = u_lightPosition - worldPosition.xyz;
    // Direction light
//    frag_TowardsLight = vec3(0.0f, 1.0f, 0.0f);

    vec3 camerPosition = (inverse(u_View) * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
    frag_towardsCamera = camerPosition - worldPosition.xyz;

	//----------------------------------------------
	// Vertex Position
	//----------------------------------------------
	gl_Position = u_Projection * u_View * u_Translation * vert_Position;

}