texture Input;
sampler InputSampler = sampler_state
{
	Texture = <Input>;
};

float2 PIXEL_SIZE;

float Strength=0.005;
float progress=0;
static const float _samples[11] =
{
	0.01222447f,
	0.02783468f,
	0.06559061f,
	0.12097757f,
	0.17466632f,

	0.19741265f,

	0.17466632f,
	0.12097757f,
	0.06559061f,
	0.02783468f,
	0.01222447f
};

static const float2 _pos[11] =
{
	-5.0f, 0.0f,
	-4.0f, 0.0f,
	-3.0f, 0.0f,
	-2.0f, 0.0f,
	-1.0f, 0.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	2.0f, 0.0f,
	3.0f, 0.0f,
	4.0f, 0.0f,
	5.0f, 0.0f,
};


float4 GaussiaBlurHFunc(float2 uv : TEXCOORD) : COLOR
{
	float4 sum = 0.0f;
	for (int i = 0; i < 11; i++)
	{
		sum += tex2D(InputSampler, uv + _pos[i].xy * Strength /*0.01f*/) * _samples[i];
	}
	return (sum);
}

float4 GaussiaBlurVFunc(float2 uv : TEXCOORD) : COLOR
{
	PIXEL_SIZE.x = 1024;
	PIXEL_SIZE.y = 768;
	float4 sum = 0.0f;
	for (int i = 0; i < 11; i++)
	{
		sum += tex2D(InputSampler, uv + _pos[i].yx * Strength /*0.01f*/) * _samples[i];
	}
	float4 base = tex2D(InputSampler, uv);
	return lerp(base, sum, progress);
	//return (sum);
	return (sum);
}




technique OgreGaussianBlur
{
	pass V
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 GaussiaBlurVFunc();
	}
}
