#include "main.h"

/**
* to_get_width - Calculates the width for printing
* @format: Formatted string in which to print the arguments.
* @i: List of arguments to be printed.
* @list: list of arguments.
* Return: width.
*/

int to_get_width(const char *format, int *i, va_list list)
	{
	int curr;

	int wid = 0;

	for (curr = *i + 1; format[curr] != '\0'; curr++)
	{
	if (digit(format[curr]))
	{
	wid *= 10;
	wid += format[curr] - '0';
	}
	else if (format[curr] == '*')
	{
	curr++;
	wid = va_arg(list, int);
	break;
	}
	else
	break;
	}
	*i = curr - 1;
	return (wid);
	}
