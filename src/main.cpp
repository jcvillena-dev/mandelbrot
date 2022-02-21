#include "Mandelbrot.h"
#include "Window.h"
#include <iostream>
#include <memory>
#include <string.h>

int main(int argc, char *argv[]) {
  // Default values to generate the Mandelbrot set
  double minx = -2.0;
  double maxx = 1.0;
  double miny = -1.0;
  double maxy = 1.0;
  int maxiter = 25;
  int threads = 4;
  int height = 750;
  int width = 800;

  // Read the arguments from command line
  if (argc > 1) {
    std::vector<std::string> allArgs(argv + 1, argv + argc);
    std::string minx_opt("--minx=");
    std::string maxx_opt("--maxx=");
    std::string miny_opt("--miny=");
    std::string maxy_opt("--maxy=");
    std::string maxiter_opt("--maxiter=");
    std::string threads_opt("--threads=");
    std::string height_opt("--height=");
    std::string width_opt("--width=");

    std::cout << "List of arguments:" << std::endl;

    for (auto &str : allArgs) {
      std::string::size_type pos = str.find(minx_opt);
      if (pos != std::string::npos) {
        std::string x = str.substr(str.find("=") + 1);
        std::cout << "minx : " << x << std::endl;
        minx = ::atof(x.c_str());
        continue;
      }

      pos = str.find(maxx_opt);
      if (pos != std::string::npos) {
        std::string x = str.substr(str.find("=") + 1);
        std::cout << "maxx : " << x << std::endl;
        maxx = ::atof(x.c_str());
        continue;
      }

      pos = str.find(miny_opt);
      if (pos != std::string::npos) {
        std::string x = str.substr(str.find("=") + 1);
        std::cout << "miny : " << x << std::endl;
        miny = ::atof(x.c_str());
        continue;
      }

      pos = str.find(maxy_opt);
      if (pos != std::string::npos) {
        std::string x = str.substr(str.find("=") + 1);
        std::cout << "maxy : " << x << std::endl;
        maxy = ::atof(x.c_str());
        continue;
      }

      pos = str.find(maxiter_opt);
      if (pos != std::string::npos) {
        std::string x = str.substr(str.find("=") + 1);
        std::cout << "maxiter : " << x << std::endl;
        maxiter = ::atoi(x.c_str());
        continue;
      }

      pos = str.find(threads_opt);
      if (pos != std::string::npos) {
        std::string x = str.substr(str.find("=") + 1);
        std::cout << "threads : " << x << std::endl;
        threads = ::atoi(x.c_str());
        continue;
      }

      pos = str.find(height_opt);
      if (pos != std::string::npos) {
        std::string x = str.substr(str.find("=") + 1);
        std::cout << "height : " << x << std::endl;
        height = ::atoi(x.c_str());
        continue;
      }

      pos = str.find(width_opt);
      if (pos != std::string::npos) {
        std::string x = str.substr(str.find("=") + 1);
        std::cout << "width : " << x << std::endl;
        width = ::atoi(x.c_str());
        continue;
      }
    }
  }

  auto mandelbrot = std::make_shared<Mandelbrot>(
      minx, maxx, miny, maxy, maxiter, threads, height, width);
  Window win(height, width, mandelbrot);

  if (win.init()) {
    win.run();
  }

  return 0;
}