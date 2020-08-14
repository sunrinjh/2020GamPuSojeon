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


float4 Saturate(float2 uv)
{
	float4 c1 = tex2D(Input1Sampler, uv);
	c1 = saturate(c1 * (2.0f * Progress + 1.0f));
	float4 c2 = tex2D(Input2Sampler, uv);

	if (Progress > 0.8f)
	{
		float new_progress = (Progress - 0.8f) * 5.0f;
		return (lerp(c1, c2, new_progress));
	}
	else
	{
		return (c1);
	}
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (Saturate(uv));
}


technique SaturateTransition
{
	pass SaturateTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
