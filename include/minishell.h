/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:34:40 by matesant          #+#    #+#             */
/*   Updated: 2024/04/16 17:11:47 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "defines.h"
# include "types.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*----------------------------------MAIN-STRUCT----------------------------*/
t_minishell		*ft_get_shell(void);
/*-------------------------------------------------------------------------*/

/*------------------------------------TOKEN--------------------------------*/
//#Validation pre-tokenization
t_bool			ft_open_quotes(char *str);
void			ft_skip_quotes(char *str, unsigned long *i);
char			*ft_forbidden_separators(char *line);
t_bool			ft_only_spaces(char *line);

//#Tokenization
int				ft_is_separator(char *str);
t_bool			ft_tokenize(t_minishell *shell);
void			ft_clear_spaces(char **str);
char			*ft_check_syntax(t_token *tokens);
void			ft_quotes_treatment(char **str);
void			ft_remove_quotes(void);
/*-------------------------------------------------------------------------*/

/*-----------------------------------EXPANSION-----------------------------*/
void			ft_clone_env(t_minishell *shell);
char			*ft_getenv(char *env);
t_bool			ft_var_expansion(void);
void			ft_replace_teemo(t_token *curr, char c, int *i, int *status);
t_bool			ft_quotes_status(char c, int status);
/*-------------------------------------------------------------------------*/

/*------------------------------------PARSER-------------------------------*/
void			append_command(t_command **cmd_list, t_command *new);
t_command		*new_command(char *name, t_bool pipe);
void			free_cmd_list(t_command **cmd_list);
t_command		*get_last_command(t_command *cmd);
int				get_len_args(t_token *token);
void			add_dummy_node(t_command **cmd);
void			populate_command_list(t_minishell *minishell);
void			get_args(t_token **tokens, t_command *last);
void			handle_words(t_token **token, t_command *last);
void			handle_pipe(t_token **token, t_command **cmd,
					unsigned *command_index);
void			handle_trunc_append_input(t_token **token, t_command *last);
void			free_io(t_io *io);
void			set_commands_with_no_argv(t_command *cmd);
void			create_argv(t_token **tokens, t_command *last);
void			add_to_argv(t_token **tokens, t_command *last);
int				array_len(char **array);
void			open_output_file(t_token *tokens, t_command *last);
void			open_input_file(t_token *tokens, t_command *last);
void			get_standard_fds(t_minishell *shell);
void			update_argv(t_command *last, char **split);
char			*get_file_name(t_bool is_first);
unsigned		count_commands(t_token *token);
t_herdoc_file	*new_file(char *file_name);
t_herdoc_file	*get_last_file(t_herdoc_file *head);
void			append_file(t_herdoc_file **head, t_herdoc_file *new);
void			free_here_docs(t_heredoc **hd);
t_bool			check_here_docs(t_minishell *shell);
t_bool			execute_here_doc(char *delimiter, unsigned index, t_heredoc *hd,
					t_bool is_first);
void			init_heredocs(t_token *tokens);
void			handle_heredoc(t_token **tokens, t_command *last,
					unsigned command_index);
void			populate_file(char *file, t_bool var, char *delimiter);
char			*expand_vars(char *line);
int				len_next_alphanum(char *str);
t_bool			have_quotes(char *delimiter);
char			*remove_quotes(char *delimiter);
/*------------------------------------------------------------------------*/

/*------------------------------------EXIT--------------------------------*/
t_bool		ft_error(char *str, int exit_code);
void		ft_lstend(t_token **tokens, char *str, int type);
void		ft_garbage_clear(t_gc **garbage);
void		ft_rlstnew(void *content);
void		clear_exit(t_minishell *shell, t_bool to_exit);
void		ft_invalid_key(char *key, char *value);
t_bool		ft_pre_token_err(char *line);
void		ft_reset_v(t_v **v);
/*------------------------------------------------------------------------*/

/*------------------------------------LIST--------------------------------*/
t_token			*ft_create_list(char *str, int type);
void			ft_free_tokens(t_minishell *shell);
void			ft_free_env(t_minishell *shell);
void			ft_lstend_var(t_env **env_list, char *key, char *value,
					int equal);
int				ft_envsize(t_env *env);
/*------------------------------------------------------------------------*/

/*---------------------------------DEBUGGING------------------------------*/
void			ft_print_stack(t_token *stack);
void			print_cmd_list(t_command *list);
void			ft_print_env_list(t_env *env_list);
void			ft_print_matrice(char **matrice);
/*------------------------------------------------------------------------*/

/*----------------------------------BUILT-IN------------------------------*/
void			ft_echo_builtin(char **argv);
void			ft_pwd_builtin(char **argv);
void			ft_env_builtin(char **argv);
void			ft_cd_builtin(char **argv);
void			ft_exit(char **argv);
void			ft_export(char **argv);
void			ft_print_in_order(char **env);
t_bool			ft_already_exists(char *key);
void			ft_change_value(char *key, char *value, int equal);
void			ft_unset(char **argv);
t_bool			ft_valid_key(char *key);
/*------------------------------------------------------------------------*/

/*----------------------------------SIGNALS-------------------------------*/
void			ft_receive_signal(void);
t_bool			ft_handle_cntl_c(int sig);
void			cmd_signal(void);
void			ft_reset_promp(int signal, siginfo_t *info, void *context);
/*------------------------------------------------------------------------*/

/*---------------------------------EXECUTION------------------------------*/
void		create_pipes(t_command *cmds);
t_bool		check_redirect_files(t_command *cmd);
void		set_pipes(t_command *cmd);
char		**get_paths(void);
char		*find_executable(t_command *cmd);
void		run_commands(t_minishell *shell, t_command *cmd);
void		wait_childs(t_minishell *shell);
void		executor(t_minishell *shell);
void		handle_vars(t_token **tokens, t_command *last);
t_bool		have_spaces(char *str);
void		ctrl_c_heredoc(int sig);
char		**list_to_array(t_env *vars);
void		close_all_fds(void);
/*------------------------------------------------------------------------*/
#endif
