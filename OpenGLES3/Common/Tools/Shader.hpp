//
//  Shader.hpp
//  Triangle
//
//  Created by hansen on 2022/10/20.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>

class Shader {
    
public:
    /// 构造器读取并构造着色器
    Shader(const char *vertextPath, const char *fragmentPath);
    
    /// program id
    unsigned int ID;
    
    /// 激活程序
    void use();
    /// uniform 工具
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    
};

#endif /* Shader_hpp */
