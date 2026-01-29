
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp = mul(mul(World, View), Projection);

    Out.Position = mul(In.Position, wvp);
    Out.Diffuse = In.Diffuse;
    Out.TexCoord = In.TexCoord;
    Out.Normal = In.Normal.xyz;
}

