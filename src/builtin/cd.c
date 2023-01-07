/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:54:31 by Vitor             #+#    #+#             */
/*   Updated: 2023/01/07 20:04:14 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	go_home(t_var_lst *env_lst, t_cmd_info *data, int *updater);
static void	oldpwd(t_var_lst *env, t_cmd_info *data, t_cmd_lst *cmd,
				int *updater);
static void	relative_or_absolute(char *path, t_cmd_info *data, int *updater,
				t_var_lst *env_lst);
static void	exec_cd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);

void	cd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env)
{
	if (data->qty == 1)
		exec_cd(cmd, data, env);
	else if (data->qty > 1)
	{
		cmd->pid = fork();
		if (!cmd->pid)
			exec_cd(cmd, data, env);
	}
}

static void	exec_cd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env)
{
	char	*old_dir;
	char	*path;
	int		updater;

	old_dir = getcwd(NULL, 0);
	path = cmd->args[1];
	updater = 1;
	if (!path || (!ft_strncmp(path, "~", 2)))
		go_home(env, data, &updater);
	else if (*path == '-' && ft_strlen(path) == 1)
		oldpwd(env, data, cmd, &updater);
	else
		relative_or_absolute(path, data, &updater, env);
	if (data->qty == 1)
	{
		if (updater)
			update_oldpwd(old_dir, env);
		change_content("PWD", getcwd(NULL, 0), env);
	}
}

static void	go_home(t_var_lst *env, t_cmd_info *data, int *updater)
{
	if (chdir(get_content("HOME", env)) == -1)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		if (data->qty != 1)
			exit(1);
		g_exit_status = 1;
		*updater = 0;
	}
	else
	{
		if (data->qty != 1)
			exit(0);
		g_exit_status = 0;
	}
}

static void	oldpwd(t_var_lst *env, t_cmd_info *data, t_cmd_lst *cmd,
		int *updater)
{
	if (get_env("OLDPWD", env))
	{
		ft_putstr_fd(get_content("OLDPWD", env), cmd->output);
		ft_putstr_fd("\n", cmd->output);
		chdir(get_content("OLDPWD", env));
		if (data->qty != 1)
			exit(0);
		g_exit_status = 0;
	}
	else
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", cmd->output);
		if (data->qty != 1)
			exit(1);
		g_exit_status = 1;
		*updater = 0;
	}
}

static void	relative_or_absolute(char *path, t_cmd_info *data, int *updater,
		t_var_lst *env_lst)
{
	if (!ft_strncmp(path, "~/", 2))
	{
		if (!exec_new_path(path, data->qty, env_lst, updater))
			return ;
	}
	else if (chdir(path) == -1)
	{
		no_such_file_or_directory(path, data->qty, updater);
		return ;
	}
	if (data->qty != 1)
		exit(0);
	g_exit_status = 0;
}
