
#include "common.hlsl"

StructuredBuffer<float3> Position : register(t2);

void main(in VS_IN In, uint instanceID : SV_InstanceID, out PS_IN Out)
{
    float4 pos = In.Position;

    // ワールド（回転・スケール用）
    pos = mul(pos, World);

    // インスタンスごとの平行移動
    pos.xyz += Position[instanceID];

    pos = mul(pos, View);
    pos = mul(pos, Projection);

    Out.Position = pos;
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;
}

