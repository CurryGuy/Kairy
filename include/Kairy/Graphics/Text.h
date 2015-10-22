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

#ifndef KAIRY_GRAPHICS_TEXT_H_INCLUDED
#define KAIRY_GRAPHICS_TEXT_H_INCLUDED

#include "Font.h"
#include "Node.h"

NS_KAIRY_BEGIN

class Text : public Node
{
public:
    Text(void);

	Text(const std::string& filename);
	
	Text(float size);
	
	Text(const std::string& filename, float size);

    virtual ~Text();

	bool loadFont(const std::string& filename);

	bool loadFont(const std::string& filename, float size);
	
	bool loadFont(float size);
	
	inline void setColor(const Color& color) override;

    inline Text& setString(const std::string& str);

    inline std::string getString(void) const;

    inline Text& setLineWidth(int width);

    inline int getLineWidth() const;

    inline Font& getFont();
	
	inline int getLineHeight() const;

    inline Text& setUseKerning(bool useKerning);

    inline bool getUseKerning() const;

	inline std::shared_ptr<Sprite> getCharacter(Uint32 index);

    Vec2 measureString(const std::string& str);

	inline Vec2 measureString();

    virtual void draw() override;

    inline void draw(const std::string& str);

protected:
    void incrementX(float& x, float& y, float amount);

	void updateCharacters();

	std::vector<std::shared_ptr<Sprite>> _characters;

    std::string _str;
    Vec2 _position;
    float _scale;
    int _lineWidth;
    bool _useKerning;
    Font _font;
};

#include "Text.inl"

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_TEXT_H_INCLUDED
