#pragma once

#include <memory>
#include <vector>
#include <mutex>

struct TColor {
  int red;
  int green;
  int blue;

  TColor(int r, int g, int b) : red(r), green(g), blue(b) {}
};

template <typename T> struct Tmatrix { std::vector<std::vector<T>> data; };

class Mandelbrot {
public:
  Mandelbrot(double xmin, double xmax, double ymin, double ymax, int maxiter,
             int nthreads, int heigth, int width);
  std::shared_ptr<Tmatrix<TColor>> get_matrix();
  void compute_threads();

private:
  int compute_point(double x, double y);
  double _xmin;
  double _xmax;
  double _ymin;
  double _ymax;
  int _maxiter;
  Tmatrix<TColor> _matrix;
  int _nthreads;
  int _height;
  int _width;
  std::mutex _mutex;
};