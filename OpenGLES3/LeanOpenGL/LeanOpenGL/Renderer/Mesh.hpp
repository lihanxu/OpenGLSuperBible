//
//  Mesh.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/12/18.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include "glm/glm.hpp"
#include <string>
#include <vector>
#include "Shader.hpp"
#include "assimp/scene.h"

/// 顶点
struct Vertex {
    // 顶点位置
    glm::vec3 Position;
    // 顶点法线
    glm::vec3 Normal;
    // 顶点纹理坐标
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    aiString path;  // 我们储存纹理的路径用于与其它纹理进行比较
};

class Mesh {
public:
    // 网格数据
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    // 构造方法
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    
    void Draw(Shader shader);
    
private:
    // 渲染数据
    unsigned int VAO, VBO, EBO;
    // 配置网格数据
    void setupMesh();
    
};

#endif /* Mesh_
*/
