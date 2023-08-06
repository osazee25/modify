#include "shell.h"

/**
 * _erratoi - converts an error string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *str) {
    int i = 0;
    unsigned long int res = 0;

    if (*str == '+')
        str++;

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            res *= 10;
            res += (str[i] - '0');
            if (res > INT_MAX)
                return -1;
        } else {
            return -1;
        }
        i++;
    }

    return (int)res;
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @e_str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *e_str)
{
	_eputs(info->fname);
	_eputs(": ");
	print_dec(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(e_str);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int input, int fd) {
    int (*__putchar)(char) = _putchar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        __putchar = _eputchar;

    if (input < 0) {
        _abs_ = -input;
        __putchar('-');
        count++;
    } else {
        _abs_ = input;
    }

    current = _abs_;
    i = 1000000000;

    while (i > 1) {
        if (_abs_ / i) {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
        i /= 10;
    }

    __putchar('0' + current);
    count++;

    return count;
}

/**
 * convert_number - converter function, a clone of itoa
 * @number: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int number, int base, int flags) {
    static char *arr;
    static char buff[50];
    char sign = 0;
    char *ptr;
    unsigned long n = number;

    if (!(flags & CONVERT_UNSIGNED) && number < 0) {
        n = -number;
        sign = '-';
    }

    arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buff[49];
    *ptr = '\0';

    for (; n != 0; n /= base) {
        *(--ptr) = arr[n % base];
    }

    if (sign)
        *(--ptr) = sign;

    return ptr;
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf) {
    int i = 0;

    while (buf[i] != '\0') {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' ')) {
            buf[i] = '\0';
            break;
        }
        i++;
    }
}
