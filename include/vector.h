#ifndef __VECTOR_H_
#define __VECTOR_H_

#include <cassert>
#include <Eigen/Core>

template <size_t Dimension=3, typename Value = double>
class Vector : public Eigen::Matrix<Value,Dimension,1> {
public:
  template<typename T>
  Vector( const T& sup ) : Eigen::Matrix<double,Dimension,1>( sup ) { }

  template< typename T>
  const Vector& operator=( const T& op ){ Eigen::Matrix<double,Dimension,1>::operator=(op); return *this; }
  Vector( std::initializer_list<Value> vals ) : Eigen::Matrix<Value,Dimension,1>(Dimension) {
    assert( vals.size() == Dimension );//, "need length of init list to equal dimension" );
    size_t i = 0;
    for( auto& a : vals ) { (*this)(i,0) = a; i++; }
  }
  Vector( size_t oneAt, int ) : Eigen::Matrix<Value,Dimension,1>(Dimension) {
    for( size_t i = 0; i < Dimension; i++ ) { (*this)(i,0) = (i==oneAt)?1:0; }
  }

  Vector( Value (vals)[Dimension] ) : Eigen::Matrix<Value,Dimension,1>(Dimension) {
    for( size_t i = 0; i < Dimension; i++ ) (*this)(i,0) = vals[i];
  }

  Value& operator[](size_t idx){ return (*this)(idx,0); }
  const Value& operator[] (size_t idx) const { return (*this)(idx,0); }
};

template <size_t Dimension=3, typename Value = double>
class SquareMatrix : public Eigen::Matrix<Value,Dimension,Dimension> {
public:
  SquareMatrix( std::initializer_list<std::initializer_list<Value>> vals ) : Eigen::Matrix<Value,Dimension,Dimension>(Dimension,Dimension) {
    assert( vals.size() == Dimension );//, "need length of init list to equal dimension" );
    size_t i = 0;
    for( auto& a : vals ) {
      size_t j = 0;
      assert( a.size() == Dimension );
      for( auto& b : a ) { (*this)(i,j) = b; j++; }
      i++;
    }
  }

  SquareMatrix( Value (vals)[Dimension][Dimension] ) : Eigen::Matrix<Value,Dimension,1>(Dimension,Dimension) {
    for( size_t i = 0; i < Dimension; i++ )
    for( size_t j = 0; j < Dimension; j++ )
      (*this)(i,j) = vals[i][j];
  }

};

#endif
