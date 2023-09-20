#include <stdio.h>
#include <stdarg.h>
/**
 * my_printf - works like printf
 * const char:checks
 * *format:checks
 * return: (0) always

int my_printf(const char *format, ...)
{
	int count = 0;

	va_list lists;
	va_start(lists, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
				{
					case 'c':
						{
							char c = va_arg(lists, int);
							putchar(c);
							count += 1;
							break;
						}
					case 's':
						{
							char *str = va_arg(lists, char *);
							while (*str != '\0')
							{
								putchar(*str);
								str++;
								count += 1;
								break;
							}
							case '%':
							{
								putchar('%');
								count += 1;
								break;
							}
							default:
							 printf("Invalid format specifier: %c", *format);
							 count += 1;
							 break;
						}
				}
		}
		else
			{
				putchar(*format);
				 count += 1;
			}
			format++;
		}
		va_end(lists);
		return count;
}

