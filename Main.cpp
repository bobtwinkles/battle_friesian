
#include <stdio.h>
#include <stdlib.h>
/* If using gl3.h */
/* Ensure we are using opengl's core profile only */
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <SDL2/SDL.h>
#define PROGRAM_NAME "Fressian"

#include "flow/GameFlow.hpp"
#include "construct/Parser.hpp"

/* A simple function that prints a message, the error code returned by SDL,
 * and quits the application */
void sdldie(const char *msg) {
  printf("%s: %s\n", msg, SDL_GetError());
  SDL_Quit();
  exit(1);
}


void checkSDLError(int line = -1) {
#ifndef NDEBUG
  const char *error = SDL_GetError();
  if (*error != '\0') {
    printf("SDL Error: %s\n", error);
    if (line != -1)
      printf(" + line: %i\n", line);
    SDL_ClearError();
  }
#endif
}


/* Our program's entry point */
int main(int argc, char *argv[]) {
  SDL_Window *mainwindow; /* Our window handle */
  SDL_GLContext maincontext; /* Our opengl context handle */

  if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
      sdldie("Unable to initialize SDL"); /* Or die on error */

  /* Request opengl 3.2 context.
   * SDL doesn't have the ability to choose which profile at this time of writing,
   * but it should default to the core profile */
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  /* Turn on double buffering with a 24bit Z buffer.
   * You may need to change this to 16 or 32 for your system */
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  /* Create our window centered at 512x512 resolution */
  mainwindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                1366, 768, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!mainwindow) /* Die if creation failed */
    sdldie("Unable to create window");

  checkSDLError(__LINE__);

  /* Create our opengl context and attach it to our window */
  maincontext = SDL_GL_CreateContext(mainwindow);
  checkSDLError(__LINE__);

  // Initialize GLEW and our stuff
  glewExperimental = true;
  int err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "Failed to initialize glew : " << glewGetErrorString(err) << std::endl;
    exit(1);
  }
  /* This makes our buffer swap syncronized with the monitor's vertical refresh */
  SDL_GL_SetSwapInterval(1);

  //
  // Initialize our [sub]systems
  //
  // Base directory
  fri::InitializeBaseDirectory(argv[0]);
  // Randomization
  srand(0);

  fri::flow::GameFlow gameflow;

  bool running = true;

  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
              running = false;
              break;
          }
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              running = false;
              break;
          }
          break;
      }
    }

    gameflow.Tick(1.0 / 60.0);

    SDL_GL_SwapWindow(mainwindow);
  }

  /* Delete our opengl context, destroy our window, and shutdown SDL */
  SDL_GL_DeleteContext(maincontext);
  SDL_DestroyWindow(mainwindow);
  SDL_Quit();

  return 0;
}
