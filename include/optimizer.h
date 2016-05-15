#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include <problem.h>
#include <string>

template <size_t Dimension, typename Value = double>
class Optimizer {
public:
  virtual Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) =0;
  virtual std::string getName() const = 0;
};

template <size_t Dimension, typename Value = double>
class GradientDescent: public Optimizer<Dimension, Value> {
public:
  GradientDescent( size_t numRepetitions ) : _numRepetitions(numRepetitions) { }
  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override {
    return new StochasticGradientDescent<Dimension, Value>(1, _numRepetitions)->optimize(problem)
  }

  std::string getName() const {
    return "Gradient Descent";
  }
};

template <size_t Dimension, typename Value = double>
class StochasticGradientDescent: public Optimizer<Dimension, Value> {
public:
  StochasticGradientDescent( size_t count, size_t numRepetitions ) : _count(count), _numRepetitions(numRepetitions) { }
  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override {
    auto returnVal = problem._bounds.randomPoint();
    for (size_t i = 0; i < _count; i++) {
      auto newVal = problem._bounds.randomPoint();
      for (size_t j = 0; j < _numRepetitions; j++) {
        // TODO: Find the optimal step-size.
        auto stepSize = 1;
        newVal = newVal - stepSize * problem._gradient(newVal);
      }
      if (problem._function(newVal) < problem._function(returnVal)) {
        returnVal = newVal;
      }
    }
    return returnVal;
  }

  std::string getName() const {
    return "Stochastic Gradient Descent";
  }
};

template <size_t Dimension, typename Value = double>
class SimulatedAnnealing: public Optimizer<Dimension, Value> {
public:

  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override {
    return problem._bounds.randomPoint();
  }

  std::string getName() const {
    return "Simulated Annealing";
  }
};

template <size_t Dimension, typename Value = double>
class NewtonsMethod: public Optimizer<Dimension, Value> {
public:
  NewtonsMethod( size_t count, size_t numRepetitions ) : _count(count), _numRepetitions(numRepetitions) { }
  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override {
    auto returnVal = problem._bounds.randomPoint();
    for (size_t i = 0; i < _count; i++) {
      auto newVal = problem._bounds.randomPoint();
      for (size_t j = 0; j < _numRepetitions; j++) {
        newVal = newVal - problem._function(newVal) / problem._gradient(newVal);
      }
      if (problem._function(newVal) < problem._function(returnVal)) {
        returnVal = newVal;
      }
    }
    return returnVal;
  }

public:
  std::string getName() const {
    return "Newton's Method";
  }
};

template <size_t Dimension, typename Value = double>
class InteriorPointsMethod: public Optimizer<Dimension, Value> {
public:

  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override {
    return problem._bounds.randomPoint();
  }

  std::string getName() const {
    return "Interior Points Method";
  }
};

template <size_t Dimension, typename Value = double>
class RandomGuessing: public Optimizer<Dimension, Value> {
 size_t _count;
public:
  RandomGuessing( size_t count ) : _count(count) { }
  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override {
    auto val = problem._bounds.randomPoint();
    for(size_t i=0; i<_count-1; i++){
      auto val2 = problem._bounds.randomPoint();
      if( problem._function( val2 ) < problem._function( val ) ) val = val2;
    }
    return val;
  }

  std::string getName() const {
    return "Random Guessing";
  }
};

#endif
