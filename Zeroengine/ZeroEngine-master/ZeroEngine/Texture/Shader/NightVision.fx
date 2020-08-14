sampler2D TextureSampler;

texture tex;
sampler noiseTex = 
sampler_state
{
  Texture = <tex>;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

float elapsedTime;
float luminanceThreshold = 0.1;
float colorAmplification = 4;



float4 UnderWater( float2 Tex : TEXCOORD0 ) : COLOR0
{

    float2 uv;
    uv.x = 0.4*sin(elapsedTime*50.0);
    uv.y = 0.4*cos(elapsedTime*50.0);
    float3 n = tex2D(noiseTex,
                 (Tex*3.5) + uv).rgb;
    float3 c = tex2D(TextureSampler, Tex + n.xy*0.005).rgb;

    float lum = dot(float3(0.30, 0.59, 0.11), c);
    if (lum < luminanceThreshold)
      c *= colorAmplification;

    float3 visionColor = float3(0.1, 0.95, 0.2);
    return  float4((c + (n*0.2)) * visionColor ,1);
    return float4(1.0f,0.0f,0.0f,1.0f);
}

technique NighVision
{
	pass P0
	{
		PixelShader = compile ps_2_0 UnderWater();
	}
}