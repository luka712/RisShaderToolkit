#version 450

// Inputs from the vertex shader
layout(location = 0) in vec4 v_color;
layout(location = 1) in vec2 v_texCoord;

// Combined image & sampler (Vulkan/OpenGL style)
layout(binding = 0) uniform sampler2D u_diffuseTexture;

// Output
layout(location = 0) out vec4 outColor;

void main()
{
    vec4 texColor = texture(u_diffuseTexture, v_texCoord);
    outColor = texColor * v_color;
}
