float Progress;

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


float4 CloudReveal(float2 uv)
{
	float cloud = tex2D(InputCloudSampler, uv).r;
	float4 c1 = tex2D(Input1Sampler, uv);
	float4 c2 = tex2D(Input2Sampler, uv);

	float a;

	if (Progress < 0.5f)
	{
		a = lerp(0.0f, cloud, Progress / 0.5f);
	}
	else
	{
		a = lerp(cloud, 1.0f, (Progress - 0.5f) / 0.5f);
	}

	return ((a < 0.5f) ? c1 : c2);
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (CloudReveal(uv));
}


technique CloudRevealTransition
{
	pass CloudRevealTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
