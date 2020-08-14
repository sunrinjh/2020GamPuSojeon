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


float4 Fade(float2 uv)
{
	float4 c1 = tex2D(Input1Sampler, uv);
	float4 c2 = tex2D(Input2Sampler, uv);

	return (lerp(c1, c2, Progress));
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (Fade(uv));
}


technique FadeTransition
{
	pass FadeTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
