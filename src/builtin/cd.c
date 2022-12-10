/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:54:31 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/09 23:23:44 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static char *get_content(char *name, t_var_lst *env);
static int is_minus(char *path);
static void update_oldpwd(char *path, char *current_dir, t_var_lst *env);
static int is_updatable(char *path);

void	cd(char **splitted_cmd, t_var_lst *env)
{
	char *current_dir;
	char *error_msg;
	char *path;
	
	current_dir = getcwd(NULL, 0);
	path = splitted_cmd[1];

	if (path == NULL)
	{
		chdir(get_content("HOME", env));
		exit_status = 0;
	}
	else if (is_minus(path))
	{
		printf("minus ok\n");
		if (is_env("OLDPWD", env))
		{
			chdir(get_content("OLDPWD", env));
			printf("%s\n", get_content("OLDPWD", env));
		}
		else
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		exit_status = 0;
	}
	else
		if (chdir(path) == -1)
		{
			error_msg = strerror(2);
			printf("bash: cd: %s: %s\n", splitted_cmd[1], error_msg);
			exit_status = 1;
		}
	update_oldpwd(path, current_dir, env);
}

static void update_oldpwd(char *path, char *current_dir, t_var_lst *env)
{
	if (is_env("OLDPWD", env) && is_updatable(path))
	{
		printf("updating oldpwd\n");
		change_content("OLDPWD", current_dir, env);
	}
	else if (is_updatable(path))
	{
		printf("creating oldpwd");
		ft_varadd_back(&env, ft_var_new("OLDPWD", current_dir));
	}
	printf("none\n");
}

static int is_updatable(char *path)
{
	if (!is_minus(path) || path == NULL)
		return (1);
	return (0);
}

static int is_minus(char *path)
{
	char first;
	int len;

	first = *path;
	len = 0;
	while(*path)
	{
		path++;
		len++;
	}
	if (first == '-' && len == 1)
		return (1);
	return (0);
}

static char *get_content(char *name, t_var_lst *env)
{
	int	name_len;

	name_len = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(name, env->name, name_len + 1))
			return(env->content);
		else
			env = env->next;
	}
	return (NULL);
}