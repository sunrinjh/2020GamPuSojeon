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

float4 Pixelate(float2 uv)
{
	float pixels;
	float segment_progress;
	if (Progress < 0.5f)
	{
		segment_progress = 1.0f - Progress * 2.0f;
	}
	else
	{
		segment_progress = (Progress - 0.5f) * 2.0f;
	}

	pixels = 5.0f + 1000.0f * segment_progress * segment_progress;
	float2 newUV = round(uv * pixels) / pixels;

	float4 c1 = tex2D(Input1Sampler, newUV);
	float4 c2 = tex2D(Input2Sampler, newUV);

	float lerp_progress = saturate((Progress - 0.4f) / 0.2f);
	return (lerp(c1, c2, lerp_progress));
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (Pixelate(uv));
}


technique PixelateTransition
{
	pass PixelateTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
