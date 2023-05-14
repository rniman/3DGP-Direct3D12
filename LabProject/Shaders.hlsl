
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
float4 PSMain(float4 input : SV_POSITION) : SV_TARGET
{
    float4 cColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
    float fDistance = distance(float2(0.5f, 0.5f), input.xy / float2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
    if (fDistance < 0.25f)
    {
        cColor.b = 1.0f;
    }
     
    return (cColor);
}