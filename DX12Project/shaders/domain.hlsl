struct Vertex
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

struct HullOutput
{
    float edgeTessFactor[3] : SV_TessFactor;
    float insideTessFactor : SV_InsideTessFactor;
};

cbuffer ConstantBufferData : register(b0)
{
    float time;
};

#define NUM_CONTROL_POINTS 3

[domain("tri")]
Vertex main(HullOutput input, float3 domain : SV_DomainLocation, const OutputPatch<Vertex, NUM_CONTROL_POINTS> patch)
{
    float3 pos = patch[0].position * domain.x + patch[1].position * domain.y + patch[2].position * domain.z;
    float3 color = patch[0].color * domain.x + patch[1].color * domain.y + patch[2].color * domain.z;
    
    const float amplitude = 0.02f;
    const float frequency = 2.0f;
    const float2 phase = float2(5.0f, 10.0f);
    
    float3 offset = float3(0.0f, 0.0f, 0.0f);
    offset.x = sin(frequency * time + pos.y * phase.x) * amplitude;
    offset.y = sin(frequency * time + pos.x * phase.y) * amplitude;
    
    Vertex output;
    output.position = float4(pos + offset, 1.0f);
    output.color = float4(color, 1.0f);
    return output;
}