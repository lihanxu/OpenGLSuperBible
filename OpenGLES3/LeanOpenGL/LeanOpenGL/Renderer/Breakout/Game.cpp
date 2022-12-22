//
//  Game.cpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/12/20.
//

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "SpriteRenderer.hpp"
#include "matrix_transform1.hpp"

#define BOTTOM_SAFE_HEIGHT        (34.0 * 3.0)

// Game-related State data
SpriteRenderer  *Renderer;
// 初始化挡板的大小
const glm::vec2 PLAYER_SIZE(300, 60);
// 初始化挡板的速率
const GLfloat PLAYER_VELOCITY(500.0f);

GameObject      *Player;

Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
    delete Player;
}

void Game::Init()
{
    // Load shaders
    Shader shader = ResourceManager::LoadShader("sprite.vs", "sprite.fs", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    shader.use().SetInteger("image", 0);
    shader.SetMatrix4("projection", projection);
    // 加载纹理
    ResourceManager::LoadTexture("background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture("awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("block.png", GL_TRUE, "block");
    ResourceManager::LoadTexture("block_solid.png", GL_TRUE, "block_solid");
    ResourceManager::LoadTexture("paddle.png", GL_TRUE, "paddle");
    // Set render-specific controls
    Renderer = new SpriteRenderer(shader);
    // 加载关卡
    GameLevel one; one.Load("one.lvl", this->Width, this->Height * 0.15);
    GameLevel two; two.Load("two.lvl", this->Width, this->Height * 0.15);
    GameLevel three; three.Load("three.lvl", this->Width, this->Height * 0.15);
    GameLevel four; four.Load("four.lvl", this->Width, this->Height * 0.15);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;
    
//    // Load textures
//    ResourceManager::LoadTexture("awesomeface.png", GL_TRUE, "face");
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y - BOTTOM_SAFE_HEIGHT);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{
    if (this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            GLfloat pos = Player->Position.x - velocity;
            if (pos >= 0)
                Player->Position.x = pos;
        }
        if (this->Keys[GLFW_KEY_D])
        {
            GLfloat pos = Player->Position.x + velocity;
            if (pos <= this->Width - Player->Size.x)
                Player->Position.x = pos;
        }
    }
}

void Game::Render()
{
//    Texture2D texture = ResourceManager::GetTexture("face");
//    glm::vec2 size = glm::vec2(512, 512);
//    glm::vec2 pos = glm::vec2((this->Width - size.x) / 2.0, (this->Height - size.y) / 2.0);
//    float rotate = 45.0f;
//    Renderer->DrawSprite(texture, pos, size, rotate, glm::vec3(0.0f, 1.0f, 0.0f));
    if (this->State == GAME_ACTIVE) {
        // 绘制背景
        Texture2D texture = ResourceManager::GetTexture("background");
        Renderer->DrawSprite(texture, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
        // 绘制关卡
        this->Levels[this->Level].Draw(*Renderer);
        Player->Draw(*Renderer);
    }
}
