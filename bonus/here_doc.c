/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsenhaj <amsenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:16:09 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/03/05 22:18:23 by amsenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	gnl(int fd, t_list *list)
{
	int		i;
	char	t[8000000];
	char	c;
	char	*tab;

	i = 0;
	write(1, "pipe heredoc> ", 14);
	while (read(fd, &c, 1) > 0)
	{
		t[i++] = c;
		if (c == '\n')
		{
			t[i] = 0;
			tab = ft_strdup(t);
			if (!ft_strcmp(tab, list->limiter))
			{
				free(tab);
				break ;
			}
			write(1, "pipe heredoc> ", 14);
			ft_putstr_fd(tab, list->inf);
			free(tab);
			i = 0;
		}
	}
}

void	here_doc( t_list *list, char **av, char **env, int ac)
{
	t_cmd	*cmd;
	char	*t;
	char	**t1;

	if (ac != 6)
		exit(1);
	t = ft_strjoin(av[2], "\n");
	list->limiter = ft_strdup(t);
	free(t);
	if (!access(".tmp", F_OK))
		unlink(".tmp");
	list->inf = open(".tmp", O_CREAT | O_RDWR, 0644);
	gnl(0, list);
	free(list->limiter);
	close(list->inf);
	t = ft_substr(env[get_np(env)], 4, ft_strlen(env[get_np(env)]));
	t1 = ft_split(t, ':');
	cmd = ft_fill_list(ac, &av[1], t1);
	free(t);
	list->inf = open(".tmp", O_RDONLY, 0644);
	free_tab(t1);
	ft_exec2(cmd, env, list);
	free_list(cmd);
}
