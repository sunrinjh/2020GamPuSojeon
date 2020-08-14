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


float4 SampleWithBorder(float4 border, sampler2D tex, float2 uv)
{
	if (any(saturate(uv) - uv))
	{
		return (border);
	}
	else
	{
		return (tex2D(tex, uv));
	}
}

float4 DropFade(float2 uv)
{
	float offset = -tex2D(InputCloudSampler, float2(uv.x / 5.0f, RANDOMSEED)).x;
	float4 c1 = SampleWithBorder(0.0f, Input1Sampler, float2(uv.x, uv.y + offset * Progress));
	float4 c2 = tex2D(Input2Sampler, uv);

	if (c1.a <= 0.0f)
	{
		return (c2);
	}
	else
	{
		return (lerp(c1, c2, Progress));
	}
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (DropFade(uv));
}


technique DropFadeTransition
{
	pass DropFadeTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
