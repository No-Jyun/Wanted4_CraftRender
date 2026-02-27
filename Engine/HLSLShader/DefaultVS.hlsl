float4 main( float3 pos : POSITION ) : SV_POSITION
{
    float4 outPosition = float4(pos.x, pos.y, pos.z, 1.0f);
	return outPosition;
}