/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 09:51:57 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/07 19:56:15 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_oldpwd(char *old_dir, t_var_lst *env)
{
	char	*oldpwd_name;

	oldpwd_name = ft_strdup("OLDPWD");
	if (get_env("OLDPWD", env))
		change_content("OLDPWD", old_dir, env);
	else
		ft_varadd_back(&env, ft_var_new(oldpwd_name, old_dir));
}

int	exec_new_path(char *path, int cmd_qty, t_var_lst *env_lst, int *updater)
{
	char	*new_path;

	new_path = ft_strjoin(get_content("HOME", env_lst), "/", 0);
	new_path = ft_strjoin(new_path, path + 2, 'f');
	if (chdir(new_path) == -1)
	{
		no_such_file_or_directory(new_path, cmd_qty, updater);
		return (0);
	}
	free(new_path);
	return (1);
}

void	no_such_file_or_directory(char *path, int cmd_qty, int *updater)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	if (cmd_qty != 1)
		exit(1);
	g_exit_status = 1;
	*updater = 0;
}
