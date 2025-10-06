struct VSInput {
    float3 a_position : POSITION;
    float4 a_color : COLOR;
    float2 a_texCoord : TEXCOORD0;
};

struct VSOutput {
    float4 position : SV_POSITION;
    float4 v_color : COLOR;
    float2 v_texCoord : TEXCOORD0;
};

cbuffer Uniforms : register(b0) {
    float4x4 u_projectionView;
};

VSOutput main(VSInput input) {
    VSOutput output;
    output.position = mul(u_projectionView, float4(input.a_position, 1.0));
    output.v_color = input.a_color;
    output.v_texCoord = input.a_texCoord;
    return output;
}