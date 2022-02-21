#include "Mandelbrot.h"
#include <complex.h>
#include <iostream>
#include <thread>

Mandelbrot::Mandelbrot(double xmin, double xmax, double ymin, double ymax,
                       int maxiter, int nthreads, int height, int width)
    : _xmin(xmin), _xmax(xmax), _ymin(ymin), _ymax(ymax), _maxiter(maxiter),
      _nthreads(nthreads), _height(height), _width(width) {}

// Compute the Mandelbrot set.
// Uses multithreading.
// The number of threads is given by _nthreads
void Mandelbrot::compute_threads() {
  std::vector<std::vector<int>> areas;
  int n = 0;
  int n_rows = _height / _nthreads;

  areas.resize(n_rows);
  _matrix.data.resize(_height, std::vector<TColor>(_width, {0, 0, 0}));

  for (int i = 0; i < _height; ++i) {
    areas[n].emplace_back(i);
    if ((areas[n].size() == n_rows) && (n < (_nthreads - 1))) {
      n++;
    }
  }
  std::vector<std::thread> workers;
  for (int i = 0; i < _nthreads; ++i) {
    int a = 0;
    const std::vector<int> &area = areas[i];
    workers.emplace_back(std::thread([this, area]() {
      for (auto &row : area) {
        std::vector<TColor> vec;
        for (int col = 0; col < _width; ++col) {
          double x = _xmin + (col * (_xmax - _xmin) / _width);
          double y = _ymin + (row * (_ymax - _ymin) / _height);
          double t = (double)compute_point(x, y) / (double)_maxiter;
          int r = (int)(9 * (1 - t) * t * t * t * 255);
          int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
          int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
          vec.emplace_back(r, g, b);
        }
        {
          std::lock_guard<std::mutex> guard(_mutex);
          _matrix.data[row] = (vec);
        }
      }
    }));
  }

  for (int i = 0; i < workers.size(); ++i) {
    if (workers.at(i).joinable()) {
      workers.at(i).join();
    }
  }
}

int Mandelbrot::compute_point(double x, double y) {
  std::complex<double> z;
  std::complex<double> a(x, y);
  int iter = 0;
  while ((std::abs(z) < 4.0f) && (iter < _maxiter)) {
    z = std::pow(z, 2) + a;
    iter++;
  }

  return iter;
}

// Return the computed matrix
std::shared_ptr<Tmatrix<TColor>> Mandelbrot::get_matrix() {
  return std::make_shared<Tmatrix<TColor>>(_matrix);
}