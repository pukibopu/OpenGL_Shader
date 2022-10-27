//
//  main.cpp
//  Test2
//
//  Created by ShuYang Yan on 2022/10/26.
//

#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "headers/shader.hpp"
const unsigned int screen_width=800;
const unsigned int screen_height=600;

void framebuffer_size_callback(GLFWwindow *window,int width,int height);
void processInput(GLFWwindow *window);

int main() {
    //initial
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //create window and bind context
    GLFWwindow *window=glfwCreateWindow(screen_width, screen_width, "shaderHeader", NULL, NULL);
    if(window==NULL){
        std::cout<<"ERROR TO CREATE WINDOW"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    
    //initial glad;
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout<<"INITIAL GLAD ERROR"<<std::endl;
        return -1;
    }
    //shader
    Shader shader("vShader.txt","fShader.txt");
    
    //indie
    float vertices[] = {
           // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
           -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
       };
    unsigned int VBO,VAO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    //pointer
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    while (!glfwWindowShouldClose(window))
       {
           // input
           // -----
           processInput(window);

           // render
           // ------
           glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
           glClear(GL_COLOR_BUFFER_BIT);

           // render the triangle
           shader.use();
           shader.setFloat("offset", 0.5f);
           glBindVertexArray(VAO);
           glDrawArrays(GL_TRIANGLES, 0, 3);

           // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
           // -------------------------------------------------------------------------------
           glfwSwapBuffers(window);
           glfwPollEvents();
       }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window,int width,int height){
    glViewport(0,0,width,height);
}
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)){
        glfwSetWindowShouldClose(window, true);
    }
}
