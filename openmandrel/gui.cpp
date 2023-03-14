#include "mandrel.h"
#include "../third_party/imgui/imgui.h"
#include "../third_party/imgui/imgui_impl_sdl.h"
#include "../third_party/imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include <windef.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "gui.cpp"


//TODO: replace this with the code in main
#include <Windows.h>

template<typename Derived>
class MyGui : public Gui<MyGui> 
{
    public:
        Gui()
        {
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
                printf("Error: %s\n", SDL_GetError());
                return -1;
            }

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
            SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
            window = SDL_CreateWindow("OpenMandrel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
            SDL_GLContext gl_context = SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, gl_context);
            SDL_GL_SetSwapInterval(1); // Enable vsync

             // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            //ImGui::StyleColorsLight();

            // Setup Platform/Renderer backends
            ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
            ImGui_ImplOpenGL3_Init("#version 130");

            

            // Main loop
            bool done = false;

        }

        ~Gui()
        {
            // Cleanup
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();

            SDL_GL_DeleteContext(gl_context);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

        void Run()
        {
            // Our state
            StartUp();
            // Main loop
            while(!done) {
                while (SDL_PollEvent(&event)) {
                    ImGui_ImplSDL2_ProcessEvent(&event);
                    if (event.type == SDL_QUIT) done = true;
                    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)) done = true;
                }

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplSDL2_NewFrame();
                ImGui::NewFrame();
                /* wip not template stuff*/
                ImGui::Begin("OpenMandrel", &my_tool_active, ImGuiWindowFlags_MenuBar);
                if (ImGui::BeginMainMenuBar()) {
                    if (ImGui::BeginMenu("File")) {
                        if (ImGui::MenuItem("New")) { }
                        if (ImGui::MenuItem("Save")) { }
                        if (ImGui::MenuItem("Save As")) { }
                        if (ImGui::MenuItem("Open")) { }
                        ImGui::EndMenu();
                    }
                    ImGui::EndMainMenuBar();
                }
                ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
                ImGui::SetNextWindowSize(ImVec2(0.4F*wsx, wsy));

                // tab bar for traces
                if (ImGui::Begin("Passes",p_open, ImGuiWindowFlags_MenuBar)) {
                    if(ImGui::BeginMenuBar()) {
                        if (ImGui::BeginMenu("Passes")) {
                            if(ImGui::MenuItem("Close", "Ctrl+W")) {*p_open = false;}
                            ImGui::EndMenu();
                        }
                    }
                    ImGui::EndMenuBar();

                    ImGui::SliderInt("Passes", &passes, 1, 100); 

                    // Left pane of passes
                    static int selected = 0;

                    ImGui::BeginChild("Passes List", ImVec2(150,0), true);
                    for(int i = 0; i < size; i++) 
                    {
                        char label[128];
                        sprintf(label, "Pass %d");
                    }
                }
                /* end not template stuff */
                        
                Update();

                // Rendering
                ImGui::Render();
                glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
                glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
                glClear(GL_COLOR_BUFFER_BIT);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                SDL_GL_SwapWindow(window);
            }
        }
        
        void Update()
        {
            static_cast<Derived*>(this)->Update();
        };
        void Startup()
        {
            static_cast<Derived*>(this)->Startup();
        }
    protected:
        SDL_Window* window;
        // Our state
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

int main(int, char**) {
    MyGui gui;
    gui.Run();
}