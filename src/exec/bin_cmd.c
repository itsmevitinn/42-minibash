/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:50:59 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/28 10:19:51 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void free_paths (int i, char **paths);
void	run_bin_cmd(char *command)
{
	char		**splitted_paths;
	char		**arguments;
	int			countargs;

	countargs = 0;
	arguments = ft_split_quotes(command, ' ');
	while (arguments[countargs++])
		arguments[countargs] = ft_strtrim_edges(arguments[countargs], "'\"");
	splitted_paths = ft_split(getenv("PATH"), ':');
	exec_bin_cmd(splitted_paths, arguments);
}

void	exec_bin_cmd(char **paths, char **arguments)
{
	char	*path_completed;
	int		process_pid;
	int		i;

	i = 0;
	while (paths[i])
	{
		path_completed = ft_strjoin(paths[i], "/", 1);
		path_completed = ft_strjoin(path_completed, arguments[0], 1);
		if (!access(path_completed, F_OK | X_OK))
		{
			process_pid = fork();
			if (!process_pid)
				execve(path_completed, arguments, NULL);
			waitpid(process_pid, NULL, 0);
			free(path_completed);
			break;
		}
		free(path_completed);
		i++;
	}
	free(paths);
	// error_msg("zsh: command not found", 127);
}

static void free_paths (int i, char **paths)
{
	//we iterate here because the current "i" was already freed by strjoin
	while (paths[i++])
		free(paths[i]);
	free(paths);
}
