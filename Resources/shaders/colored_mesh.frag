#version 420

struct Material {
    vec3 diffuse;    
    vec3 specular;
};

struct Light {
    vec3 direction;
    
    vec3 color;    
};

in VS_OUT {
    vec3 fragPos;
    vec2 texCoords;
    vec3 normal;
} fs_in;

out vec4 FragColor;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

vec3 calcLight(vec3 objectColor, vec3 specular, vec3 normal, vec3 lightDir, vec3 viewDir);

void main() {        
    vec3 viewDir = normalize(viewPos - fs_in.fragPos);

    FragColor = vec4(calcLight(material.diffuse, material.specular, fs_in.normal, light.direction, viewDir), 1.0);                    
}

vec3 calcLight(vec3 objectColor, vec3 specular, vec3 normal, vec3 lightDir, vec3 viewDir) {
    // ambient
    vec3 ambient = specular.x * light.color;

    // diffuse
    float diff = max(dot(normal, -lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    // specular
    float specularStrength = specular.y;
    float shiniess = 256 * specular.z;
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shiniess);
    vec3 specularColor = specularStrength * spec * light.color;

    return (ambient + diffuse + specularColor) * objectColor;    
}