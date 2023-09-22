#include "main.h"

/*PRITN THE CHARACTERS*/
/**
 * print_char - will print a character
 * @types: List of all the arguments
 * @buffer: is the buffer array to handle print
 * @flags: this will calculate active flags
 * @width: Width
 * @precision: this is the precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char s = va_arg(types, int);

	return (handle_write_char(s, buffer, flags, width, precision, size));
}

/*THIS prints a string*/
/**
 * print_string - this prints a string
 * @types: this is the list of arguments
 * @buffer: the buffer array to handle print
 * @flags: this calculates active flags
 * @width: this gets width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, j;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "  ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (j = width - len; j > 0; j--)
				write(1, "", 1);
			return (width);
		}
		else
		{
			for (j = width - len; j > 0; j--)
				write(1, "", 1);
			write(1, &str[0], len);
			return (width);
		}
	}
	return (write(1, str, len));
}

/*this will print the percentage sign*/
/**
 * print_percent - this prints a percentage sign
 * @types: this is the list of arguments
 * @buffer: this is the buffer array to handle print
 * @flags: this calculates active flags
 * @width: this gets width
 * @precision: Precision specifications
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/*this will print an integer*/
/**
 * print_int - this prints int
 * @types: this is the lists of arguments
 * @buffer: this is the buffer array to handle print
 * @flags: calculates active flags
 * @width: Gets width
 * @precision: precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	int is_negative = 0;
	long int l = va_arg(types, long int);
	unsigned long int num;

	l = convert_size_number(l, size);

	if (l == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)l;

	if (l < 0)
	{
		num = (unsigned long int)((-1) * l);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}
	j++;

	return (write_number(is_negative, j, buffer, flags, width, precision, size));
}

/*this will print binary*/

/**
 * print_binary - this prints an unsigned number
 * @types: this is the lists of arguments
 * @buffer: this is the uffer array to handle print
 * @flags: this calculates active flags
 * @width: this gets width
 * @precision: this is the precision specifier
 * @size: Size specifier
 *
 * Return: Number of char printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, j, all;/*variable all refers to sum*/
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (j = 1; j < 32; j++)
	{
		m /= 2;
		a[j] = (n / m) % 2;
	}
	for (j = 0, all = 0, count = 0; j < 32; j++)
	{
		all += a[j];
		if (all || j == 31)
		{
			char z = '0' + a[j];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
