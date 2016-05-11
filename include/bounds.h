#ifndef _BOUNDS_H_
#define _BOUNDS_H_

#include <vector.h>

template <size_t Dimension, typename Value = double>
class Bounds {
  Vector<Dimension, Value> minimum;
  Vector<Dimension, Value> maximum;

  //! Tests if a vector is in bounds
  inline bool valid(const Vector<Dimension, Value> &v) const {
    for (size_t idx = 0; idx < Dimension; idx++) {
      if (v._data[idx] > maximum._data[idx] || v._data[idx] < minimum._data[idx]) return false;
    }
    return true;
  };

};

#endif
