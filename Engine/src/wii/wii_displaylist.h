#pragma once

#include "wii_defines.h"

// For display lists, each command has an associated "cost" in bytes.
// Add all these up to calculate the size of your display list before rounding up.
// eke-eke says GX_Begin() costs 3 bytes (u8 + u16)
// According to my research:
// GX_Position3f32() is 12 bytes (f32*3)
// GX_Normal3f32() is 12 bytes (f32*3)
// GX_Color3f32() is actually 3 bytes ((f32 -> u8) * 3)
// GX_TexCoord2f32() is 8 bytes (f32*2)
// GX_End() seems to cost zero (there's no actual code in it)
// Size -must- be multiple of 32, so (12*24) + (12*24) + (3*24) + (8*24) + 3 = 843
// Rounded up to the nearest 32 is 864.
// NOTE: Actual size may be up to 63 bytes -larger- than you calculate it to be due to padding and cache alignment.

namespace renderer {
class DisplayList
{
public:
    DisplayList();
    explicit DisplayList(const size_t sizeOfDisplayList);
    ~DisplayList();
    DisplayList(const DisplayList&) = delete;
    DisplayList(DisplayList&&) = delete;
    void operator=(const DisplayList&) = delete;
    void operator=(DisplayList&&) = delete;
    void Render();
    void Begin(const size_t bufferSize);
    void End();
    void Clear();
    inline uint32_t GetBufferSize() const;
    inline bool IsDirty() const;

private:
    void* mDispList;
    uint32_t mBufferSize;
};

inline uint32_t DisplayList::GetBufferSize() const
{
    return mBufferSize;
}

inline bool DisplayList::IsDirty() const
{
    return mBufferSize == 0 || !mDispList;
}

}



