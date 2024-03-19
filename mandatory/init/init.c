/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:54:16 by almarcos          #+#    #+#             */
/*   Updated: 2024/03/15 17:37:52 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_create_var_list(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		ft_error("malloc error");
	ft_bzero(new, sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	ft_lstend_var(t_env **env_list, char *key, char *value)
{
	t_env	*curr;

	curr = *env_list;
	if (!*env_list)
	{
		*env_list = ft_create_var_list(key, value);
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = ft_create_var_list(key, value);
	if (!curr->next)
		ft_error("malloc error");
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
		ft_lstend_var(&shell->env_list, split[0], split[1]);
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
	ft_delete_matrice(env);
}

char	*ft_getenv(char *env)
{
	(void)env;
	return ("opa");
}
