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

#ifndef KAIRY_GRAPHICS_SHADER_PROGRAM_H_INCLUDED
#define KAIRY_GRAPHICS_SHADER_PROGRAM_H_INCLUDED

#include <Kairy/Math/Vec4.h>

NS_KAIRY_BEGIN

class RenderDevice;
class Transform;

/** @class ShaderProgram
    @brief Manages PICA200 shader programs.
*/
class ShaderProgram
{
public:
    /**
     * @brief Return a pointer to the shader program in use.
     * @return The shader program in use or null if there's none.
     */
    inline static ShaderProgram* getCurrentProgram() { return s_currentProgram; }

    /**
     * @brief Default constructor.
     * Construct a shader program without a vertex shader attached.
     */
    ShaderProgram(void);

    /**
     * @brief Construct a shader program and load
     * the vertex shader using the given data.
     * @param device The render device to use for loading the shaders.
     * @param vsh_data The vertex shader binary data.
     * @param vsh_data_size The vertex shader data size in bytes.
     */
    ShaderProgram(const byte* vsh_data, Uint32 vsh_data_size);

    /**
     * @brief Destructor
     */
    virtual ~ShaderProgram();

    /**
     * @brief Loads the vertex shader.
     * @param vsh_data The vertex shader binary data.
     * @param vsh_data_size The data size in bytes.
     * @return True if the vertex shader is loaded without errors.
     */
    bool load(const byte* vsh_data, Uint32 vsh_data_size);

    /**
     * @brief Unload all the shaders attached to the program.
     */
    void unload();

    /**
     * @brief Get the location of a uniform in the vertex shader.
     * @param name The uniform name.
     * @return The uniform location.
     */
    int getUniformLocation(const std::string& name) const;

    void use();

    // Functions for setting uniforms values to the program in use
    static void setUniform(const std::string& name, float value);
    static void setUniform(const std::string& name, float x, float y, float z);
    static void setUniform(const std::string& name, float x, float y, float z, float w);
	static void setUniform(const std::string& name, const Vec4& v4);
    static void setUniform(const std::string& name, const Vec3& v3);
    static void setUniform(const std::string& name, const Transform& t);

private:
    static ShaderProgram* s_currentProgram;
	
	mutable std::map<std::string, int> _locationsMap;

#ifdef _3DS
    DVLB_s*         _vertexShader;
    shaderProgram_s _shaderProgram;
#else
	GLuint _program;
#endif // _3DS
    bool            _initialized;
};

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_SHADER_PROGRAM_H_INCLUDED
