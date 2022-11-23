/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_fractol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 08:59:49 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/05 12:14:00 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

long int	ft_atoi_fractol(char *str)
{
	long int	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
			str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (!check_atoi_fractol(str))
		suggest_exit();
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (res > 2147483647 || res < -2147483648)
			suggest_exit();
		str++;
	}
	return (sign * res);
}
