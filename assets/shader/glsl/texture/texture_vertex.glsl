#version 330

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_Color;
layout(location = 2) in vec3 in_Normals;
layout(location = 3) in vec2 in_TexCoord;

out vec4 color;
out vec2 texCoord;
uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * vec4(in_position, 1.0);
    color = in_Color;
    texCoord = in_TexCoord;
}