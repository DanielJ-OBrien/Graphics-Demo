cbuffer ConstantBuffer
{
	matrix	WorldViewProjection;
	matrix  World;
	float4	AmbientLightColour;
	float4  DirectionalLightColour;
	float4  DirectionalLightVector;
};

Texture2D Texture;
SamplerState ss;

struct VertexIn
{
	float3 InputPosition : POSITION;
	float3 Normal		 : NORMAL;
	float2 TexCoord		 : TEXCOORD;
};

struct VertexOut
{
	float4 OutputPosition	: SV_POSITION;
	float4 Colour			: COLOR;
	float2 TexCoord			: TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	// Transform to homogeneous clip space.
	float4 vectorBackToLight = -DirectionalLightVector;
	float4 adjustedNormal = normalize(mul(World, float4(vin.Normal, 0.0f)));
	float diffuseBrightness = saturate(dot(adjustedNormal, vectorBackToLight));
	vout.TexCoord = vin.TexCoord;
	vout.Colour = saturate(AmbientLightColour * 0.25 + diffuseBrightness * DirectionalLightColour);
	vout.OutputPosition = mul(WorldViewProjection, float4(vin.InputPosition, 1.0f));
	
	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	return pin.Colour * Texture.Sample(ss, pin.TexCoord);
}


