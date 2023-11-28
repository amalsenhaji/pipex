/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsenhaj <amsenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:15:22 by amsenhaj          #+#    #+#             */
/*   Updated: 2022/03/05 22:18:57 by amsenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	int		out;
	int		inf;
	char	*t;
	char	**t1;

	if (ac != 5)
		exit(write(1, "number of arg is not 5\n", 23));
	if (!env[0])
		exit(write(1, "env is empty\n", 13));
	inf = open(av[1], O_RDWR);
	t = ft_substr(env[get_np(env)], 4, ft_strlen(env[get_np(env)]));
	out = check_file(ac, av);
	t1 = ft_split(t, ':');
	cmd = ft_fill_list(ac, av, t1);
	free(t);
	free_tab(t1);
	exc_cmd(cmd, env, out, inf);
	free_list(cmd);
	return (0);
}
