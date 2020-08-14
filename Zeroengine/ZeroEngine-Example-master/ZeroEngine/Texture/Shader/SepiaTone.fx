sampler2D TexSampler;

float4 ps_main(float2 texCoord : TEXCOORD0) : COLOR0
{   
  float4 tex = tex2D(TexSampler,texCoord);
  
  float4 sepia;
  sepia.a = tex.a;
  
  sepia.r = dot(tex.rgb,float3(0.393f,0.769f,0.189f));
  sepia.g = dot(tex.rgb,float3(0.349f,0.686f,0.168f));
  sepia.b = dot(tex.rgb,float3(0.272f,0.534f,0.131f));

  return sepia;
}

technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader =  null;
      PixelShader = compile ps_2_0 ps_main();
   }

}

