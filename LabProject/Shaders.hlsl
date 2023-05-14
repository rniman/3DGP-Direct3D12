
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
    float x = abs(frac((input.x * 10.0f) / FRAME_BUFFER_HEIGHT) - 0.5f);
    float y = abs(frac((input.y * 10.0f) / FRAME_BUFFER_HEIGHT) - 0.5f);
    cColor.r = ((x <= 0.0125f) || (y <= 0.0125f)) ? 1.0f : 0.0f;
    return (cColor);
}