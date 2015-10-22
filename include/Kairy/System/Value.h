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

#ifndef KAIRY_SYSTEM_VALUE_H_INCLUDED
#define KAIRY_SYSTEM_VALUE_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

class Value
{
public:
	enum class Type
	{
		Null,
		Byte,
		Integer,
		Float,
		Double,
		Boolean,
		String
	};

	Value(void);

	explicit Value(byte v);

	explicit Value(int v);

	explicit Value(float v);

	explicit Value(double v);

	explicit Value(bool v);

	explicit Value(const std::string& v);

	inline Type getType() const { return _type; }

	inline bool isNull() const { return _type == Type::Null; }

	byte asByte() const;

	int asInt() const;

	float asFloat() const;

	double asDouble() const;

	bool asBool() const;

	std::string asString() const;

	void clear();

	Value& operator=(byte v);
	Value& operator=(int v);
	Value& operator=(float v);
	Value& operator=(double v);
	Value& operator=(const std::string& v);

	bool equals(const Value& other) const;

	bool operator==(const Value& other) const;
	bool operator!=(const Value& other) const;

private:
	Type _type{ Type::Null };

	union
	{
		byte byteVal;
		int intVal;
		float floatVal;
		double doubleVal;
		bool boolVal;
	} _primVal;

	std::string _strVal;
};

NS_KAIRY_END

#endif // KAIRY_SYSTEM_VALUE_H_INCLUDED
