#ifndef __VECTOR_H_
#define __VECTOR_H_

#include <algorithm>

template <size_t Dimension, typename Value = double>
class Vector {

  Value _data[Dimension];
  
public:
  //! Constructor for Vector class that represents an point in space.
  Vector(Value data[Dimension]) {
    std::copy(data, data+Dimension, _data);
  }

  inline Vector<Dimension, Value>& operator +=(const Vector &v2) {
    for (size_t i = 0; i < Dimension; i++) {
      _data[i] += v2._data[i];
    }
    return *this;
  }

  inline Value& operator[](const size_t idx) { return _data[idx]; }

  inline Vector<Dimension, Value>& operator -=(const Vector &v2) {
    for (size_t i = 0; i < Dimension; i++) {
      _data[i] -= v2._data[i];
    }
    return *this;
  }

  template <typename T2>
  inline Vector<Dimension, Value>& operator *=(const T2 & v2) {
    for (size_t i = 0; i < Dimension; i++) {
      _data[i] *= v2;
    }
    return *this;
  }

  template <typename T2>
  inline Vector<Dimension, Value>& operator /=(const T2 & v2) {
    for (size_t i = 0; i < Dimension; i++) {
      _data[i] *= v2;
    }
    return *this;
  }

  inline void operator +(const Vector &v2) {
    Vector v1 = *this;
    return v1 += v2;
  }

  inline void operator -(const Vector &v2) {
    Vector v1 = *this;
    return v1 -= v2;
  }

  template <typename T2>
  inline void operator *(const T2 &v2) {
    Vector v1 = *this;
    return v1 *= v2;
  }

  template <typename T2>
  inline void operator /(const T2 &v2) {
    Vector v1 = *this;
    return v1 /= v2;
  }
};

#endif
