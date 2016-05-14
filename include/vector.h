#ifndef __VECTOR_H_
#define __VECTOR_H_

#include <cassert>
#include <Eigen/Core>

template <size_t Dimension=3, typename Value = double>
class Vector : public Eigen::Matrix<Value,Dimension,1> {
public:
  Vector( std::initializer_list<Value> vals ) : Eigen::Matrix<Value,Dimension,1>(Dimension) {
    assert( vals.size() == Dimension );//, "need length of init list to equal dimension" );
    size_t i = 0;
    for( auto& a : vals ) { (*this)(i,0) = a; i++; }
  }
  Vector( Value (vals)[Dimension] ) : Eigen::Matrix<Value,Dimension,1>(Dimension) {
    for( size_t i = 0; i < Dimension; i++ ) (*this)(i,0) = vals[i];
  }

  Value& operator[](size_t idx){ return (*this)(idx,0); }
  const Value& operator[] (size_t idx) const { return (*this)(idx,0); }

};

#endif
