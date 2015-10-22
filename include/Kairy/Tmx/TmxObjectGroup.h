/******************************************************************************
 *
 * Copyright (C) 2015 Nanni
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *****************************************************************************/

#ifndef KAIRY_TMX_TMX_OBJECT_GROUP_H_INCLUDED
#define KAIRY_TMX_TMX_OBJECT_GROUP_H_INCLUDED

#include <Kairy/Graphics/Color.h>
#include "TmxObject.h"

NS_KAIRY_BEGIN

class TmxObjectGroup
{
public:
    TmxObjectGroup(void);

    inline std::string getName() const { return _name; }

    inline Color getColor() const { return _color; }

    inline int getIndex() const { return _index; }

    inline int getX() const { return _x; }

    inline int getY() const { return _y; }

    inline int getWidth() const { return _width; }

    inline int getHeight() const { return _height; }

    inline float getOpacity() const { return _opacity; }

    inline bool isVisible() const { return _visible; }

    inline const TmxProperties& getProperties() const { return _properties; }

    inline const std::vector<TmxObject>& getObjects() const { return _objects; }

	inline int getObjectsCount() const { return (int)_objects.size(); }

private:
    friend class TmxMap;
    friend class TmxTilesetTile;

    bool parseElement(void*);

    std::string _name;
    Color _color;
    int _index;
    int _x;
    int _y;
    int _width;
    int _height;
    float _opacity;
    bool _visible;
    TmxProperties _properties;
    std::vector<TmxObject> _objects;
};

NS_KAIRY_END

#endif // KAIRY_TMX_TMX_OBJECT_GROUP_H_INCLUDED
