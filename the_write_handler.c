#include "main.h"

//this handles write
/**
 * handle_write_char - this prints a string
 * @c: char types
 * @buffer: the buffer array to handle print
 * @flags: this calculates active flags
 * @width: this gets width
 * @precision: this is the precision specifier
 * @size: this is the size specifier
 *
 * Return: Number of chars printed
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{/* char is stored at left and padding at buffer's right*/
	int a = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding = '0';

	buffer[a++] = c;
	buffer[a] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (a = 0; a < width - 1; a++)
			buffer[BUFF_SIZE - a - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

//this will write a number
/**
 * write_number - this prints a string
 * @is_negative: this is aList of arguments
 * @ind: Char types
 * @buffer: this is the uffer array to handle print
 * @flags: this will calculate all active flags
 * @width: this will get width
 * @precision: this is the precision specifier
 * @size: this is the size specifier
 *
 * Return: number of chars printed
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padding = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision, length
			       	padding, extra_ch));
	return(0);
}

/**
 * write_num - this will write a number using a buffer
 * @ind: this is the index at which the number starts on the buffer
 * @buffer: the buffer
 * @flags: the flags
 * @width: the width
 * @prec: this is the precision specifier
 * @length: number of length
 * @padd: pading char
 * @extra_c:  extra char
 *
 * Return: number of printed chars
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int a, padding_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0) and no character is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd == ' '; /* the width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (a = 1; a < width - length + 1; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')/* this will assign extra char to left buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], a - 1));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* tis will leave an extra char to left pf padd */
		{
			if (extra_c)
				buffer[--padding_start] = extra_c;
			return (write(1, &buffer[padding_start], a - padding_start) +
				write(1, &buffer[ind], length - (1 - padding_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - this will write an unsigned number
 * @is_negative: this is teh number indicating if the num is negative
 * @ind: this is the index at which the number starts in the buffer
 * @buffer: this is an array of chars
 * @flags: these are the flag  specifiers
 * @width: this is the width specifier
 * @precision: this is the precision specifier
 * @size: this is the size specifier
 *
 * Return: number of written chars
 */
int write_unsgnd(int is_negative, int ind, 
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* the number is stored at the buffer's right and starts at position i */
	int len = BUFF_SIZE - ind - 1, a = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0) hence no char is printed */

	if (precision > 0 && precision < len)
		padding = ' ';

	while (precision > len)
	{
		buffer[--ind] = '0';
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';

	if (width > len)
	{
		for (a = 0; a < width - len; a++)
			buffer[a] = padding;

		buffer[a] = '\0';

		if (flags & F_MINUS) /* this will assign extra char to left of buffer [buffer>padd] */
		{
			return (write(1, &buffer[ind], len) + write(1, &buffer[0], a));
		}
		else /* this will assign extra char to left of padding [padd>buffer] */
		{
			return (write(1, &buffer[0], a) + write(1, &buffer[ind], len));
		}
	}

	return (write(1, &buffer[ind], len));
}

/**
 * write_pointer - this writes a memory address
 * @buffer: this is  arrays of chars
 * @ind: this is the index at which the number starts in the buffer
 * @length: this is the length of number
 * @width: this is the width specifier
 * @flags: this is the flags specifier
 * @padd: this is the character representing the padding
 * @extra_c: char representing extra char
 * @padd_start: index at which padding should start
 *
 * Return: number of written chars
 */
int write_pointer(char buffer[], int ind, int width,
	int length, int flags, char extra_c, char padd, int padd_start)
{
	int a;

	if (width > length)
	{
		for (a = 3; a < width - length + 3; a++)
			buffer[a] = padd;
		buffer[a] = '\0';
		if (flags & F_MINUS && padd == ' ')/* this will assign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], a - 3));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], a - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], a - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
