#version 330
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Color;
layout(location = 2) in vec3 in_Normal;

out vec4 color;
uniform mat4 u_mvp;
uniform mat4 u_model;
uniform mat4 u_normalMtx;
uniform float u_ambientStrength;
uniform float u_specularStrength;
uniform float u_specularShininess;
uniform vec4 u_ambientColor;
uniform vec3 u_lightPosition;
uniform vec3 u_viewPos;

void main()
{		
    vec3 fragPos = vec3(u_model * vec4(in_Position, 1.0));
    vec3 normal = mat3(u_normalMtx) * in_Normal;		
    vec3 lightColor = vec3(u_ambientColor.xyz / 255);

    // ambient
    vec3 ambient = u_ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_lightPosition - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;		

    // specular
    vec3 viewDir = normalize(u_viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_specularShininess);
    vec3 specular = u_specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * vec3(in_Color.xyz / 255.0);
    color = vec4(result, 1.0);
    gl_Position = u_mvp * vec4(in_Position, 1.0);
}