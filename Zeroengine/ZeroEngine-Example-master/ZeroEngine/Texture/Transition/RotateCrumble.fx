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


float4 RotateCrumple(float2 uv)
{
	float2 offset = (tex2D(InputCloudSampler, float2(uv.x / 10.0f, frac(uv.y / 10.0f + min(0.9f, RANDOMSEED)))).xy * 2.0f - 1.0f);
	float2 center = uv + offset / 10.0f;
	float2 toUV = uv - center;
	float len = length(toUV);
	float2 normToUV = toUV / len;
	float angle = atan2(normToUV.y, normToUV.x);

	angle += 3.141592f * 2.0f * Progress;
	float2 newOffset;
	sincos(angle, newOffset.y, newOffset.x);
	newOffset *= len;

	float4 c1 = tex2D(Input1Sampler, frac(center + newOffset));
	float4 c2 = tex2D(Input2Sampler, frac(center + newOffset));

	return (lerp(c1, c2, Progress));
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (RotateCrumple(uv));
}


technique RotateCrumpleTransition
{
	pass RotateCrumpleTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
