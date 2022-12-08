/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:10:05 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/08 15:20:54 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	find_right_path(char **splitted_cmd);
static void	print_cmd(char **splitted_cmd);
static void	cmd_notfound(char *cmd_name);
static void free_paths (char **paths, int i);

void	parse_input(char *user_input, t_var_lst *env_lst)
{
	char	**splitted_cmd;
	int		args;

	args = 0;
	//Split all the spaces and preserve whats is inside quotes
	splitted_cmd = ft_split_quotes(user_input, ' ');
	while (splitted_cmd[args++])
	//Cut the quotes at the edges of each arguments
		splitted_cmd[args] = ft_strtrim_edges(splitted_cmd[args], "'\"");
	print_cmd(splitted_cmd);
	if (!isbuiltin(splitted_cmd, env_lst))
		find_right_path(splitted_cmd);
}

void	find_right_path(char **splitted_cmd)
{
	char	**paths;
	char	*full_path;
	int		i;
	int success;

	i = 0;
	success = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/", 1);
		full_path = ft_strjoin(full_path, splitted_cmd[0], 1);
		if (!access(full_path, F_OK | X_OK))
		//right path found
		{
			exec_bin_cmd(full_path, splitted_cmd);
			success = 1;
			break;
		}
		//free wrong path
		free(full_path);
		i++;
	}
	if (!success)
		cmd_notfound(splitted_cmd[0]);
	free_paths(paths, i);
}

static void	cmd_notfound(char *cmd_name)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit_status = 127;
}

static void free_paths (char **paths, int i)
{
	//we iterate here because the current "i" was already freed by strjoin
	while (paths[i++])
		free(paths[i]);
	free(paths);
}

static void	print_cmd(char **splitted_cmd)
{
	int i;

	i = 0;
	while(splitted_cmd[i])
	{
		printf("[%i] %s\n", i, splitted_cmd[i]);
		i++;
	}
}
