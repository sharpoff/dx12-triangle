struct Vertex
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

float4 main(Vertex input) : SV_TARGET
{
    return input.color;
}