/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:54:31 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/24 17:36:37 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static void oldpwd(t_var_lst *env, t_cmd_info *data, t_cmd_lst *cmd, int *updater);
static void relative_or_absolute(char *path, t_cmd_info *data);
static void update_oldpwd(char *current_dir, t_var_lst *env);

void cd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	char *current_dir;
	char *path;
	int updater;
	int status;

	updater = 1;
	current_dir = getcwd(NULL, 0);
	path = cmd->args[1];
	if (cmd->delimiter)
	{
		if (!fork())
		{
			restore_sigint();
			get_heredoc_input(cmd);
			exit(0);
		}
		wait(&status);
		if (!WIFEXITED(status))
			return;
	}
	if (data->qty == 1)
	{
		if (!path)
			chdir(get_content("HOME", env_lst));
		else if (*path == '-' && ft_strlen(path) == 1)
			oldpwd(env_lst, data, cmd, &updater);
		else
			relative_or_absolute(path, data);
		if (updater)
			update_oldpwd(current_dir, env_lst);
		g_exit_status = 0;
	}
	else if (data->qty != 1)
	{
		cmd->pid = fork();
		if (!cmd->pid)
		{
			if (!path)
				chdir(get_content("HOME", env_lst));
			else if (*path == '-' && ft_strlen(path) == 1)
				oldpwd(env_lst, data, cmd, &updater);
			else
				relative_or_absolute(path, data);
			exit(0);
		}
	}
	if (cmd->id < (data->qty - 1))
		close(data->pipes[cmd->id][1]);
	waitpid(cmd->pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
}

static void oldpwd(t_var_lst *env, t_cmd_info *data, t_cmd_lst *cmd, int *updater)
{
	if (get_env("OLDPWD", env))
	{
		ft_putstr_fd(get_content("OLDPWD", env), cmd->output);
		ft_putstr_fd("\n", cmd->output);
		chdir(get_content("OLDPWD", env));
	}
	else
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", cmd->output);
		if (data->qty != 1)
			exit(1);
		else if (data->qty == 1)
			g_exit_status = 1;
		*updater = 0;
	}
}

static void relative_or_absolute(char *path, t_cmd_info *data)
{
	int ret_chdir;

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
	}
}

static void update_oldpwd(char *current_dir, t_var_lst *env)
{
	if (get_env("OLDPWD", env))
		change_content("OLDPWD", current_dir, env);
	else
		ft_varadd_back(&env, ft_var_new("OLDPWD", current_dir));
}