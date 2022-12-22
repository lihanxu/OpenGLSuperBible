//
//  Model.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/12/18.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include "Shader.hpp"
#include "Mesh.hpp"
#include <vector>
#include <string>

#include "scene.h"

using namespace std;

class Model {
    
public:
    Model() {};

    Model(char *path) {
        loadModel(path);
    }
    void Draw(Shader shader);
    
private:
    // 模型数据
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;

    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    unsigned int TextureFromFile(const char *path, const string &directory);
};

#endif /* Model_hpp */
