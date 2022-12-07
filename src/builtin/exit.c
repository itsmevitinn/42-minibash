/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:11:22 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/06 10:09:12 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void ft_exit(char **splitted_cmd)
{
	int status;

	if (splitted_cmd[1])
	{
		status = ft_atoi(splitted_cmd[1]);
		exit(status);
	}
	else
	//If n is omitted, the exit status is that of the last command executed.
		exit(0);
}
