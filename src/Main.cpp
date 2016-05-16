#include <iostream>
#include <vector>
#include <algorithm>

#include <problem.h>
#include <optimizer.h>

using namespace std;

#define Power pow
#define Pi 3.14159265358979323
#define E 2.7182818284590452

//! Runs all of the optimizations on a test case and prints the result.
template <size_t Dimension, typename Value = double>
void run_opts(const Problem<Dimension, Value> &problem) {

  // The optimization methods.
  Optimizer<Dimension, Value> *opts[] = {
    new GradientDescent<Dimension, Value>(10),
    new GradientDescent<Dimension, Value>(100),
    new GradientDescent<Dimension, Value>(1000),
    new MultiplePointRestartAcceleratedGradientDescent<Dimension, Value>(10, 10),
    new MultiplePointRestartAcceleratedGradientDescent<Dimension, Value>(10, 100),
    new MultiplePointRestartAcceleratedGradientDescent<Dimension, Value>(10, 1000),
    new MultiplePointRestartAcceleratedGradientDescent<Dimension, Value>(100, 10),
    new MultiplePointRestartAcceleratedGradientDescent<Dimension, Value>(100, 100),
    new MultiplePointRestartAcceleratedGradientDescent<Dimension, Value>(100, 1000),
    new MultiplePointRestartAcceleratedGradientDescent<Dimension, Value>(1000, 10),
    new MultiplePointRestartAcceleratedGradientDescent<Dimension, Value>(1000, 100),
    new MultiplePointRestartAcceleratedGradientDescent<Dimension, Value>(1000, 1000),
    new SimulatedAnnealing<Dimension, Value>(10, .1, .001),
    new SimulatedAnnealing<Dimension, Value>(10, .01, .001),
    new SimulatedAnnealing<Dimension, Value>(10, .001, .001),
    new SimulatedAnnealing<Dimension, Value>(10, .0001, .001),
    new SimulatedAnnealing<Dimension, Value>(100, .1, .001),
    new SimulatedAnnealing<Dimension, Value>(100, .01, .001),
    new SimulatedAnnealing<Dimension, Value>(100, .001, .001),
    new SimulatedAnnealing<Dimension, Value>(100, .0001, .001),
    new SimulatedAnnealing<Dimension, Value>(1000, .1, .001),
    new SimulatedAnnealing<Dimension, Value>(1000, .01, .001),
    new SimulatedAnnealing<Dimension, Value>(1000, .001, .001),
    new SimulatedAnnealing<Dimension, Value>(1000, .0001, .001),
//    new NewtonsMethod<Dimension, Value>(1, 10),
    new InteriorPointsMethod<Dimension, Value>(),
    new RandomGuessing<Dimension, Value>(100),
    new RandomGuessing<Dimension, Value>(1000),
    new RandomGuessing<Dimension, Value>(10000),
  };

  // Performs each optimization in the listed optimization methods.
  for (auto &opt : opts) {
    problem.reset();
    auto solution = opt->optimize(problem);
    printf("%s:\n  Calls:%8d Grad:%8d  IH:%8d    val:%2.7f\n", opt->getName().c_str(), problem.fcount, problem.gcount, problem.icount, problem.function(solution) );
//    cout << opt->getName() << ":\n" << "Calls:" << problem.fcount << "  Grad:" << problem.gcount << "  IH:" << problem.icount << "\n     " << problem.function(solution) << " at {" << solution.transpose() << "}" << endl;
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
  #define test_dimension 2
  #define test_value double
  //Vector<test_dimension, test_value> v(a);

  Bounds<test_dimension, test_value> test_bounds( {-5.0, -5.0}, {5.0, 5.0} );
  VarExpression<2> x2(0);
  VarExpression<2> y2(1);

  VarExpression<3> x3(0);
  VarExpression<3> y3(1);
  VarExpression<3> z3(2);


  const Expression<2,double>& test_function = 20 + E - exp((cos(2*Pi*x2) + cos(2*Pi*y2))/2.) - 20*exp(-0.2*sqrt(0.5*(x2*x2 + y2*y2)));

  // Runs the test case specified.
  Problem<test_dimension, test_value> problem(test_bounds, test_function);
  run_opts(problem);
  return 0;
}
