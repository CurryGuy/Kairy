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

#ifndef KAIRY_SYSTEM_RESOURCE_MANAGER_H_INCLUDED
#define KAIRY_SYSTEM_RESOURCE_MANAGER_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

template<typename T>
class ResourceManager
{
public:

	ResourceManager(void)
	{
		_deleteFunc = nullptr;
	}

	ResourceManager(const std::function<void(T&)>& deleteFunc)
	{
		_deleteFunc = deleteFunc;
	}

	virtual ~ResourceManager(void)
	{
		if (_deleteFunc)
		{
			for (auto& resource : _resources)
			{
				if (resource.second.preloaded)
					_deleteFunc(resource.second.userData);
			}
		}
	}

	void setDeleteFunction(const std::function<void(T&)>& deleteFunc)
	{
		_deleteFunc = deleteFunc;
	}

	bool addResource(const std::string& key, const T& userData)
	{
		if (_resources.find(key) != _resources.end())
			return false;

		Resource resource;
		resource.preloaded = false;
		resource.refCount = 1;
		resource.userData = userData;

		_resources[key] = resource;

		return true;
	}

	bool removeResource(const std::string& key)
	{
		auto it = _resources.find(key);

		if (it == _resources.end())
			return false;

		Resource& resource = it->second;

		resource.refCount--;

		if (resource.refCount <= 0)
		{
			if (_deleteFunc)
				_deleteFunc(resource.userData);
			_resources.erase(it);
		}

		return true;
	}

	bool preloadResource(const std::string& key, const T& userData)
	{
		if (_resources.find(key) != _resources.end())
			return true;

		Resource resource;
		resource.preloaded = true;
		resource.refCount = 1;
		resource.userData = userData;

		_resources[key] = resource;

		return true;
	}

	bool unloadPreloaded(const std::string& key)
	{
		auto it = _resources.find(key);

		if (it != _resources.end())
			return false;

		Resource& resource = it->second;

		if (resource.preloaded)
		{
			if(_deleteFunc)
				_deleteFunc(resource.userData);
			_resources.erase(it);
		}

		return true;
	}

	bool hasResource(const std::string& key) const
	{
		return _resources.find(key) != _resources.end();
	}

	bool getResourceData(const std::string& key, T& outData)
	{
		auto it = _resources.find(key);

		if (it == _resources.end())
			return false;

		outData = it->second.userData;

		return true;
	}

	bool loadResource(const std::string& key, T& outData)
	{
		auto it = _resources.find(key);

		if (it == _resources.end())
			return false;

		Resource& resource = it->second;

		if (resource.preloaded)
		{
			resource.refCount = 1;
			resource.preloaded = false;
		}
		else
		{
			resource.refCount++;
		}

		outData = resource.userData;

		return true;
	}

private:
	struct Resource
	{
		T userData;
		int refCount;
		bool preloaded;
	};

	std::function<void(T&)> _deleteFunc;
	std::map<std::string, Resource> _resources;
};

NS_KAIRY_END

#endif // KAIRY_SYSTEM_RESOURCE_MANAGER_H_INCLUDED
