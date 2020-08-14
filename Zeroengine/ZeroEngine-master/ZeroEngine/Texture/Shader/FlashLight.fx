sampler2D TexSampler;

float4 ps_main(float2 texCoord : TEXCOORD0) : COLOR0
{   
  float4 tex = tex2D(TexSampler,texCoord);

  tex.a = pow(1-tex.r,2);
  tex.rgb = dot(tex,float3(0,0,0));
  
  
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

