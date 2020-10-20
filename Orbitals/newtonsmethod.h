#ifndef NEWTONSMETHOD_H
#define NEWTONSMETHOD_H

#include <functional>

class NewtonsMethod
{
public:
  static double compute(
      const std::function<double(double)>& f,
      const std::function<double(double)>& fPrime,
      double guess,
      double maxIterations = 1000,
      double threshold = 0.0001);
};

#endif // NEWTONSMETHOD_H