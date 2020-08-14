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


float4 RadialWiggle(float2 uv)
{
	float2 center = float2(0.5f, 0.5f);
	float2 toUV = uv - center;
	float distanceFromCenter = length(toUV);
	float2 normToUV = toUV / distanceFromCenter;
	float angle = (atan2(normToUV.y, normToUV.x) + 3.141592f) / (2.0f * 3.141592f);
	float offset1 = tex2D(InputCloudSampler, float2(angle, frac(Progress / 3.0f + distanceFromCenter / 5.0f + RANDOMSEED))).x * 2.0f - 1.0f;
	float offset2 = offset1 * 2.0f * min(0.3f, (1.0f - Progress)) * distanceFromCenter;
	offset1 = offset1 * 2.0f * min(0.3f, Progress) * distanceFromCenter;

	float4 c1 = tex2D(Input1Sampler, frac(center + normToUV * (distanceFromCenter + offset1)));
	float4 c2 = tex2D(Input2Sampler, frac(center + normToUV * (distanceFromCenter + offset2)));

	return (lerp(c1, c2, Progress));
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (RadialWiggle(uv));
}


technique RadialWiggleTransition
{
	pass RadialWiggleTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
