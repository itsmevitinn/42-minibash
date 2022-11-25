/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/24 22:50:52 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void)
{
	t_prompt prompt_msg;
	char *user_input;

	get_prompt_msg(&prompt_msg);

	//logname are not mallocated
	prompt_msg.logname = ft_strjoin(prompt_msg.logname, "@", 0);
	prompt_msg.final_msg = ft_strjoin(prompt_msg.logname, prompt_msg.hostname, 'a');
	prompt_msg.final_msg = ft_strjoin(prompt_msg.final_msg, ":", 1);
	prompt_msg.final_msg = ft_strjoin(prompt_msg.final_msg, prompt_msg.pwd, 'a');
	prompt_msg.final_msg = ft_strjoin(prompt_msg.final_msg, "$ ", 1);
	
	//print a prompt message and waits for user input from terminal
	user_input = readline(prompt_msg.final_msg);
	printf("Input from terminal: %s\n", user_input);
	free(prompt_msg.final_msg);
}

void	get_hostname(int *pipe_hostname)
{
	dup2(pipe_hostname[1], 1);
	execve("/bin/hostname", NULL, NULL);
}

void	get_prompt_msg(t_prompt *prompt_msg)
{
	int pipe_hostname[2];
	int child_hostname;

	//malloc len accordingly to 42 hostname's
	prompt_msg->hostname = malloc(6);
	
	//Receive the value of a environment variable (with malloc)
	prompt_msg->logname = getenv("LOGNAME");
	
	//Variable that will receive value from read
	pipe(pipe_hostname);
	//Process that will run execve and write the hostname in pipe
	child_hostname = fork();
	if (child_hostname == 0)
		get_hostname(pipe_hostname);
	//Wait untill child processs end
	waitpid(child_hostname, NULL, 0);
	//Read the hostname from pipe and send to variable "hostname"
	read(pipe_hostname[0], prompt_msg->hostname, 6);
	get_prompt_dir(prompt_msg);
}

void	get_prompt_dir(t_prompt *prompt_msg)
{
	char	*home;
	char	*current_dir;
	int		home_len;

	//receive the actual directory
	current_dir = getcwd(NULL, 0);
	//this is equal to "/Users/vsergio"
	home = ft_strjoin("/Users/", prompt_msg->logname, 0);
	home_len = ft_strlen(home);

	//check if the current dir have "/Users/username"
	if (ft_strncmp(current_dir, home, home_len) == 0)
	{
		//Replace "/Users/username" to "~" and copy the rest
		prompt_msg->pwd = ft_strjoin("~", &current_dir[home_len], 0);
		free(home);
		free(current_dir);
	}
	else
		prompt_msg->pwd = current_dir;
}
