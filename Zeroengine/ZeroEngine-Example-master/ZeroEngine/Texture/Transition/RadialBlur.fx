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


float4 RadialBlur(float2 uv)
{
	float2 center = float2(0.5f, 0.5f);
	float2 toUV = uv - center;
	float2 normToUV = toUV;

	float4 c1 = 0.0f;
	int count = 24;
	float s = Progress * 0.02f;

	for (int i = 0; i < count; i++)
	{
		c1 += tex2D(Input1Sampler, uv - normToUV * s * i);
	}

	c1 /= count;
	float4 c2 = tex2D(Input2Sampler, uv);

	return (lerp(c1, c2, Progress));
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (RadialBlur(uv));
}


technique RadialBlurTransition
{
	pass RadialBlurTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
