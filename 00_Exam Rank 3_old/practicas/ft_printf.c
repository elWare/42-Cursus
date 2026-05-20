/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:10:20 by jumarque          #+#    #+#             */
/*   Updated: 2025/04/21 09:29:45 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	ft_putstr(char *str, int *len)
{
	if (str == NULL)
		str = "(null)";
	while (*str)
	{
		*len = write(1, str, 1);
		str++;
	}
}

void	ft_putnumb(long long int numb, int base, int *len)
{
	if (numb < 0)
	{
		*len = write(1, "-", 1);
		numb *= -1;
	}
	if (numb >= base)
		ft_putnumb(numb / base, base, len);
	len = write(1, &"0123456789abcdef"[numb % base], 1);
}

int		ft_printf(char *format, ...)
{
	va_list	ptr_arg;
	int		len;

	len = 0;
	va_start(ptr_arg, format);
	if (format == NULL)
		return (len);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			if (*format == 's')
				ft_putstr((char *)va_arg(ptr_arg, char *), &len);
			if (*format == 'i' || *format == 'd')
				ft_putnumb((long long int)va_arg(ptr_arg, int), 10, &len);
			if (*format == 'x')
				ft_putnumb((long long int)va_arg(ptr_arg, unsigned int), 16, &len);
		}
		else
			len = write(1, format, 1);
		format++;
	}
	return (len);
}