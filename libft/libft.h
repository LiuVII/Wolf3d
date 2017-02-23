/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 15:27:50 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/23 15:27:52 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define BUFF_SIZE 1024

typedef	struct	s_list
{
	void			*content;
	int				id;
	size_t			c_s;
	struct s_list	*next;
}				t_list;

char			*ft_strrchr(const char *s, int c);
void			ft_putstr(char const *s);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			**ft_strsplit(char const *s, char c);
char			*ft_strncpy(char *dst, const char *src, size_t len);
void			ft_striter(char *s, void (*f)(char *));
char			*ft_strstr(const char *big, const char *little);
int				ft_isdigit(int c);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			ft_strdel(char **ap);
void			*ft_memchr(const void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
void			ft_putstr_fd(char const *s, int fd);
int				ft_toupper(int c);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s1);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
void			ft_putendl_fd(char const *s, int fd);
void			ft_memdel(void **ap);
char			*ft_strnstr(const char *big, const char *little, size_t len);
void			ft_putchar(char c);
int				ft_isascii(int c);
size_t			ft_strlen(const char *s);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strnew(size_t size);
void			*ft_memalloc(size_t size);
void			ft_putendl(char const *s);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_itoa(int n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strtrim(char const *s);
int				ft_strequ(char const *s1, char const *s2);
void			ft_putchar_fd(char c, int fd);
void			*ft_memset(void *b, int c, size_t len);
int				ft_isalpha(int c);
char			*ft_strcat(char *s1, const char *s2);
int				ft_tolower(int c);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_atoi(const char *nptr);
void			ft_strclr(char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_isprint(int c);
char			*ft_strchr(const char *s, int c);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t c_s);
int				ft_isspace(int c);
double			ft_atof(const char *nptr);
long double		ft_power(double base, int power);
char			*ft_strndup(const char *s1, size_t len);
int				ft_strnequ_ci(char const *s1, char const *s2, size_t n);
void			ft_mapfree(char ***map);
char			**ft_mapmake(int rows, int cols, char c);
void			ft_bit_rev_print(void *addr, size_t size);
void			ft_memprint(const void *addr, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strnchr(char *buf, size_t size, int c);
void			*ft_memrealloc(void *src, size_t n_size, size_t size);
void			ft_lstremoveif(t_list **begin_list,
	void *data_ref, int (*cmp)());
int				get_next_line(const int fd, char **line);
void			ft_lstclr(t_list **begin_list);

#endif
