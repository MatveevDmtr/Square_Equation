#include <stdio.h>
#include <TXLib.h>

#include "Testing_System.h"
#include "Solve_Equation.h"

#define Assert(condition) \
        $r;\
        if(condition)\
        {printf("ERROR in line %d in \n%s \nFound (%s).\n", __LINE__, __FILE__, #condition);}


int test_solving_eq()
{
    FILE* file_with_tests = fopen("file_with_tests_solve_equation.txt", "r");

    if(file_with_tests == NULL)
    {
        $r;
        printf("File not found\n");
        $d;
    }
    else
    {
        int num_current_test = 1;
        int tests_passed = 0;

        while (!feof(file_with_tests))
        {
            if(single_test_of_eq(file_with_tests, num_current_test))
            {
                tests_passed += 1;
            }
            num_current_test++;
        }

        $y;
        printf("\n%d/%d tests passed.\n", tests_passed, num_current_test - 1);

        fclose(file_with_tests);
    }

    return 0;
}


bool single_test_of_eq(FILE* file, int test_num)
{
    double a = 0,
           b = 0,
           c = 0;

    double root1 = 0,
           root2 = 0;

    double right_root1 = 0,
           right_root2 = 0;

    int right_num_solutions = 0;
    if (fscanf(file, "%lg %lg %lg %d %lg %lg",
           &a, &b, &c, &right_num_solutions, &right_root1, &right_root2) != 6)
    {
        $r;
        printf("Test %d failed: error in test file detected. \n", test_num);
        $d;
        int sym;
        while (!feof(file))
        {
            sym = fgetc(file);
            if (sym == '\n')
                {
                printf("left cause of new_line - ");
                break;
                }
            printf("sym: %c\n", sym);
        }
        return false;
    }

    int num_solutions = solve_equation(a, b, c, &root1, &root2);

    if (num_solutions != right_num_solutions)
    {
        $r;
        printf("Test %d failed: incorrect number of solutions. \n"
               "Expected %d solutions, found %d. \n"
               "Expected %lg and %lg, found %lg and %lg.",
               test_num, right_num_solutions, num_solutions, right_root1, right_root2, root1, root2);
    } // sort roots
    else if (!(is_equal(root1, right_root1) &&
               is_equal(root2, right_root2)) &&
             !(is_equal(root1, right_root2) &&
               is_equal(root2, right_root1)))
    {
        $r;
        printf("Test %d failed: incorrect solutions. \n"
               "Expected %lg and %lg, found %lg and %lg.\n",
                test_num, right_root1, right_root2, root1, root2);
        $d;
    }
    else
    {
        $g;
        printf("Test %d passed.\n", test_num);
        $d;
        return true;
    }

    return false;
}
