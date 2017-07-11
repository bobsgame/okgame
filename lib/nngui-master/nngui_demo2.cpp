/*
    src/example1.cpp -- C++ version of an example application that shows 
    how to use the various widget classes.

    Original NanoGUI was developed by Wenzel Jakob <wenzel@inf.ethz.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    nnGUI was improved by Dalerank <dalerankn8@gmail.com>

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#include <nngui.h>
#if defined(_WIN32)
#include <windows.h>
#endif
#include <iostream>
#ifdef NNGUI_SDL
#include <SDL.h>
#elif defined NNGUI_GLFW
#include <GLFW/glfw3.h>
#endif

using std::cout;
using std::cerr;
using std::endl;

#undef main


enum test_enum {
    Item1 = 0,
    Item2,
    Item3
};

using namespace nngui;

bool bvar = true;
int ivar = 12345678;
double dvar = 3.1415926;
float fvar = (float)dvar;
std::string strval = "A string";
test_enum enumval = Item2;
Color colval(0.5f, 0.5f, 0.7f, 1.f);

int main(int /* argc */, char ** /* argv */)
{
#ifdef NNGUI_SDL
    SDL_Init(SDL_INIT_VIDEO);   // Initialize SDL2

    SDL_Window *window;        // Declare a pointer to an SDL_Window

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);

    int winWidth = 1024;
    int winHeight = 768;

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
      "An SDL2 window",         //    const char* title
      SDL_WINDOWPOS_UNDEFINED,  //    int x: initial x position
      SDL_WINDOWPOS_UNDEFINED,  //    int y: initial y position
      winWidth,                      //    int w: width, in pixels
      winHeight,                      //    int h: height, in pixels
      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN          //    Uint32 flags: window options, see docs
    );

    // Check that the window was successfully made
    if(window==NULL){
      // In the event that the window could not be made...
      std::cout << "Could not create window: " << SDL_GetError() << '\n';
      SDL_Quit();
      return 1;
    }

    SDL_GL_CreateContext(window);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );

    Screen *screen = new Screen( window, Vec2i(winWidth, winHeight), "NanoGUI test");

    bool enabled = true;
    FormHelper *gui = new FormHelper(screen);
    ref<Window> rwindow = gui->addWindow(Vec2i(10, 10), "Form helper example");
    gui->addGroup("Basic types");
    gui->addVariable("bool", bvar);
    gui->addVariable("string", strval);

    gui->addGroup("Validating fields");
    gui->addVariable("int", ivar);
    gui->addVariable("float", fvar);
    gui->addVariable("double", dvar);

    gui->addGroup("Complex types");
    gui->addVariable("Enumeration", enumval, enabled)
       ->setItems({"Item 1", "Item 2", "Item 3"});
    gui->addVariable("Color", colval);

    gui->addGroup("Other widgets");
    gui->addButton("A button", [](){ std::cout << "Button pressed." << std::endl; });

    screen->setVisible(true);
    screen->performLayout();
    rwindow->center();


    bool quit = false;
    try
    {
        //Event handler
        SDL_Event e;
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                screen->onEvent( e );
            }

            SDL_SetRenderDrawColor(renderer, 0xd3, 0xd3, 0xd3, 0xff );
            SDL_RenderClear( renderer );

            screen->drawAll();

            SDL_SetRenderDrawColor(renderer, 0xff, 0, 0, 0xff );
            SDL_Rect r{ 0, 0, 20, 30 };
            SDL_RenderFillRect( renderer, &r );

            //Update screen
            SDL_GL_SwapWindow(window);
        }
    }
    catch (const std::runtime_error &e)
    {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        #if defined(_WIN32)
            MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
        #else
            std::cerr << error_msg << endl;
        #endif
        return -1;
    }
