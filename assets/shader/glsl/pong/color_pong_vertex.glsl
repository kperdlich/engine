#version 330
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Color;
layout(location = 2) in vec3 in_Normal;
out vec4 color;
out vec3 normal;
out vec3 fragPos;
uniform mat4 u_mvp;
uniform mat4 u_model;
uniform mat4 u_normalMtx;

void main()
{		
    fragPos = vec3(u_model * vec4(in_Position, 1.0));
    gl_Position = u_mvp * vec4(in_Position, 1.0);
    normal = mat3(u_normalMtx) * in_Normal;
    color = in_Color;
}