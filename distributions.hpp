#include <random>
#include <ctime>
//#include <boost/math/distributions.hpp>



//Triangular distribution
double _Triangular(double a,double b,double c) {
   srand ( time(NULL) );
   double U = rand() / (double) RAND_MAX;
   double F = (c - a) / (b - a);
   if (U <= F)
      return a + sqrt(U * (b - a) * (c - a));
   else
      return b - sqrt((1 - U) * (b - a) * (b - c));
}

//lognormal distribution

std::random_device rd;
std::mt19937 generator(rd());
std::lognormal_distribution<double> Lognormal(0.452, 0.11);




/*
   The beta distribution is related to the gamma distribution.
   Let X be a random number drawn from Gamma(α,1) and Y from Gamma(β,1),
   where the first argument to the gamma distribution is the shape parameter.
   Then Z=X/(X+Y) has distribution Beta(α,β).
*/
double _Beta(double P, double Q, double min, double max){
   srand ( time(NULL) );
   std::random_device rd;
   std::mt19937 generator(rd());
   std::gamma_distribution<double> gamma1(1.0,P);
   std::gamma_distribution<double> gamma2(1.0,Q);
   double x = gamma1(generator);
   double y = gamma2(generator);
   double betaVal = x/(x+y);

   //linear transformation to min max interval
   betaVal = (betaVal * (max - min)) + min;

   return betaVal;
}

