float Progress;
float2 slideAmount : register(C1);

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


float4 SlideLeft(float2 uv)
{
	slideAmount.x = 1;
	slideAmount.y = 1;
	uv += slideAmount * Progress;
	if(any(saturate(uv)-uv))
	{
		uv = frac(uv);
		return tex2D(Input2Sampler, uv);
	}
	else
	{
		return tex2D(Input1Sampler, uv);
	}
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (SlideLeft(uv));
}


technique SlideLeftTransition
{
	pass SlideLeftTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
