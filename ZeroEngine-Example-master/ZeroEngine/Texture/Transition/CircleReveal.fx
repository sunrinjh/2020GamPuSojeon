float Progress;
float FuzzyAmount=0.25;

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


float4 Circle(float2 uv)
{
	float radius = -FuzzyAmount + Progress * (0.70710678f + 2.0f * FuzzyAmount);
	float fromCenter = length(uv - float2(0.5f, 0.5f));
	float distFromCircle = fromCenter - radius;

	float4 c1 = tex2D(Input1Sampler, uv);
	float4 c2 = tex2D(Input2Sampler, uv);

	float p = saturate((distFromCircle + FuzzyAmount) / (2.0f * FuzzyAmount));
	return (lerp(c2, c1, p));
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (Circle(uv));
}


technique CircleTransition
{
	pass CircleTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
