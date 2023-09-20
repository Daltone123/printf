#include "main.h"

/**
* to_get_precision - used to calculate the precision for printing
* @format: this is a formatted string in which to print the arguments
* @i: List of arguments to be printed.
* @list: list of arguments.
* Return: Precision.
*/

int to_get_precision(const char *format, int *i, va_list list)

{
	int curr = *i + 1;
	int prec = -1;

	if (format[curr] != '.')
	return (prec);
	prec = 0;
	for (curr += 1; format[curr] != '\0'; curr++)
	{
	if (digit(format[curr]))
	{
	prec *= 10;
	prec += format[curr] - '0';
	}
	else if (format[curr] == '*')
	{
	curr++;
	prec = va_arg(list, int);
	break;
	}
	else
	break;
	}
	*i = curr - 1;
	return (prec);
}
