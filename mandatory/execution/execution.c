#include "minishell.h"

void	restore_standard_fds(t_minishell *shell)
{
	dup2(shell->standard_fds[0], STDIN_FILENO);
	dup2(shell->standard_fds[1], STDOUT_FILENO);
}

void	create_pipes(t_command *cmds)
{
	while (cmds)
	{
		if (cmds->output_to_pipe)
			pipe(cmds->pipe);
		cmds = cmds->next;
	}
}

void	close_needless_pipes(t_command *cmds, t_command *to_keep)
{
	while (cmds)
	{
		if (cmds->output_to_pipe && cmds != to_keep)
		{
			close(cmds->pipe[0]);
			close(cmds->pipe[1]);
		}
		cmds = cmds->next;
	}
}

void	set_pipes(t_command *cmd)
{
	if (cmd->output_to_pipe)
	{
		dup2(cmd->pipe[1], STDOUT_FILENO);
	}
	if (cmd->prev && cmd->prev->output_to_pipe)
	{
		dup2(cmd->prev->pipe[0], STDIN_FILENO);
	}
}

t_bool	check_redirect_files(t_command *cmd)
{
	t_io	*io;

	io = cmd->io;
	if (!io)
		return (TRUE);
	if (!io->infile && !io->outfile)
		return (TRUE);
	if ((io->infile && (io->infile_fd < 0)) ||
		(io->outfile && (io->outfile_fd < 0)))
		return (FALSE);
	return (TRUE);
}

void	set_redirects(t_command *cmd)
{
	t_io	*io;

	io = cmd->io;
	if (!io)
		return ;
	if (io->infile_fd > 0)
		dup2(io->infile_fd, STDIN_FILENO);
	if (io->outfile_fd > 0)
		dup2(io->outfile_fd, STDOUT_FILENO);
}

void	close_redirect_files(t_command *cmd)
{
	t_io	*io;

	io = cmd->io;
	if (!io)
		return ;
	if (io->infile_fd > 0)
		close(io->infile_fd);
	if (io->outfile_fd > 0)
		close(io->outfile_fd);
}

char	**get_paths(t_minishell *shell)
{
	char	**paths;
	char	*path;
	char	**env;

	env = shell->env;
	while (ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	path = *env + 5;
	paths = ft_split(path, ':');
	return (paths);
}

char	*find_executable(t_minishell *shell, t_command *cmd)
{
	char	*executable;
	char	**paths;
	char	*tmp;
	int		i;

	if (!cmd->name)
		return (NULL);
	if (access(cmd->name, X_OK) == 0)
		return (ft_strdup(cmd->name));
	paths = get_paths(shell);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		executable = ft_strjoin(tmp, cmd->name);
		free(tmp);
		if (access(executable, X_OK) == 0)
		{
			ft_delete_matrice(paths);
			return(executable);
		}
		free(executable);
	}
	ft_delete_matrice(paths);
	return (NULL);
}

void	executor(t_minishell *shell)
{
	t_command	*cmds;

	cmds = shell->commands;
	create_pipes(cmds);
	while (cmds)
	{
		shell->last_child = fork();
		if (shell->last_child == 0)
			run_commands(shell, cmds);
		cmds = cmds->next;
	}
	close_needless_pipes(shell->commands, NULL);
	wait_childs(shell);
}

void	exit_builtin(t_minishell *shell)
{
	free(shell->user_input);
	ft_delete_matrice(shell->env);
	ft_free_tokens(shell);
	ft_free_env(shell);
	free_cmd_list(&shell->commands);
	exit(1);
}

void	run_commands(t_minishell *shell, t_command *cmd)
{
	if (!check_redirect_files(cmd))
		exit_builtin(shell);
	if (!cmd->name)
		exit_builtin(shell);
	set_pipes(cmd);
	set_redirects(cmd);
	close_redirect_files(cmd);
	close_needless_pipes(shell->commands, cmd);
	cmd->path = find_executable(shell, cmd);
	if (!cmd->path)
		exit(127);
	execve(cmd->path, cmd->argv, shell->env);
}

void	wait_childs(t_minishell *shell)
{
	int		status;
	pid_t	last_child;

	last_child = 0;
	while (last_child != shell->last_child)
		last_child = waitpid(-1, &status, 0);
	shell->exit_status = status;
}