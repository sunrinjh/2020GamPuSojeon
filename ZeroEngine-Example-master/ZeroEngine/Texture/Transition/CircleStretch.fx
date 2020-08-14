float Progress;

texture Input1;
sampler Input1Sampler = sampler_state
{
	Texture = <Input1>;
};
texture Input2;
sampler Input2Sampler = sampler_state
{
	Texture = <Input2>;
};


float DistanceFromCenterToSquareEdge(float2 dir)
{
	dir = abs(dir);
	float dist = dir.x > dir.y ? dir.x : dir.y;
	return (dist);
}

float4 CircleStretch(float2 uv)
{
	float2 center = float2(0.5f, 0.5f);
	float radius = Progress * 0.70710678f;
	float2 toUV = uv - center;
	float len = length(toUV);
	float2 normToUV = toUV / len;

	if (len < radius)
	{
		float distFromCenterToEdge = DistanceFromCenterToSquareEdge(normToUV) / 2.0f;
		float2 edgePoint = center + distFromCenterToEdge * normToUV;

		float minRadius = min(radius, distFromCenterToEdge);
		float percentFromCenterToRadius = len / minRadius;

		float2 newUV = lerp(center, edgePoint, percentFromCenterToRadius);
		return tex2D(Input2Sampler, newUV);
	}
	else
	{
		float distFromCenterToEdge = DistanceFromCenterToSquareEdge(normToUV);
		float2 edgePoint = center + distFromCenterToEdge * normToUV;
		float distFromRadiusToEdge = distFromCenterToEdge - radius;

		float2 radiusPoint = center + radius * normToUV;
		float2 radiusToUV = uv - radiusPoint;

		float percentFromRadiusToEdge = length(radiusToUV) / distFromRadiusToEdge;

		float2 newUV = lerp(center, edgePoint, percentFromRadiusToEdge);
		return tex2D(Input1Sampler, newUV);
	}
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(float2 uv : TEXCOORD) : COLOR
{
	return (CircleStretch(uv));
}


technique CircleStretchTransition
{
	pass CircleStretchTransition
	{
		VertexShader = null;
		PixelShader = compile ps_2_0 main();
	}
}
