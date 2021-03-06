#include "tp1_shader_program.h"

//
/// Fragment Shader
//

void Tp1FragmentShader::bindOutputs(UINT programHandle)
{

}

//
/// Vertex Shader
//

void Tp1VertexShader::bindAttributes(UINT programHandle)
{

}

//
/// Shader Program
//

Tp1ShaderProgram::Tp1ShaderProgram() : ShaderProgram()
{
    mFragmentShader = new Tp1FragmentShader();
    mVertexShader = new Tp1VertexShader();
    
    mFragmentShader->load();
    mVertexShader->load();

    attachFragmentShader(mFragmentShader);
    attachVertexShader(mVertexShader);
}

Tp1ShaderProgram::~Tp1ShaderProgram()
{
    delete mFragmentShader;
    delete mVertexShader;
}

void Tp1ShaderProgram::bindUniforms()
{
  
}