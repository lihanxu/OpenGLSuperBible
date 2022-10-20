//
//  Shader.cpp
//  Triangle
//
//  Created by hansen on 2022/10/20.
//

#include "Shader.hpp"
#include "esUtil.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Shader::Shader(const char *vertextPath, const char *fragmentPath) {
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    //确保ifstream对象可以抛出异常:
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        // 打开文件
        vShaderFile.open(vertextPath);
        fShaderFile.open(fragmentPath);
        // 将文件的缓冲区内容读入流
        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件
        vShaderFile.close();
        fShaderFile.close();
        // 将stream转换为string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (ifstream::failure &e) {
        cout<< "<Shader.cpp>ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " <<e.what()<<endl;
    }
    
    const char *vertShaderSrc = vertexCode.c_str();
    const char *fragShaderSrc = fragmentCode.c_str();
    ID = esLoadProgram(vertShaderSrc, fragShaderSrc);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    setInt(name, (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat3(const std::string &name, float value1, float value2, float value3) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}

void Shader::setFloat4(const std::string &name, float value1, float value2, float value3, float value4) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}
