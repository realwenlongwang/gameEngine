#version 400

in vec4 frag_ClipSpace;
in vec2 frag_TextureCoordinates;
in vec3 frag_TowardsCamera;

uniform sampler2D u_ReflectionTexture;
uniform sampler2D u_RefractionTexture;
uniform sampler2D u_DudvMap;

uniform float u_MoveFactor;
// Output from Fragment Shader RGBA colour
out vec4 pixel_Color;

const float waveStrength = 0.03f;
const float reflactiveStrength = 1.0f;

void main(void) {
    // Get the device space coordinates and divided by 2 add 0.5 to put the origin from middle of display to the bottom left
    vec2 normalisedDeviceSpace = (frag_ClipSpace.xy/ frag_ClipSpace.w)/ 2.0f + 0.5f;

    // inverted the y coordinates so that is upside down
    vec2 reflectionCoordinates = vec2(normalisedDeviceSpace.x, -normalisedDeviceSpace.y);
    vec2 refractionCoordinates = normalisedDeviceSpace;

    // Multiply the red green value by 2 and minus 1 to create negative value
    vec2 distortion1 = (texture(u_DudvMap, vec2(frag_TextureCoordinates.x + u_MoveFactor, frag_TextureCoordinates.y)).rg * 2.0f - 1.0f) * waveStrength;
    vec2 distortion2 = (texture(u_DudvMap, vec2(-frag_TextureCoordinates.x + u_MoveFactor, frag_TextureCoordinates.y + u_MoveFactor)).rg * 2.0f - 1.0f) * waveStrength;

    vec2 totalDistortion = distortion1 + distortion2;

//    reflectionCoordinates += totalDistortion;
//    reflectionCoordinates.x = clamp(reflectionCoordinates.x, 0.001f, 0.999f);
//    reflectionCoordinates.y = clamp(reflectionCoordinates.y, -0.999f, -0.001f);
//
//    refractionCoordinates += totalDistortion;
//    refractionCoordinates = clamp(refractionCoordinates, 0.001, 0.999);

    vec4 reflectionColour = texture(u_ReflectionTexture, reflectionCoordinates);
    vec4 refractionColour = texture(u_RefractionTexture, refractionCoordinates);

    vec3 torwardsCameraUnit = normalize(frag_TowardsCamera);
    // As our water is just a x,z face, normal is hardcoded
    float refractionFactor = dot(torwardsCameraUnit, vec3(0.0f, 1.0f, 0.0f));
    // The higher the reflactive strength is the more reflactive the water is
    refractionFactor = pow(refractionFactor, reflactiveStrength);

	pixel_Color = mix(reflectionColour, refractionColour, refractionFactor);
	pixel_Color = mix(pixel_Color, vec4(0.0f, 0.3f, 0.5f, 1.0f), 0.1);
}