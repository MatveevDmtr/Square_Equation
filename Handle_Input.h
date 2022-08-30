#ifndef HANDLE_INPUT_H_INCLUDED
#define HANDLE_INPUT_H_INCLUDED

bool ifstop(char* str);

bool isdigit(char* str);

bool read_double(char* line, double* double_number);

bool read_coef(char* str_c, char* str2, char* str3);

int handle_errors(char* str_a, char* str_b, char* str_c,
                  double* ptr_a, double* ptr_b, double* ptr_c);

int handle_input(char* str, double* ptr_coef, char invalid_coef);

void print_error(int err_code, char invalid_coef);

enum ERROR_CODES
{
    FORBIDDEN_SYMBOLS = 1,
    INVALID_NUMBER = 2,
    NUMBER_IS_OK = 0,
    FOUND_STOP = -1
};

#endif // HANDLE_INPUT_H_INCLUDED
