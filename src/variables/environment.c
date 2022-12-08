/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:20:58 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/08 15:19:38 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern char **environ;

#include "../../include/minishell.h"

void	initialize_env(t_var_lst **env_lst)
{
	int		i;
	char	**temp;

	i = 0;
	*env_lst = NULL;
	while (environ[i])
	{
		temp = ft_split(environ[i], '=');
		ft_varadd_back(env_lst, ft_var_new(*temp, *(temp + 1)));
		free(temp);
		i++;
	}
}
