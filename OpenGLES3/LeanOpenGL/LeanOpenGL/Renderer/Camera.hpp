//
//  Camera.hpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/24.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "glm.hpp"
#include "matrix_transform1.hpp"

//默认相机值
const float CAMERA_YAW         = -90.0f;
const float CAMERA_PITCH       =  0.0f;
const float CAMERA_SPEED       =  2.5f;
const float CAMERA_SENSITIVITY =  0.1f;
const float CAMERA_ZOOM        =  45.0f;

//处理输入并计算相应的欧拉角、向量和矩阵的抽象相机类，供OpenGL使用
class Camera
{
public:
    
    //定义摄像机移动的几个可能选项。用作抽象，以远离特定于窗口系统的输入方法
    enum Camera_Movement {
        FORWARD, // 前进
        BACKWARD, // 后退
        LEFT, // 向左
        RIGHT // 向右
    };
    
public:
    // 相机属性
    glm::vec3 _position; //相机位置
    glm::vec3 _front; // 相机方向
    glm::vec3 _up; // 上向量
    glm::vec3 _right; // 右向量
    glm::vec3 _worldUp; // 全局（世界）上向量
    // 欧拉角
    float _yaw; // 偏航角
    float _pitch; // 俯仰角
    // 相机的选项
    float _movementSpeed; // 移动速度
    float _mouseSensitivity; // 鼠标灵敏度
    float _zoom; // 缩放

    // 构造函数与向量
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = CAMERA_YAW, float pitch = CAMERA_PITCH);
    
    // 带有标量值的构造函数
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // 返回使用欧拉角和LookAt矩阵计算的视图矩阵
    glm::mat4 GetViewMatrix();

    // 处理从任何类似键盘的输入系统接收的输入。接受摄像机定义ENUM形式的输入参数(从窗口系统中抽象它)
    void ProcessKeyboard(Camera_Movement direction, float offset);
    void ProcessKeyboard2(Camera_Movement direction, float deltaTime);

    // 处理从鼠标输入系统接收的输入。期望在x和y方向上的偏移值。
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    // 处理从鼠标滚轮事件接收的输入。只需要在垂直轮轴上输入
    void ProcessMouseScroll(float yoffset);

private:
    // 从相机的(更新的)欧拉角计算前方矢量
    void updateCameraVectors();
};

#endif /* Camera_hpp */
