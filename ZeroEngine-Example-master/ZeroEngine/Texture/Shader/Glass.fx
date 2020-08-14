texture Input;
sampler InputSampler = sampler_state
{
	Texture = <Input>;
};

texture NormalMap;
sampler NormalMapSampler = sampler_state
{
	Texture = <NormalMap>;
};


float4 GlassFunc(float2 uv : TEXCOORD) : COLOR
{
	float4 nm = 1.0f * (tex2D(NormalMapSampler, uv));

	return (tex2D(InputSampler, uv + nm.xy *0.02f));
}


technique OgreGlass
{
	pass OgreGlass
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 GlassFunc();
	}
}
