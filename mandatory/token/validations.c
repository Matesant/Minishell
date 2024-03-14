/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:30:22 by matesant          #+#    #+#             */
/*   Updated: 2024/03/14 10:59:34 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_spaces(char **str)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	end = ft_strlen(*str) - 1;
	while (ft_isspace((*str)[start]))
		start++;
	while (end >= start && ft_isspace((*str)[end]))
		end--;
	i = start;
	while (i <= end)
	{
		(*str)[i - start] = (*str)[i];
		i++;
	}
	(*str)[i - start] = '\0';
}

t_bool	ft_open_quotes(char *str)
{
	int	status;
	int	i;

	i = -1;
	status = 0;
	while (str[++i])
	{
		if (str[i] == '\"' && status == 0)
			status = 1;
		else if (str[i] == '\"' && status == 1)
			status = 0;
		else if (str[i] == '\'' && status == 0)
			status = 2;
		else if (str[i] == '\'' && status == 2)
			status = 0;
		if (str[i + 1] == '\0' && status != 0)
			return (TRUE);
	}
	return (FALSE);
}

void	ft_skip_quotes(char *str, unsigned long *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
	}
	else if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"')
			(*i)++;
	}
}

t_bool	ft_double_separators(char *line)
{
	unsigned long i;

	i = 0;
	while (line[i])
	{
		ft_skip_quotes(line, &i);
		if (line[i] == '&' && line[i + 1] == '&')
			return (TRUE);
		i++;
	}
	return (FALSE);
}
