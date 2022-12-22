//
//  Game.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/12/20.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

#include "GameLevel.hpp"

#define GLFW_KEY_A      (100)
#define GLFW_KEY_D      (103)

// 代表了游戏的当前状态
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    // 游戏状态
    GameState  State;
    GLboolean  Keys[1024];
    GLuint     Width, Height;
    std::vector<GameLevel> Levels;
    GLuint                 Level;
    // 构造函数/析构函数
    Game(GLuint width, GLuint height);
    ~Game();
    // 初始化游戏状态（加载所有的着色器/纹理/关卡）
    void Init();
    // 游戏循环
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
};

#endif /* Game_hpp */
