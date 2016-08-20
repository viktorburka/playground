#version 430
in vec2 texcoordFragment;
out vec4 outColor;
uniform sampler2D texSampler;
void main()
{
   outColor = texture(texSampler, texcoordFragment);
}
