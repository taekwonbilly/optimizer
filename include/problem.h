#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include <bounds.h>
#include <functional>
#include <vector.h>

template <size_t Dimension, typename Value = double>
class Problem {
  Bounds<Dimension, Value> _bounds;
  std::function<Value (Vector<Dimension, Value>)> _function;
  std::function<Vector<Dimension, Value> (Vector<Dimension, Value>)> _gradient;

public:
  //! Constructor for Problem class that represents an optimization problem.
  Problem(const Bounds<Dimension, Value> &bounds,
          const std::function<Value (Vector<Dimension, Value>)> &function,
          const std::function<Vector<Dimension, Value> (Vector<Dimension, Value>)> &gradient)
    : _bounds(bounds), _function(function), _gradient(gradient) {
  }
  Problem(const Bounds<Dimension, Value> &&bounds,
          const std::function<Value (Vector<Dimension, Value>)> &function,
          const std::function<Vector<Dimension, Value> (Vector<Dimension, Value>)> &gradient)
    : _bounds(bounds), _function(function), _gradient(gradient) {
  }

  const Bounds<Dimension,Value> &bounds() const { return _bounds; }
  Value function( Vector<Dimension, Value> point ) const { return _function(point); }
  Vector<Dimension, Value> gradient( Vector<Dimension, Value> point ) const { return _gradient(point); }

};

#endif
