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


float4 Ripple(float2 uv)
{
	float frequency = 20.0f;
	float speed = 10.0f;
	float amplitude = 0.05f;
	float2 center = float2(0.5f, 0.5f);
	float2 toUV = uv - center;
	float distanceFromCenter = length(toUV);
	float2 normToUV = toUV / distanceFromCenter;

	float wave = cos(frequency * distanceFromCenter - speed * Progress);
	float offset1 = Progress * wave * amplitude;
	float offset2 = (1.0f - Progress) * wave * amplitude;

	float2 newUV1 = center + normToUV * (distanceFromCenter + offset1);
	float2 newUV2 = center + normToUV * (distanceFromCenter + offset2);

	float4 c1 = tex2D(Input1Sampler, newUV1);
	float4 c2 = tex2D(Input2Sampler, newUV2);

	return (lerp(c1, c2, Progress));
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (Ripple(uv));
}


technique RippleTransition
{
	pass RippleTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
