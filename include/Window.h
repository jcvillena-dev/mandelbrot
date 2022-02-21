#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include <Mandelbrot.h>

class Window {
public:
  Window(int height, int width, std::shared_ptr<Mandelbrot> fractal);
  bool init();
  void run();

private:
  void show_fractal();
  void screenshot();

  int _height, _width;
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Event _event;  
  std::shared_ptr<Mandelbrot> _fractal;
};