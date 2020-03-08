#pragma once
#include "platform.h"
#include "vector3f.h"
#include "glm/mat4x4.hpp"

namespace renderer {
	struct ShaderSourceInfo
	{
		uint32_t Type;
		std::string Source;
	};

	class Shader
	{
	public:
		~Shader();
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) = delete;
		static std::shared_ptr<Shader> CreateDefaultColor();
		static std::shared_ptr<Shader> Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

		void Bind();
		void Unbind();

		void SetUniformInt32(const std::string& uniformName, int32_t value);
		void SetUniformFloat(const std::string& uniformName, float value);
		void SetUniformColorRGB(const std::string& uniformName, const renderer::ColorRGBA& value);
		void SetUniformColorRGBA(const std::string& uniformName, const renderer::ColorRGBA& value);
		void SetUniformFloat3(const std::string& uniformName, const math::Vector3f& value);
		void SetUniformFloat4(const std::string& uniformName, const math::Vector4f& value);
		void SetUniformMatrix4x4(const std::string& uniformName, const math::Matrix4x4& value);
		void SetUniformGLM(const std::string& uniformName, const glm::mat4x4& value);

	private:
		Shader(uint32_t programId);
		uint32_t mProgramId;
	};
}

