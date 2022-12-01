/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:54:31 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/30 23:37:45 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd(char **splitted_cmd)
{
	char *error_msg;
	char *path;

	path = splitted_cmd[1];
	// char *old_dir;
	// old_dir = getcwd(NULL, 0);
	//after "export" done, update oldpwd and handle CDPATH env variables
	if (path == NULL)
	{
		if (chdir(getenv("HOME")) == -1)
		{
			perror("Wrong home value!");
			exit(1);
		}
	}
	else
		if (chdir(path) == -1)
		{
			error_msg = strerror(2);
			printf("bash: cd: %s: %s\n", splitted_cmd[1], error_msg);
			exit(1);
		}
	// free_matrix(splitted_cmd);
}
