float STRENGTH;
float FREQUENCY=80;
float SPEED=0.5;
float CURRENT_TIME;



texture SrcMap;
sampler SrcSamp = sampler_state
{
	Texture = <SrcMap>;
};





float4 YopparaiFunc1(float2 tex : TEXCOORD) : COLOR
{
	float cosValue = cos(tex.y * FREQUENCY + CURRENT_TIME * SPEED) / STRENGTH;
	float sinValue = sin(tex.x * FREQUENCY + CURRENT_TIME * SPEED) / STRENGTH;

	float ntx = saturate(tex.x + cosValue);
	float nty = saturate(tex.y + sinValue);

	float4 color = tex2D(SrcSamp, float2(ntx, nty));

	return (saturate(color));
}


float4 YopparaiFunc2(float2 tex : TEXCOORD) : COLOR
{
	float d = sqrt((tex.x - 0.5f) * (tex.x - 0.5f) + (tex.y - 0.5f) * (tex.y - 0.5f));
	float cosValue = cos(d * FREQUENCY + CURRENT_TIME * SPEED) / STRENGTH;

	float ntx = saturate(tex.x + (tex.y - 0.5f) * cosValue / d);
	float nty = saturate(tex.y + (tex.x - 0.5f) * cosValue / d);

	float4 color = tex2D(SrcSamp, float2(ntx, nty));

	return (saturate(color));
}



float4 YopparaiFunc3(float2 tex : TEXCOORD) : COLOR
{
	float d = sqrt((tex.x - 0.5f) * (tex.x - 0.5f) + (tex.y - 0.5f) * (tex.y - 0.5f));
	float cosValue = cos(d * FREQUENCY + CURRENT_TIME * SPEED) / STRENGTH;

	float ntx = saturate(tex.x + cosValue);
	float nty = saturate(tex.y + cosValue);

	float4 color = tex2D(SrcSamp, float2(ntx, nty));

	return (saturate(color));
}



float4 YopparaiFunc4(float2 tex : TEXCOORD) : COLOR
{
	float d = sqrt((tex.x - 0.5f) * (tex.x - 0.5f) + (tex.y - 0.5f) * (tex.y - 0.5f));
	float cosValue = cos(d * FREQUENCY + CURRENT_TIME * SPEED) / STRENGTH;

	cosValue *= min(1.0f, d / 0.1f);

	float ntx = saturate(tex.x + (tex.x - 0.5f) * cosValue / d);
	float nty = saturate(tex.y + (tex.y - 0.5f) * cosValue / d);

	float4 color = tex2D(SrcSamp, float2(ntx, nty));

	return (saturate(color));
}



technique Yopparai
{
	pass Yopparai1
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 YopparaiFunc1();
	}

	pass Yopparai2
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 YopparaiFunc2();
	}

	pass Yopparai3
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 YopparaiFunc3();
	}

	pass Yopparai4
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 YopparaiFunc4();
	}
}
