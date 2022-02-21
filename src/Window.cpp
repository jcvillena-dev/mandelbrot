#include "Window.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>

Window::Window(int height, int width, std::shared_ptr<Mandelbrot> fractal)
    : _height(height), _width(width), _fractal(fractal) {}

bool Window::init() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s",
                 SDL_GetError());
    return false;
  }

  _window = SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, _width, _height,
                             SDL_WINDOW_SHOWN);
  if (_window == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s",
                 SDL_GetError());
    return false;
  }

  _renderer = SDL_CreateRenderer(
      _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (_renderer == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s",
                 SDL_GetError());
    return false;
  }

  SDL_RenderSetLogicalSize(_renderer, _width, _height);

  return true;
}

void Window::screenshot() {
  std::time_t t = std::time(NULL);
  std::string stime = std::ctime(&t);
  stime.erase(std::remove(stime.begin(), stime.end(), ' '), stime.end());
  stime.erase(std::remove(stime.begin(), stime.end(), ':'), stime.end());
  std::string str =
      "../images/screenshot" + stime.substr(0, stime.size() - 1) + ".bmp";
  SDL_Surface *sshot = SDL_CreateRGBSurface(SDL_SWSURFACE, _width, _height, 32, 0x00ff0000,
                                            0x0000ff00, 0x000000ff, 0xff000000);
  SDL_RenderReadPixels(_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels,
                       sshot->pitch);
  SDL_SaveBMP(sshot, str.data());
  SDL_FreeSurface(sshot);
  std::cout << "Saved screenshot in : " << str.data() << std::endl;
}

// Render the Mandelbrot set in the Renderer
void Window::show_fractal() {
  _fractal->compute_threads();
  auto matrix = _fractal->get_matrix();
  for (std::size_t row{}; row < matrix->data.size(); ++row) {
    for (std::size_t col{}; col < matrix->data.at(row).size(); ++col) {
      auto value = matrix->data.at(row)[col];
      SDL_SetRenderDrawColor(_renderer, value.red, value.green, value.blue,
                             SDL_ALPHA_OPAQUE);
      SDL_RenderDrawPoint(_renderer, col, row);
    }
  }
  SDL_RenderPresent(_renderer);
}

void Window::run() {
  if ((_renderer != nullptr) && (_window != nullptr)) {
    show_fractal();
    bool quit = false;
    while (!quit) {
      SDL_PollEvent(&_event);
      switch (_event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        if (_event.key.keysym.sym == SDLK_s) {
          screenshot();
        }
      default:
        break;
      }
    }
  }
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  SDL_Quit();
}