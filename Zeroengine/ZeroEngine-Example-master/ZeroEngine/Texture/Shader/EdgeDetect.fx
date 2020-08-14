sampler2D TexSampler;

float3x3 Kx = { -1, 0, 1,
                -2, 0, 2,
                -1, 0, 1};
float3x3 Ky = {  1, 2, 1,
                 0, 0, 0,
                -1,-2,-1};

float2 gPixelOffset;

float4 ps_main(float2 texCoord : TEXCOORD0) : COLOR0
{
  float Lx = 0;
  float Ly = 0;

  for(int y = -1; y<= 1; y++){
    for(int x=-1; x<=1; ++x){
      float2 offset = float2(x,y) * gPixelOffset;
      float3 tex = tex2D(TexSampler, texCoord + offset).rgb;
      float luminance = dot(tex, float3(0.3,0.59,0.11));
      //float luminance = dot(tex, float3(1,1,1));

      Lx += luminance * Kx[y+1][x+1];
      Ly += luminance * Ky[y+1][x+1];
    }
  }
  
  float L = sqrt((Lx*Lx) + (Ly*Ly));
  return float4(L.xxx,1);
}
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader =  null;
      PixelShader = compile ps_2_0 ps_main();
   }

}

