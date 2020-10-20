#include "newtonsmethod.h"

#include <cmath>
#include <stdexcept>

double NewtonsMethod::compute(
    const std::function<double(double)>& f,
    const std::function<double(double)>& fPrime,
    double guess,
    double maxiterations,
    double threshold)
{
  // Use newtons method to solve an equation.
  // f: function
  // fprime: function derivative
  // guess: initial value guess
  // optional maxIterations: maximum iterations allowed. Error will
  //      be thrown if this limit is reached
  // optional threshold: Once x-f/f' is less than threshold, the
  //      solution is considered converged and the value is returned

  double value;
  double valuePrime;

  double x = guess;
  bool converged = false;

  for (auto i = 1; i <= maxiterations; ++i)
  {
    value = f(x);
    valuePrime = fPrime(x);
    x = x - value / valuePrime;
    if (std::abs(value / valuePrime) <= threshold)
    {
      converged = true;
      break;
    }
  }

  if (!converged)
    throw std::runtime_error("Newton's method did not converge.");
  else
    return x;
}