//
//  Game.cpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/12/20.
//

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "SpriteRenderer.hpp"
#include "glm/gtc/matrix_transform1.hpp"

// Game-related State data
SpriteRenderer  *Renderer;


Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    // Load shaders
    Shader shader = ResourceManager::LoadShader("sprite.vs", "sprite.fs", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    shader.use().SetInteger("image", 0);
    shader.SetMatrix4("projection", projection);
    // Load textures
    ResourceManager::LoadTexture("awesomeface.png", GL_TRUE, "face");
    // Set render-specific controls
    Renderer = new SpriteRenderer(shader);
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{
    Texture2D texture = ResourceManager::GetTexture("face");
    glm::vec2 size = glm::vec2(512, 512);
    glm::vec2 pos = glm::vec2((this->Width - size.x) / 2.0, (this->Height - size.y) / 2.0);
    float rotate = 45.0f;
    Renderer->DrawSprite(texture, pos, size, rotate, glm::vec3(0.0f, 1.0f, 0.0f));
}
