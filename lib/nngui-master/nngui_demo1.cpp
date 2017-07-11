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

#include <cmath>
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

using namespace nngui;

class TestScreen : public nngui::Screen
{
public:
    TestScreen(Screen::ParentWindowPtr pwindow, int rwidth, int rheight )
      : nngui::Screen( pwindow, Vec2i(rwidth, rheight), "SDL_gui Test")
      {
        mProgress = nullptr;
        using namespace nngui;

        {
          auto& nwindow = add<Window>("Button demo");
          nwindow.setPosition(Vec2i(15, 15));
          nwindow.setLayout(new GroupLayout());

          nwindow.add<Label>("Push buttons", "sans-bold");
          nwindow.add<Button>("Plain button").withCallback([] { cout << "pushed!" << endl; } );

          nwindow.add<Button>("Styled", ENTYPO_ICON_ROCKET).withCallback([] { cout << "pushed!" << endl; })
                                                           .withBackgroundColor( Color(0, 0, 255, 25) );

          nwindow.add<Label>("Toggle buttons", "sans-bold");
          nwindow.add<Button>("Toggle me").withFlags(Button::ToggleButton)
                                          .withChangeCallback([](bool state) { cout << "Toggle button state: " << state << endl; });

          nwindow.add<Label>("Radio buttons", "sans-bold");
          nwindow.add<Button>("Radio button 1").withFlags(Button::RadioButton);

          nwindow.add<Button>("Radio button 2").withFlags(Button::RadioButton);
          nwindow.add<Label>("A tool palette", "sans-bold");

          auto& tools = nwindow.add<Widget>().withLayout<BoxLayout>(Orientation::Horizontal,
                                                                    Alignment::Middle, 0, 6);

          tools.add<ToolButton>().withIcon(ENTYPO_ICON_CLOUD);
          tools.add<ToolButton>().withIcon(ENTYPO_ICON_FF)
                                 .withTooltip("Is a tooltip text");
          tools.add<ToolButton>(ENTYPO_ICON_COMPASS);
          tools.add<ToolButton>(ENTYPO_ICON_INSTALL);

          nwindow.add<Label>("Popup buttons", "sans-bold");
          PopupButton& pButton = nwindow.add<PopupButton>("Popup", ENTYPO_ICON_EXPORT);
          pButton.popup()->withLayout<GroupLayout>();
          pButton.popup()->add<Label>("Arbitrary widgets can be placed here");
          pButton.popup()->add<CheckBox>("A check box");

          PopupButton& rPopupBtn = pButton.popup()->add<PopupButton>("Recursive popup", ENTYPO_ICON_FLASH);
          rPopupBtn.popup()->withLayout<GroupLayout>();
          rPopupBtn.popup()->add<CheckBox>("Another check box");

          nwindow.setContextCallback([](const Vec2i& p, Widget* w) {
              ContextMenu& cm = w->add<ContextMenu>();
              cm.setSize(Vec2i(200, 200));
          });
        }

        std::vector<std::pair<int, std::string>>
            icons = loadImageDirectory(mNVGContext, "icons");

        {
          auto& window = add<Window>("Basic widgets")
                              .withPosition(Vec2i(200, 15))
                              .withLayout<GroupLayout>();

          window.add<Label>("Message dialog", "sans-bold");
          auto& tools = window.add<Widget>()
                              .withLayout<BoxLayout>(Orientation::Horizontal,
                                                       Alignment::Middle, 0, 6);
          tools.add<Button>("Info")
                .withCallback([&] {
                    add<MessageDialog>(MessageDialog::Type::Information, "Title", "This is an information message")
                    .withCallback([](int result) { cout << "Dialog result: " << result << endl; });
            } );
          tools.add<Button>("Warn")
              .withCallback([&]
              {
                add<MessageDialog>(MessageDialog::Type::Warning, "Title", "This is a warning message")
                      .withCallback([](int result) { cout << "Dialog result: " << result << endl; });
              }
          );
          tools.add<Button>("Ask")
                .withCallback([&] {
                    add<MessageDialog>(MessageDialog::Type::Warning, "Title", "This is a question message", "Yes", "No", true)
                     .withCallback([](int result) { cout << "Dialog result: " << result << endl; });
            });

          window.add<Label>("Image panel & scroll panel", "sans-bold");
          PopupButton& imagePanelBtn = window.add<PopupButton>("Image Panel");

          imagePanelBtn.setIcon(ENTYPO_ICON_FOLDER);
          auto* popup = imagePanelBtn.popup();
          VScrollPanel& vscroll = popup->add<VScrollPanel>();
          ImagePanel& imgPanel = vscroll.add<ImagePanel>()
                                        .withImages(icons);

          popup->setFixedSize(Vec2i(245, 150));

          auto& img_window = add<Window>("Selected image");
          img_window.withPosition(Vec2i(675, 15))
                    .withLayout<GroupLayout>();

          auto& img = img_window.add<ImageView>()
                                .withPolicy(ImageView::SizePolicy::Expand)
                                .withImage(icons[0].first);
          img.setFixedSize(Vec2i(300, 300));
          imgPanel.setCallback([&img, &imgPanel, &imagePanelBtn](int i) {
              img.setImage(imgPanel.images()[i].first); cout << "Selected item " << i << endl;
          });

          auto& img_cb = img_window.add<CheckBox>( "Expand",
              [&img](bool state) { if (state) img.setPolicy(ImageView::SizePolicy::Expand);
                                   else       img.setPolicy(ImageView::SizePolicy::Fixed); });
          img_cb.setChecked(true);
          window.add<Label>("File dialog", "sans-bold");
          auto& tools2 = window.add<Widget>().withLayout<BoxLayout>( Orientation::Horizontal,
                                                                     Alignment::Middle, 0, 6 );
          tools2.add<Button>("Open")
                .withCallback([&] {
                    cout << "File dialog result: " << file_dialog(
                    { {"png", "Portable Network Graphics"}, {"txt", "Text file"} }, false) << endl;
              });

          tools2.add<Button>("Save").withCallback([&] {
              cout << "File dialog result: " << file_dialog(
                      { {"png", "Portable Network Graphics"}, {"txt", "Text file"} }, true) << endl;
          });

          window.add<Label>("Combo box", "sans-bold");
          window.add<ComboBox>(std::vector<std::string>{ "Combo box item 1", "Combo box item 2", "Combo box item 3"});
          window.add<Label>("Check box", "sans-bold");

          auto& cb = window.add<CheckBox>("Flag 1",
              [](bool state) { cout << "Check box 1 state: " << state << endl; }
          );
          cb.setChecked(true);
          window.add<CheckBox>("Flag 2",
              [](bool state) { cout << "Check box 2 state: " << state << endl; }
          );
          window.add<Label>("Progress bar", "sans-bold");
          mProgress = &window.add<ProgressBar>();

          window.add<Label>("Slider and text box", "sans-bold");

          auto& panel = window.add<Widget>()
                              .withLayout<BoxLayout>(Orientation::Horizontal,
                                                     Alignment::Middle, 0, 20);

          auto& slider = panel.add<Slider>();
          slider.setValue(0.5f);
          slider.setFixedWidth(80);

          auto& textBox = panel.add<TextBox>();
          textBox.setFixedSize(Vec2i(60, 25));
          textBox.setValue("50");
          textBox.setUnits("%");
          slider.setCallback([&textBox](float value) {
              textBox.setValue(std::to_string((int) (value * 100)));
          });
          slider.setFinalCallback([](float value) {
              cout << "Final slider value: " << (int) (value * 100) << endl;
          });
          textBox.setFixedSize(Vec2i(60,25));
          textBox.setFontSize(20);
          textBox.setAlignment(TextBox::Alignment::Right);
        }

        {
          auto& window = add<Window>("Misc. widgets");
          window.setPosition(Vec2i(425,15));
          window.setLayout(new GroupLayout());
          window.add<Label>("Color wheel","sans-bold");
          window.add<ColorWheel>();
          window.add<Label>("Function graph", "sans-bold");
          Graph& graph = window.add<Graph>("Some function");
          graph.setHeader("E = 2.35e-3");
          graph.setFooter("Iteration 89");
          VectorXf &func = graph.values();
          func.resize(100);

          for (int i = 0; i < 100; ++i)
              func[i] = 0.5f * (0.5f * std::sin(i / 10.f) +
                                0.5f * std::cos(i / 23.f) + 1);


        }

        {
          auto& window = add<Window>("Grid of small widgets");
          window.withPosition({425, 288});
          auto* layout = new GridLayout(Orientation::Horizontal, 2,
                                         Alignment::Middle, 15, 5);
          layout->setColAlignment({ Alignment::Maximum, Alignment::Fill });
          layout->setSpacing(Vec2i(0, 10));
          window.setLayout(layout);

          window.add<Label>("Floating point :", "sans-bold");
          auto& textBox = window.add<TextBox>();
          textBox.setEditable(true);
          textBox.setFixedSize(Vec2i(100, 20));
          textBox.setValue("50");
          textBox.setUnits("GiB");
          textBox.setDefaultValue("0.0");
          textBox.setFontSize(16);
          textBox.setFormat("[-]?[0-9]*\\.?[0-9]+");

          window.add<Label>("Positive integer :", "sans-bold");
          auto& textBox2 = window.add<TextBox>();
          textBox2.setEditable(true);
          textBox2.setFixedSize(Vec2i(100, 20));
          textBox2.setValue("50");
          textBox2.setUnits("Mhz");
          textBox2.setDefaultValue("0.0");
          textBox2.setFontSize(16);
          textBox2.setFormat("[1-9][0-9]*");

          window.add<Label>( "Checkbox :", "sans-bold");

          window.add<CheckBox>("Check me")
                .withChecked(true)
                .withFontSize(16);

          window.add<Label>("Combo box :", "sans-bold");
          window.add<ComboBox>()
                .withItems(std::vector<std::string>{ "Item 1", "Item 2", "Item 3" })
                .withFontSize(16)
                .withFixedSize(Vec2i(100,20));

          window.add<Label>("Color button :", "sans-bold");
          auto& popupBtn = window.add<PopupButton>("", 0);
          popupBtn.setBackgroundColor(Color(255, 120, 0, 255));
          popupBtn.setFontSize(16);
          popupBtn.setFixedSize(Vec2i(100, 20));
          auto& popup = popupBtn.popup()->withLayout<GroupLayout>();

          ColorWheel& colorwheel = popup.add<ColorWheel>();
          colorwheel.setColor(popupBtn.backgroundColor());

          Button& colorBtn = popup.add<Button>("Pick");
          colorBtn.setFixedSize(Vec2i(100, 25));
          Color c = colorwheel.color();
          colorBtn.setBackgroundColor(c);

          colorwheel.setCallback([&colorBtn](const Color &value) {
              colorBtn.setBackgroundColor(value);
          });

          colorBtn.setChangeCallback([&colorBtn, &popupBtn](bool pushed) {
              if (pushed) {
                  popupBtn.setBackgroundColor(colorBtn.backgroundColor());
                  popupBtn.setPushed(false);
              }
          });
        }
        performLayout(mNVGContext);
    }

    ~TestScreen() {
    }

    virtual bool keyboardEvent(int key, int scancode, int action, int modifiers)
    {
        if (Screen::keyboardEvent(key, scancode, action, modifiers))
            return true;

        //if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        // {
        //    setVisible(false);
        //    return true;
        //}
        return false;
    }

    virtual void draw(NVGcontext *ctx) {
        // Animate the scrollbar
        if( mProgress )
        {
          mProgress->setValue( mProgress->value() + 0.001f );
          if( mProgress->value() >= 1.f )
            mProgress->setValue( 0.f );
        }

        // Draw the user interface
        Screen::draw(ctx);
    }

    virtual void drawContents()
    {
    }
private:
    nngui::ProgressBar *mProgress;
};

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
    TestWindow *screen = new TestWindow( window, winWidth, winHeight );

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
#if !defined(_WIN32)
    /* Avoid locale-related number parsing issues */
    setlocale(LC_NUMERIC, "C");
#endif

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

    TestScreen *screen = new TestScreen(window, size.x(), size.y());

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
