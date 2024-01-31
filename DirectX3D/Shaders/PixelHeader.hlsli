//PixelHeader
#define MAX_LIGHT 10

static const float2 shininessRange = { 0.1f, 50.0f };

//Pixel Struct
struct Material
{
	float3 normal;
	float4 diffuseColor;
	float4 specularIntensity;
	float3 viewPos;
	float3 worldPos;
};

struct Light
{
	float4 color;
	
	float3 direction;
	int type;
	
	float3 position;
	float range;
	
	float inner;
	float outer;
	float length;
	int active;
};

struct LightPixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float3 viewPos : POSITION0;
	float3 worldPos : POSITION1;
};

struct GBufferOutput
{
	float4 diffuse : SV_TARGET0;
	float4 specular : SV_TARGET1;
	float4 normal : SV_TARGET2;
};

//Pixel ConstBuffer
cbuffer LightBuffer : register(b0)
{
	Light lights[MAX_LIGHT];
	
	uint lightCount;
	
	float3 ambientLight;
	float3 ambientCeil;
}

cbuffer MaterialBuffer : register(b3)
{
	float4 mDiffuse;
	float4 mSpecular;
	float4 mAmbient;
	float4 mEmissive;
	
	float shininess;
	int hasNormalMap;
}

//Texture & Sampler
SamplerState samp : register(s0);

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);

//Pixel Function
float3 NormalMapping(float3 T, float3 B, float3 N, float2 uv)
{
	T = normalize(T);
	B = normalize(B);
	N = normalize(N);
	
	[flatten]
	if (hasNormalMap)
	{	
		float3 normal = normalMap.Sample(samp, uv).rgb;
		normal = normal * 2.0f - 1.0f; //0~1 -> -1~1
		float3x3 TBN = float3x3(T, B, N);
		N = normalize(mul(normal, TBN));
	}
	
	return N;
}


Material GetMaterial(LightPixelInput input)
{
	Material material;
	material.normal = NormalMapping(input.tangent,
		input.binormal, input.normal, input.uv);
		
	material.diffuseColor = diffuseMap.Sample(samp, input.uv);
	material.specularIntensity = specularMap.Sample(samp, input.uv);
	material.viewPos = input.viewPos;
	material.worldPos = input.worldPos;
	
	return material;
}

float4 CalcAmbient(Material material)
{
	float up = material.normal.y * 0.5f + 0.5f;
	
	float4 resultAmbient = float4(ambientLight + up * ambientCeil, 1.0f);
	
	return resultAmbient * material.diffuseColor * mAmbient;
}

float4 CalcEmissive(Material material)
{
	float emissiveIntensity = 0.0f;
	
	[flatten]
	if(mEmissive.a > 0.0f)
	{
		float3 viewDir = normalize(material.viewPos - material.worldPos);

		float t = saturate(dot(material.normal, viewDir));
		emissiveIntensity = smoothstep(1.0f - mEmissive.a, 1.0f, 1.0f - t);
	}
	
	return mEmissive * emissiveIntensity;
}

float4 CalcDirectional(Material material, Light light)
{	
	float3 toLight = normalize(light.direction);
	
	float diffuseIntensity = saturate(dot(material.normal, -toLight));
	float4 finalColor = light.color * diffuseIntensity * mDiffuse;
	
	[flatten]
	if (diffuseIntensity > 0)
	{
		float3 viewDir = normalize(material.worldPos - material.viewPos);
		float3 halfWay = normalize(viewDir + toLight);
		float specular = saturate(dot(material.normal, -halfWay));
		
		finalColor += light.color * pow(specular, shininess)
			* material.specularIntensity * mSpecular;
	}
	
	return finalColor * material.diffuseColor;
}

float4 CalcPoint(Material material, Light light)
{
	float3 toLight = material.worldPos - light.position;
	float distanceToLight = length(toLight);
	toLight /= distanceToLight;
	
	float diffuseIntensity = saturate(dot(material.normal, -toLight));
	float4 finalColor = light.color * diffuseIntensity * mDiffuse;
	
	[flatten]
	if (diffuseIntensity > 0)
	{
		float3 viewDir = normalize(material.worldPos - material.viewPos);
		float3 halfWay = normalize(viewDir + toLight);
		float specular = saturate(dot(material.normal, -halfWay));
		
		finalColor += light.color * pow(specular, shininess)
			* material.specularIntensity * mSpecular;
	}
	
	float distanceToLightNormal = 1.0f - saturate(distanceToLight / light.range);
	float attention = pow(distanceToLightNormal, 2);
	
	return finalColor * material.diffuseColor * attention;
}

