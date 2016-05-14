#ifndef __VECTOR_H_
#define __VECTOR_H_

#include <Eigen/Core>

template <size_t Dimension, typename Value = double>
class Vector {
  Eigen::Matrix<Value,Dimension,1> _data;

public:
  inline Vector( const Eigen::Matrix<Value,Dimension,1> &mat ) : _data( mat ) { }

  inline Vector( Value (vals)[Dimension] ) : _data( Dimension ) {
    for( size_t i=0; i<Dimension; i++ ) {
      _data(i,0) = vals[i];
    }
  }

  inline Vector<Dimension, Value>& operator +=(const Vector &v2) {
    _data += v2._data;
    return *this;
  }
  
  inline Value& operator[](const size_t idx){ return _data(idx,0); }

  inline Vector<Dimension, Value>& operator -=(const Vector &v2) {
    _data -= v2._data;
    return *this;
  }

  template < typename T2 >
  inline Vector<Dimension, Value>& operator *=(const T2 & v2) {
    _data *= v2;
    return *this;
  }

  template < typename T2 >
  inline Vector<Dimension, Value>& operator /=(const T2 & v2) {
     _data /= v2;
   return *this;
  }

  inline Vector<Dimension,Value> operator +(const Vector &v2) {
    return Vector<Dimension,Value>( _data + v2._data );
  }

  inline void operator -(const Vector &v2) {
    return Vector<Dimension,Value>( _data - v2._data );
  }

  template < typename T2 >
  inline void operator *(const T2 &v2) {
    return Vector<Dimension,Value>( _data * v2 );
  }

  template < typename T2 >
  inline void operator /(const T2 &v2) {
    return Vector<Dimension,Value>( _data / v2 );
  }
};

#endif
