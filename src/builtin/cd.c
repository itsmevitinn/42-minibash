/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:54:31 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/22 11:57:58 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static void oldpwd(t_var_lst *env);
static void relative_or_absolute(char *path);
static void update_oldpwd(char *current_dir, t_var_lst *env);

void cd(t_cmd_lst *cmd, t_var_lst *env_lst)
{
	char *current_dir;
	char *path;

	current_dir = getcwd(NULL, 0);
	path = cmd->args[1];
	if (!path)
		chdir(get_content("HOME", env_lst));
	else if (*path == '-' && ft_strlen(path) == 1)
		oldpwd(env_lst);
	else
		relative_or_absolute(path);
	update_oldpwd(current_dir, env_lst);
	g_exit_status = 0;
}

static void oldpwd(t_var_lst *env)
{
	if (get_env("OLDPWD", env))
	{
		printf("%s\n", get_content("OLDPWD", env));
		chdir(get_content("OLDPWD", env));
	}
	else 
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		g_exit_status = 1;
	}
}

static void relative_or_absolute(char *path)
{
	char *error_msg;

	if (chdir(path) == -1)
	{
		error_msg = strerror(2);
		printf("bash: cd: %s: %s\n", path, error_msg);
		g_exit_status = 1;
	}
}

static void update_oldpwd(char *current_dir, t_var_lst *env)
{
	if (get_env("OLDPWD", env))
		change_content("OLDPWD", current_dir, env);
	else
		ft_varadd_back(&env, ft_var_new("OLDPWD", current_dir));
}
