#version 460 core

// 点光源
struct PointLight {
    vec3 position;

    // 用于计算光强度
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir);

in vec3 Normal; // 法向量
in vec3 FragPos; // 片段坐标
in vec2 TexCoords; // 纹理坐标

uniform vec3 viewPos; // 观察者位置
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform PointLight pointLights[2];

out vec4 FragColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);
    for(int i = 0; i < 2; i++)
        result += calcPointLight(pointLights[i], norm, viewDir);

    FragColor = vec4(result, 1.0);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - FragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflect(-lightDir, normal)), 0.0), 32.0);

    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

    // 光强
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    return (ambient + diffuse + specular) * attenuation;
}
