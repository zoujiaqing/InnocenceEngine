// ----------------------------------------------------------------------------
float PCFResolver(vec3 projCoords, texture2DArray shadowMap, sampler shadowMapSampler, int index, float currentDepth, vec2 texelSize)
{
	// PCF
	float shadow = 0.0;

	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(sampler2DArray(shadowMap, shadowMapSampler), vec3(projCoords.xy + vec2(x, y) * texelSize, index)).r;
			shadow += currentDepth > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /= 9.0;

	return shadow;
}
// ----------------------------------------------------------------------------
float VSMKernel(vec4 shadowMapValue, float currentDepth)
{
	float shadow = 0.0;
	float Ex = shadowMapValue.r;
	float E_x2 = shadowMapValue.g;
	float variance = E_x2 - (Ex * Ex);
	float mD = Ex - currentDepth;
	float p = variance / (variance + mD * mD);

	shadow = max(p, float(currentDepth >= Ex));

	return shadow;
}
// ----------------------------------------------------------------------------
float VSMResolver(vec3 projCoords, texture2DArray shadowMap, sampler shadowMapSampler, int index, float currentDepth)
{
	// VSM
	vec4 shadowMapValue = texture(sampler2DArray(shadowMap, shadowMapSampler), vec3(projCoords.xy, index));

	float shadow = VSMKernel(shadowMapValue, currentDepth);
	return shadow;
}
// ----------------------------------------------------------------------------
float SunShadowResolver(vec3 fragPos)
{
	vec3 projCoords = vec3(0.0);
	float shadow = 0.0;
	vec2 textureSize = textureSize(uni_sunShadow, 0).xy;
	vec2 texelSize = 1.0 / textureSize;

	int splitIndex = NR_CSM_SPLITS;
	for (int i = 0; i < NR_CSM_SPLITS; i++)
	{
		if (fragPos.x >= CSMCBuffer.data[i].AABBMin.x &&
			fragPos.y >= CSMCBuffer.data[i].AABBMin.y &&
			fragPos.z >= CSMCBuffer.data[i].AABBMin.z &&
			fragPos.x <= CSMCBuffer.data[i].AABBMax.x &&
			fragPos.y <= CSMCBuffer.data[i].AABBMax.y &&
			fragPos.z <= CSMCBuffer.data[i].AABBMax.z)
		{
			splitIndex = i;
			break;
		}
	}

	if (splitIndex == NR_CSM_SPLITS)
	{
		shadow = 0.0;
	}
	else
	{
		vec4 lightSpacePos = CSMCBuffer.data[splitIndex].p * CSMCBuffer.data[splitIndex].v * vec4(fragPos, 1.0f);
		lightSpacePos = lightSpacePos / lightSpacePos.w;
		projCoords = lightSpacePos.xyz;

		// transform to [0,1] range
		projCoords = projCoords * 0.5 + 0.5;

		// get depth of current fragment from light's perspective
		float currentDepth = projCoords.z;

		shadow = PCFResolver(projCoords, uni_sunShadow, samplerLinear, splitIndex, currentDepth, texelSize);
	}

	return shadow;
}
// ----------------------------------------------------------------------------
float linearDepth(float depthSample)
{
	float zLinear = perFrameCBuffer.data.zNear * perFrameCBuffer.data.zFar / (perFrameCBuffer.data.zFar + perFrameCBuffer.data.zNear - depthSample * (perFrameCBuffer.data.zFar - perFrameCBuffer.data.zNear));
	return zLinear;
}