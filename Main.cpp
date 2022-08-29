// square_equation_solution.c - решает квадратное уравнение
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <TXLib.h>

#include "Solve_Equation.h"
#include "Handle_Input.h"
#include "Testing_System.h"

#define Assert(condition) \
        $r;\
        if(condition)\
        {printf("ERROR in line %d in \n%s \nFound (%s).\n", __LINE__, __FILE__, #condition);}

const int MAX_LEN_STRING = 30;

int user_interface();


int user_interface()
 {
    double a = 0;
    double b = 0;
    double c = 0;

    double root1 = 0;
    double root2 = 0;

    bool stop = false;

    char str_a[MAX_LEN_STRING] = "",
         str_b[MAX_LEN_STRING] = "",
         str_c[MAX_LEN_STRING] = "";


    $f;
    printf("Square equation solver\n\n");


    while(!stop)
    {
        stop = read_coef(str_a, str_b, str_c);
        int is_input_ok = 0;

        if(!stop)
        {
            is_input_ok = handle_errors(str_a, str_b, str_c, &a, &b, &c);
        }
        else
        {
            $f;
            printf("Goodbye!");
            $d;
        }

        if(is_input_ok)
        {
            int num_solutions = solve_equation(a, b, c, &root1, &root2);
            print_solutions(num_solutions, root1, root2);
        }
    }

    return 0;
 }

 int main(int argc, char* argv[])
 {
    for(int args_count = 1; args_count < argc; args_count++)
    {
        if (!strcmp(argv[args_count], "stop"))
        {
            exit(0);
            break;
        }
        else if (!strcmp(argv[args_count], "test"))
        {
            test_solving_eq();
        }
        else if(!strcmp(argv[args_count], "solve"))
        {
            user_interface();
        }
        else
        {
            $r;
            printf("Incorrect mode of program.\n"
                   "Restart the program and choose its mode: "
                   "test, solve or stop.\n");
            $d;
        }
    }

    if(argc == 1)
    {
        $r;
        printf("Mode of the program hasn't been chosen.\n"
                "Please, restart the program and "
                "enter mode through the command line.\n"
                "For example: solve\n");
        $d;
    }

    return 0;
 }
