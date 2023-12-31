#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * to_print_char - Prints a character
 * @types: List a of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: Width
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int to_print_char(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	char c = va_arg(types, int);

	return (to_handle_write_char(c, b, flag, wid, prec, size));
}
/************************* FOR PRINTING A STRING *************************/
/**
 * to_print_string - Prints a string
 * @types: List a of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width.
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int to_print_string(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(b);
	UNUSED(flag);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (prec >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (prec >= 0 && prec < length)
		length = prec;

	if (wid > length)
	{
		if (flag & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = wid - length; i > 0; i--)
				write(1, " ", 1);
			return (wid);
		}
		else
		{
			for (i = wid - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (wid);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * to_print_percent - Prints a percent sign
 * @types: Lista of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width.
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int to_print_percent(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	UNUSED(types);
	UNUSED(b);
	UNUSED(flag);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * to_print_int - Print int
 * @types: Lista of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width.
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int to_print_int(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	int i = BUFF_SIZE - 2;
	int negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int number;

	n = to_convert_size_number(n, size);

	if (n == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';
	number = (unsigned long int)n;

	if (n < 0)
	{
		number = (unsigned long int)((-1) * n);
		negative = 1;
	}

	while (number > 0)
	{
		b[i--] = (number % 10) + '0';
		number /= 10;
	}

	i++;

	return (to_write_number(negative, i, b, flag, wid, prec, size));
}

/************************* FOR PRINTING TO BINARY *************************/
/**
 * to_print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width.
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int to_print_binary(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(b);
	UNUSED(flag);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}



