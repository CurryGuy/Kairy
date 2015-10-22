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

#ifndef KAIRY_UI_CHECKBOX_H_INCLUDED
#define KAIRY_UI_CHECKBOX_H_INCLUDED

#include "Control.h"
#include <Kairy/Graphics/Sprite.h>

NS_KAIRY_BEGIN

class CheckBox : public Control
{
public:
	typedef std::function<void(bool)> CheckCallback;

	CheckBox(void);

	CheckBox(
		const std::string& uncheckedImage,
		const std::string& checkedImage,
		const std::string& disabledImage = "");

	bool setImages(
		const std::string& uncheckedImage,
		const std::string& checkedImage,
		const std::string& disabledImage = "");

	virtual void onTouchDown(const Vec2& position, float dt) override;

	virtual void setEnabled(bool enabled) override;

	inline bool isChecked() const { return _checked; }

	virtual void setChecked(bool checked);

	void setCheckCallback(const CheckCallback& callback);

	virtual void setColor(const Color& color) override;

private:
	CheckCallback _checkCallback;
	std::shared_ptr<Sprite> _uncheckedImage;
	std::shared_ptr<Sprite> _checkedImage;
	std::shared_ptr<Sprite> _disabledImage;
	bool _checked;
};

NS_KAIRY_END

#endif // KAIRY_UI_CHECKBOX_H_INCLUDED
