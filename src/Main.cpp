#include <iostream>
#include <vector>
#include <algorithm>

#include <chrono>

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
  Optimizer<Dimension, Value> *opts[8 + 7*7*7] = { 0 };
  for( int i=0; i<4; i++) opts[0+i] = new GradientDescent<Dimension, Value>(100*(2<<i));

  for( int i=0; i<4; i++) opts[4+i] = new RandomGuessing<Dimension, Value>(100*(2<<i));

  for( int i=0; i<7; i++) 
  for( int j=0; j<7; j++) 
  for( int k=0; k<7; k++) 
opts[8+7*7*i+7*j+k] = new SimulatedAnnealing<Dimension, Value>(10*(2<<i), .1/(2<<j), .001/(2<<k) );

  // Performs each optimization in the listed optimization methods.
  for (auto &opt : opts) {
  printf("%s %s:\n", problem._name.c_str(), opt->getName().c_str() );
  size_t f = 0, g = 0, t = 0; double lg = 0;
  size_t NUM = 5;
  for( int i=0; i<NUM; i++)
{
    problem.reset();
auto begin = std::chrono::high_resolution_clock::now();
    auto solution = opt->optimize(problem);
auto end = std::chrono::high_resolution_clock::now();
    f += problem.fcount;
    g += problem.gcount;
    lg += log( problem.function(solution) - problem._optimal);
    t += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
  }
    f/=NUM;
    g/=NUM;
    lg/=NUM;
    t/=NUM;
    printf("{% 8d,% 8d, % 5.7f, % 16llu}\n", f, g, lg, t );
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

  VarExpression<2> x2(0);
  VarExpression<2> y2(1);

  VarExpression<3> x3(0);
  VarExpression<3> y3(1);
  VarExpression<3> z3(2);

  // Runs the test case specified.
  Problem<test_dimension, test_value> problems[] = {
    {"Ackley's Function", 0, {{-5.0, -5.0}, {5.0, 5.0}}, 20 + E - exp((cos(2*Pi*x2) + cos(2*Pi*y2))/2.) - 20*exp(-0.2*sqrt(0.5*(x2*x2 + y2*y2)))},
    {"Rosenbrock Function", 0, {{-2.0, 2.0}, {-1.0, 3.0}}, 100 * (y2 - x2 * x2) * (y2 - x2 * x2) + (x2 - 1) * (x2 - 1)},
    {"Sphere Function", 0, {{-2.0, 2.0}, {-2.0, 2.0}}, x2 * x2 + y2 * y2},
    {"Beale's Function", 0, {{-4.0, 4.0}, {-4.0, 4.0}}, (1.5 - x2 + x2 * y2) * (1.5 - x2 + x2 * y2) + (2.25 - x2 + x2 * y2 * y2) * (2.25 - x2 + x2 * y2 * y2) + (2.625 - x2 + x2 * y2 * y2 * y2) * (2.625 - x2 + x2 * y2 * y2 * y2)},
    {"Easom Function", -1, {{-5.0, 5.0}, {-5.0, 5.0}}, -cos(x2) * cos(y2) * exp(-((x2 - Pi) * (x2 - Pi) + (y2 - Pi) * (y2 - Pi)))},
    {"Eggholder Function", -959.6407, {{-400.0, 400.0}, {-400.0, 400.0}}, -(y2 + 47) * sin(sqrt(abs(x2 / 2 + y2 + 47))) - x2 * sin(sqrt(abs(x2 - y2 - 47)))},
    {"Holder Table Function", -19.2085, {{-5.0, 5.0}, {-5.0, 5.0}}, -abs(sin(x2) * cos(y2) * exp(abs(1 - sqrt(x2 * x2 + y2 * y2) / Pi)))}
  };
  for (auto &p : problems) {
    run_opts(p);
  }
  return 0;
}
