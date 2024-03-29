/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:38:01 by matesant          #+#    #+#             */
/*   Updated: 2024/03/26 11:51:36 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_builtin(char **argv)
{
	t_env	*env;

	(void)argv;
	env = ft_get_shell()->env_list;
	while (env)
	{
		if (env->value)
			ft_printf_fd(STDOUT_FILENO, "%s=%s\n", env->key, env->value);
		else if (!env->value)
			ft_printf_fd(STDOUT_FILENO, "%s=\n", env->key);
		env = env->next;
	}
}
