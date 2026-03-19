# RisShaderToolkit

**RisShaderToolkit** is a supporting library created for the **RisGameFramework** project.  
Its main purpose is to provide a convenient, reliable foundation for **loading**, **compiling**, and **managing shaders** — especially those written in **Slang**.

## Project Structure

The toolkit consists of two main parts:

### 1. `RisShaderToolkit` (C# / .NET library)
- High-level, public-facing **C# API**
- Depends on the `shader_toolkit_c` native library
- Provides easy-to-use methods for compiling Slang shaders into multiple target formats:
  - WGSL
  - SPIR-V
  - possibly others in the future
- Published as **NuGet package(s)**
- Used by **RisGameFramework** but can be used by any other .NET project

### 2. `shader_toolkit_c` (C++ layer)
- Low-level **C++** implementation using the official **[Slang compilation API](https://shader-slang.org/docs/compilation-api/)**
- Exposes `ShaderCompiler` classes and a clean **C-compatible API**
- Compiled into a **dynamic library** (`.dll` / `.so` / `.dylib`)
- Acts as the bridge between Slang and higher-level managed code
- Currently considered **internal** even though it's open sourced — it is not planned to be released as a standalone package

## Goals & Philosophy

- Make **Slang** shader compilation dead simple in .NET / C# game/engine projects
- Provide a single, consistent API regardless of target backend (WebGPU, Vulkan, DirectX 12, etc.)
- Keep native code minimal and focused → most logic & convenience lives in C#
- Enable fast iteration when working with modern shading languages

## Current Status

- **C# NuGet package** → released and publicly available
- **C++ native layer** → internal / tightly coupled to the C# project (for now)
- Primarily developed & used by **RisGameFramework**

## Planned / Possible Future Directions

- Better diagnostic & error reporting in C#
- Shader reflection & metadata extraction helpers
- Support for more target profiles and optimization levels
- Using Slang modules
- (maybe) pure C# frontend for Slang

Feel free to use the **RisShaderToolkit NuGet package** in your own projects if you're working with Slang shaders in .NET!

## Basic Usage Example

Here's how you might compile a simple vertex + fragment shader pair to WGSL:

```c#
using RisShaderToolkit;
/// ...
const string SLANG_SOURCE = @"
    struct VSInput
    { 
        float3 position : POSITION;
        float2 texCoord : TEXCOORD0;
        float4 color : COLOR0;
    }

    struct VSOutput
    {
        float4 position : SV_POSITION;
        float2 texCoord : TEXCOORD0;
        float4 color : COLOR0;
    }

    ConstantBuffer<float4x4> viewProjection : register(b0, space0);

    [shader("vertex")]
    VSOutput main_vs(VSInput input)
    {
        VSOutput output;
        output.position = mul(viewProjection, float4(input.position, 1.0));
        output.texCoord = input.texCoord;
        output.color = input.color;
        return output;
    }

    Texture2D diffuseTexture: register(t0, space1);
    SamplerState diffuseTexSampler : register(s1, space1);

    [shader("fragment")]
    float4 main_fs(VSOutput input) : SV_TARGET
    {
        float4 textureColor = diffuseTexture.Sample(diffuseTexSampler, input.texCoord);
        return textureColor * input.color;
    }";

ShaderCompiler compiler = new ();
ShaderStage[] stages = [ShaderStage.VERTEX, ShaderStage.FRAGMENT]
CompileResult result = compiler.CompileSlangToWgsl(SLANG_SOURCE, stages);
var wgsl = result.SourceCode;
```
