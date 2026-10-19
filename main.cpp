#include <iostream>
#include <emscripten.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#include <cmath>

SDL_Window* window = nullptr;
SDL_GLContext glContext;
float angle = 0.0f;

void main_loop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) break;
    }

    angle += 0.02f;
    float r = (std::sin(angle) + 1.0f) / 2.0f;
    float g = (std::cos(angle) + 1.0f) / 2.0f;
    float b = (std::sin(angle * 0.5f) + 1.0f) / 2.0f;

    glClearColor(r * 0.2f, g * 0.3f, b * 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
}

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void cpp_interact() {
        std::cout << "C++ graphics engine interaction triggered!" << std::endl;
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    window = SDL_CreateWindow("Interactive ICT Canvas",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    glContext = SDL_GL_CreateContext(window);
    emscripten_set_main_loop(main_loop, 0, 1);

    return 0;
}