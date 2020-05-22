#include "wii_material.h"

void renderer::Material::Bind()
{
	if (mTexture)
		mTexture->Bind();
}