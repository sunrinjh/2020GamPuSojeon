float STRENGTH=100;
float FREQUENCY=50;
float SPEED=1;
float CURRENT_TIME;

texture SrcMap;
sampler SrcSamp = sampler_state
{
	Texture = <SrcMap>;
};

float4 YopparaiFunc1(float2 tex : TEXCOORD) : COLOR
{
	
	float4 color = 0.0f;
	float cosValue = cos(tex.y * FREQUENCY + CURRENT_TIME * SPEED) / STRENGTH;
	float sinValue = sin(tex.x * FREQUENCY + CURRENT_TIME * SPEED) / STRENGTH;

	float ntx = saturate(tex.x + cosValue);
	float nty = saturate(tex.y + sinValue);
	
	color = tex2D(SrcSamp, float2(ntx, nty));
	return (saturate(color));
	
}

technique Yopparai
{
	pass Yopparai4
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 YopparaiFunc1();
	}
}
