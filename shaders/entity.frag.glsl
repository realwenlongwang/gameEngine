// OpenGL 3.3
#version 330
in vec4 frag_UV;
in vec4 frag_Normal;
in vec3 frag_TowardsLight;
in vec3 frag_towardsCamera;

uniform sampler2D textureSampler;
uniform vec3 lightColour;
uniform float shineDamper;
uniform float reflectivity;

// Output from Fragment Shader RGBA colour
out vec4 pixel_Colour;

void main () {
    // Normalise the vector to make sure unit vector
    vec3 unitNormal = normalize(frag_Normal.xyz);
    vec3 unitTowardsLight = normalize(frag_TowardsLight);
    vec3 unitTowardsCamera = normalize(frag_towardsCamera);

    // Do the dot production to calculate the angle between 2 vectors
    float normalDotLight = dot(unitNormal, unitTowardsLight);
    // Make sure result is above 0.1 which is our ambient light
    float brightness = max(normalDotLight, 0.0f);
    vec3 diffuse = brightness * lightColour;

    // Light direction is just opposite vector towards light
    vec3 lightDirection = -unitTowardsLight;
    // Calculate reflect light
    vec3 reflectLightDirection = reflect(lightDirection, unitNormal);
    // Do dot production between reflect light direction and towards camera to see how much light goes to the camera
    float specularFactor = dot(reflectLightDirection, unitTowardsCamera);

    specularFactor = max(specularFactor, 0.0f);
    // This make low value even lower but does affect high value much
    float dampedFactor = pow(specularFactor, shineDamper);

    vec3 finalSpecular = dampedFactor * reflectivity * lightColour;
	//----------------------------------------------
	// Fragment Colour
	//----------------------------------------------
	pixel_Colour = texture(textureSampler, frag_UV.xy);
	pixel_Colour = vec4(vec3(1.0), 0.0);
	//TODO: Here need to muptiply by the texture, later can change to phone lighting
	pixel_Colour = vec4(diffuse, 1.0f)  + vec4(finalSpecular, 1.0f);
}