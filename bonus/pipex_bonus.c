/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsenhaj <amsenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:16:25 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/03/05 22:18:33 by amsenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	check_heredoc_file(int ac, char **av)
{
	int	fd;

	fd = open(av[ac - 1], O_CREAT, 0644);
	close(fd);
	fd = open(av[ac - 1], O_RDWR | O_APPEND);
	return (fd);
}

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	int		i;
	char	*ptr;

	ptr = (char *)big;
	if (!*little)
		return (ptr);
	while (*ptr && len)
	{
		if (*ptr == *little)
		{
			i = 1;
			while (little[i] && ptr[i] == little[i] && len >= ft_strlen(little))
				i++;
			if (!little[i])
				return (ptr);
		}
		ptr++;
		len--;
	}
	return (0);
}

int	get_np(char **env)
{
	int	out;

	out = 0;
	if (!env[0])
		exit(write(1, "env is empty\n", 13));
	while (env[out])
	{
		if (ft_strnstr(env[out], "PATH=", 6))
			return (out);
		out++;
	}
	return (-1);
}

int	main(int ac, char *av[], char *env[])
{
	t_cmd	*cmd;
	t_list	list;
	char	*t;
	char	**t1;

	if (!ft_strcmp(av[1], "here_doc"))
	{
		list.out = check_heredoc_file(ac, av);
		here_doc(&list, av, env, ac);
	}
	else
	{
		list.out = check_file(ac, av);
		if (access(av[1], F_OK) == -1)
			exit(write(1, "the infile is not exist\n", 24));
		list.inf = open(av[1], O_RDWR);
		t = ft_substr(env[get_np(env)], 4, ft_strlen(env[get_np(env)]));
		t1 = ft_split(t, ':');
		cmd = ft_fill_list(ac, av, t1);
		free(t);
		free_tab(t1);
		loop_pipe(cmd, env, &list);
		free_list(cmd);
	}
	return (0);
}
