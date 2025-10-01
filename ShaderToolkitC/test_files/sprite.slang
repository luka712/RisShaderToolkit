struct VSInput
{
    float3 position : POSITION;
    float2 texCoord;
    float4 color;
}

struct VSOutput
{
    float4 position : SV_POSITION;
    float2 texCoord;
    float4 color;
}

ConstantBuffer<float4x4> c_viewProjection;

[shader("vertex")] VSOutput main_vs(VSInput input)
{
    VSOutput output;
    output.position = mul(c_viewProjection, float4(input.position, 1.0));
    output.texCoord = input.texCoord;
    output.color = input.color;
    return output;
}

Texture2D t_diffuseTexture;
SamplerState s_diffuseTexSampler;

[shader("fragment")]
float4 main_fs(VSOutput input) : SV_TARGET
{
    float4 textureColor = t_diffuseTexture.Sample(s_diffuseTexSampler, input.texCoord);
    return textureColor * input.color;
}