#elif defined NNGUI_GLFW
    glfwSetErrorCallback(
        [](int error, const char *descr) {
            if (error == GLFW_NOT_INITIALIZED)
                return; /* Ignore */
            std::cerr << "GLFW error " << error << ": " << descr << std::endl;
        }
    );

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    bool resizable = false;
    bool fullscreen = false;
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);

    if (!glfwInit())
        throw std::runtime_error("Could not initialize GLFW!");
    glfwSetTime(0);

    std::string caption = "An GLFW window";

    Vec2i size(1024, 768);
    Screen::ParentWindowPtr window;
    if (fullscreen) {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        size.set(mode->width, mode->height);
        window = glfwCreateWindow(mode->width, mode->height,
                                       caption.c_str(), monitor, nullptr);
    } else {
        window = glfwCreateWindow(size.x(), size.y(),
                                  caption.c_str(), nullptr, nullptr);
    }

    if (!window)
        throw std::runtime_error("Could not create an OpenGL " +
                                 std::to_string(3) + "." +
                                 std::to_string(3) + " context!");

    glfwMakeContextCurrent(window);

    Screen *screen = new Screen( window, Vec2i(size.x(), size.y()), "NanoGUI test");

    bool enabled = true;
    FormHelper *gui = new FormHelper(screen);
    ref<Window> rwindow = gui->addWindow(Vec2i(10, 10), "Form helper example");
    gui->addGroup("Basic types");
    gui->addVariable("bool", bvar);
    gui->addVariable("string", strval);

    gui->addGroup("Validating fields");
    gui->addVariable("int", ivar);
    gui->addVariable("float", fvar);
    gui->addVariable("double", dvar);

    gui->addGroup("Complex types");
    gui->addVariable("Enumeration", enumval, enabled)
       ->setItems({"Item 1", "Item 2", "Item 3"});
    gui->addVariable("Color", colval);

    gui->addGroup("Other widgets");
    gui->addButton("A button", [](){ std::cout << "Button pressed." << std::endl; });

    screen->setVisible(true);
    screen->performLayout();
    rwindow->center();
    glfwSetCursorPosCallback(window,
        [](GLFWwindow *w, double x, double y)
        {
            Screen* s = __nngui_findScreen(w);
            if (s)
            {
                s->cursorPosCallbackEvent(x, y);
            }
        }
    );

    glfwSetMouseButtonCallback(window,
        [](GLFWwindow *w, int button, int action, int modifiers) {
            Screen* s = __nngui_findScreen(w);
            if (s)
            {
                s->mouseButtonCallbackEvent(button, action, modifiers);
            }
        }
    );

    glfwSetKeyCallback(window,
        [](GLFWwindow *w, int key, int scancode, int action, int mods) {
            Screen* s = __nngui_findScreen(w);
            if (s)
            {
                s->keyCallbackEvent(key, scancode, action, mods);
            }
        }
    );

    glfwSetCharCallback(window,
        [](GLFWwindow *w, unsigned int codepoint) {
            Screen* s = __nngui_findScreen(w);
            if (s)
            {
                s->charCallbackEvent(codepoint);
            }
        }
    );

    glfwSetDropCallback(window,
        [](GLFWwindow *w, int count, const char **filenames) {
            Screen* s = __nngui_findScreen(w);
            if (s)
            {
                s->dropCallbackEvent(count, filenames);
            }
        }
    );

    glfwSetScrollCallback(window,
        [](GLFWwindow *w, double x, double y) {
            Screen* s = __nngui_findScreen(w);
            if (s)
            {
                s->scrollCallbackEvent(x, y);
            }
        }
    );

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow* w, int width, int height) {
            Screen* s = __nngui_findScreen(w);
            if (s)
            {
                s->resizeCallbackEvent(width, height);
            }
        }
    );

    try
    {
        screen->setVisible(true);
        //Event handler
        while (!glfwWindowShouldClose(screen->window()))
        {
            float ratio;
            ratio = size.x() / (float)size.y();
            glViewport(0, 0, size.x(), size.y());
            glClear(GL_COLOR_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
            glBegin(GL_TRIANGLES);
            glColor3f(1.f, 0.f, 0.f);
            glVertex3f(-0.6f, -0.4f, 0.f);
            glColor3f(0.f, 1.f, 0.f);
            glVertex3f(0.6f, -0.4f, 0.f);
            glColor3f(0.f, 0.f, 1.f);
            glVertex3f(0.f, 0.6f, 0.f);
            glEnd();

            screen->drawAll();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    catch (const std::runtime_error &e)
    {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        #if defined(_WIN32)
            MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
        #else
            std::cerr << error_msg << endl;
        #endif
        return -1;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
#endif
    return 0;    
}
