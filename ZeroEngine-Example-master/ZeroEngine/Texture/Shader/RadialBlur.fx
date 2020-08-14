sampler2D TextureSampler;

float2 Center = { 0.5, 0.5 }; ///center of the screen (could be any place)
float BlurStart = 1.0f; /// blur offset
float BlurWidth = 0.0f; ///how big it should be

float4 PS_RadialBlur(float2 UV	: TEXCOORD0 ) : COLOR0
{
    int nsamples = 20;

    UV -= Center;
    float4 c = 0;
    for(int i=0; i<nsamples; i++){
    	float scale = BlurStart + (-BlurWidth)*(i/(float) (nsamples-1));
    	c += tex2D(TextureSampler, UV * scale + Center );
    }
    c /= nsamples;
    //return float4(1.0f,0.0f,0.0f,1.0f);
    return c;
}
technique Default_DirectX_Effect{
  pass Pass_0{
    VertexShader = null;
    PixelShader = compile ps_2_0 PS_RadialBlur();
  }
}
