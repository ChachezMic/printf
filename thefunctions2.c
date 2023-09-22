#include "main.h"
/*this prints the value of a pointer variable*/
/**
 * print_pointer - this prints the value of a pointer variable
 * @types: this lists all of arguments
 * @buffer: buffer array to handle print
 * @flags: calculates active flags
 * @width: this gets width
 * @precision: tis is the precision specification
 * @size: this is the size specifier
 *
 * Return: number of characters printed
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int size, int precision)
{
	char extra_char = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, len = 2, padd_start = 1;/* len(length) = 2, for '0x' */
	unsigned long num_address;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_address = (unsigned long)addrs;

	while (num_address > 0)
	{
		buffer[ind--] = map_to[num_address % 16];
		num_address /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_char = '+', len++;
	else if (flags & F_SPACE)
		extra_char = ' ', len++;

	ind++;
	/* return (write(1, &buffer[i], BUFF_SIZE - i - 1)); */
	return (write_pointer(buffer, ind, len,
		width, flags, padd, extra_char, padd_start));
}

/*this part prints ascii codes in hexa from */
/**
 * print_non_printable - this prints ascii codes in hexa of non printable chars
 * @types: this lists all of arguments
 * @buffer: this is the buffer array to handle print
 * @flags: this calculates active flags
 * @width: this gets width
 * @precision: this is the precision specification
 * @size: this is the size specifier
 *
 * Return: number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = 0, off_set = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[j] != '\0')
	{
		if (is_printable(str[j]))
			buffer[j + off_set] = str[j];
		else
			off_set += append_hexa_code(str[j], buffer, j + off_set);

		j++;
	}

	buffer[j + off_set] = '\0';

	return (write(1, buffer, j + off_set));
}

/*this willprint a string in reverse*/
/**
 * print_reverse - this prints reverse string
 * @types: this will list all of arguments
 * @buffer: this is the buffer array to handle print
 * @flags: this calculates active flags
 * @width: this gets width
 * @precision: precision specification
 * @size: size specifier
 *
 * Return: numbers of chars printed
 */
int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	char c;
	int j, counter = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")NULL(";
	}
	for (j = 0; str[j]; j++)
		;
	for (j = j - 1; j >= 0; j--)
	{
		c = str[j];

		write(1, &c, 1);
		counter++;
	}
	return (counter);
}

/*this will print a string in rot13 fromat*/
/**
 * print_rot13string - this will print a string in rot 13
 * @types: this will list all of arguments
 * @buffer: buffer array to handle print
 * @flags: calculates active flags
 * @width: get width
 * @precision: precision specification
 * @size: size specifier
 *
 * Return: numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int a, b;
	int counter = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (a = 0; str[a]; a++)
	{
		for (b = 0; in[b]; b++)
		{
			if (in[b] == str[a])
			{
				x = out[b];
				write(1, &x, 1);
				counter++;
				break;
			}
		}
		if (!in[b])
		{
			x = str[a];
			write(1, &x, 1);
			counter++;
		}
	}
	return (counter);
}
