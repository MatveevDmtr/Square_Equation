#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TXLib.h>

#include "Handle_Input.h"

#define Assert(condition) \
        $r;\
        if(condition)\
        {printf("ERROR in line %d in \n%s \nFound (%s).\n", __LINE__, __FILE__, #condition);}

const unsigned int LEN_LIST_ALLOWED_SYM = 12;
const char LIST_ALLOWED_SYM[] = "0123456789.-";


bool ifstop(char* str)
{
    Assert(str == NULL);

    return strcmp(str, "stop") == 0;
}

bool isdigit(char* str)
{
    Assert(str == NULL);

    int str_len = strlen(str);
    bool is_allowed;

    for (int i = 0; i < str_len; i++)
    {
        is_allowed = false;
        for (unsigned int j = 0; j < LEN_LIST_ALLOWED_SYM; j++)
        {
            if(LIST_ALLOWED_SYM[j] == str[i])
            {
                is_allowed = true;
            }
        }
        if(!is_allowed)
        {
            return false;
        }
    }

    return true;
}

// tries to convert string to double, returns success
bool read_double(char* line, double* double_number)
{
    char* ptr_end = NULL;

    *double_number = strtod(line, &ptr_end);

    if (*ptr_end)
        return false;

    return true;
}

// reads strings and checks if user wants to stop
bool read_coef(char* str_a, char* str_b, char* str_c)
{
    //scanf("%*s %*s %*s", MAX_LEN_STRING, str_a,
    //                     MAX_LEN_STRING, str_b,
    //                     MAX_LEN_STRING, str_c);
    //scanf("%5s %5s %5s", str_a, str_b, str_c);

    $b;
    //printf("addresses: %p %p %p\n", str_a, str_b, str_c);

    printf("Insert coefficients a:\n");
    $o;
    scanf("%29s", str_a);
    while (getchar () != '\n');

    if (ifstop(str_a))
    {
        return true;
    }

    //printf("1 coef_a: %s\n", str_a);

    $b;
    printf("Insert coefficients b:\n");
    $o;
    scanf("%29s", str_b);
    while (getchar () != '\n');

    if (ifstop(str_b))
    {
        return true;
    }

    //printf("2 coef_a: %s\n", str_a);

    $b;
    printf("Insert coefficients c:\n");
    $o;
    scanf("%29s", str_c);
    while (getchar () != '\n');

    if (ifstop(str_c))
    {
        return true;
    }

    //txDump(str_c);

    /*printf("[MEOW]\n"
           "A line: %s\n"
           "B line: %s\n"
           "C line: %s\n", str_a, str_b, str_c);*/

    return ifstop(str_a) || ifstop(str_b) || ifstop(str_c);

}

int handle_errors(char* str_a, char* str_b, char* str_c,
                  double* ptr_a, double* ptr_b, double* ptr_c)
{
    Assert(str_a == NULL);
    Assert(str_b == NULL);
    Assert(str_c == NULL);

    Assert(ptr_a == NULL);
    Assert(ptr_b == NULL);
    Assert(ptr_c == NULL);

    int status = 0;
    status += handle_input(str_a, ptr_a, 'a');
    status += handle_input(str_b, ptr_b, 'b');
    status += handle_input(str_c, ptr_c, 'c');

    return !status;
}

int handle_input(char* str, double* ptr_coef, char invalid_coef)
 {
    if(!isdigit(str))
    {
        print_error(FORBIDDEN_SYMBOLS, invalid_coef);

        return FORBIDDEN_SYMBOLS;
    }

    if(!read_double(str, ptr_coef))
    {
        print_error(INVALID_NUMBER, invalid_coef);

        return INVALID_NUMBER;
    }

    return NUMBER_IS_OK;
 }

  void print_error(int err_code, char invalid_coef)
{
    $r;
    switch(err_code)
    {
        case FORBIDDEN_SYMBOLS:
            printf("Your coefficient %c includes forbidden symbols. Please, use only this symbols: 0123456789.-\n",
                    invalid_coef);
            break;

        case INVALID_NUMBER:
            printf("Your coefficient %c is invalid. Please, insert coefficients in such format: 12.345\n",
                    invalid_coef);
            break;

        case NUMBER_IS_OK:
            printf("Everything is OK.\n");
            break;

        default:
            printf("ERROR: unexpected error code.\n");
    }
}