float4 CalcSpot(Material material, Light light)
{
	float3 toLight = material.worldPos - light.position;
	float distanceToLight = length(toLight);
	toLight /= distanceToLight;
	
	float diffuseIntensity = saturate(dot(material.normal, -toLight));
	float4 finalColor = light.color * diffuseIntensity * mDiffuse;
	
	[flatten]
	if (diffuseIntensity > 0)
	{
		float3 viewDir = normalize(material.worldPos - material.viewPos);
		float3 halfWay = normalize(viewDir + toLight);
		float specular = saturate(dot(material.normal, -halfWay));
		
		finalColor += light.color * pow(specular, shininess)
			* material.specularIntensity * mSpecular;
	}
	
	float3 dir = normalize(light.direction);
	float cosAngle = dot(dir, toLight);
	
	float outer = cos(radians(light.outer));
	float inner = 1.0f / cos(radians(light.inner));
	
	float conAttention = saturate((cosAngle - outer) * inner);
	conAttention = pow(conAttention, 2);
	
	float distanceToLightNormal = 1.0f - saturate(distanceToLight / light.range);
	float attention = pow(distanceToLightNormal, 2);
	
	return finalColor * material.diffuseColor * attention * conAttention;
}

float4 CalcCapsule(Material material, Light light)
{
	float3 direction = normalize(light.direction);
	float3 start = material.worldPos - light.position;
	float distanceOnLine = dot(start, direction) / light.length;
	distanceOnLine = saturate(distanceOnLine) * light.length;
	
	float3 pointOnLine = light.position + direction * distanceOnLine;	
	
	float3 toLight = material.worldPos - pointOnLine;
	float distanceToLight = length(toLight);
	toLight /= distanceToLight;
	
	float diffuseIntensity = saturate(dot(material.normal, -toLight));
	float4 finalColor = light.color * diffuseIntensity * mDiffuse;
	
	[flatten]
	if (diffuseIntensity > 0)
	{
		float3 viewDir = normalize(material.worldPos - material.viewPos);
		float3 halfWay = normalize(viewDir + toLight);
		float specular = saturate(dot(material.normal, -halfWay));
		
		finalColor += light.color * pow(specular, shininess)
			* material.specularIntensity * mSpecular;
	}
	
	float distanceToLightNormal = 1.0f - saturate(distanceToLight / light.range);
	float attention = pow(distanceToLightNormal, 2);
	
	return finalColor * material.diffuseColor * attention;
}

float4 CalcLights(LightPixelInput input)
{
	Material material = GetMaterial(input);
	
	float4 color = 0;	
	
	[unroll(MAX_LIGHT)]
	for (int i = 0; i < lightCount; i++)
	{
		[flatten]
		if (!lights[i].active)
			continue;

		[flatten]
		if(lights[i].type == 0)
			color += CalcDirectional(material, lights[i]);
		else if (lights[i].type == 1)
			color += CalcPoint(material, lights[i]);
		else if (lights[i].type == 2)
			color += CalcSpot(material, lights[i]);
		else if (lights[i].type == 3)
			color += CalcCapsule(material, lights[i]);
	}
	
	float4 ambient = CalcAmbient(material);
	//float4 emissive = CalcEmissive(material);
	float4 emissive = mEmissive;
	
	return color + ambient + emissive;
}

GBufferOutput PackGBuffer(float3 baseColor, float3 normal, float specularIntensity)
{
	GBufferOutput output;
	
	float specPowNorm = (shininess - shininessRange.x) / shininessRange.y;
	
	output.diffuse = float4(baseColor, 1.0f);
	output.specular = float4(specPowNorm, specularIntensity, 0, 1);
	output.normal = float4(normal * 0.5f + 0.5f, 1);

	return output;
}