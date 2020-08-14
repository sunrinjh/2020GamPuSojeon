sampler2D TexSampler;
float blurX=0;
float blurY=0;
float4 ps_main( float2 texCoord : TEXCOORD0 ) : COLOR0
{
    float4 Color;

	Color  = tex2D( TexSampler, float2(texCoord.x+blurX/2, texCoord.y+blurY/2) );
	Color += tex2D( TexSampler, float2(texCoord.x+blurX, texCoord.y+blurY) );
	Color += tex2D( TexSampler, float2(texCoord.x+blurX*2, texCoord.y+blurY*2) );
    return Color / 3;
}

technique Shake
{
    pass p1
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 ps_main();
    }
}
