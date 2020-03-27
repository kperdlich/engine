#pragma once

#include <stdint.h>
#include <memory>

namespace renderer {

class Image2D;
class Renderer;
struct Texture2DData;

class Texture2D
{
    friend class Renderer;

public:
    explicit Texture2D(const Image2D& image);
    ~Texture2D();
    Texture2D(const Texture2D&) = default;
    Texture2D(Texture2D&&) = default;
    Texture2D& operator=(const Texture2D&) = default;
    Texture2D& operator=(Texture2D&&) = default;

    void Bind(uint8_t unit = 0);

private:
    std::unique_ptr<Texture2DData> mTextureData;
};

}
