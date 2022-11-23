/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_atoi_numbers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:44:39 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/05 12:19:44 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	check_atoi_numbers(char *string)
{
	char	*temp;

	temp = string;
	if (*temp == 0)
		return (0);
	while (*temp)
	{
		if (*temp >= '0' && *temp <= '9')
			temp++;
		else
			return (0);
	}
	return (1);
}

int	check_atoi_fractol(char *string)
{
	char	*temp;
	int		dots;

	temp = string;
	dots = 0;
	if (*temp == 0 || *string == '.')
		return (0);
	while (*temp)
	{
		if (*temp >= '0' && *temp <= '9')
			temp++;
		else if (*temp == '.')
		{
			dots++;
			temp++;
		}
		else
			return (0);
	}
	if (dots > 1)
		return (0);
	return (1);
}
