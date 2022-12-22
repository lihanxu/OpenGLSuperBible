//
//  Breakout.cpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/12/20.
//

#include "Breakout.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"
#include "TimeTool.hpp"

extern "C" {
#include "FileWrapper.h"
}


// The Width of the screen
const GLuint SCREEN_WIDTH = 1170;
// The height of the screen
const GLuint SCREEN_HEIGHT = 2532;


class Breakout::Impl {
public:
    GLint _width;
    GLint _height;
    
    // DeltaTime variables
    double _deltaTime;
    double _lastFrame;
    
private:
    Game _game;

public:
    Impl()
    : _game(Game(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        _deltaTime = 0.0;
        _lastFrame = 0.0;
    }
    
    ~Impl() {}
    
    int setupGL() {
        // 踩坑，剔除面需要知道是 GL_FRONT 还是 GL_BACK，或者制定顺时针或逆时针
        // 否则很有可能把想要显示的面给剔除掉
//        glEnable(GL_CULL_FACE);
//        glCullFace(GL_FRONT);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        // Initialize game
        _game.Init();
        // Start Game within Menu State
        _game.State = GAME_ACTIVE;
        
        return GL_TRUE;
    }
    
    void tearDownGL() {
//        glDeleteProgram(_shader.ID);
        ResourceManager::Clear();
    }
    
    void updateWindowSize(GLint width, GLint height) {
        if (_width == width || _height == height) {
            return;
        }
        _width = width;
        _height = height;
        glViewport(0, 0, _width, _height);
    }
    
    void move(float radian) {
        if (radian > 0 && radian < M_PI) {
            _game.Keys[GLFW_KEY_A] = GL_FALSE;
            _game.Keys[GLFW_KEY_D] = GL_TRUE;
        } else if (radian > M_PI && radian < M_PI * 2) {
            _game.Keys[GLFW_KEY_A] = GL_TRUE;
            _game.Keys[GLFW_KEY_D] = GL_FALSE;
        } else if (radian == -10086) {
            _game.Keys[GLFW_KEY_A] = GL_FALSE;
            _game.Keys[GLFW_KEY_D] = GL_FALSE;
        }
    }
    
    void draw() {
        // Calculate delta time
        long currentFrame = static_cast<long>(getCurrentTime());
        if (_lastFrame == 0) {
            _lastFrame = currentFrame;
        }
        _deltaTime = currentFrame - _lastFrame;
        _lastFrame = currentFrame;

        //deltaTime = 0.001f;
        // Manage user input
        _game.ProcessInput(_deltaTime / 1000.0);

        // Update Game state
        _game.Update(_deltaTime);

        // Render
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        _game.Render();
    }
    
private:
    
    
};

Breakout::Breakout()
    :BaseRenderer(),
    m_pImpl(new Impl()) {
}

Breakout::~Breakout() {
    printf("  Breakout::~Breakout() \n");
}

int Breakout::setupGL() {
    return m_pImpl->setupGL();
}

void Breakout::tearDownGL() {
    m_pImpl->tearDownGL();
}

void Breakout::updateWindowSize(int width, int height) {
    m_pImpl->updateWindowSize(width, height);
}

void Breakout::draw() {
    m_pImpl->draw();
}

void Breakout::move(float radian) {
    m_pImpl->move(radian);
}

