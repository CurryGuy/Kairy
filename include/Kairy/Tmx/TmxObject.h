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

#ifndef KAIRY_TMX_TMX_OBJECT_H_INCLUDED
#define KAIRY_TMX_TMX_OBJECT_H_INCLUDED

#include "TmxPolygon.h"
#include "TmxPolyline.h"
#include "TmxEllipse.h"
#include "TmxProperties.h"
#include "TmxImage.h"

NS_KAIRY_BEGIN

class TmxObject
{
public:

    enum class Shape
    {
        Rectangle,
        Ellipse,
        Polygon,
        Polyline
    };

    TmxObject();

    inline int getId() const { return _id; }

    inline int getX() const { return _x; }

    inline int getY() const { return _y; }

    inline int getWidth() const { return _width; }

    inline int getHeight() const { return _height; }

    inline Uint32 getGid() const { return _gid; }

    inline std::string getName() const { return _name; }

    inline std::string getType() const { return _type; }

    inline bool isVisible() const { return _visible; }

    inline float getRotation() const { return _rotation; }

    inline Shape getShape() const { return _shape; }

    inline const TmxProperties& getProperties() const { return _properties; }

    inline const TmxPolygon& getPolygon() const { return _polygon; }

    inline const TmxPolyline& getPolyline() const { return _polyline; }

    inline const TmxEllipse& getEllipse() const { return _ellipse; }

    inline const TmxImage& getImage() const { return _image; }

private:
    friend class TmxObjectGroup;

    bool parseElement(void*);

    int _id;
    int _x;
    int _y;
    int _width;
    int _height;
    Uint32 _gid;
    std::string _name;
    std::string _type;
    bool _visible;
    float _rotation;
    Shape _shape;
    TmxProperties _properties;
    TmxPolygon _polygon;
    TmxPolyline _polyline;
    TmxEllipse _ellipse;
    TmxImage _image;
};

NS_KAIRY_END

#endif // KAIRY_TMX_TMX_OBJECT_H_INCLUDED
