#include "main.h"

/**
* to_handle_print - used to print an argument based on its type
* @fmt: Formatted string in which to print the arguments.
* @list: List of arguments to be printed.
* @index: ind.
* @b: Buffer array to handle print.
* @flag: Calculates active flags
* @wid: get width.
* @prec: Precision specification
* @size: Size specifier
* Return: 1 or 2;
*/

int to_handle_print(const char *fmt, int *index, va_list list, char b[],

	int flag, int wid, int prec, int size)

{
	int i, the_len = 0, put_chars = -1;
	fmt_t fmt_types[] = {
	{'c', to_print_char}, {'s', to_print_string}, {'%', to_print_percent},
	{'i', to_print_int}, {'d', to_print_int}, {'b', to_print_binary},
	{'u', to_print_unsigned}, {'o', to_print_octal}, {'x', to_print_hexadecimal},
	{'X', to_print_hexa_u}, {'p', to_print_pointer},
	{'S', to_print_non_printable},
	{'r', to_print_reverse}, {'R', to_print_rot13}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
	if (fmt[*index] == fmt_types[i].fmt)
	return (fmt_types[i].fn(list, b, flag, wid, prec, size));
	if (fmt_types[i].fmt == '\0')
	{
	if (fmt[*index] == '\0')
	return (-1);
	the_len += write(1, "%%", 1);
	if (fmt[*index - 1] == ' ')
	the_len += write(1, " ", 1);
	else if (wid)
	{
	--(*index);
	while (fmt[*index] != ' ' && fmt[*index] != '%')
	--(*index);
	if (fmt[*index] == ' ')
	--(*index);
	return (1);
	}
	the_len += write(1, &fmt[*index], 1);
	return (the_len);
	}
	return (put_chars);
}
