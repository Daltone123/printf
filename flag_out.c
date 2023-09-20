#include "main.h"

/**
* to_get_flags - Calculates active flags
* @format: Formatted string in which to print the arguments
* @i: takes a parameter.
* Return: Flags:
*/

int to_get_flags(const char *format, int *i)

{
	int j, curr;
	int flag = 0;
	const char FLAGS_CC[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr = *i + 1; format[curr] != '\0'; curr++)
	{
	for (j = 0; FLAGS_CC[j] != '\0'; j++)
	if (format[curr] == FLAGS_CC[j])
	{
	flag |= FLAGS_ARR[j];
	break;
	}
	if (FLAGS_CC[j] == 0)
	break;
	}
	*i = curr - 1;
	return (flag);
}
