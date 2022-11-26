/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/26 11:52:52 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	get_prompt_msg(t_prompt *prompt_msg)
{
	
	//Receive the value of a environment variable (without malloc)
	prompt_msg->logname = getenv("LOGNAME");
	get_hostname(prompt_msg);
	get_current_dir(prompt_msg);
}

void	get_hostname(t_prompt *prompt_msg)
{
	int pipe_hostname[2];
	int process_pid;

	//malloc len accordingly to 42 hostname's
	prompt_msg->hostname = malloc(6);
	pipe(pipe_hostname);
	//Process that will run execve and write the hostname in pipe
	process_pid = fork();
	if (process_pid == 0)
	{
		dup2(pipe_hostname[1], 1);
		execve("/bin/hostname", NULL, NULL);
	}
	//Wait untill child processs end
	waitpid(process_pid, NULL, 0);
	//Read the hostname from pipe and send to variable "prompt_msg->hostname"
	read(pipe_hostname[0], prompt_msg->hostname, 6);
}

void	get_current_dir(t_prompt *prompt_msg)
{
	char	*home;
	char	*pwd;
	int		home_len;

	//receive the actual directory (pwd)
	pwd = getcwd(NULL, 0);
	//this is equal to "/Users/vsergio"
	home = ft_strjoin("/Users/", prompt_msg->logname, 0);
	home_len = ft_strlen(home);

	//check if the current dir have "/Users/username"
	if (ft_strncmp(pwd, home, home_len) == 0)
	{
		//Replace "/Users/username" to "~" and copy the rest
		prompt_msg->current_dir = ft_strjoin("~", &pwd[home_len], 0);
		free(home);
		free(pwd);
	}
	else
		prompt_msg->current_dir = pwd;
}

void	build_prompt_msg(t_prompt *prompt_msg)
{
	//logname hasnt malloc
	prompt_msg->display = ft_strjoin(prompt_msg->logname, "@", 0);
	prompt_msg->display = ft_strjoin(prompt_msg->display, prompt_msg->hostname, 'a');
	prompt_msg->display = ft_strjoin(prompt_msg->display, ":", 1);
	prompt_msg->display = ft_strjoin(prompt_msg->display, prompt_msg->current_dir, 'a');
	prompt_msg->display = ft_strjoin(prompt_msg->display, "$ ", 1);
}
