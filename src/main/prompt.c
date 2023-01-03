/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/03 15:58:30 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	build_prompt_msg(t_prompt *prompt_msg);
static void	get_current_dir(t_prompt *prompt_msg);
static void	get_hostname(t_prompt *prompt_msg);
static void	get_prompt_msg(t_prompt *prompt_msg);

char	*display_prompt(void)
{
	char		*user_input;
	t_prompt	prompt_msg;

	get_prompt_msg(&prompt_msg);
	build_prompt_msg(&prompt_msg);
	user_input = readline(prompt_msg.display);
	free(prompt_msg.display);
	return (user_input);
}

static void	get_prompt_msg(t_prompt *prompt_msg)
{
	prompt_msg->logname = getenv("LOGNAME");
	get_hostname(prompt_msg);
	get_current_dir(prompt_msg);
}

static void	get_hostname(t_prompt *prompt_msg)
{
	int		pipe_hostname[2];
	char	**args;

	args = ft_split("hostname", ' ');
	pipe(pipe_hostname);
	if (!fork())
	{
		dup2(pipe_hostname[1], 1);
		execve("/bin/hostname", args, NULL);
	}
	free(*args);
	free(args);
	wait(NULL);
	prompt_msg->hostname = get_next_line(pipe_hostname[0]);
	prompt_msg->hostname[ft_strlen(prompt_msg->hostname) - 1] = '\0';
}

static void	get_current_dir(t_prompt *prompt_msg)
{
	char	*home;
	char	*pwd;
	int		home_len;

	pwd = getcwd(NULL, 0);
	home = ft_strjoin("/Users/", prompt_msg->logname, 0);
	home_len = ft_strlen(home);
	if (ft_strncmp(pwd, home, home_len) == 0)
	{
		prompt_msg->current_dir = ft_strjoin("~", &pwd[home_len], 0);
		free(pwd);
	}
	else
		prompt_msg->current_dir = pwd;
	free(home);
}

static void	build_prompt_msg(t_prompt *prompt_msg)
{
	prompt_msg->display = ft_strjoin(prompt_msg->logname, "@", 0);
	prompt_msg->display = ft_strjoin(prompt_msg->display,
			prompt_msg->hostname, 'a');
	prompt_msg->display = ft_strjoin(prompt_msg->display, ":", 'f');
	prompt_msg->display = ft_strjoin(prompt_msg->display,
			prompt_msg->current_dir, 'a');
	prompt_msg->display = ft_strjoin(prompt_msg->display, "$ ", 'f');
}
