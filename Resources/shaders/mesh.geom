#version 420
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 fragPos;
    vec2 texCoords;
    vec3 normal;
} gs_in[];

out GS_OUT {
    vec3 fragPos;
    vec2 texCoords;
    mat3 tbn;
} gs_out;

mat3 calcTBN(vec3 normal, vec3 edge1, vec3 edge2, vec2 duv1, vec2 duv2);

void main() {
    for (int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        
        gs_out.fragPos = gs_in[i].fragPos;
        gs_out.texCoords = gs_in[i].texCoords;

        vec3 edge1 = gs_in[(i + 1) % 3].fragPos - gs_in[i].fragPos;
        vec3 edge2 = gs_in[(i + 2) % 3].fragPos - gs_in[i].fragPos;

        vec2 duv1 = gs_in[(i + 1) % 3].texCoords - gs_in[i].texCoords;
        vec2 duv2 = gs_in[(i + 2) % 3].texCoords - gs_in[i].texCoords;

        gs_out.tbn = calcTBN(gs_in[i].normal, edge1, edge2, duv1, duv2);
        EmitVertex();
    }
    EndPrimitive();
}

mat3 calcTBN(vec3 normal, vec3 edge1, vec3 edge2, vec2 duv1, vec2 duv2) {
    float f = 1 / (duv1.x * duv2.y - duv2.x * duv1.y);

    vec3 tangent = vec3(
        f * (duv2.y * edge1.x - duv1.y * edge2.x),
        f * (duv2.y * edge1.y - duv1.y * edge2.y),
        f * (duv2.y * edge1.z - duv1.y * edge2.z)
    );

    vec3 bitangent = vec3(
        f * (-duv2.x * edge1.x + duv1.x * edge2.x),
        f * (-duv2.x * edge1.y + duv1.x * edge2.y),
        f * (-duv2.x * edge1.z + duv1.x * edge2.z)
    );

    return mat3(tangent, bitangent, normal);
}