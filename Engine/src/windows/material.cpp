#include "material.h"

void renderer::Material::Bind(renderer::Shader& shader)
{
	if (mAmbientMap) 
	{
		mAmbientMap->Bind(0);
		shader.SetUniformSampler2D("ambientTexture", 0);
	}
	
	if (mDiffuseMap)
	{
		mDiffuseMap->Bind(1);
		shader.SetUniformSampler2D("diffuseTexture", 1);
	}

	if (mSpecularMap)
	{
		mSpecularMap->Bind(2);
		shader.SetUniformSampler2D("specularTexture", 2);
	}
	
	if (mNormalMap)
	{
		mNormalMap->Bind(3);
		shader.SetUniformSampler2D("normalTexture", 3);
	}
}