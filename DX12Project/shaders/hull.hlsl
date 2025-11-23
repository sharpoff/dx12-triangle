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

#define NUM_CONTROL_POINTS 3

HullOutput patchConstantHS(InputPatch<Vertex, NUM_CONTROL_POINTS> patch, uint PatchID : SV_PrimitiveID)
{
    const float tessFactor = 10.0f;
    
    HullOutput output;
    output.edgeTessFactor[0] = tessFactor;
    output.edgeTessFactor[1] = tessFactor;
    output.edgeTessFactor[2] = tessFactor;
    output.insideTessFactor = 1.0f;
    return output;
}

[domain("tri")]
[partitioning("fractional_even")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("patchConstantHS")]
Vertex main(InputPatch<Vertex, NUM_CONTROL_POINTS> patch, uint i : SV_OutputControlPointID, uint PatchID : SV_PrimitiveID)
{
    return patch[i];
}