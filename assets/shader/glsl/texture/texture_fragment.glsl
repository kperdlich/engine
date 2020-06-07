#version 330

in vec4 color;
in vec2 texCoord;
out vec4 out_color;
uniform sampler2D texture2d;
uniform float ambientStrength;
uniform vec4 ambientColor;

void main()
{
    vec4 object_color = texture(texture2d, texCoord) * vec4(color.xyzw / 255);

    vec3 ambient = ambientStrength * vec3(ambientColor.xyz / 255);
    out_color = vec4(ambient.xyz, ambientColor.w / 255) * object_color;
}