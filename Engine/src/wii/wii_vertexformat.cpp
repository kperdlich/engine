#include <unordered_map>
#include "vertexformat.h"
#include "core.h"
#include "wii_defines.h"

static std::array<bool, GX_MAXVTXFMT> sVertexFormats = { false };

static const std::unordered_map<renderer::VertexDataInputType, uint8_t> sVertexDataInputTypeGXMapping = {
    { renderer::VertexDataInputType::DIRECT, GX_DIRECT},
    { renderer::VertexDataInputType::INDEX, GX_INDEX16 }
};

static const std::unordered_map<renderer::VertexAttribute, uint8_t> sVertexAttributesGXMapping = {
    { renderer::VertexAttribute::Position, GX_VA_POS },
    { renderer::VertexAttribute::Color, GX_VA_CLR0 },
    { renderer::VertexAttribute::Texture, GX_VA_TEX0 },
    { renderer::VertexAttribute::Normal, GX_VA_NRM },
};

static const std::unordered_map<renderer::VertexAttributeComponentType, std::pair<uint32_t, size_t>> sVertexAttributesComponentTypeGXMapping = {
    { renderer::VertexAttributeComponentType::Position_XY, {GX_POS_XY, 2} },
    { renderer::VertexAttributeComponentType::Position_XYZ, {GX_POS_XYZ, 3} },
    { renderer::VertexAttributeComponentType::Normal_XYZ, {GX_NRM_XYZ, 3} },
    { renderer::VertexAttributeComponentType::Color_RGB, {GX_CLR_RGB, 3} },
    { renderer::VertexAttributeComponentType::Color_RGBA, {GX_CLR_RGBA, 4}},
    { renderer::VertexAttributeComponentType::Texture_ST, {GX_TEX_ST, 2} }
};

static const std::unordered_map<renderer::VertexAttributeComponentTypeSize, std::pair<uint32_t, size_t>> sVertexAttributesComponentTypeSizeGXMapping = {
    { renderer::VertexAttributeComponentTypeSize::Integer8, {GX_S8, sizeof(int8_t) } },
    { renderer::VertexAttributeComponentTypeSize::Integer16, {GX_S16, sizeof(int16_t)} },
    { renderer::VertexAttributeComponentTypeSize::Integer32, {GX_F32, sizeof(int32_t)} },
    { renderer::VertexAttributeComponentTypeSize::Float32, {GX_F32, sizeof(float)}},
    { renderer::VertexAttributeComponentTypeSize::RGB8, {GX_RGB8, sizeof(int8_t)}},
    { renderer::VertexAttributeComponentTypeSize::RGBA8, {GX_RGBA8, sizeof(int8_t) } }
};

renderer::VertexFormat::VertexFormat()
{
    for (size_t i = 0; i < GX_MAXVTXFMT; ++i)
    {
        if (!sVertexFormats[i])
        {
            mFormatIndex = i;
            sVertexFormats[i] = true;
            return;
        }
    }

    ASSERT_TEXT(false, "Max Vertex Formats reached!");
}

void renderer::VertexFormat::AddAttribute(const renderer::VertexFormatAttribute& attribute)
{
    mAttributes.emplace_back(attribute);
    const uint8_t dataInputType = sVertexDataInputTypeGXMapping.at(attribute.DataInputType);
    const uint8_t attributeIndex = sVertexAttributesGXMapping.at(attribute.Attribute);
    const auto& attributeComponentType = sVertexAttributesComponentTypeGXMapping.at(attribute.ComponentType).first;
    const auto& attributeComponentTypeGXSize = sVertexAttributesComponentTypeSizeGXMapping.at(attribute.ComponentSizeType).first;

    GX_SetVtxDesc(attributeIndex, dataInputType);
    GX_SetVtxAttrFmt(mFormatIndex, attributeIndex, attributeComponentType, attributeComponentTypeGXSize, 0);
}

size_t renderer::VertexFormat::GetStrideSize(const VertexAttributeComponentType attribute,
            const VertexAttributeComponentTypeSize componentTypeSize) const
{
    return sVertexAttributesComponentTypeGXMapping.at(attribute).second *
            sVertexAttributesComponentTypeSizeGXMapping.at(componentTypeSize).second;
}


int32_t renderer::VertexFormat::GetVertexAttributeId(const VertexAttribute attribute) const
{
    return sVertexAttributesGXMapping.at(attribute);
}

void renderer::VertexFormat::Bind()
{
    for (const auto& attribute : mAttributes)
    {
        const uint8_t dataInputType = sVertexDataInputTypeGXMapping.at(attribute.DataInputType);
        const uint8_t attributeIndex = sVertexAttributesGXMapping.at(attribute.Attribute);
        const auto& attributeComponentType = sVertexAttributesComponentTypeGXMapping.at(attribute.ComponentType).first;
        const auto& attributeComponentTypeGXSize = sVertexAttributesComponentTypeSizeGXMapping.at(attribute.ComponentSizeType).first;

        GX_SetVtxDesc(attributeIndex, dataInputType);
        GX_SetVtxAttrFmt(mFormatIndex, attributeIndex, attributeComponentType, attributeComponentTypeGXSize, 0);
    }
}

std::shared_ptr<renderer::VertexFormat> renderer::VertexFormat::Create()
{
    return std::shared_ptr<renderer::VertexFormat>(new renderer::VertexFormat());
}

