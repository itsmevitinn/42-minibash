/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:53:23 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/06 16:50:10 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (try_echo_execution(cmd))
		return ;
	else if (try_cd_execution(cmd, data, env_lst))
		return ;
	else if (try_pwd_execution(cmd))
		return ;
	else if (try_export_execution(cmd, data, env_lst))
		return ;
	else if (try_unset_execution(cmd, data, env_lst))
		return ;
	else if (try_env_execution(cmd, env_lst))
		return ;
	else if (try_exit_execution(cmd, data))
		return ;
}
