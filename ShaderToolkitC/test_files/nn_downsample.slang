// Slang Compute Shader

// Source texture (read-only)
Texture2D<float4> g_source : register(t0);

// Destination texture (write-only)
RWTexture2D<float4> g_destination : register(u0);

cbuffer DownsampleParams : register(b0)
{
    int  g_step;
    int2 g_srcSize;
    int2 g_dstSize;
};

[numthreads(8, 8, 1)]
void main_cs(uint3 dispatchThreadID : SV_DispatchThreadID)
{
    int2 gid = int2(dispatchThreadID.xy);

    // Bounds check (destination bounds)
    if (gid.x >= g_dstSize.x || gid.y >= g_dstSize.y)
        return;

    int2 srcCoord = gid * g_step;

    // Bounds check (source bounds)
    if (srcCoord.x >= g_srcSize.x || srcCoord.y >= g_srcSize.y)
        return;

    // Load = exact texel fetch (no filtering)
    float4 color = g_source.Load(int3(srcCoord, 0));

    g_destination[gid] = color;
}
