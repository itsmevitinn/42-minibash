/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:16:07 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/28 22:54:01 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	size_and_print_int(va_list list_arg)
{
	char	*converted;
	int		sizeconverted;

	converted = ft_itoa(va_arg(list_arg, int));
	sizeconverted = ft_putstr_int(converted);
	free (converted);
	return (sizeconverted);
}

int	size_and_print_uint(va_list list_arg, char check)
{
	char	*converted;
	int		sizeconverted;

	if (check == 'd' || check == 'i')
		converted = ft_utoa(va_arg(list_arg, int));
	else
		converted = ft_utoa(va_arg(list_arg, unsigned int));
	sizeconverted = ft_putstr_int(converted);
	free (converted);
	return (sizeconverted);
}

int	size_and_print_hex(va_list list_arg, char *basehex, char check)
{
	char	*converted;
	int		sizeconverted;

	if (check == 'x' || check == 'X')
		converted = ft_ultohex(va_arg(list_arg, unsigned int), basehex);
	else
		converted = ft_ultohex(va_arg(list_arg, unsigned long), basehex);
	sizeconverted = ft_putstr_int(converted);
	free (converted);
	return (sizeconverted);
}
