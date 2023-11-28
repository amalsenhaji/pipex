/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsenhaj <amsenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:15:04 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/03/05 22:18:49 by amsenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exc_cmd2(t_cmd *cmd, char **env, int out, t_list *list)
{
	int	pid2;

	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Error");
		exit(0);
	}
	if (pid2 == 0)
	{
		dup2(list->fd[0], 0);
		dup2(out, 1);
		close(list->fd[0]);
		close(list->fd[1]);
		execve(cmd->next->path, cmd->next->cmd, env);
	}
}

void	exc_cmd(t_cmd *cmd, char **env, int out, int inf)
{
	t_list	list;

	if (pipe(list.fd) == -1)
	{
		perror("Error");
		exit(0);
	}
	list.pid = fork();
	if (list.pid < 0)
	{
		perror("Error");
		exit(0);
	}
	if (list.pid == 0)
	{
		dup2(list.fd[1], 1);
		dup2(inf, 0);
		close(list.fd[0]);
		close(list.fd[1]);
		execve(cmd->path, cmd->cmd, env);
	}
	exc_cmd2(cmd, env, out, &list);
	close(list.fd[0]);
	close(list.fd[1]);
	waitpid(list.pid, NULL, 0);
}
