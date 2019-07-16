/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polooo <polooo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 12:19:58 by jjourdai          #+#    #+#             */
/*   Updated: 2019/04/25 14:43:07 by polooo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_fd	*new_fd(int fd)
{
	t_fd	*new;

	new = ft_memalloc(sizeof(t_fd));
	new->fd = fd;
	return (new);
}

static t_fd	*search_fd(t_fd *lst, int fd)
{
	t_fd	*begin;
	t_fd	*tmp;
	int		fd_tmp;
	char	*str;

	begin = lst;
	while (lst && (lst->fd) != fd)
		lst = lst->next;
	if (lst && (lst->fd) == fd)
	{
		fd_tmp = lst->fd;
		str = lst->str;
		lst->fd = begin->fd;
		lst->str = begin->str;
		begin->fd = fd_tmp;
		begin->str = str;
	}
	else
	{
		tmp = new_fd(fd);
		tmp->next = begin;
		return (tmp);
	}
	return (begin);
}

static int	core_get(char **line, char *buf, t_fd **lst, int fd)
{
	char		*tmp;
	int			ret;
	char		*bef;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		ft_bzero(buf + ret, BUFF_SIZE - ret);
		if (ret == -1)
			return (-1);
		if (((*lst)->str = ft_strchr(buf, '\n')))
		{
			(*lst)->str = ft_strdup((*lst)->str + 1);
			tmp = ft_strsub(buf, 0, ft_strlen(buf) -
			(ft_strlen((*lst)->str) + 1));
			bef = *line;
			*line = ft_strjoin_free(bef, tmp, 3);
			free(buf);
			return (ret);
		}
		tmp = *line;
		*line = ft_strjoin(tmp, buf);
		free(tmp);
	}
	return (0);
}

static int	rest_exist(char **line, t_fd **lst)
{
	char *tmp;
	char *bef;

	bef = NULL;
	tmp = NULL;
	if ((bef = ft_strchr((*lst)->str, '\n')))
	{
		*line = ft_strsub((*lst)->str, 0, bef - (*lst)->str);
		tmp = (*lst)->str;
		(*lst)->str = ft_strdup(bef + 1);
		free(tmp);
		return (1);
	}
	else
	{
		*line = ft_strdup((*lst)->str);
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static t_fd *lst;
	char		*buf;
	int			ret;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	lst = search_fd(lst, fd);
	*line = NULL;
	if (lst->str != NULL)
		if ((rest_exist(line, &lst)) == 1)
			return (1);
	buf = ft_strnew(BUFF_SIZE);
	ret = core_get(line, buf, &lst, fd);
	if (ret == -1)
		return (-1);
	if ((*line && ft_strlen(*line) > 0) || (ret != 0))
		return (1);
	free(buf);
	return (0);
}
