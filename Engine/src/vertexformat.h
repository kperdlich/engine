#pragma once

#include "vector"
#include <memory>
#include "stdint.h"
#include <stddef.h>

namespace renderer {

    enum class VertexDataInputType: int8_t
    {
        Direct,
        Index
    };

	enum class VertexAttribute : int8_t
    {
        Position,
		Color,
		Normal,
        Texture,		
    };

	enum class VertexAttributeComponentType : int8_t
	{
		Position_XY,
		Position_XYZ,	
		Normal_XYZ,
		Color_RGB,
		Color_RGBA,
		Texture_ST
	};

	enum class VertexAttributeComponentTypeSize : int8_t
	{		
		Integer8,
		Integer16,
		Integer32,
		Float32,
        RGB8,
		RGBA8
	};

	struct VertexFormatAttribute
	{
        VertexDataInputType DataInputType;
		VertexAttribute Attribute;
		VertexAttributeComponentType ComponentType;
		VertexAttributeComponentTypeSize ComponentSizeType;
	};

	class VertexFormat {
		friend class VertexArray;
		friend class Renderer;
	public:
        VertexFormat();
		~VertexFormat() = default;
		VertexFormat(const VertexFormat&) = delete;
		VertexFormat(VertexFormat&&) = delete;
		VertexFormat& operator=(const VertexFormat&) = delete;
		VertexFormat& operator=(VertexFormat&&) = delete;

		static std::shared_ptr<VertexFormat> Create();

		void AddAttribute(const VertexFormatAttribute& attribute);
        int32_t GetVertexAttributeId(const VertexAttribute attribute) const;
        size_t GetStrideSize(const VertexAttributeComponentType componentType,
                                                            const VertexAttributeComponentTypeSize componentTypeSize) const;

        void Bind();

		inline size_t VertexAttributeCount() const;
		inline uint8_t GetFormatIndex() const;
        inline const std::vector<VertexFormatAttribute>& GetVertexFormatAttributes() const;

	private:
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

    inline const std::vector<VertexFormatAttribute>& VertexFormat::GetVertexFormatAttributes() const
    {
        return mAttributes;
    }
}
