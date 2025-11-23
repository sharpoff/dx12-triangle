struct Vertex
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

Vertex main(float4 position : POSITION, float4 color : COLOR)
{
    Vertex result;
    result.position = position;
    result.color = color;
    return result;
}