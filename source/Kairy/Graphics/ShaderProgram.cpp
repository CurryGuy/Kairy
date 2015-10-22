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

#include <Kairy/Graphics/ShaderProgram.h>
#include <Kairy/Graphics/RenderDevice.h>

NS_KAIRY_BEGIN

//=============================================================================

ShaderProgram* ShaderProgram::s_currentProgram = nullptr;

//=============================================================================

ShaderProgram::ShaderProgram(void)
    :_initialized(false)
#ifndef _3DS
	, _program(0)
#endif // _3DS
{
}

//=============================================================================

ShaderProgram::ShaderProgram(const byte* vsh_data,
        Uint32 vsh_data_size)
    : ShaderProgram()
{
    load(vsh_data, vsh_data_size);
}

//=============================================================================

ShaderProgram::~ShaderProgram()
{
    unload();

    if(_initialized)
    {
#ifdef _3DS
        shaderProgramFree(&_shaderProgram);
#endif // _3DS
    }

    if(s_currentProgram == this)
    {
        s_currentProgram = nullptr;
    }
}

//=============================================================================

bool ShaderProgram::load(const byte* vsh_data,
        Uint32 vsh_data_size)
{
    unload();

    if(vsh_data == nullptr || vsh_data_size == 0 ||
		!RenderDevice::getInstance()->isInitialized())
    {
        return false;
    }

#ifdef _3DS
    _vertexShader = DVLB_ParseFile((u32*)vsh_data, vsh_data_size);

    if(_vertexShader == nullptr)
    {
        return false;
    }

    if(!_initialized)
    {
        shaderProgramInit(&_shaderProgram);
        _initialized = true;
    }

    shaderProgramSetVsh(&_shaderProgram, &_vertexShader->DVLE[0]);
#else

	constexpr const char* fShaderData =
		"#version 330 core\n"
		"in vec4 color;\n"
		"in vec2 texCoords;\n"
		"out vec4 outColor;\n"
		"uniform sampler2D uTexture;\n"
		"uniform bool textureEnabled = true;\n"
		"void main() {\n"
		"if(textureEnabled) {"
		"outColor = texture(uTexture, texCoords) * color;\n"
		"} else {\n"
		"outColor = color;\n"
		"}\n"
		"}\n";

	const GLint fShaderDataLen = strlen(fShaderData);

	const char* vShaderData = (const char*)vsh_data;
	const GLint vShaderDataLen = vsh_data_size;

	GLuint vshaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fshaderId = glCreateShader(GL_FRAGMENT_SHADER);

	if (vshaderId == 0)
	{
		return false;
	}

	if (fshaderId == 0)
	{
		return false;
	}

	_program = glCreateProgram();

	if (_program == 0)
	{
		return false;
	}

	glShaderSource(fshaderId, 1, &fShaderData, &fShaderDataLen);
	glShaderSource(vshaderId, 1, &vShaderData, &vShaderDataLen);

	glCompileShader(fshaderId);
	glCompileShader(vshaderId);

	GLint result = 0;

	glGetShaderiv(vshaderId, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		return false;
	}

	glGetShaderiv(fshaderId, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		return false;
	}

	glAttachShader(_program, vshaderId);
	glAttachShader(_program, fshaderId);
	glLinkProgram(_program);

	glGetProgramiv(_program, GL_LINK_STATUS, &result);

	if (result == GL_FALSE)
	{
		return false;
	}

	glValidateProgram(_program);

	glDeleteShader(vshaderId);
	glDeleteShader(fshaderId);

	_initialized = true;

#endif // _3DS

    return true;
}

//=============================================================================

void ShaderProgram::unload()
{
	_locationsMap.clear();
	
#ifdef _3DS
    if(_vertexShader)
    {
        DVLB_Free(_vertexShader);
        _vertexShader = nullptr;
    }

    if(_initialized)
    {
        shaderProgramSetVsh(&_shaderProgram, nullptr);
    }
#else

	if (_program != 0)
	{
		glDeleteProgram(_program);
		_program = 0;
	}

#endif // _3DS
}

//=============================================================================

