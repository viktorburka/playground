#version 430
in vec2 texcoordFragment;
in vec3 normalFragment;
out vec4 outColor;
uniform sampler2D texSampler;
uniform vec3 lightColor;
uniform float ambientIntensity;
uniform float diffuseIntensity;
uniform vec3 lightDirection;
void main()
{
    vec4 diffuseColor;
    vec4 ambientColor = vec4(lightColor * ambientIntensity, 1.0f);
    float diffuseFactor = dot(normalize(normalFragment), lightDirection);
    if (diffuseFactor > 0) {
        diffuseColor = vec4(lightColor * diffuseIntensity * diffuseFactor, 1.0f);
    }
    else {
        diffuseColor = vec4(0, 0, 0, 0);
    }
    outColor = texture(texSampler, texcoordFragment) * (ambientColor + diffuseColor);
}
