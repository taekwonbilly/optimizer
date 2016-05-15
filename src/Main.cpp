#include <iostream>
#include <vector>
#include <algorithm>

#include <problem.h>
#include <optimizer.h>

using namespace std;

//! Runs all of the optimizations on a test case and prints the result.
template <size_t Dimension, typename Value = double>
void run_opts(const Problem<Dimension, Value> &problem) {

  // The optimization methods.
  Optimizer<Dimension, Value> *opts[] = {
    new GradientDescent<Dimension, Value>(10),
    new MultiplePointRestartAcceleratedGradientDescent<Dimension, Value>(10, 10),
    new SimulatedAnnealing<Dimension, Value>(),
    new NewtonsMethod<Dimension, Value>(1, 10),
    new InteriorPointsMethod<Dimension, Value>(),
    new RandomGuessing<Dimension, Value>(100),
    new RandomGuessing<Dimension, Value>(1000),
    new RandomGuessing<Dimension, Value>(10000),
  };

  // Performs each optimization in the listed optimization methods.
  for (auto &opt : opts) {
    auto solution = opt->optimize(problem);
    cout << opt->getName() << " " << problem.function(solution) << " at {" << solution.transpose() << "}" << endl;
  }
}

/*
In[53]:= outputC[x_] :=
 StringReplace[If[ListQ[x],
   "{" <> StringRiffle[Map[outputC, x], ", "] <> "}",
   ToString[CForm[x /. {a_^2 -> HoldForm[a*a]}]]
   ], {"x" -> "v[0]", "y" -> "v[1]", "z" -> "v[2]"}]

In[17]:= Clear[x]; Clear[y]; Clear[z];

In[56]:= out = (x - 0.3)^2 + 3 (y - 0.5)^2 + 3 (z - 0.7)^2;

In[59]:= outputC[out]

Out[59]= "(-0.3 + v[0])*(-0.3 + v[0]) + 3*((-0.5 + v[1])*(-0.5 + \
v[1])) + 3*((-0.7 + v[2])*(-0.7 + v[2]))"

In[55]:= outputC[Grad[out, {x, y, z}]]

Out[55]= "{2*(-0.3 + v[0]), 6*(-0.5 + v[1]), 6*(-0.7 + v[2])}"

In[58]:= outputC[D[out, {{x, y, z}, 2}]]

Out[58]= "{{2, 0, 0}, {0, 6, 0}, {0, 0, 6}}"
*/

int main (int argc, char** argv) {
  // Testing setup.
  #define test_dimension 3
  #define test_value double
  //Vector<test_dimension, test_value> v(a);
  Bounds<test_dimension, test_value> test_bounds( Vector<>({0.0, 0.0, 0.0}), Vector<>({1.0, 1.0, 1.0}) );
  auto test_function = [](Vector<test_dimension, test_value> v) -> test_value {
    return (-0.3 + v[0])*(-0.3 + v[0]) + 3*((-0.5 + v[1])*(-0.5 + v[1])) + 3*((-0.7 + v[2])*(-0.7 + v[2]));
  };
  auto test_gradient = [](Vector<test_dimension, test_value> v) -> Vector<test_dimension, test_value> {
    return {2*(-0.3 + v[0]), 6*(-0.5 + v[1]), 6*(-0.7 + v[2])};
  };
  auto test_hessian = [](Vector<test_dimension, test_value> v) -> SquareMatrix<test_dimension, test_value> {
    return {{2, 0, 0}, {0, 6, 0}, {0, 0, 6}};
  };
  auto test_ihessian = [](Vector<test_dimension, test_value> v) -> SquareMatrix<test_dimension, test_value> {
    return {{0.5, 0, 0}, {0, 0.16666666666666666, 0}, {0, 0, \
0.16666666666666666}};
  };

  // Runs the test case specified.
  Problem<3, double> problem(test_bounds, test_function, test_gradient, test_hessian, test_ihessian);
  run_opts(problem);
  return 0;
}
