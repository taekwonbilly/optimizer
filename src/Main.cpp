#include <iostream>
#include <vector>
#include <algorithm>

#include <problem.h>
#include <optimizer.h>

using namespace std;

//! Runs all of the optimizations on a test case and prints the result.
template <size_t Dimension, typename Value = double>
void run_opts(Problem<Dimension, Value> problem) {

  // The optimization methods.
  Optimizer<Dimension, Value> *opts[] = {
    new GradientDescent<Dimension, Value>(),
    new StochasticGradientDescent<Dimension, Value>(),
    new SimulatedAnnealing<Dimension, Value>(),
    new NewtonsMethod<Dimension, Value>(),
    new InteriorPointsMethod<Dimension, Value>(),
    new RandomGuessing<Dimension, Value>(),
  };

  // Performs each optimization in the listed optimization methods.
  for (auto &opt : opts) {
    auto solution = opt->optimize(problem);
    cout << opt->getName() << " " << problem._function(solution) << endl;
  }
}

int main (int argc, char** argv) {

  // Testing setup.
  #define test_dimension 3
  #define test_value double
  double z[3] = {0.0, 0.0, 0.0};
  double ones[3] = {1.0, 1.0, 1.0};
  //Vector<test_dimension, test_value> v(a);
  auto test_bounds = new Bounds<test_dimension, test_value>(Vector<test_dimension, test_value>(z), Vector<test_dimension, test_value>(ones));
  auto test_function = [](Vector<test_dimension, test_value> v) -> test_value {
    return (v[0] - 0.3) * (v[0] - 0.3) + 3 * (v[1] - 0.5) * (v[1] - 0.5) + 3 * (v[2] - 0.7) * (v[2] - 0.7);
  };
  auto test_gradient = [](Vector<test_dimension, test_value> v) -> Vector<test_dimension, test_value> {
    return {2 * v[0] - 0.6, 6 * v[1] - 3, 6 * v[2] - 4.2};
  };

  // Runs the test case specified.
  run_opts(new Problem<3, double>(test_bounds, test_function, test_gradient))
  return 0;
}
