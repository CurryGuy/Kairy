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

#ifndef KAIRY_ACTIONS_ACTION_H_INCLUDED
#define KAIRY_ACTIONS_ACTION_H_INCLUDED

#include <Kairy/Updatable.h>

NS_KAIRY_BEGIN

class Node;

class Action : public Updatable
{
public:
	Action(void);

	virtual ~Action(void);

	virtual void start(Node* target);

	virtual void stop();

	inline bool isDone() const { return _done; }

	virtual void update(float dt);

	virtual void step(float dt);

	inline int getTag() const { return _tag; }

	inline void setTag(int tag) { _tag = tag; }

	inline std::string getName() const { return _name; }

	inline void setName(const std::string& name) { _name = name; }

	inline std::string getDesc() const { return _desc; }

	inline void setDesc(const std::string& desc) { _desc = desc; }

protected:
	bool _done;
	Node* _target;
	int _tag;
	std::string _name;
	std::string _desc;
};

NS_KAIRY_END

#endif // KAIRY_ACTIONS_ACTION_H_INCLUDED
