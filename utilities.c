#include "main.h"

/**
* printable - used to evaluate if a char is printable
* @c: Char to be evaluated.
* Return: 1 if c is printable, 0 otherwise
*/

int printable(char c)

{
	if (c >= 32 && c < 127)
	return (1);
	return (0);
}

/**
* to_append_hexa_code - Append ascci in hexadecimal code to buffer
* @b: Array of chars.
* @i: Index at which to start appending.
* @ascii: ASSCI CODE.
* Return: Always 3
*/

int to_append_hexa_code(char ascii, char b[], int i)

{
	char to_map_to[] = "0123456789ABCDEF";

  /* The hexa format code is always 2 digits long */

	if (ascii < 0)
	ascii *= -1;
	b[i++] = '\\';
	b[i++] = 'x';
	b[i++] = to_map_to[ascii / 16];
	b[i] = to_map_to[ascii % 16];
	return (3);
}

/**
* digit - used to verify if a char is a digit
* @c: Char to be evaluated
* Return: 1 if c is a digit, 0 otherwise
*/

int digit(char c)

{
	if (c >= '0' && c <= '9')
	return (1);
	return (0);
}

/**
* to_convert_size_number - used to cast a number to the specified size
* @number: Number to be casted.
* @size: Number indicating the type to be casted.
* Return: Casted value of num
*/

long int to_convert_size_number(long int number, int size)

{
	if (size == S_LONG)
	return (number);
	else if (size == S_SHORT)
	return ((short)number);
	return ((int)number);
}

/**
* to_convert_size_unsgnd - used to cast a number to the specified size
* @number: Number to be casted
* @size: Number indicating the type to be casted
* Return: Casted value of num
*/

long int to_convert_size_unsgnd(unsigned long int number, int size)

{
	if (size == S_LONG)
	return (number);
	else if (size == S_SHORT)
	return ((unsigned short)number);
	return ((unsigned int)number);
}
