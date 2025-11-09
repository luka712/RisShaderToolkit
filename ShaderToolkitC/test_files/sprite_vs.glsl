#version 450

// Vertex attributes (match your VAO bindings)
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCoord;

// Uniform buffer
layout(binding = 0) uniform Uniforms {
    mat4 u_projectionView;
};

// Outputs to fragment shader
layout(location = 0) out vec4 v_color;
layout(location = 1) out vec2 v_texCoord;

void main()
{
    gl_Position = u_projectionView * vec4(a_position, 1.0);
    v_color = a_color;
    v_texCoord = a_texCoord;
}
