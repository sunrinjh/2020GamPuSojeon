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


float4 Crumple(float2 uv)
{
	float2 offset = tex2D(InputCloudSampler, float2(uv.x / 5.0f, frac(uv.y / 5.0f + min(0.9f, RANDOMSEED)))).xy * 2.0f - 1.0f;
	float p = Progress * 2.0f;
	if (p > 1.0f)
	{
		p = 1.0f - (p - 1.0f);
	}
	float4 c1 = tex2D(Input1Sampler, frac(uv + offset * p));
	float4 c2 = tex2D(Input2Sampler, frac(uv + offset * p));

	return (lerp(c1, c2, Progress));
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (Crumple(uv));
}


technique CrumpleTransition
{
	pass CrumpleTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
