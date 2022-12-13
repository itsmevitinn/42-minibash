/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:10:05 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/13 18:24:41 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_cmd(char **splitted_cmd);
void	remove_chunk(char *cmd_line, int len);
void	generate_args(t_cmd_lst *lst_cmd);
static void	cmd_notfound(char *cmd_name);
static void free_paths (char **paths, int i);
static char **split_pipes(char *line);
static void build_lst_cmd(char **all_cmds);
void	get_filename(char *cmd_line, int offset);
void	redirect_checker(t_cmd_lst *lst_cmd);

void	parse_input(char *line, t_var_lst *env_lst)
{
	// int offset;

	env_lst++;
	// offset = 0;
	// while(line[offset])
	// {
	// 	if (line[offset] == '|')
	// 		build_cmd(line, offset);
	// 	offset++;
	// }
	char	**all_cmds;
	all_cmds = split_pipes(line);
	// if (!is_builtin(all_cmds, env_lst))
		// find_right_path(splitted_cmd);
}

static void build_lst_cmd(char **all_cmds)
{
	t_cmd_lst *lst_cmd;
	int offset;

	lst_cmd = NULL;
	offset = 0;
	while(all_cmds[offset])
		ft_cmdadd_back(&lst_cmd, ft_cmd_new(all_cmds[offset++]));
	while(lst_cmd)
	{
		printf("%s\n", lst_cmd->cmd_line);
		redirect_checker(lst_cmd);
		lst_cmd = lst_cmd->next;
	}
	generate_args(NULL);
}

void	redirect_checker(t_cmd_lst *lst_cmd)
{
	int offset;
	
	offset = 0;
	while(lst_cmd->cmd_line[offset])
	{
		if (lst_cmd->cmd_line[offset] == '<')
			get_filename(lst_cmd->cmd_line, offset);
		offset++;
	}
}

void	get_filename(char *cmd_line, int offset)
{
	char *buffer;
	int filename;
	int len;
	int end_cleaner;
	int start_clean;
	int buffer_offset;

	start_clean = offset;
	end_cleaner = 0;
	buffer_offset = 0;
	len = 0;
	offset++;
	end_cleaner++;
	while(cmd_line[offset] && ft_isspace(cmd_line[offset]))
	{
		end_cleaner++;
		offset++;
	}
	filename = offset;
	while(cmd_line[offset] && !ft_isspace(cmd_line[offset]))
	{
		end_cleaner++;
		offset++;
		len++;
	}
	buffer = malloc(sizeof(char) * (len + 1));
	while(cmd_line[filename] && !ft_isspace(cmd_line[filename]))
		buffer[buffer_offset++] = cmd_line[filename++];
	buffer[buffer_offset] = '\0';
	remove_chunk(&cmd_line[start_clean], end_cleaner);
	printf("redirect: %s\n", buffer);
	printf("cmd line after:%s\n", cmd_line);
}

void	remove_chunk(char *cmd_line, int len)
{
	char *aux;

	while(len >= 0)
	{
		aux = cmd_line;
		while(*aux)
		{
			*aux = aux[1];
			aux++;
		}
		len--;
	}
}

void	generate_args(t_cmd_lst *lst_cmd)
{
	while(lst_cmd)
	{
		lst_cmd->args = ft_split(lst_cmd->cmd_line, ' ');
		print_cmd(lst_cmd->args);
		lst_cmd = lst_cmd->next;
	}
}

static char **split_pipes(char *line)
{
	char	**all_cmds;

	int offset;

	offset = 0;
	all_cmds = ft_split_quotes(line, '|');
	
	build_lst_cmd(all_cmds);
	return (NULL);
	// cmd = ft_split_quotes(cmd[0], ' ');
	// while (cmd[args++])
	//Cut the quotes at the edges of each arguments
		// cmd[args] = ft_strtrim_edges(cmd[args], "'\"");
	// return (cmd);
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
