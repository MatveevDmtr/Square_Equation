#ifndef SOLVE_EQUATION_H_INCLUDED
#define SOLVE_EQUATION_H_INCLUDED

int solve_linear_eq(double b, double c, double* ptr_root);

int solve_square_eq(double a, double b, double c, double* ptr_root1, double* ptr_root2);

int solve_equation(double a, double b, double c, double *ptr_root1, double *ptr_root2);

void print_solutions(int num_solutions, double root1, double root2);

bool is_equal(double x, double y);

enum NUM_SOLUTIONS
{
    NO_SOLUTIONS = 0,
    INFINITY_SOLUTIONS = -1,
    ONE_SOLUTION = 1,
    TWO_SOLUTIONS = 2
};


#endif // SOLVE_EQUATION_H_INCLUDED
