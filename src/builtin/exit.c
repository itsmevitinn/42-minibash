/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:11:22 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/20 12:50:11 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void ft_exit(char **cmd_args)
{
	int status;

	if (cmd_args[1])
	{
		status = ft_atoi(cmd_args[1]);
		printf("new status: %i\n", status);
		exit(status);
	}
	else
	{
		//If n is omitted, the exit status is that of the last command executed.
		printf("last status: %i\n", g_exit_status);
		exit(g_exit_status);
	}
}
