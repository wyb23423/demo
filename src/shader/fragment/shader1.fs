#version 460 core

struct Material {
    sampler2D diffuse; // 漫反射
    sampler2D specular; // 镜面反射
    float shininess; // 反光度
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec2 TexCoords;

uniform Material material;
uniform Light light;

void main() {
    vec3 normal = normalize(Normal); // 法向量
    vec3 lightDir = normalize(LightPos - FragPos); // 光照方向

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(normalize(-FragPos), reflect(-lightDir, normal)), 0.0), material.shininess);

    vec3 materialDiffuseColor = vec3(texture(material.diffuse, TexCoords));
    vec3 ambient = light.ambient * materialDiffuseColor;
    vec3 diffuse = diff * light.diffuse * materialDiffuseColor;
    vec3 specular = spec * light.specular * vec3(texture(material.specular, TexCoords));

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
