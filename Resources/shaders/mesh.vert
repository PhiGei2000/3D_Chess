#version 420 
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT {
    vec3 fragPos;
    vec2 texCoords;
    vec3 normal;
} vs_out;

void main() {
    vs_out.fragPos = (model * vec4(aPosition, 1.0)).xyz;
    vs_out.texCoords = aTextureCoords;
    vs_out.normal = normalize(aNormal);

    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}