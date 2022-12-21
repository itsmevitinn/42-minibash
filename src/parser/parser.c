/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:10:05 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/21 17:00:04 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void build_lst_cmd(t_cmd_lst **lst_cmd, char *line);
static void	parse_cmds(t_cmd_lst *lst_cmd, t_var_lst *env_lst);
static void initialize_ids(t_cmd_lst *lst_cmd);

t_cmd_lst *parse_input(char *line, t_var_lst *env_lst)
{
	t_cmd_lst *lst_cmd;

	lst_cmd = NULL;
	build_lst_cmd(&lst_cmd, line);
	parse_cmds(lst_cmd, env_lst);
	return (lst_cmd);
}

static void build_lst_cmd(t_cmd_lst **lst_cmd, char *line)
{
	char	**all_cmds;

	all_cmds = ft_split_quotes(line, '|');

	while (*all_cmds)
		ft_cmdadd_back(lst_cmd, ft_cmd_new(*all_cmds++));
	initialize_ids(*lst_cmd);
}

static void initialize_ids(t_cmd_lst *lst_cmd)
{
	int counter;

	counter = 0;
	while (lst_cmd)
	{
		lst_cmd->id = counter++;
		lst_cmd = lst_cmd->next;
	}
}

static void	parse_cmds(t_cmd_lst *lst_cmd, t_var_lst *env_lst)
{
	while (lst_cmd)
	{
		interpret_redirects(lst_cmd, lst_cmd->line);
		lst_cmd->args = ft_split_quotes(lst_cmd->line, ' ');
		interpret_vars(lst_cmd->args, env_lst);
		cleanup(lst_cmd->args);
		print_matrix(lst_cmd->args);
		lst_cmd = lst_cmd->next;
	}
}

void print_matrix(char **splitted_cmd)
{
	int i;

	i = 0;
	while (splitted_cmd[i])
	{
		printf("[%i] %s ", i, splitted_cmd[i]);
		i++;
	}
	printf("\n");
}
