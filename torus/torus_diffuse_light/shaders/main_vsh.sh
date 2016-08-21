#version 430
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
in vec3 position;
in vec2 texcoord;
in vec3 normal;
out vec2 texcoordFragment;
out vec3 normalFragment;
void main()
{
    normalFragment = (model * vec4(normal, 0.0)).xyz;
    texcoordFragment = texcoord;
    gl_Position = proj * view * model * vec4(position, 1.0);
}
