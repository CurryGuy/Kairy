#include <Kairy/Math/Rect.h>

NS_KAIRY_BEGIN

//=============================================================================

const Rect Rect::Zero(0, 0, 0, 0);

//=============================================================================

bool Rect::intersects(const Rect& other, Rect& intersection) const
{
    float left = std::max(getLeft(), other.getLeft());
    float top = std::max(getTop(), other.getTop());
    float right = std::min(getRight(), other.getRight());
    float bottom = std::min(getBottom(), other.getBottom());

    if(left < right && top < bottom)
    {
        intersection.x = left;
        intersection.y = top;
        intersection.width = right - left;
        intersection.height = bottom - top;

        return true;
    }

    intersection = Rect();
    return false;
}

//=============================================================================

std::string Rect::toString() const
{
    char buffer[512];
    snprintf(buffer, 512, "(%f, %f, %f, %f)", x, y, width, height);
    return std::string(buffer);
}

//=============================================================================

NS_KAIRY_END
