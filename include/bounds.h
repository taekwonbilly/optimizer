#ifndef _BOUNDS_H_
#define _BOUNDS_H_

#include <vector.h>

double randDouble() { return (double)rand() / RAND_MAX; }
size_t randInt( size_t max ) { size_t mm = RAND_MAX / max * max; size_t tmp; do { tmp = rand(); } while( tmp >= mm ); return tmp % max; }

template <size_t Dimension, typename Value = double>
class Bounds {
  Vector<Dimension, Value> _minimum;
  Vector<Dimension, Value> _maximum;

public:
  //! Constructor for Bounds class that checks if a Vector is in a valid range.
  Bounds(const Vector<Dimension, Value> &minimum,
         const Vector<Dimension, Value> &maximum)
    : _minimum(minimum), _maximum(maximum) {
  }

  Bounds(const Vector<Dimension, Value> &&minimum,
         const Vector<Dimension, Value> &&maximum)
    : _minimum(minimum), _maximum(maximum) {
  }

  //! Tests if a vector is in the valid range specified by the bounds.
  inline bool valid(const Vector<Dimension, Value> &v) const {
    for (size_t idx = 0; idx < Dimension; idx++) {
      if (v._data[idx] > _maximum._data[idx] || v._data[idx] < _minimum._data[idx]) return false;
    }
    return true;
  };
  inline Vector<Dimension,Value> randomPoint() const { 
    Value vals[Dimension];
    for( size_t i=0; i<Dimension; i++ ) {
      double d = randDouble();
      vals[i] = _minimum[i] + d * (_maximum[i] - _minimum[i]);
    }
    return Vector<Dimension,Value>( vals );
  }
};

#endif
