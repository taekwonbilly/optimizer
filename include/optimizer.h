#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include <problem.h>

template <size_t Dimension, typename Value = double>
class Optimizer {
  virtual Value (&optimize( Problem<Dimension,Value> problem ))[Dimension] = 0;  
};


#endif
