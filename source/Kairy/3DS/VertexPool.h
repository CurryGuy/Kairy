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

#ifndef KAIRY_GRAPHICS_VERTEX_POOL_H_INCLUDED
#define KAIRY_GRAPHICS_VERTEX_POOL_H_INCLUDED

#include "../Graphics/Vertex.h"

NS_KAIRY_BEGIN

class VertexPool
{
public:

    enum
    {
        START_SIZE = 0x10000
    };

    static VertexPool* getInstance();

    void* pushVertices(Uint32 size, Uint32 count);

	template<typename T>
	T* pushVertices(Uint32 count) {
		return static_cast<T*>(pushVertices(sizeof(T), count));
	}

    void clear();

    virtual ~VertexPool();

private:

    VertexPool();
    VertexPool(const VertexPool&) = default;

    Uint32 _size;
    Uint32 _index;
    void* _vertices;
};

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_VERTEX_POOL_H_INCLUDED
