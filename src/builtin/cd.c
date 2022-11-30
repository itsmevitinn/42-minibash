/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:54:31 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/30 01:22:23 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_lastpath(char *current_dir);
void	cd(char *new_dir)
{
	char *current_dir;
	// char *old_dir;
	char *dot_dir;

	//we need to update oldpwd env variable to this value
	// old_dir = getcwd(NULL, 0);
	if (new_dir == NULL)
		chdir(getenv("HOME"));
	else if (new_dir[0] == '/')
		chdir(new_dir);
	else if (!ft_strncmp(new_dir, "..", 2))
	{
		current_dir = getcwd(NULL, 0);
		dot_dir = remove_lastpath(current_dir);
		chdir(dot_dir);
		free(dot_dir);
	}
	else
	{
		current_dir = getcwd(NULL, 0);
		current_dir = ft_strjoin(current_dir, "/", 1);
		current_dir = ft_strjoin(current_dir, new_dir, 1);
		chdir(current_dir);
		free(current_dir);
	}
}

char	*remove_lastpath(char *current_dir)
{
	char *new_path;
	int max;
	int i;

	max = ft_strlen(current_dir);
	max--;
	i = 0;
	while(current_dir[max] && current_dir[max] != '/')
		max--;
	new_path = malloc(sizeof(char) * (max + 1));
	while(current_dir[i] && i < max)
	{
		new_path[i] = current_dir[i];
		i++;
	}
	new_path[i] = '\0';
	return (new_path);
}
