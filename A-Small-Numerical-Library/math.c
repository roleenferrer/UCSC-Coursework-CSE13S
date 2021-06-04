#include <getopt.h>
#include <math.h>
#include <stdio.h>

#define OPTIONS "sctea"
#define EPSILON 0.000000001

// Sin Function
// This function will print the results of the Pade approximation for Sin.
// Variables:
// pi: Holds the current iteration of pi in the domain [-2pi,2pi]
// pi_squared: Holds pi * pi
// answer: Holds the current double from the Pade approximation
double Sin(double pi) {
  double answer;
  double pi_squared = pi * pi;
  answer = (pi
               * ((pi_squared * (52785432 - 479249 * pi_squared) - 1640635920)
                       * pi_squared
                   + 11511339840))
           / (((18361 * pi_squared + 3177720) * pi_squared + 277920720)
                   * pi_squared
               + 11511339840);
  return answer;
}

// Cos Function
// This function will print the results of the Pade approximation for Cos.
// Variables:
// pi: Holds the current iteration of pi in the domain [-2pi,2pi]
// pi_squared: Holds pi * pi
// answer: Holds the current double from the Pade approximation
double Cos(double pi) {
  double answer;
  double pi_squared = pi * pi;
  answer
      = ((pi_squared * (1075032 - 14615 * pi_squared) - 18471600) * pi_squared
            + 39251520)
        / (((127 * pi_squared + 16632) * pi_squared + 1154160) * pi_squared
            + 39251520);
  return answer;
}

// Tan Function
// This function will print the results of the Pade approximation for Tan.
// Variables:
// pi: Holds the current iteration of pi in the domain [-pi/3,pi/3]
// pi_squared: Holds pi * pi
// answer: Holds the current double from the Pade approximation
double Tan(double pi) {
  double answer;
  double pi_squared = pi * pi;
  answer = (pi
               * ((pi_squared * ((pi_squared - 990) * pi_squared + 135135)
                      - 4729725)
                       * pi_squared
                   + 34459425))
           / ((pi_squared * ((45 * pi_squared - 13860) * pi_squared + 945945)
                  - 16216200)
                   * pi_squared
               + 34459425);
  return answer;
}

// Exponential Function
// This function will print the Taylor series approximation for the exponential
// function e^x.
// Variables:
// term: Holds the current term in the iteration
// sum: Holds the sum of the current iteration of x.
// k: For each iteration k in the Taylor Series, the approximation will become more
//    accurate
double Exp(double x) {
  long double term = 1.0;
  long double sum = term;
  for (long double k = 1.0; term > EPSILON; k += 1.0) {
    // This loop will continue until the current term is less than EPSILON (10^-9)
    term = x / k * term;
    sum += term;
  }
  return sum;
}

// Main Function
// Main is used primarily to take the input command when the user types
// a certain letter corresponding to the function they want to run.
// Calling a certain command will call the function and print statements.
// These commands are mutually exclusive, meaning the user is able to
// only one command at a time.
int main(int argc, char **argv) {
  int c = 0;
  c = getopt(argc, argv, OPTIONS);

  double pi;
  double answer;

  switch (c) {
  case 's': // Sin
    printf("%s\t %2s\t %15s\t %10s\n", "x", "Sin", "Library", "Difference");
    printf("%s\t %2s\t %15s\t %10s\n", "-", "---", "-------", "----------");
    for (double x = -2 * M_PI; x <= 2 * M_PI + M_PI / 16; x = x + M_PI / 16) {
      pi = fmod(x, 2 * M_PI);
      answer = Sin(pi);

      double actual;
      actual = sin(pi);

      printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, answer, actual,
          answer - actual);
    }
    break;
  case 'c': // Cos
    printf("%s\t %2s\t %15s\t %10s\n", "x", "Cos", "Library", "Difference");
    printf("%s\t %2s\t %15s\t %10s\n", "-", "---", "-------", "----------");
    for (double x = -2 * M_PI; x < 2 * M_PI + M_PI / 16; x = x + M_PI / 16) {
      pi = fmod(x, 2 * M_PI);
      answer = Cos(pi);

      double actual;
      actual = cos(pi);

      printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, answer, actual,
          answer - actual);
    }
    break;
  case 't': // Tan
    printf("%s\t %2s\t %15s\t %10s\n", "x", "Tan", "Library", "Difference");
    printf("%s\t %2s\t %15s\t %10s\n", "-", "---", "-------", "----------");
    for (double x = -M_PI / 3; x <= M_PI / 3; x = x + M_PI / 16) {
      answer = Tan(x);

      double actual;
      actual = tan(x);

      printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, answer, actual,
          answer - actual);
    }
    break;
  case 'e': // Exp
    printf("%s\t %2s\t %15s\t %10s\n", "x", "Exp", "Library", "Difference");
    printf("%s\t %2s\t %15s\t %10s\n", "-", "---", "-------", "----------");
    for (double x = 0.0; x <= 9.0;
         x += 0.1) { // Takes iterations from [0,9] in 0.1 steps
      answer = Exp(x);

      double actual;
      actual = exp(x);

      printf("% 6.4lf\t% 10.8f\t% 10.8lf\t% 12.10lf\n", x, answer, actual,
          answer - actual);
    }
    break;
  case 'a': // All
    printf("%s\t %2s\t %15s\t %10s\n", "x", "Sin", "Library", "Difference");
    printf("%s\t %2s\t %15s\t %10s\n", "-", "---", "-------", "----------");
    for (double x = -2 * M_PI; x <= 2 * M_PI + M_PI / 16; x = x + M_PI / 16) {
      pi = fmod(x, 2 * M_PI);
      answer = Sin(pi);

      double actual;
      actual = sin(pi);

      printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, answer, actual,
          answer - actual);
    }

    printf("%s\t %2s\t %15s\t %10s\n", "x", "Cos", "Library", "Difference");
    printf("%s\t %2s\t %15s\t %10s\n", "-", "---", "-------", "----------");
    for (double x = -2 * M_PI; x < 2 * M_PI + M_PI / 16; x = x + M_PI / 16) {
      pi = fmod(x, 2 * M_PI);
      answer = Cos(pi);

      double actual;
      actual = cos(pi);

      printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, answer, actual,
          answer - actual);
    }

    printf("%s\t %2s\t %15s\t %10s\n", "x", "Tan", "Library", "Difference");
    printf("%s\t %2s\t %15s\t %10s\n", "-", "---", "-------", "----------");
    for (double x = -M_PI / 3; x <= M_PI / 3; x = x + M_PI / 16) {
      answer = Tan(x);

      double actual;
      actual = tan(x);

      printf("% 6.4lf\t% 10.8lf\t% 10.8lf\t% 12.10lf\n", x, answer, actual,
          answer - actual);
    }

    printf("%s\t %2s\t %15s\t %10s\n", "x", "Exp", "Library", "Difference");
    printf("%s\t %2s\t %15s\t %10s\n", "-", "---", "-------", "----------");
    for (double x = 0.0; x <= 9.0;
         x += 0.1) { // Takes iterations from [0,9] in 0.1 steps
      answer = Exp(x);

      double actual;
      actual = exp(x);

      printf("% 6.4lf\t% 10.8f\t% 10.8lf\t% 12.10lf\n", x, answer, actual,
          answer - actual);
    }
    break;
  }
  return 0;
}
