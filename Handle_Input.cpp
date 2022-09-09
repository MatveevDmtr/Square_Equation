#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TXLib.h>

#include "Handle_Input.h"

#define Assert(condition) \
        $r;\
        if(condition)\
        {printf("ERROR in line %d in \n%s \nFound (%s).\n", __LINE__, __FILE__, #condition);}


bool ifstop(const char* str)
{
    Assert(str == NULL);

    return strcmp(str, "stop") == 0;
}

bool isdigit(const char* str)
{
    Assert(str == NULL);

    char sym;

    while ((sym = *str) != '\0')
    {
        if (!((sym >= '0' && sym <= '9') || sym == '-' || sym == '.'))
            return false;

        str++;
    }

    return true;
}

// tries to convert string to double, returns success
bool read_double(const char* line, double* double_number)
{
    char* ptr_end = NULL;

    *double_number = strtod(line, &ptr_end);

    if (*ptr_end)
        return false;

    return true;
}

bool read_one_coef(char* dest, char name_coef)
{
    $b;

    printf("Insert coefficients %c:\n", name_coef);
    $o;
    scanf("%29s", dest);
    while (getchar () != '\n');

    if (ifstop(dest))
        return true;

    return false;
}

// reads strings and checks if user wants to stop
bool read_all_coefs(char* str_a, char* str_b, char* str_c)
{
    return read_one_coef(str_a, 'a') || read_one_coef(str_b, 'b') || read_one_coef(str_c, 'c');
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
