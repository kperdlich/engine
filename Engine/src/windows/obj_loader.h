#pragma once

#include "mesh.h"

namespace core {
	std::vector<std::shared_ptr<renderer::Mesh>> LoadMeshesFromObj(const std::string& file, const std::string& mtlFilePath);
}