/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiglesia <aiglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:42:43 by rprieto-          #+#    #+#             */
/*   Updated: 2021/03/31 09:46:53 by aiglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_list_dbl
{
	void				*content;
	struct s_list_dbl	*next;
	struct s_list_dbl	*prev;
}						t_list_dbl;

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef struct s_gnl
{
	void			*line;
	int				fd;
	struct s_gnl	*next;
}					t_gnl;

typedef struct s_gnl_bf
{
	char			*line;
	struct s_gnl_bf	*next;
}					t_gnl_buffer;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
unsigned int		ft_strlen(const char *s);
t_bool				ft_isalpha(int c);
t_bool				ft_isdigit(int c);
t_bool				ft_isalnum(int c);
t_bool				ft_isascii(int c);
t_bool				ft_isprint(int c);
t_bool				ft_isspace(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, char const *src, size_t dstsize);
size_t				ft_strlcat(char *dst, char const *src, size_t dstsize);
char				*ft_strnstr(char const *haystack, const char *needle,
						size_t len);
int					ft_atoi(char const *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstmove_backwards(t_list *lst);
void				ft_lstdbl_delone(t_list_dbl *lst, void (*del)(void *));
void				ft_lstdbl_clear(t_list_dbl **lst, void (*del)(void *));
void				ft_lstdbl_add_front(t_list_dbl **lst, t_list_dbl *new);
t_list_dbl			*ft_lstdbl_last(t_list_dbl *lst);
void				ft_lstdbl_add_back(t_list_dbl **lst, t_list_dbl *new);
void				ft_lstdbl_move_backwards(t_list_dbl *lst);
t_list_dbl			*ft_lstdbl_new(void *content);
int					ft_lstdbl_size(t_list_dbl *lst);
t_bool				ft_checkchar(char c, char *set);
int					ft_get_index_of(char *string, char c);
int					ft_nbrlen(int n);
long				ft_abs(long n);
char				*ft_strncat_in(char *s1, char *s2, int n);
int					get_next_line	(int fd, char **line);
void				end_get_next_line(int fd);
int					gnl_buffer(int fd, int n, t_gnl_buffer **buffer);
void				free_gnl_buffer(t_gnl_buffer *buffer, t_bool erase_mode);
int					fill_gnl_buffer(t_gnl_buffer **buffer, char *line);
int					ft_extract(char **line, unsigned int index,
						unsigned int lenght);
int					ft_insert(char **line, char *addendum, unsigned int index,
						unsigned int lenght);
int					ft_array_size(void **array);
void				ft_array_clear(void **array, void (*del)(void *));
void				*ft_alloc(size_t count, size_t size);
char				*ft_buffer_fd(int fd);
char				*ft_strncpy(char *s2, int n);
t_bool				ft_str_checkset(char *string, char *set);

/*
**				FT_PRINTF.C
*/

int					ft_printf(int fd, const char *format_string, ...);

#endif
