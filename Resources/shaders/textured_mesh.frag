#version 420

struct Material {
    sampler2D diffuse;
    sampler2D normal;    
    sampler2D specular;
};

struct Light {
    vec3 direction;
    
    vec3 color;    
};

in GS_OUT {
    vec3 fragPos;
    vec2 texCoords;
    vec3 normal;
    mat3 tbn;
} fs_in;

out vec4 FragColor;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

uniform bool useNormalMap;

vec3 calcLight(vec3 objectColor, vec3 specular, vec3 normal, vec3 lightDir, vec3 viewDir);

void main() {
    vec3 diffuse = texture(material.diffuse, fs_in.texCoords).rgb;
    vec3 specular = texture(material.specular, fs_in.texCoords).rgb;
    vec3 normal;

    if(useNormalMap) {
        normal = normalize(texture(material.normal, fs_in.texCoords).rgb * 2.0 - 1.0);
        normal = normalize(fs_in.tbn * normal);
    }
    else {
        normal = fs_in.normal;
    }
    
    vec3 viewDir = normalize(viewPos - fs_in.fragPos);

    FragColor = vec4(calcLight(diffuse, specular, normal, light.direction, viewDir), 1.0);                
    // FragColor = vec4(diffuse, 1.0);
}

vec3 calcLight(vec3 objectColor, vec3 specular, vec3 normal, vec3 lightDir, vec3 viewDir) {
    // ambient
    vec3 ambient = specular.x * light.color;

    // diffuse
    float diff = max(dot(normal, -lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    // specular
    float specularStrength = specular.y / 4.0;
    float shiniess = 256 * specular.z / 4.0;
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shiniess);
    vec3 specularColor = specularStrength * spec * light.color;

    return (ambient + diffuse + specularColor) * objectColor;    
}