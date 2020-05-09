#pragma once

#include "stdint.h"

namespace renderer {
class ColorRGBA
{
public:
    ColorRGBA();
    ColorRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    ~ColorRGBA() = default;
    ColorRGBA(const ColorRGBA&) = default;
    ColorRGBA& operator = (const ColorRGBA&) = default;
    ColorRGBA(ColorRGBA&&) = default;
    ColorRGBA& operator = (ColorRGBA&&) = default;

    inline uint8_t Red() const;
    inline uint8_t Green() const;
    inline uint8_t Blue() const;
    inline uint8_t Alpha() const;
    inline uint32_t Color() const;

	inline uint8_t* Data();
	inline const uint8_t* Data() const;

	inline ColorRGBA operator / (uint8_t value) const;

    static const ColorRGBA RED;
    static const ColorRGBA GREEN;
    static const ColorRGBA BLUE;
    static const ColorRGBA BLACK;
    static const ColorRGBA WHITE;
    static const ColorRGBA YELLOW;
    static const ColorRGBA ORANGE;

private:
    uint8_t mChannels[4];
};

inline uint8_t ColorRGBA::Red() const
{
    return mChannels[0];
}

inline uint8_t ColorRGBA::Green() const
{
    return mChannels[1];
}

inline uint8_t ColorRGBA::Blue() const
{
    return mChannels[2];
}

inline uint8_t ColorRGBA::Alpha() const
{
    return mChannels[3];
}

inline uint8_t* ColorRGBA::Data()
{
	return mChannels;
}

inline const uint8_t* ColorRGBA::Data() const
{
	return mChannels;
}

inline ColorRGBA ColorRGBA::operator / (uint8_t value) const
{
	ColorRGBA color = ColorRGBA(
		mChannels[0] / value, 
		mChannels[1] / value,
		mChannels[2] / value, 
		mChannels[3] / value);
	return color;
}

inline uint32_t ColorRGBA::Color() const
{
    return static_cast<uint32_t>(((mChannels[0] & 0xff) << 24) + ((mChannels[1] & 0xff) << 16) + ((mChannels[2] & 0xff) << 8) + (mChannels[3] & 0xff));
}

}


