/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/23 15:08:16 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

static void	build_prompt_msg(t_prompt *prompt_msg);
static void	get_current_dir(t_prompt *prompt_msg);
static void	get_hostname(t_prompt *prompt_msg);
static void	populate_hostname(t_prompt *prompt_msg, char *buffer, int readed);
static void	get_prompt_msg(t_prompt *prompt_msg);

char	*display_prompt(void)
{
	char		*user_input;
	t_prompt	prompt_msg;

	user_input = NULL;
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
	int pipe_hostname[2];
	int process_pid;
	char *buffer;
	int readed;
	char	*args[] = {NULL};

	buffer = malloc(1000);
	pipe(pipe_hostname);
	process_pid = fork();
	if (process_pid == 0)
	{
		dup2(pipe_hostname[1], 1);
		execve("/bin/hostname", args, NULL);
	}
	waitpid(process_pid, NULL, 0);
	readed = read(pipe_hostname[0], buffer, 1000);
	populate_hostname(prompt_msg, buffer, readed);
	free(buffer);
}

static void	populate_hostname(t_prompt *prompt_msg, char *buffer, int readed)
{
	int i;

	i = 0;
	prompt_msg->hostname = malloc(sizeof(char) * (readed + 1));
	while(buffer[i] && buffer[i] != '\n')
	{
		prompt_msg->hostname[i] = buffer[i];
		i++;
	}
	prompt_msg->hostname[i] = '\0';
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
	prompt_msg->display = ft_strjoin(prompt_msg->display, prompt_msg->hostname, 'a');
	prompt_msg->display = ft_strjoin(prompt_msg->display, ":", 1);
	prompt_msg->display = ft_strjoin(prompt_msg->display, prompt_msg->current_dir, 'a');
	prompt_msg->display = ft_strjoin(prompt_msg->display, "$ ", 1);
}
