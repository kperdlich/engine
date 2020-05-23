#pragma once

#include <vector>
#include "mesh.h"
#include "platform.h"

namespace primitive {	
	std::unique_ptr<renderer::Mesh> CreatePlaneMesh();
}