#include<iostream>

template<class Expr>
void evaluate(Expr<Expr> e, double start, double end)
{
  const double step = 1.0;
  for(double i=start; i<end; i+=step)
    std::cout << e(i) << std::endl;
}

int main()
{
  Expr<ExprIdentity> x; // placeholder
  evaluate(x/(1.0 + x), 0.0, 10.0);
}
