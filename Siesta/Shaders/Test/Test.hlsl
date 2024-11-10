float4 MainVS(in float4 Position : POSITION0) : SV_Position
{
    return float4(Position.xyz, 1.0f);
}

float4 MainPS() : SV_Target0
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}