float Progress;
float RANDOMSEED;

texture Input1;
sampler Input1Sampler = sampler_state
{
	Texture = <Input1>;
};
texture Input2;
sampler Input2Sampler = sampler_state
{
	Texture = <Input2>;
};
texture InputCloud;
sampler InputCloudSampler = sampler_state
{
	Texture = <InputCloud>;
};


float4 RandomCircle(float2 uv)
{
	float radius = Progress * 0.70710678f;
	float2 fromCenter = uv - float2(0.5f, 0.5f);
	float len = length(fromCenter);

	float2 toUV = normalize(fromCenter);
	float angle = (atan2(toUV.y, toUV.x) + 3.141592f) / (2.0f * 3.141592f);
	radius += Progress * tex2D(InputCloudSampler, float2(angle, frac(RANDOMSEED + Progress / 5.0f))).r;

	if (len < radius)
	{
		return (tex2D(Input2Sampler, uv));
	}
	else
	{
		return (tex2D(Input1Sampler, uv));
	}
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (RandomCircle(uv));
}


technique RandomCircleTransition
{
	pass RandomCircleTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
