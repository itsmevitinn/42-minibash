/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:54:31 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/30 22:53:30 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd(char *new_dir)
{
	char *error_msg;
	// char *old_dir;
	// old_dir = getcwd(NULL, 0);
	//after "export" done, update oldpwd and handle CDPATH env variables
	if (new_dir == 0)
	{
		if (chdir(getenv("HOME")) == -1)
		{
			perror("Wrong home value!");
			exit(1);
		}
	}
	else
		if (chdir(new_dir) == -1)
		{
			error_msg = strerror(2);
			printf("bash: cd: %s: %s\n", new_dir, error_msg);
			exit(1);
		}
}
