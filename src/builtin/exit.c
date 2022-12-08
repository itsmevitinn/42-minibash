/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:11:22 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/08 00:06:38 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void ft_exit(char **splitted_cmd)
{
	int status;

	if (splitted_cmd[1])
	{
		status = ft_atoi(splitted_cmd[1]);
		printf("new status: %i\n", status);
		exit(status);
	}
	else
	{
		//If n is omitted, the exit status is that of the last command executed.
		printf("last status: %i\n", exit_status);
		exit(exit_status);
	}
}