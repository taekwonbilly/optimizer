#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include <bounds.h>
#include <problem.h>
#include <string>

template <size_t Dimension, typename Value = double>
class Optimizer {
public:
  virtual Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) =0;
  virtual std::string getName() const = 0;
};


template <size_t Dimension, typename Value = double>
class StochasticGradientDescent: public Optimizer<Dimension, Value> {
  size_t _count;
  size_t _numRepetitions;
public:
  StochasticGradientDescent( size_t count, size_t numRepetitions ) : _count(count), _numRepetitions(numRepetitions) { }
  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override final {
    auto returnVal = problem.bounds().randomPoint();
    for (size_t i = 0; i < _count; i++) {
      auto newVal = problem.bounds().randomPoint();
      for (size_t j = 0; j < _numRepetitions; j++) {
        // TODO: Find the optimal step-size.
        auto stepSize = 1;
        newVal -= stepSize * problem.gradient(newVal);
      }
      if (problem.function(newVal) < problem.function(returnVal)) {
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
class GradientDescent: public Optimizer<Dimension, Value> {
//  size_t _numRepetitions;
  StochasticGradientDescent<Dimension, Value> _sgd;
public:
  GradientDescent( size_t numRepetitions ) : _sgd(1, numRepetitions) { }
  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override final {
    return _sgd.optimize(problem);
  }

  std::string getName() const {
    return "Gradient Descent";
  }
};

template <size_t Dimension, typename Value = double>
class SimulatedAnnealing: public Optimizer<Dimension, Value> {
 double _temp, _cooling, _ftemp;
public:
  SimulatedAnnealing( double temp, double cooling, double ftemp ) : _temp(temp), _cooling(cooling), _ftemp(ftemp) { }
  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override final {
    auto val = problem.bounds().randomPoint();
    for( double temp = _temp; temp > _ftemp; temp *= (1 - _cooling) ) {
      size_t axis = randInt( Dimension );
      auto val2 = problem.bounds().randomPoint();
      for( size_t i=0; i<Dimension; i++ ) if( i != axis ) val2[i] = val[i];
      double v2 = problem.function(val2), v1 = problem.function(val);
      double tmp = exp( -(v2-v1)/temp);
      if( tmp >= 1 ) { val = val2; continue; }
      double rd = randDouble();
//      if( tmp <= 1.0 ) {
//         printf("bad=%f, v2=%f v1=%f rd=%f temp=%f\n", tmp, v2, v1, rd, temp);
//      }
      assert( tmp <= 1.0 );
      if( rd < tmp ) { val = val2; }
    }
    return val;
  }

  std::string getName() const {
    char buffer[512];
    sprintf(buffer, "Simulated Annealing[temp=%f,cooling=%f,ftemp=%f]", _temp, _cooling, _ftemp);
    return buffer;
  }
};

template <size_t Dimension, typename Value = double>
class NewtonsMethod: public Optimizer<Dimension, Value> {
  size_t _count;
  size_t _numRepetitions;
public:
  NewtonsMethod( size_t count, size_t numRepetitions ) : _count(count), _numRepetitions(numRepetitions) { }
  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override final {
    auto returnVal = problem.bounds().randomPoint();
    for (size_t i = 0; i < _count; i++) {
      auto newVal = problem.bounds().randomPoint();
      for (size_t j = 0; j < _numRepetitions; j++) {
        newVal -= problem.ihessian(newVal) * problem.gradient(newVal);
      }
      if (problem.function(newVal) < problem.function(returnVal)) {
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

  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override final {
    return problem.bounds().randomPoint();
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
  Vector<Dimension, Value> optimize(const Problem<Dimension, Value>&  problem) override final{
    auto val = problem.bounds().randomPoint();
    for(size_t i=0; i<_count-1; i++){
      auto val2 = problem.bounds().randomPoint();
      if( problem.function( val2 ) < problem.function( val ) ) val = val2;
    }
    return val;
  }

  std::string getName() const {
    char buffer[512];
    sprintf(buffer, "Random Guessing[count=%u]", _count);
    return buffer;
  }
};

#endif
