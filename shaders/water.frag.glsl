#version 400

in vec4 frag_ClipSpace;
in vec2 frag_TextureCoordinates;
in vec3 frag_TowardsCamera;
in vec3 frag_FromLight;

uniform sampler2D u_ReflectionTexture;
uniform sampler2D u_RefractionTexture;
uniform sampler2D u_DudvMap;
uniform sampler2D u_NormalMap;
uniform sampler2D u_DepthMap;
uniform vec3 u_LightColour;

uniform float u_MoveFactor;

// Output from Fragment Shader RGBA colour
out vec4 pixel_Color;

const float waveStrength = 0.04f;
const float reflactiveStrength = 1.0f;
const float shineDamper = 5.0f;
const float reflectivity = 0.5f;
// TODO: Consider to make them uniform, params in MasterRender
const float nearPlane = 0.2f;
const float farPlane = 500.0f;
void main(void) {
    // Get the device space coordinates and divided by 2 add 0.5 to put the origin from middle of display to the bottom left
    vec2 normalisedDeviceSpace = (frag_ClipSpace.xy/ frag_ClipSpace.w)/ 2.0f + 0.5f;

    // inverted the y coordinates so that is upside down
    vec2 reflectionCoordinates = vec2(normalisedDeviceSpace.x, -normalisedDeviceSpace.y);
    vec2 refractionCoordinates = normalisedDeviceSpace;


    // Before coordinates get distorted, get the depth from depth map
    float depthFromCamToFloor = texture(u_DepthMap, refractionCoordinates).r; //[0, 1]
    // Convert it to actual distance
    float floorDistance = 2.0f * nearPlane * farPlane/ (farPlane + nearPlane - (2.0f * depthFromCamToFloor - 1.0f) * (farPlane - nearPlane));

    float depthFromCamToWater = gl_FragCoord.z;
    // Convert it to actual distance
    float waterDistance = 2.0f * nearPlane * farPlane/ (farPlane + nearPlane - (2.0f * depthFromCamToWater - 1.0f) * (farPlane - nearPlane));
    float waterDepth = floorDistance - waterDistance;
    // This factor can multiply by other effects to make them changing according to depth
    float waterDepthFactor = clamp(waterDepth/ 5.0f, 0.0f, 1.0f);
    // DEBUG: Cancel the factor
    waterDepthFactor = 1.0f;



    // Multiply the red green value by 2 and minus 1 to create negative value
    vec2 distortedTextureCoordinates = texture(u_DudvMap, vec2(frag_TextureCoordinates.x + u_MoveFactor, frag_TextureCoordinates.y)).rg * 0.1f;
    distortedTextureCoordinates = frag_TextureCoordinates + vec2(distortedTextureCoordinates.x, distortedTextureCoordinates.y + u_MoveFactor);
    // |clamp(waterDepth/ 20.0f, 0.0f, 1.0f)| make the distortion alround shallow place less
    vec2 totalDistortion = (texture(u_DudvMap, distortedTextureCoordinates).rg * 2.0f - 1.0f) * waveStrength * waterDepthFactor;


    reflectionCoordinates += totalDistortion;
    reflectionCoordinates.x = clamp(reflectionCoordinates.x, 0.001f, 0.999f);
    reflectionCoordinates.y = clamp(reflectionCoordinates.y, -0.999f, -0.001f);

    refractionCoordinates += totalDistortion;
    refractionCoordinates = clamp(refractionCoordinates, 0.001, 0.999);

    vec4 reflectionColour = texture(u_ReflectionTexture, reflectionCoordinates);
    vec4 refractionColour = texture(u_RefractionTexture, refractionCoordinates);

    // Normal mapping
    vec4 normalMapColour = texture(u_NormalMap, distortedTextureCoordinates);
    // Change the x, z value from [0, 1] to [-1, 1], can increase the y component of normal to make water more "calm"
    vec3 normal = vec3(normalMapColour.r * 2.0f - 1.0f, normalMapColour.b, normalMapColour.g * 2.0f - 1.0f);
    vec3 unitNormal = normalize(normal);

    vec3 unitTowardsCamera = normalize(frag_TowardsCamera);
    // As our water is just a x,z face, normal comes from normal map
    float refractionFactor = dot(unitTowardsCamera, unitNormal);
    // The higher the reflactive strength is the more reflactive the water is
    refractionFactor = pow(refractionFactor, reflactiveStrength);
    refractionFactor = clamp(refractionFactor, 0.0f, 1.0f);


    vec3 unitFormLight = normalize(frag_FromLight);
    // Calculate reflect light
    vec3 reflectLightDirection = reflect(unitFormLight, unitNormal);
    // Do dot production between reflect light direction and towards camera to see how much light goes to the camera
    float specularFactor = dot(reflectLightDirection, unitTowardsCamera);
    specularFactor = max(specularFactor, 0.0f);
    // This make low value even lower but does affect high value much
    float dampedFactor = pow(specularFactor, shineDamper);
    // Make the water at shallow place less specular than deep
    vec3 finalSpecular = dampedFactor * reflectivity * u_LightColour * waterDepthFactor;

	pixel_Color = mix(reflectionColour, refractionColour, refractionFactor);
	pixel_Color = mix(pixel_Color, vec4(0.0f, 0.3f, 0.5f, 1.0f), 0.05) + vec4(finalSpecular, 0.0f);
	// Set the water alpha value to the actual water depth
	pixel_Color.a = waterDepthFactor;
//	pixel_Color = normalMapColour;
//    pixel_Color = vec4(waterDepth/50.0f);]]

// fresnel term
// schlicks approximation

}