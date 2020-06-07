#version 330
in vec3 fragPos;
in vec4 color;
in vec3 normal;

out vec4 out_color;

uniform float u_ambientStrength;
uniform float u_specularStrength;
uniform float u_specularShininess;
uniform vec4 u_ambientColor;
uniform vec3 u_lightPosition;
uniform vec3 u_viewPos;

void main()
{
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

    vec3 result = (ambient + diffuse + specular) * vec3(color.xyz / 255.0);
    out_color = vec4(result, 1.0);
    
}