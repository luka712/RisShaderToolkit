struct VSInput
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD0;
};

[shader("vertex")]
VSOutput main_vs(VSInput input)
{
    VSOutput output;

    output.position = float4(input.position, 1.0);
    output.texCoord = input.texCoord;

    return output;
}

Texture2D    u_diffuseTexture    : register(t0);
SamplerState u_diffuseSampler    : register(s0);

[shader("fragment")]
float4 main_fs(VSOutput input) : SV_TARGET
{
    return u_diffuseTexture.Sample(u_diffuseSampler, input.texCoord);
}
