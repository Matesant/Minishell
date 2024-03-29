/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:57:33 by matesant          #+#    #+#             */
/*   Updated: 2024/03/28 12:43:18 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_env(void)
{
	char	*oldpwd;
	char	*pwd;
	t_env	*cur;

	cur = ft_get_shell()->env_list;
	oldpwd = ft_getenv("PWD");
	pwd = getcwd(NULL, 0);
	while (cur)
	{
		if (!ft_strncmp(cur->key, "OLDPWD", 6))
		{
			free(cur->value);
			cur->value = ft_strdup(oldpwd);
			free(oldpwd);
			oldpwd = NULL;
		}
		if (!ft_strncmp(cur->key, "PWD", 3))
		{
			free(cur->value);
			cur->value = ft_strdup(pwd);
			free(pwd);
			pwd = NULL;
		}
		cur = cur->next;
	}
}

void	ft_chdir(char *path)
{
	if (!chdir(path))
		ft_set_env();
	else
	{
		ft_error("cd: no such file or directory", 1);
		return ;
	}
}

t_bool	ft_isdir(char *path)
{
	struct stat	statbuf;

	if (access(path, F_OK) == -1)
	{
		ft_error("cd: no such file or directory", 1);
		return (FALSE);
	}
	if (lstat(path, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
			return (TRUE);
		else
		{
			ft_error("cd: not a directory", 1);
			return (FALSE);
		}
	}
	return (FALSE);
}

void	ft_cd_builtin(char **argv)
{
	char	*path;

	if (ft_matrice_len(argv) > 2)
	{
		ft_error("cd: too many arguments", 1);
		return ;
	}
	if (!argv || !argv[1] || !argv[1][0] || !ft_strcmp(argv[1], " ")
		|| !ft_strcmp(argv[1], "--") || !ft_strcmp(argv[1], "~"))
	{
		ft_rlstnew(path = ft_getenv("HOME"));
		if (!path)
		{
			ft_error("cd: HOME not set", 1);
			return ;
		}
	}
	else
	{
		path = argv[1];
	}
	if (ft_isdir(path))
		ft_chdir(path);
}
