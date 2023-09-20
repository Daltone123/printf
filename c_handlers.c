#include "main.h"

/************************* FOR WRITING HANDLERS *************************/

/**
 * to_handle_write_char - Prints a string
 * @c: char types.
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags.
 * @wid: get width.
 * @prec: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int to_handle_write_char(char c, char b[],
	int flag, int wid, int prec, int size)
{
	int i = 0;
	char pad = ' ';

	UNUSED(prec);
	UNUSED(size);

	if (flag & F_ZERO)
		pad = '0';

	b[i++] = c;
	b[i] = '\0';

	if (wid > 1)
	{
		b[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < wid - 1; i++)
			b[BUFF_SIZE - i - 2] = pad;

		if (flag & F_MINUS)
			return (write(1, &b[0], 1) +
					write(1, &b[BUFF_SIZE - i - 1], wid - 1));
		else
			return (write(1, &b[BUFF_SIZE - i - 1], wid - 1) +
					write(1, &b[0], 1));
	}

	return (write(1, &b[0], 1));
}

/*************************FOR WRITING NUMBER *************************/
/**
 * to_write_number - Prints a string
 * @negative: Lista of arguments
 * @index: char types.
 * @b: Buffer array to handle print
 * @flag:  Calculates active flags
 * @wid: get width.
 * @prec: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int to_write_number(int negative, int index, char b[],
	int flag, int wid, int prec, int size)
{
	int length = BUFF_SIZE - index - 1;
	char pad = ' ', xtra_ch = 0;

	UNUSED(size);

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		pad = '0';
	if (negative)
		xtra_ch = '-';
	else if (flag & F_PLUS)
		xtra_ch = '+';
	else if (flag & F_SPACE)
		xtra_ch = ' ';

	return (to_write_num(index, b, flag, wid, prec,
		length, pad, xtra_ch));
}

/**
 * to_write_num - used to write a number using a bufffer
 * @index: Index at which the number starts on the buffer
 * @b: Buffer
 * @flag: Flags
 * @wid: width
 * @prec: Precision specifier
 * @length: Number length
 * @pad: Pading char
 * @xtra_ch: Extra char
 * Return: Number of printed chars.
 */
int to_write_num(int index, char b[],
	int flag, int wid, int prec,
	int length, char pad, char xtra_c)
{
	int i, pad_stat = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && b[index] == '0' && wid == 0)
		return (0);
	if (prec == 0 && index == BUFF_SIZE - 2 && b[index] == '0')
		b[index] = pad = ' ';
	if (prec > 0 && prec < length)
		pad = ' ';
	while (prec > length)
		b[--index] = '0', length++;
	if (xtra_c != 0)
		length++;
	if (wid > length)
	{
		for (i = 1; i < wid - length + 1; i++)
			b[i] = pad;
		b[i] = '\0';
		if (flag & F_MINUS && pad == ' ')/* Asign extra char to left of buffer */
		{
			if (xtra_c)
				b[--index] = xtra_c;
			return (write(1, &b[index], length) + write(1, &b[1], i - 1));
		}
		else if (!(flag & F_MINUS) && pad == ' ')/* extra char to left of buff */
		{
			if (xtra_c)
				b[--index] = xtra_c;
			return (write(1, &b[1], i - 1) + write(1, &b[index], length));
		}
		else if (!(flag & F_MINUS) && pad == '0')/* extra char to left of padd */
		{
			if (xtra_c)
				b[--pad_stat] = xtra_c;
			return (write(1, &b[pad_stat], i - pad_stat) +
				write(1, &b[index], length - (1 - pad_stat)));
		}
	}
	if (xtra_c)
		b[--index] = xtra_c;
	return (write(1, &b[index], length));
}

/**
 * to_write_unsgnd - used to write an unsigned number
 * @negative: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @b: Array of chars
 * @flag: Flags specifiers
 * @wid: Width specifier
 * @prec: Precision specifier
 * @size: Size specifier
 * Return: Number of written chars.
 */
int to_write_unsgnd(int negative, int index,
	char b[],
	int flag, int wid, int prec, int size)
{
	/**
	* The number above is stored at the bufer's
	*right and starts at position i
	*/
	int length = BUFF_SIZE - index - 1, i = 0;
	char pad = ' ';

	UNUSED(negative);
	UNUSED(size);

	if (prec == 0 && index == BUFF_SIZE - 2 && b[index] == '0')
		return (0);

	if (prec > 0 && prec < length)
		pad = ' ';

	while (prec > length)
	{
		b[--index] = '0';
		length++;
	}

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		pad = '0';

	if (wid > length)
	{
		for (i = 0; i < wid - length; i++)
			b[i] = pad;

		b[i] = '\0';

		if (flag & F_MINUS)
		/* Asigning an extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &b[index], length) + write(1, &b[0], i));
		}
		else /* Asign extra char to left of padding */
		{
			return (write(1, &b[0], i) + write(1, &b[index], length));
		}
	}

	return (write(1, &b[index], length));
}

/**
 * to_write_pointer - Write a memory address
 * @b: Arrays of chars
 * @index: Index at which the number starts in the buffer
 * @length: Length of number
 * @wid: Wwidth specifier
 * @flag: Flags specifier
 * @pad: Char representing the padding
 * @xtra_c: Char representing extra char
 * @pad_stat: Index at which padding should start
 * Return: Number of written chars.
 */
int to_write_pointer(char b[], int index, int length,
	int wid, int flag, char pad, char xtra_c, int pad_stat)
{
	int i;

	if (wid > length)
	{
		for (i = 3; i < wid - length + 3; i++)
			b[i] = pad;
		b[i] = '\0';
		if (flag & F_MINUS && pad == ' ')
		/* for asigning extra char to left of buffer */
		{
			b[--index] = 'x';
			b[--index] = '0';
			if (xtra_c)
				b[--index] = xtra_c;
			return (write(1, &b[index], length) + write(1, &b[3], i - 3));
		}
		else if (!(flag & F_MINUS) && pad == ' ')
		/* an extra char to left of buffer */
		{
			b[--index] = 'x';
			b[--index] = '0';
			if (xtra_c)
				b[--index] = xtra_c;
			return (write(1, &b[3], i - 3) + write(1, &b[index], length));
		}
		else if (!(flag & F_MINUS) && pad == '0')/* extra char to left of padd */
		{
			if (xtra_c)
			b[--pad_stat] = xtra_c;
			b[1] = '0';
			b[2] = 'x';
			return (write(1, &b[pad_stat], i - pad_stat) +
				write(1, &b[index], length - (1 - pad_stat) - 2));
		}
	}
	b[--index] = 'x';
	b[--index] = '0';
	if (xtra_c)
		b[--index] = xtra_c;
	return (write(1, &b[index], BUFF_SIZE - index - 1));
}




