
#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int to_handle_print(const char *fmt, int *index,
va_list list, char b[], int flag, int wid, int prec, int size);

/****************** HANDLING FUNCTIONS ******************/

/* Funtions to print chars and strings */
int to_print_char(va_list types, char b[],
	int flag, int wid, int prec, int size);
int to_print_string(va_list types, char b[],
	int flag, int wid, int prec, int size);
int to_print_percent(va_list types, char b[],
	int flag, int wid, int prec, int size);

/* Functions to print numbers */
int to_print_int(va_list types, char b[],
	int flag, int wid, int prec, int size);
int to_print_binary(va_list types, char b[],
	int flag, int wid, int prec, int size);
int to_print_unsigned(va_list types, char b[],
	int flag, int wid, int prec, int size);
int to_print_octal(va_list types, char b[],
	int flag, int wid, int prec, int size);
int to_print_hexadecimal(va_list types, char b[],
	int flag, int wid, int prec, int size);
int to_print_hexa_u(va_list types, char b[],
	int flag, int wid, int prec, int size);

int to_print_hexa_l(va_list types, char to_map_to[], char b[],
	int flag, char flag_cc, int wid, int prec, int size);

/* Function to print non printable characters */
int to_print_non_printable(va_list types, char b[],
	int flag, int wid, int prec, int size);

/* Funcion to print memory address */
int to_print_pointer(va_list types, char b[],
	int flag, int wid, int prec, int size);

/* Funciotns to handle other specifiers */
int to_get_flags(const char *format, int *i);
int to_get_width(const char *format, int *i, va_list list);
int to_get_precision(const char *format, int *i, va_list list);
int to_get_size(const char *format, int *i);

/*Function to print string in reverse*/
int to_print_reverse(va_list types, char b[],
	int flag, int wid, int prec, int size);

/*Function to print a string in rot 13*/
int to_print_rot13(va_list types, char b[],
	int flag, int wid, int prec, int size);

/* width handler */
int to_handle_write_char(char c, char b[],
	int flag, int wid, int prec, int size);
int to_write_number(int positive, int index, char b[],
	int flag, int wid, int prec, int size);
int to_write_num(int ind, char b[], int flag, int wid, int prec,
	int length, char pad, char xtra_c);
int to_write_pointer(char b[], int index, int length,
	int wid, int flag, char pad, char xtra_c, int pad_stat);

int to_write_unsgnd(int negative, int index,
char b[],
	int flag, int wid, int prec, int size);

/****************** UTILS ******************/
int printable(char);
int to_append_hexa_code(char, char[], int);
int digit(char);

long int to_convert_size_number(long int number, int size);
long int to_convert_size_unsgnd(unsigned long int number, int size);

#endif/* MAIN_H */


