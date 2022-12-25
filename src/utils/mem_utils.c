/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:45:19 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/25 14:45:37 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_matrix(char **cmd_args)
{
	int i;

	i = 0;
	while(cmd_args[i])
		free(cmd_args[i++]);
	free(cmd_args);
}

void free_paths(char **paths, int i)
{
	// we iterate here because the current "i" was already freed by strjoin
	while (paths[i++])
		free(paths[i]);
	free(paths);
}
