/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:49:08 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/28 22:53:49 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_string(char char_tocheck, va_list list_arg)
{
	char	*bhex;
	int		prefix;

	bhex = "0123456789abcdef";
	if (char_tocheck == '%')
		return (ft_putchar_int('%'));
	else if (char_tocheck == 'c')
		return (ft_putchar_int(va_arg(list_arg, int)));
	else if (char_tocheck == 's')
		return (ft_putstr_int(va_arg(list_arg, char *)));
	else if (char_tocheck == 'p')
	{
		prefix = ft_putstr_int("0x");
		return (prefix + size_and_print_hex(list_arg, bhex, char_tocheck));
	}
	else if (char_tocheck == 'd' || char_tocheck == 'i')
		return (size_and_print_int(list_arg));
	else if (char_tocheck == 'u')
		return (size_and_print_uint(list_arg, char_tocheck));
	else if (char_tocheck == 'x')
		return (size_and_print_hex(list_arg, bhex, char_tocheck));
	else if (char_tocheck == 'X')
		return (size_and_print_hex(list_arg, "0123456789ABCDEF", char_tocheck));
	return (0);
}

int	ft_printf(const char *string, ...)
{
	va_list	list_arg;
	int		printf_return;
	int		i;

	i = 0;
	printf_return = 0;
	va_start (list_arg, string);
	while (string[i])
	{
		if (string[i] == '%')
		{
			printf_return += check_string(string[i + 1], list_arg);
			i++;
		}
		else
		{
			printf_return += ft_putchar_int(string[i]);
		}
		i++;
	}
	va_end(list_arg);
	return (printf_return);
}
