#include "main.h"

void to_print_buffer(char b[], int *b_index);

/**
 * _printf - handling printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, put = 0, put_chars = 0;
	int flag, wid, prec, size, b_index = 0;
	va_list list;
	char b[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			b[b_index++] = format[i];
			if (b_index == BUFF_SIZE)
				to_print_buffer(b, &b_index);
			/* write(1, &format[i], 1);*/
			put_chars++;
		}
		else
		{
			to_print_buffer(b, &b_index);
			flag = to_get_flags(format, &i);
			wid = to_get_width(format, &i, list);
			prec = to_get_precision(format, &i, list);
			size = to_get_size(format, &i);
			++i;
			put = to_handle_print(format, &i, list, b,
				flag, wid, prec, size);
			if (put == -1)
				return (-1);
			put_chars += put;
		}
	}

	to_print_buffer(b, &b_index);

	va_end(list);

	return (put_chars);
}

/**
 * to_print_buffer - Prints the contents of the buffer if it exist
 * @b: Array of chars
 * @b_index: Index at which to add next char, represents the length.
 */
void to_print_buffer(char b[], int *b_index)
{
	if (*b_index > 0)
		write(1, &b[0], *b_index);

	*b_index = 0;
}




