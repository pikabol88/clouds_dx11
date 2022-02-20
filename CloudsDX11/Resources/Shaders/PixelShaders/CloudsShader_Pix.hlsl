
/////////////
// GLOBALS //
/////////////
Texture2D cloudTexture : register(t0);
Texture2D perturbTexture : register(t1);
SamplerState SampleType;

cbuffer SkyBuffer
{
    float translation;
    float scale;
    float brightness;
    float padding;
};


//////////////
// TYPEDEFS //
//////////////
struct Input
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 main(Input input) : SV_TARGET
{
    float4 perturbValue;
    float4 cloudColor;


	// Translate the texture coordinate sampling location by the translation value.
    input.tex.x = input.tex.x + translation;

	// Sample the texture value from the perturb texture using the translated texture coordinates.
    perturbValue = perturbTexture.Sample(SampleType, input.tex);

	// Multiply the perturb value by the perturb scale.
    perturbValue = perturbValue * scale;

	// Add the texture coordinates as well as the translation value to get the perturbed texture coordinate sampling location.
    perturbValue.xy = perturbValue.xy + input.tex.xy + translation;

	// Now sample the color from the cloud texture using the perturbed sampling coordinates.
    cloudColor = cloudTexture.Sample(SampleType, perturbValue.xy);

	// Reduce the color cloud by the brightness value.
    cloudColor = cloudColor * brightness;

    return cloudColor;
}

