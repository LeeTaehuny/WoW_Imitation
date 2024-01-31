//ComputePicking.hlsl
cbuffer RayBuffer : register(b0)
{
	float3 pos;
	uint triangleSize;
	
	float3 dir;
}

struct InputDesc
{
	float3 v0, v1, v2;
};
StructuredBuffer<InputDesc> input : register(t0);

struct OutputDesc
{
	int picked;
	float distance;
};
RWStructuredBuffer<OutputDesc> output : register(u0);

void Intersection(uint index)
{
	float3 A = input[index].v0;
	float3 B = input[index].v1;
	float3 C = input[index].v2;
	
	float3 e0 = B - A;
	float3 e1 = C - A;
	
	float3 P, T, Q;
	P = cross(dir, e1);
	
	float d = 1.0f / dot(e0, P);

	float u, v;
	
	T = pos - A;
	u = dot(T, P) * d;
	
	Q = cross(T, e0);
	v = dot(dir, Q) * d;
	output[index].distance = dot(e1, Q) * d;

	bool b = (u >= 0.0f) && (v >= 0.0f) &&
				(u + v <= 1.0f) && (output[index].distance >= 0.0f);

	output[index].picked = b ? 1 : 0;
}

[numthreads(64, 1, 1)]
void CS( uint3 DTid : SV_DispatchThreadID )
{
	uint index = DTid.x;
	
	if (triangleSize > index)
		Intersection(index);
}