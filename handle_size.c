#include "main.h"
/**
 * get_size - this calculates the size to cast the argument
 * @format: formatted string in which to print the arguments
 * @i: this is the list of the arguments to be printed
 *
 * Return: precision(arg_size)
 */
int get_size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int arg_size = 0;/*counter for precision*/

	if (format[curr_i] == 'I')
		arg_size = S_LONG;
	else if (format[curr_i] == 'h')
		arg_size = S_SHORT;

	if (arg_size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (arg_size);
	/*returns the size of the arguments given*/
}
