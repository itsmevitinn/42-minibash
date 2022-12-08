/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:54:31 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/07 23:40:27 by Vitor            ###   ########.fr       */
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
		chdir(getenv("HOME"));
		exit_status = 0;
	}
	else
		if (chdir(path) == -1)
		{
			error_msg = strerror(2);
			printf("bash: cd: %s: %s\n", splitted_cmd[1], error_msg);
			exit_status = 1;
		}
	// free_matrix(splitted_cmd);
}
