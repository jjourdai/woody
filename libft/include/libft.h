/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:20:09 by jjourdai          #+#    #+#             */
/*   Updated: 2019/02/01 10:35:39 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# define BUFF_SIZE 4096

# define TRUE 1
# define FALSE 0

typedef struct		s_fd
{
	int				fd;
	char			*str;
	struct s_fd		*next;
}					t_fd;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_btree
{
	struct s_btree	*right;
	struct s_btree	*left;
	void			*item;
}					t_btree;

typedef int			t_bool;

t_btree				*btree_create_node(void *item);
void				btree_apply_prefix(t_btree *root, void (*applyf)(void*));
void				btree_apply_infix(t_btree *root, void (*applyf)(void*));
void				btree_apply_suffix(t_btree *root, void (*applyf)(void*));
void				btree_insert_data(t_btree **root, void *item,
int (cmpf)(void*, void*));
void				*btree_search_item(t_btree *root, void *data_ref,
int	(*cmpf)(void *, void*));
int					btree_level_count(t_btree *root);

int					tab_is_sort(int *tab, int lenght, int (*f)(int, int));
void				shift_data(char *data, int len, int size);

void				*list_pop_front(t_list **list);
void				*list_push(t_list **alst, void const *content,\
	size_t content_size);
void				*list_push_back(t_list **alst, void const *content,\
	size_t content_size);
t_list				*list_atoisplit(char const *s, char c);
void				list_reverse(t_list **elem);
void				list_remove(t_list **alst, void (*del)(void *));
int					list_not_sort(t_list *p_a, t_bool order);
void				list_merge(t_list **begin_list1, t_list *begin_list2);
void				list_iter(t_list *lst, void (*f)(t_list *elem));
t_list				*list_map(t_list *lst, t_list *(*f)(t_list *elem));

t_bool				ft_list_is_sort(t_list *p_a, t_bool order);
int					list_size(t_list *begin_list);
t_list				*ft_lststrsplit(char const *s, char c);

void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_memcmp_ignorecase(const void *s1, const void *s2,
					size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strlen_without_char(const char *s, char c);
char				*ft_strdup(const char *s);
char				*ft_strdup_without_char(const char *s, char c);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strlcpy(char *dest, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strrnchr(const char *s, int c, size_t max);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strrstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strnstraf(const char *big, const char *little,
						size_t len);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strcmplen(const char *s1, const char *s2);
int					ft_strcmp_ignorecase(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
unsigned int		ft_atoi_u(const char *nptr);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_split(const char *s, char *charset);
void				ft_putchar(unsigned int value);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr_base(int nbr, char *base);
void				ft_putlong_base(long nbr, char *base);
int					ft_atoi_base(char *str, char *base);
char				*ft_strncat(char *dst, const char *src, size_t n);
char				*ft_strndup(const char *s, size_t size_max);
char				*ft_strnjoin(const char *s1, const char *s2, size_t size);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, char *base);
char				*ft_strchr_base(char *str, char *base);
char				*ft_strjoin_free(char *s1, char *s2, int free_s1_or_s2);
void				print_bits(int64_t octet);
void				ft_putnstr(char *str, size_t n);
char				*ft_strjoin_size(char *s1, char *s2, int len_s1,
					int len_s2);
char				*ft_strcut(char *str, char c);
int					get_next_line(const int fd, char **line);
uint16_t			compute_checksum(void *data, size_t size);
t_bool				ft_str_is_only_digit(char *str);
t_bool				str_is_hexa(char *str);
uint64_t        swap_bigendian_littleendian(uint64_t number, size_t sizeoff);

#endif
