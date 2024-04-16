/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matesant <matesant@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:52:28 by matesant          #+#    #+#             */
/*   Updated: 2024/04/16 17:12:56 by matesant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isvar(char *c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *str, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
char				*ft_strnstr(const char *str, const char *substr, size_t n);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t elem, size_t n);
char				*ft_strdup(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_delete_matrice(char **matrice);
int					ft_isspace(char c);
int					ft_issignal(char str);
long				ft_atol(const char *str);
int					ft_abs(int n);
void				ft_free(void *ptr);
void				ft_free_ptr(void **ptr);
char				*ft_replace(char *old, char *new, char *str, int *i);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_matrice_len(char **matrice);
char				*ft_nullstrdup(const char *str);
void				ft_free_char(char **ptr);
int					ft_has_alpha(char *str);
char				*ft_strjoin_three(char *one, char *two, char *three,
						t_bool to_free);

// GNL
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char				*get_next_line(int fd);
size_t				g_ft_strlen(const char *str);
char				*g_ft_strjoin(const char *dest, char *str);
char				*g_ft_strchr(const char *str, int c);
char				*g_ft_strdup(const char *str);
size_t				g_ft_strlcpy(char *dest, const char *str, size_t n);

// ft_printf_fd

# define DECIMAL_BASE "0123456789"
# define HEXA_LOW_BASE "0123456789abcdef"
# define HEXA_UP_BASE "0123456789ABCDEF"

int					ft_printf_fd(int fd, const char *format, ...);

#endif