struct PSInput {
    float4 position : SV_POSITION;
    float4 v_color : COLOR;
    float2 v_texCoord : TEXCOORD0;
};

Texture2D u_diffuseTexture : register(t0);
SamplerState u_diffuseTextureSampler : register(s0);

float4 main(PSInput input) : SV_TARGET {
    float4 texColor = u_diffuseTexture.Sample(u_diffuseTextureSampler, input.v_texCoord);
    return texColor * input.v_color;
}