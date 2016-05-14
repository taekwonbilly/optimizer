#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include <problem.h>
#include <string>

template <size_t Dimension, typename Value = double>
class Optimizer {
  virtual Vector<Dimension, Value> optimize(Problem<Dimension, Value> problem) = 0;
  virtual std::string getName() const = 0;
};

template <size_t Dimension, typename Value = double>
class GradientDescent: Optimizer<Dimension, Value> {

  Vector<Dimension, Value> optimize(Problem<Dimension, Value> problem) {

  }

  std::string getName() const {
    return "Gradient Descent";
  }
};

template <size_t Dimension, typename Value = double>
class StochasticGradientDescent: Optimizer<Dimension, Value> {

  Vector<Dimension, Value> optimize(Problem<Dimension, Value> problem) {

  }

  std::string getName() const {
    return "Stochastic Gradient Descent";
  }
};

template <size_t Dimension, typename Value = double>
class SimulatedAnnealing: Optimizer<Dimension, Value> {

  Vector<Dimension, Value> optimize(Problem<Dimension, Value> problem) {

  }

  std::string getName() const {
    return "Simulated Annealing";
  }
};

template <size_t Dimension, typename Value = double>
class NewtonsMethod: Optimizer<Dimension, Value> {

  Vector<Dimension, Value> optimize(Problem<Dimension, Value> problem) {

  }

  std::string getName() const {
    return "Newton's Method";
  }
};

template <size_t Dimension, typename Value = double>
class InteriorPointsMethod: Optimizer<Dimension, Value> {

  Vector<Dimension, Value> optimize(Problem<Dimension, Value> problem) {

  }

  std::string getName() const {
    return "Interior Points Method";
  }
};

template <size_t Dimension, typename Value = double>
class RandomGuessing: Optimizer<Dimension, Value> {

  Vector<Dimension, Value> optimize(Problem<Dimension, Value> problem) {

  }

  std::string getName() const {
    return "Random Guessing";
  }
};

#endif
