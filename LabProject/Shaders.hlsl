
// 정점 셰이더
float4 VSMain(uint nVertexID : SV_VertexID) : SV_POSITION
{
    float4 output = (float4) 0;
    if (nVertexID == 0)
    {
        output = float4(-1.0f, +1.0f, 0.0f, 1.0f);
    }
    else if (nVertexID == 1)
    {
        output = float4(+1.0f, +1.0f, 0.0f, 1.0f);
    }
    else if (nVertexID == 2)
    {
        output = float4(+1.0f, -1.0f, 0.0f, 1.0f);
    }
    else if (nVertexID == 3)
    {
        output = float4(-1.0f, +1.0f, 0.0f, 1.0f);
    }
    else if (nVertexID == 4)
    {
        output = float4(+1.0f, -1.0f, 0.0f, 1.0f);
    }
    else if (nVertexID == 5)
    {
        output = float4(-1.0f, -1.0f, 0.0f, 1.0f);
    }
     
    return (output);
}


#define FRAME_BUFFER_WIDTH 800.0f
#define FRAME_BUFFER_HEIGHT 600.0f
//픽셀 쉐이더를 다음과 같이 정의하여 실행해 보면 다음과 같은 결과를 볼 수 있다.
float RegularPolygon(float2 f2NDC, float fSides, float fRadius)
{
    float fAngle = atan(f2NDC.y / f2NDC.x);
    float fSlices = (2.0f * 3.14159f) / fSides;
    float fShape = step(cos(floor((fAngle / fSlices) + 0.5f) * fSlices - fAngle) * length(f2NDC), fRadius);
    return (fShape);
}

float4 PSMain(float4 input : SV_POSITION) : SV_TARGET
{
    float4 cColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
    float2 f2NDC = float2(input.x / FRAME_BUFFER_WIDTH, input.y / FRAME_BUFFER_HEIGHT) - 0.5f; // (0, 1) : (-0.5, 0.5)
    f2NDC.x *= (FRAME_BUFFER_WIDTH / FRAME_BUFFER_HEIGHT);

    cColor.b = RegularPolygon(f2NDC - float2(-0.3f, -0.1f), 8.0f, 0.2f); //4, 6, 8, ... 
    cColor.r = RegularPolygon(f2NDC - float2(+0.3f, +0.2f), 4.0f, 0.15f);
    return (cColor);
}