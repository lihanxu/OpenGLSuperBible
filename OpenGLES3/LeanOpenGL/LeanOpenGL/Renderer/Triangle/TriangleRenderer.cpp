//
//  TriangleRenderer.cpp
//  LeanOpenGL
//
//  Created by hansen on 2022/10/20.
//

#include "TriangleRenderer.hpp"
#include "Shader.hpp"

class TriangleRenderer::Impl {
public:
    GLint _width;
    GLint _height;
    
private:
    Shader _shader;
    GLuint _VAO;
public:
    Impl(const char *vertextPath, const char *fragmentPath)
        :_shader(Shader(vertextPath, fragmentPath)) {
    }
    
    ~Impl() {}
    
    int setupGL() {
        glClearColor(1.0, 1.0, 1.0, 0.0f);
        genVAO();
        return GL_TRUE;
    }
    
    void tearDownGL() {
        glDeleteProgram(_shader.ID);
    }
    
    void updateWindowSize(GLint width, GLint height) {
        if (_width == width || _height == height) {
            return;
        }
        _width = width;
        _height = height;
    }
    
    void draw() {
        glViewport(0, 0, _width, _height);
        glClear(GL_COLOR_BUFFER_BIT);
        
        _shader.use();
        _shader.setFloat3("ourColor", 1.0, 0.0, 1.0);
        glBindVertexArray(_VAO);
/*
 void glDrawArrays(GLenum mode, GLint first, GLsizei count);

    mode: 第一个参数是我们打算绘制的OpenGL图元的类型。由于我们在一开始时说过，我们希望绘制的是一个三角形，这里传递 GL_TRIANGLES 给它。
    first: 第二个参数指定了顶点数组的起始索引，我们这里填0。
    count: 最后一个参数指定我们打算绘制多少个顶点，这里是3（ 我们只从我们的数据中渲染一个三角形，它只有3个顶点长 ）。
 */
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    
private:
    void genVAO() {
        float vertices[] = {
            // 位置              // 颜色
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
        };
        
        GLuint VBO;
        
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &VBO);
        
        glBindVertexArray(_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
/*
 void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
 
     target: 第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到 GL_ARRAY_BUFFER 目标上。
     size: 第二个参数指定传输数据的大小(以字节为单位)；用一个简单的 sizeof 计算出顶点数据大小就行。
     data: 第三个参数是我们希望发送的实际数据。
     usage:  第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
        GL_STATIC_DRAW ：数据不会或几乎不会改变。
        GL_DYNAMIC_DRAW：数据会被改变很多。
        GL_STREAM_DRAW ：数据每次绘制时都会改变。
*/
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
       
/*
 void glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *ptr);

    indx: 第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用 layout(location = 0) 定义了 position 顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
    size: 第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
    type: 第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
    normalized: 第四个参数定义我们是否希望数据被标准化 (Normalize) 。如果我们设置为 GL_TRUE ，所有数据都会被映射到 0（对于有符号型 signed 数据是 -1 ）到 1 之间。我们把它设置为 GL_FALSE。
    stride: 第五个参数叫做步长( Stride )，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个 float 之后，我们把步长设置为3 * sizeof(float) 。 要注意的是由于我们知道这个数组是紧密排列的（ 在两个顶点属性之间没有空隙 ）我们也可以设置为0来让 OpenGL 决定具体步长是多少（ 只有当数值是紧密排列时才可用 ）。 一旦我们有更多的顶点属性 ，我们就必须更小心地定义每个顶点属性之间的间隔 ，我们在后面会看到更多的例子（ 译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节 ）。
    ptr: 最后一个参数的类型是 void* ，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量 ( Offset ) 。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
*/
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void *)(3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(1);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
};

TriangleRenderer::TriangleRenderer(const char *vertextPath, const char *fragmentPath)
    :BaseRenderer(vertextPath, fragmentPath),
    m_pImpl(new Impl(vertextPath, fragmentPath)) {
}

TriangleRenderer::~TriangleRenderer() {
    printf("  TriangleRenderer::~TriangleRenderer() \n");
}

int TriangleRenderer::setupGL() {
    return m_pImpl->setupGL();
}

void TriangleRenderer::tearDownGL() {
    m_pImpl->tearDownGL();
}

void TriangleRenderer::updateWindowSize(int width, int height) {
    m_pImpl->updateWindowSize(width, height);
}

void TriangleRenderer::draw() {
    m_pImpl->draw();
}

