#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include <bounds.h>
#include <functional>
#include <vector.h>
#include <cas.h>
#include <unsupported/Eigen/AutoDiff>
#include <unsupported/Eigen/NumericalDiff>

template <size_t Dimension, typename Value = double>
class Problem {
  Bounds<Dimension, Value> _bounds;
  const Expression<Dimension,Value>& _function;
//  std::function<SquareMatrix<Dimension, Value> (Vector<Dimension, Value>)> _ihessian;
public:
  Value _optimal;
  mutable size_t fcount;
  mutable size_t gcount;
  mutable size_t icount;
  //! Constructor for Problem class that represents an optimization problem.
  Problem(const double optimal, const Bounds<Dimension, Value> &bounds,
          const Expression<Dimension,Value> &function
//          const std::function<SquareMatrix<Dimension, Value> (Vector<Dimension, Value>)> &ihessian
    )
    : _optimal(optimal), _bounds(bounds), _function(function) {
    fcount = gcount = icount = 0;
  }
  Problem(const double optimal, const Bounds<Dimension, Value> &&bounds,
          const Expression<Dimension,Value> &function
//          const std::function<SquareMatrix<Dimension, Value> (Vector<Dimension, Value>)> &ihessian
    )
    : _optimal(optimal), _bounds(bounds), _function(function) {
    fcount = gcount = icount = 0;
  }
  void reset() const { fcount = gcount = icount = 0; }
  const Bounds<Dimension,Value> &bounds() const { return _bounds; }
  Value function( Vector<Dimension, Value> point ) const { fcount++; return _function(point); }
  Vector<Dimension, Value> gradient( Vector<Dimension, Value> point ) const { gcount++; return _function.grad(point); }
//  SquareMatrix<Dimension, Value> ihessian( Vector<Dimension, Value> point ) const { icount++; return _ihessian(point); }
};

#endif
