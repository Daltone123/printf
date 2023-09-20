#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * to_print_unsigned - Prints an unsigned number
 * @types: List a of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int to_print_unsigned(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		b[i--] = (number % 10) + '0';
		number /= 10;
	}

	i++;

	return (to_write_unsgnd(0, i, b, flag, wid, prec, size));
}

/************* FOR PRINTING UNSIGNED NUMBERS IN OCTAL  ****************/
/**
 * to_print_octal - Prints an unsigned number in octal notation
 * @types: Lista of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int to_print_octal(va_list types, char b[],
	int flag, int wid, int prec, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_number = number;

	UNUSED(wid);

	number = to_convert_size_unsgnd(number, size);

	if (number == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		b[i--] = (number % 8) + '0';
		number /= 8;
	}

	if (flag & F_HASH && init_number != 0)
		b[i--] = '0';

	i++;

	return (to_write_unsgnd(0, i, b, flag, wid, prec, size));
}

/**************FOR PRINTING UNSIGNED NUMBERS IN HEXADECIMAL **************/
/**
 * to_print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int to_print_hexadecimal(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	return (to_print_hexa(types, "0123456789abcdef", b,
		flag, 'x', wid, prec, size));
}

/** FOR PRINTING UNSIGNED NUMBERS IN UPPER HEXADECIMAL **/
/**
 * to_print_hexa_upper - Prints an unsigned
 * number in upper hexadecimal notation
 * @types: Lista of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int to_print_hexa_u(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	return (to_print_hexa(types, "0123456789ABCDEF", b,
		flag, 'X', wid, prec, size));
}

/************** FOR PRINTING HEXX NUM IN LOWER OR UPPER **************/
/**
 * to_print_l - Prints a hexadecimal number in lower or upper
 * @types: Lista of arguments
 * @to_map_to: Array of values to map the number to
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @flag_cc: Calculates active flags
 * @wid: get width
 * @prec: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int to_print_hexa_l(va_list types, char to_map_to[], char b[],
	int flag, char flag_cc, int wid, int prec, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_number = number;

	UNUSED(wid);

	number = to_convert_size_unsgnd(number, size);

	if (number == 0)
		b[i--] = '0';

	b[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		b[i--] = to_map_to[number % 16];
		number /= 16;
	}

	if (flag & F_HASH && init_number != 0)
	{
		b[i--] = flag_cc;
		b[i--] = '0';
	}

	i++;

	return (to_write_unsgnd(0, i, b, flag, wid, prec, size));
}



