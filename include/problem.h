#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include <bounds.h>
#include <functional>
#include <vector.h>
#include <unsupported/Eigen/AutoDiff>
#include <unsupported/Eigen/NumericalDiff>

template <size_t Dimension, typename Value = double>
class Problem {
  Bounds<Dimension, Value> _bounds;
  std::function<Value (Vector<Dimension, Value>)> _function;
  std::function<Vector<Dimension, Value> (Vector<Dimension, Value>)> _gradient;
  std::function<SquareMatrix<Dimension, Value> (Vector<Dimension, Value>)> _hessian;
public:
  //! Constructor for Problem class that represents an optimization problem.
  Problem(const Bounds<Dimension, Value> &bounds,
          const std::function<Value (Vector<Dimension, Value>)> &function,
          const std::function<Vector<Dimension, Value> (Vector<Dimension, Value>)> &gradient,
          const std::function<SquareMatrix<Dimension, Value> (Vector<Dimension, Value>)> &hessian)
    : _bounds(bounds), _function(function), _gradient(gradient), _hessian(hessian) {
  }
  Problem(const Bounds<Dimension, Value> &&bounds,
          const std::function<Value (Vector<Dimension, Value>)> &function,
          const std::function<Vector<Dimension, Value> (Vector<Dimension, Value>)> &gradient,
          const std::function<SquareMatrix<Dimension, Value> (Vector<Dimension, Value>)> &hessian)
    : _bounds(bounds), _function(function), _gradient(gradient), _hessian(hessian) {
  }

  const Bounds<Dimension,Value> &bounds() const { return _bounds; }
  Value function( Vector<Dimension, Value> point ) const { return _function(point); }
  Vector<Dimension, Value> gradient( Vector<Dimension, Value> point ) const { return _gradient(point); }
  SquareMatrix<Dimension, Value> hessian( Vector<Dimension, Value> point ) const { return _hessian(point); }

};

#endif
