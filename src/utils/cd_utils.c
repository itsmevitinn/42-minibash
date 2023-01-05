/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 09:51:57 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/05 09:52:52 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_oldpwd(char *current_dir, t_var_lst *env)
{
	if (get_env("OLDPWD", env))
		change_content("OLDPWD", current_dir, env);
	else
		ft_varadd_back(&env, ft_var_new("OLDPWD", current_dir));
}
