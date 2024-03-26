/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:36:10 by matesant          #+#    #+#             */
/*   Updated: 2024/03/26 12:25:20 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*ft_get_shell(void)
{
	static t_minishell	shell;

	return (&shell);
}

void	ft_process(t_minishell *shell)
{
	if (ft_tokenize(shell))
		return ;
	ft_print_stack(shell->tokens);
	//populate_command_list(shell);
	//print_cmd_list(shell->commands);
}

void	ft_loop(void)
{
	t_minishell	*shell;
	char		*line;

	shell = ft_get_shell();
	while (1)
	{
		ft_receive_signal();
		line = readline(PROMPT);
		if (!line)
			break ;
		shell->user_input = ft_strdup(line);
		add_history(line);
		free(line);
		if (shell->user_input[0] == '\0')
		{
			free(shell->user_input);
			continue ;
		}
		ft_process(shell);
		ft_clear_all(shell);
	}
	ft_free_env(shell);
	rl_clear_history();
}

int	main(void)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	ft_clone_env(shell);
	shell->teemo = -1;
	// ft_print_env_list(shell->env_list);
	ft_loop();
	return (0);
}
