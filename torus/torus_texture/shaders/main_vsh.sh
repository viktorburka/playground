#version 430
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
in vec3 position;
in vec2 texcoord;
out vec2 texcoordFragment;
void main()
{
    texcoordFragment = texcoord;
    gl_Position = proj * view * model * vec4(position, 1.0);
}
