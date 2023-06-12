#include "Core.h"
#include "GameState.h"
#include "GameObject.h"
#include "ScreenText.h"
#include "Bullet.h"
#include "PlayerShip.h"
#include "Enemy.h"
#include "EnemyBolter.h"
#include "EnemyBoss.h"
#include "Background.h"
#include "MainMethods.h"
#include "SceneMethods.h"


int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "spcae stoorhe", NULL, NULL);
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keycallback);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)  
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1); // essentially set coordinate system, origin is at upper left corner
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        /*Delta Time Calculations*/
        static double prevTime = glfwGetTime();
        double curTime = glfwGetTime(); 
        deltaTime = curTime - prevTime;
        prevTime = curTime;               

        //draw objects
        drawObjects();

        /*Game State specific stuff*/
        switch (gameState) {
        case GameState::START:
            if (keys[GLFW_KEY_ENTER])
                startPlayingStateStage();
            drawStartTexts();
            break;
        case GameState::PLAYING:
            updatePlayer();
            

            /*Playing State specific stuff*/
            switch (playingState) {
            case PlayingState::STAGE:
                playingStateStage();
                updateEnemies();
                break;
            case PlayingState::BOSS_TRANSITION:
                playingStateBossTransition();
                break;
            case PlayingState::BOSS:
                playingStateBoss();
                updateEnemies();
                break;
            }

            break;
        case GameState::GAME_OVER:
            if (keys[GLFW_KEY_ENTER])
                resetScene();         
            drawGameOverTexts();
            break;
        case GameState::GAME_WIN:
            updatePlayer();
            if (keys[GLFW_KEY_ENTER])
                resetScene();           
            drawGameWinTexts();
            break;
        }                

        //update bullets and collisions
        updateBullets();        

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}




