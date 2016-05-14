#ifndef __VECTOR_H_
#define __VECTOR_H_

#include <Eigen/Core>

template <size_t Dimension, typename Value = double>
using Vector = Eigen::Matrix<Value,Dimension,1>;

#endif
