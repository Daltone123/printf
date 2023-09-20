#include "main.h"

/****************** FOR PRINTING POINTERS ******************/
/**
 * to_print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int to_print_pointer(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	char xtra_c = 0, pad = ' ';
	int index = BUFF_SIZE - 2, length = 2, pad_stat = 1; /* length=2, for '0x' */
	unsigned long number_addrs;
	char to_map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(wid);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	b[BUFF_SIZE - 1] = '\0';
	UNUSED(prec);

	number_addrs = (unsigned long)addrs;

	while (number_addrs > 0)
	{
		b[index--] = to_map_to[number_addrs % 16];
		number_addrs /= 16;
		length++;
	}

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		pad = '0';
	if (flag & F_PLUS)
		xtra_c = '+', length++;
	else if (flag & F_SPACE)
		xtra_c = ' ', length++;

	index++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (to_write_pointer(b, index, length,
		wid, flag, pad, xtra_c, pad_stat));
}

/**** FOR PRINTING NON PRINTABLE *****/
/**
 * to_print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int to_print_non_printable(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flag);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (printable(str[i]))
			b[i + offset] = str[i];
		else
			offset += to_append_hexa_code(str[i], b, i + offset);

		i++;
	}

	b[i + offset] = '\0';

	return (write(1, b, i + offset));
}

/************************* FOR PRINTING REVERSE *************************/
/**
 * to_print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int to_print_reverse(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(b);
	UNUSED(flag);
	UNUSED(wid);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(prec);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/**** FOR PRINTING A STRING IN ROT13 ****/
/**
 * to_print_rot13 - Print a string in rot13.
 * @types: Lista of arguments
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width
 * @prec: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int to_print_rot13(va_list types, char b[],
	int flag, int wid, int prec, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char get[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(b);
	UNUSED(flag);
	UNUSED(wid);
	UNUSED(prec);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; get[j]; j++)
		{
			if (get[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!get[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}

