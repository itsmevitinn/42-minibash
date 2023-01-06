/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:54:31 by Vitor             #+#    #+#             */
/*   Updated: 2023/01/06 18:35:47 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	go_home(t_var_lst *env_lst, t_cmd_info *data, int *updater);
static void	oldpwd(t_var_lst *env, t_cmd_info *data, t_cmd_lst *cmd,
				int *updater);
static void	relative_or_absolute(char *path, t_cmd_info *data, int *updater, t_var_lst *env_lst);
static void	exec_cd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst);

void	cd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	if (data->qty == 1)
		exec_cd(cmd, data, env_lst);
	else if (data->qty > 1)
	{
		cmd->pid = fork();
		if (!cmd->pid)
			exec_cd(cmd, data, env_lst);
	}
}

static void	exec_cd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	char	*current_dir;
	char	*path;
	int		updater;

	current_dir = getcwd(NULL, 0);
	path = cmd->args[1];
	updater = 1;
	if (!path || (*path == '~' && ft_strlen(path) == 1))
		go_home(env_lst, data, &updater);
	else if (*path == '-' && ft_strlen(path) == 1)
		oldpwd(env_lst, data, cmd, &updater);
	else
		relative_or_absolute(path, data, &updater, env_lst);
	if (data->qty == 1)
	{
		if (updater)
			update_oldpwd(current_dir, env_lst);
	}
}

static void	go_home(t_var_lst *env_lst, t_cmd_info *data, int *updater)
{
	int	ret_chdir;

	ret_chdir = chdir(get_content("HOME", env_lst));
	if (ret_chdir == -1)
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

static void	relative_or_absolute(char *path, t_cmd_info *data, int *updater, t_var_lst *env_lst)
{
	int		ret_chdir;
	char	*home;

	if (!ft_strncmp(path, "~/", 2))
	{
		home = ft_strjoin(get_content("HOME", env_lst), "/", 0);
		path = ft_strjoin(home, path + 2, 'f');
	}
	ret_chdir = chdir(path);
	if (ret_chdir == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
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
