#include <stdio.h>
#include <TXLib.h>
#include <math.h>

#include "Solve_Equation.h"

#define Assert(condition) \
        $r;\
        if(condition)\
        {printf("ERROR in line %d in \n%s \nFound (%s).\n", __LINE__, __FILE__, #condition);}

const double EPS = 0.000001;

bool is_equal(double x, double y)
{
    Assert(isinf(x));
    Assert(isinf(y));

    return fabs(x - y) < EPS;
}

int solve_linear_eq(double b, double c, double* ptr_root)
{
    Assert(isinf(b));
    Assert(isinf(c));

    Assert(ptr_root == NULL);

    if(is_equal(b, 0))
    {
        if(is_equal(c, 0))
            return INFINITY_SOLUTIONS;
        else
            return NO_SOLUTIONS;
    }
    else
    {
        if(is_equal(c, 0))
        {
            *ptr_root = 0;
        }
        else
        {
            *ptr_root = -c / b;
        }
        return ONE_SOLUTION;
    }
}

int solve_square_eq(double a, double b, double c, double* ptr_root1, double* ptr_root2)
{
    Assert(isinf(a));
    Assert(isinf(b));
    Assert(isinf(c));

    Assert(ptr_root1 == NULL);
    Assert(ptr_root2 == NULL);

    if (is_equal(c, 0))
    {
        if (is_equal(b, 0))
        {
            *ptr_root1 = 0;
            return ONE_SOLUTION;
        }

        Assert(is_equal(a, 0));

        *ptr_root1 = 0;
        *ptr_root2 = -b / a;

        return TWO_SOLUTIONS;
    }

    double discrim = b * b - 4 * a * c;

    if (is_equal(discrim, 0))
    {
        *ptr_root1 = -b / (2 * a);
        return ONE_SOLUTION;
    }
    else if (discrim < 0)
    {
        return NO_SOLUTIONS;
    }
    else
    {
        double sqrt_discrim = sqrt(discrim);

        *ptr_root1 = ( sqrt_discrim - b) / (2 * a);
        *ptr_root2 = (-sqrt_discrim - b) / (2 * a);
        return TWO_SOLUTIONS;
    }
}

int solve_equation(double a, double b, double c, double *ptr_root1, double *ptr_root2)
{
    Assert(isinf(a));
    Assert(isinf(b));
    Assert(isinf(c));

    Assert(ptr_root1 == NULL);
    Assert(ptr_root2 == NULL);

    if (is_equal(a, 0))
    {
        return solve_linear_eq(b, c, ptr_root1);
    }

    return solve_square_eq(a, b, c, ptr_root1, ptr_root2);
}

void print_solutions(int num_solutions, double root1, double root2)
{
    $y;
    switch(num_solutions)
    {
        case INFINITY_SOLUTIONS:
            printf("infinity solutions\n\n");
            break;

        case NO_SOLUTIONS:
            printf("no solutions\n\n");
            break;

        case ONE_SOLUTION:
            printf("one solution: x1=%.10lg\n\n", root1);
            break;

        case TWO_SOLUTIONS:
            printf("two solutions: x1=%.10lg and x2=%.10lg\n\n", root1, root2);
            break;

        default:
            printf("ERROR: unexpected number of solutions\n\n");
    }
}
