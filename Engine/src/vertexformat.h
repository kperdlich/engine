#pragma once

#include "vector"
#include <memory>
#include "stdint.h"
#include <stddef.h>

namespace renderer {

	enum class VertexAttribute : char
	{
		Position,
		Texture,
		Color,
		Normal
	};

	enum class VertexAttributeComponentType : char 
	{
		Position_XY,
		Position_XYZ,	
		Normal_XYZ,
		Color_RGB,
		Color_RGBA,
		Texture_ST
	};

	enum class VertexAttributeComponentTypeSize : char
	{		
		Integer8,
		Integer16,
		Integer32,
		Float32,
		RGA8,
		RGBA8
	};

	struct VertexFormatAttribute
	{
		VertexAttribute Attribute;
		VertexAttributeComponentType ComponentType;
		VertexAttributeComponentTypeSize ComponentSizeType;
	};

	class VertexFormat {
		friend class VertexArray;
		friend class Renderer;
	public:
		~VertexFormat() = default;
		VertexFormat(const VertexFormat&) = delete;
		VertexFormat(VertexFormat&&) = delete;
		VertexFormat& operator=(const VertexFormat&) = delete;
		VertexFormat& operator=(VertexFormat&&) = delete;

		static std::shared_ptr<VertexFormat> Create();

		void AddAttribute(const VertexFormatAttribute& attribute);

		inline size_t VertexAttributeCount() const;
		inline uint8_t GetFormatIndex() const;

	private:
		VertexFormat() = default;
		std::vector<VertexFormatAttribute> mAttributes;
		uint8_t mFormatIndex;
	};

	inline size_t VertexFormat::VertexAttributeCount() const
	{
		return mAttributes.size();
	}

	inline uint8_t VertexFormat::GetFormatIndex() const
	{
		return mFormatIndex;
	}	
}
