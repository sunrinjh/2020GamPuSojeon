sampler2D TexSampler;

float4 ps_main(float2 texCoord : TEXCOORD0) : COLOR0
{   
  float4 tex = tex2D(TexSampler,texCoord);
  
  tex.rgb = dot(tex,float3(0.3,0.59,0.11));
  
  return tex;
}

technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader =  null;
      PixelShader = compile ps_2_0 ps_main();
   }

}

