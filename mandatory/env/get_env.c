/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:54:16 by almarcos          #+#    #+#             */
/*   Updated: 2024/04/02 16:30:29 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_get_env_list(void)
{
	t_minishell	*shell;
	char		**env;
	int			i;
	char		**split;

	shell = ft_get_shell();
	i = 0;
	env = shell->env;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		ft_lstend_var(&shell->env_list, split[0], split[1], 0);
		ft_delete_matrice(split);
		i++;
	}
}

void	ft_clone_env(t_minishell *shell)
{
	int		i;
	char	**env;

	i = 0;
	while (__environ[i])
		i++;
	env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (__environ[i])
	{
		env[i] = ft_strdup(__environ[i]);
		i++;
	}
	shell->env = env;
	ft_get_env_list();
}

char	*ft_getenv(char *env)
{
	t_minishell	*shell;
	t_env		*curr;

	shell = ft_get_shell();
	curr = shell->env_list;
	if (!env)
		return (NULL);
	while (curr)
	{
		if (!ft_strcmp(curr->key, env))
			return (ft_strdup(curr->value));
		if (!ft_strcmp(env, "?"))
			return (ft_itoa(shell->exit_status));
		if (!ft_strcmp(env, "$"))
			return (ft_strdup(&shell->teemo));
		curr = curr->next;
	}
	if (!curr)
		return (ft_strdup(""));
	return (NULL);
}

void	get_standard_fds(t_minishell *shell)
{
	shell->standard_fds[0] = dup(STDIN_FILENO);
	shell->standard_fds[1] = dup(STDOUT_FILENO);
}
