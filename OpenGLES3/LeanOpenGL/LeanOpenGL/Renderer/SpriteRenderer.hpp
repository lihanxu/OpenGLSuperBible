//
//  SpriteRenderer.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/12/20.
//

#ifndef SpriteRenderer_hpp
#define SpriteRenderer_hpp

#include <stdio.h>
#include "glm.hpp"
#include "matrix_transform1.hpp"

#include "Texture2D.hpp"
#include "Shader.hpp"


class SpriteRenderer
{
public:
    // Constructor (inits shaders/shapes)
    SpriteRenderer(Shader &shader);
    // Destructor
    ~SpriteRenderer();
    // Renders a defined quad textured with given sprite
    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
    // Render state
    Shader shader;
    GLuint quadVAO;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};

#endif /* SpriteRenderer_hpp */
