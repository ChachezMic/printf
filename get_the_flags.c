#include "main.h"
/**
 * get_flags - calculates the number of active flags
 * @format: this is the formatted string in which to print the arguments
 * @i: takes a parameter
 *
 * Return: total number of flags
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8 16 */
	int b, curr_i;
	int flags = 0;
	const char FLAG_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	/*these are the flag characters*/
	const int FLAG_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};
	/*this is an array containing the flags*/

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (b = 0; FLAG_CH[b] != '\0'; b++)
			if (format[curr_i] == FLAG_CH[b])
			{
				flags |= FLAG_ARR[b];
				break;
			}

		if (FLAG_CH[b] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flags);
}
