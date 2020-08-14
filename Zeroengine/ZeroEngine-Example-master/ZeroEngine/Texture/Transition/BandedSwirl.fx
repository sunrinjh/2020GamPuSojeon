float Progress;
float TwistAmount=4;
float Frequency=10;

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


float4 BandedSwirl(float2 uv)
{
	float2 center = float2(0.5f, 0.5f);
	float2 toUV = uv - center;
	float distanceFromCenter = length(toUV);
	float2 normToUV = toUV / distanceFromCenter;
	float angle = atan2(normToUV.y, normToUV.x);
	angle += sin(distanceFromCenter * Frequency) * TwistAmount * Progress;
	float2 newUV;
	sincos(angle, newUV.y, newUV.x);
	newUV = newUV * distanceFromCenter + center;

	float4 c1 = tex2D(Input1Sampler, frac(newUV));
	float4 c2 = tex2D(Input2Sampler, uv);

	return (lerp(c1, c2, Progress));
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (BandedSwirl(uv));
}



technique BandedSwirlTransition
{
	pass BandedSwirlTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
