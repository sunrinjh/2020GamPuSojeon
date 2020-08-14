//--------------------------------------------------------------------------------------
// 
// WPF ShaderEffect HLSL -- BloomEffect
//
//--------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Shader constant register mappings (scalars - float, double, Point, Color, Point3D, etc.)
//-----------------------------------------------------------------------------------------

float BaseIntensity=1;
float BaseSaturation=1;
float BloomIntensity=0;
float BloomSaturation=0;

//--------------------------------------------------------------------------------------
// Sampler Inputs (Brushes, including ImplicitInput)
//--------------------------------------------------------------------------------------

texture SourceTexture;
sampler SourceTextureSampler = sampler_state
{
	Texture = <SourceTexture>;
};


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 AdjustSaturation(float4 color, float saturation)
{
    float grey = dot(color, float3(0.3f, 0.59f, 0.11f));
    return lerp(grey, color, saturation);
}

float4 BloomFunc(float2 uv : TEXCOORD) : COLOR
{
    float BloomThreshold = 0.25f;

    float4 base = tex2D(SourceTextureSampler, uv);
    float4 bloom = saturate((base - BloomThreshold) / (1 - BloomThreshold));
    
    // Adjust color saturation and intensity.
    bloom = AdjustSaturation(bloom, BloomSaturation) * BloomIntensity;
    base = AdjustSaturation(base, BaseSaturation) * BaseIntensity;
    
    // Darken down the base image in areas where there is a lot of bloom,
    // to prevent things looking excessively burned-out.
    base *= (1.0f - saturate(bloom));
    
    // Combine the two images.
    return base + bloom;
}

technique Bloom
{
	pass Bloom
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 BloomFunc();
	}
}
