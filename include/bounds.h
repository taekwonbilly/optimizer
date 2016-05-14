#ifndef _BOUNDS_H_
#define _BOUNDS_H_

#include <vector.h>

template <size_t Dimension, typename Value = double>
class Bounds {
  Vector<Dimension, Value> _minimum;
  Vector<Dimension, Value> _maximum;

public:
  //! Constructor for Bounds class that checks if a Vector is in a valid range.
  Bounds(Vector<Dimension, Value> &minimum,
         Vector<Dimension, Value> &maximum)
    : _minimum(minimum), _maximum(maximum) {
  }

  //! Tests if a vector is in the valid range specified by the bounds.
  inline bool valid(const Vector<Dimension, Value> &v) const {
    for (size_t idx = 0; idx < Dimension; idx++) {
      if (v._data[idx] > _maximum._data[idx] || v._data[idx] < _minimum._data[idx]) return false;
    }
    return true;
  };
};

#endif
