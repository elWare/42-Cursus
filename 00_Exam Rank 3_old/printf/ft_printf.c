/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:17:29 by jumarque          #+#    #+#             */
/*   Updated: 2025/04/02 09:09:32 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	ft_putstr(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		*len += write(1, str, 1);
		str++;
	}
}

void ft_putnumb(long long int numb, int base, int *len)
{
	if (numb < 0)
	{
		numb *= -1;
		*len += write(1, "-", 1);
	}
	if (numb >= base)
		ft_putnumb(numb / base, base, len);
	*len += write(1, &"0123456789abcdef"[numb % base], 1);
}

int	ft_printf(char *format, ...)
{
	va_list	ptr_args;
	int		len;

	va_start(ptr_args, format);
	len = 0;
	if (!format)
		return (len);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			if (*format == 's')
				ft_putstr((char *)va_arg(ptr_args, char *), &len);
			if (*format == 'i' || *format == 'd')
				ft_putnumb((long long int)va_arg(ptr_args, int), 10, &len);
			if (*format == 'x')
				ft_putnumb((long long int)va_arg(ptr_args, unsigned int), 16, &len);
		}
		else
			len += write (1, format, 1);
		format++;
	}
	va_end(ptr_args);
	return (len);
}