void ShaderProgram::use()
{
    if(_initialized && s_currentProgram != this)
    {
#ifdef _3DS
        shaderProgramUse(&_shaderProgram);
#else
		glUseProgram(_program);
#endif // _3DS
        s_currentProgram = this;
    }
}

//=============================================================================

int ShaderProgram::getUniformLocation(const std::string& name) const
{
    if(!_initialized)
    {
        return -1;
    }
	
	auto it = _locationsMap.find(name);
	
	if(it != _locationsMap.end())
	{
		return it->second;
	}

    int result;
	
#ifdef _3DS
	result = shaderInstanceGetUniformLocation(_shaderProgram.vertexShader, name.c_str());
#else
	result = glGetUniformLocation(_program, name.c_str());
#endif // _3DS

	if(result >= 0)
	{
		_locationsMap[name] = result;
	}
	
	return result;
}

//=============================================================================

void ShaderProgram::setUniform(const std::string& name, float value)
{
    if(s_currentProgram && s_currentProgram->_initialized)
    {
#ifdef _3DS
        GPU_SetFloatUniform(GPU_VERTEX_SHADER,
                            s_currentProgram->getUniformLocation(name),
                            (u32*)&value, 1);
#else
		glUniform1f(s_currentProgram->getUniformLocation(name), value);
#endif // _3DS
    }
}

//=============================================================================

void ShaderProgram::setUniform(const std::string& name, float x, float y, float z)
{
    if(s_currentProgram && s_currentProgram->_initialized)
    {
#ifdef _3DS
        float values[] = { x, y, z };
        GPU_SetFloatUniform(GPU_VERTEX_SHADER,
                            s_currentProgram->getUniformLocation(name),
                            (u32*)values, 3);
#else
		glUniform3f(s_currentProgram->getUniformLocation(name), x, y, z);
#endif // _3DS
    }
}

//=============================================================================

void ShaderProgram::setUniform(const std::string& name, float x, float y, float z, float w)
{
    if(s_currentProgram && s_currentProgram->_initialized)
    {
#ifdef _3DS
        float values[] = { x, y, z, w };
        GPU_SetFloatUniform(GPU_VERTEX_SHADER,
                            s_currentProgram->getUniformLocation(name),
                            (u32*)values, 4);
#else
		glUniform4f(s_currentProgram->getUniformLocation(name), x, y, z, w);
#endif // _3DS
    }
}

//=============================================================================

void ShaderProgram::setUniform(const std::string& name, const Vec4& v4)
{
    if(s_currentProgram && s_currentProgram->_initialized)
    {
#ifdef _3DS
        GPU_SetFloatUniform(GPU_VERTEX_SHADER,
                            s_currentProgram->getUniformLocation(name),
                            (u32*)&v4, 4);
#else
		glUniform4f(s_currentProgram->getUniformLocation(name),
			v4.x, v4.y, v4.z, v4.w);
#endif // _3DS
    }
}

//=============================================================================

void ShaderProgram::setUniform(const std::string& name, const Vec3& v3)
{
    if(s_currentProgram && s_currentProgram->_initialized)
    {
#ifdef _3DS
        GPU_SetFloatUniform(GPU_VERTEX_SHADER,
                            s_currentProgram->getUniformLocation(name),
                            (u32*)&v3, 3);
#else
		glUniform3f(s_currentProgram->getUniformLocation(name),
			v3.x, v3.y, v3.z);
#endif // _3DS
    }
}

//=============================================================================

void ShaderProgram::setUniform(const std::string& name, const Transform& t)
{
    if(s_currentProgram && s_currentProgram->_initialized)
    {
        float mu[16];

        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                mu[i*4 + j] = t.getValue(3 - j, i);
            }
        }

#ifdef _3DS
        GPU_SetFloatUniform(GPU_VERTEX_SHADER,
                            s_currentProgram->getUniformLocation(name),
                            (u32*)mu, 4);
#else
		glUniformMatrix4fv(s_currentProgram->getUniformLocation(name),
			1, GL_TRUE, (float*)&t);
#endif // _3DS
    }
}

//=============================================================================

NS_KAIRY_END
