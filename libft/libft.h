/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:05:19 by abensett          #+#    #+#             */
/*   Updated: 2022/01/05 18:10:11 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

/*Part 1*/
/*ft absolute */
long long	ft_abs(long long n);
/* str to int*/
int			ft_atoi(const char *str);
/* str to long int*/
long		ft_atol(const char *str);
/* str to long long int*/
long long	ft_atoll(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);

// DOUBLE
double		ft_double_abs(double a);
double		ft_double_pow(double a);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);

void		*ft_memccpy(void *dest, const void *src, int c, size_t n);
/*The memccpy() function copies bytes from string src to string dst.  If
	 the character c (as converted to an unsigned char) occurs in the string
	 src, the copy stops and a pointer to the byte after the copy of c in the
	 string dst is returned.  Otherwise, n bytes are copied, and a NULL
	 pointer is returned.*/

void		*ft_memchr(const void *s, int c, size_t n);
/*The memchr() function locates the first occurrence of c (converted to an
	 unsigned char) in string s.
*/
int			ft_memcmp(const void *s1, const void *s2, size_t n);
/**The memcmp() function compares byte string s1 against byte string s2.
	 Both strings are assumed to be n bytes long.*/

void		*ft_memcpy(void *dest, const void *src, size_t n);
/* The memcpy() function copies n bytes from memory area src to memory area
	 dst.  If dst and src overlap, behavior is undefined.  Applications in
	 which dst and src might overlap should use memmove(3) instead.*/

void		*ft_memmove(void *dest, const void *src, size_t n);
/*The memmove() function copies len bytes from string src to string dst.
	 The two strings may overlap; the copy is always done in a non-destructive
	 manner.*/
void		*ft_memset(void *s, int c, size_t n);
/*The memset() function writes len bytes of value c (converted to an
	 unsigned char) to the string b.*/

char		*ft_strchr(const char *s, int c);
/*The strchr() function locates the first occurrence of c (converted to a
	 char) in the string pointed to by s.  The terminating null character is
	 considered to be part of the string; therefore if c is `\0', the func-
	 tions locate the terminating `\0'*/

char		*ft_strdup(const char *s1);
/* The strdup() function allocates sufficient memory for a copy of the
	 string s1, does the copy, and returns a pointer to it.  The pointer may
	 subsequently be used as an argument to the function free(3).*/

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
/*iThe strlcpy() and strlcat() functions copy and concatenate strings with
	 the same input parameters and output result as snprintf(3).  They are
	 designed to be safer, more consistent, and less error prone replacements
	 for the easily misused functions strncpy(3) and strncat(3).*/

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
/*The strlcpy() and strlcat() functions copy and concatenate strings with
	 the same input parameters and output result as snprintf(3).  They are
	 designed to be safer, more consistent, and less error prone replacements
	 for the easily misused functions strncpy(3) and strncat(3).*/

size_t		ft_strlen(const char *s);
/*The strlen() function computes the length of the string s.  The strnlen()
	 function attempts to compute the length of s, but never scans beyond the
	 first maxlen bytes of s.*/

int			ft_strncmp(const char *s1, const char *s2, size_t n);
/*The strncmp() function compares not more than n characters.  Because
	 strncmp() is designed for comparing strings rather than binary data,
	 characters that appear after a `\0' character are not compared.*/

char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
/*The strstr() function locates the first occurrence of the null-terminated
	 string needle in the null-terminated string haystack.

	 The strcasestr() function is similar to strstr(), but ignores the case of
	 both strings.

	 The strnstr() function locates the first occurrence of the null-termi-
	 nated string needle in the string haystack, where not more than len char-
	 acters are searched.  Characters that appear after a `\0' character are
	 not searched.  Since the strnstr() function is a FreeBSD specific API, it
	 should only be used when portability is not a concern.

	 While the strcasestr() function uses the current locale, the
	 strcasestr_l() function may be passed a locale directly. See xlocale(3)
	 for more information.*/

char		*ft_strrchr(const char *s, int c);
/*The strchr() function locates the first occurrence of c in the
	 string pointed to by s.  The terminating null character is considered
	 to be part of the
	 string; therefore if c is `\0', the functions locate the terminating `\0'.

	 The strrchr() function is identical to strchr(), except
	  it locates the last occurrence
	 of c.*/

// ARRAY  INT
/*print tab made of longs*/
void		ft_tab_long_print(long *tab, int len);

/*print tab made of ints*/
void		ft_tab_int_print(int *tab, int len);
/*sort in an ascending order */
void		ft_tab_long_sort(long *tab, int size);
// ARRAY STR
void		ft_tab_str_print(char **tabstr);
/*turn into lowercase*/
int			ft_tolower(int c);
/*turn into uppercase*/
int			ft_toupper(int c);

/* PART 2 */
char		*ft_itoa(int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* PART 3 */
/*alst is the adress of the first element of the list
and new the new element to add */
void		ft_lstadd_back(t_list **alst, t_list *new);
/*alst is the adress of the first element of the list
and new the new element to add */
void		ft_lstadd_front(t_list **alst, t_list *new);
/* delete the element and the first pointer becomes NULL */
void		ft_lstclear(t_list **lst, void (*del)(void *));
/* delete the element */
void		ft_lstdelone(t_list *lst, void (*del)(void *));
// Free the list
void		ft_lstfree(t_list *list);
/* apply f() on the list*/
void		ft_lstiter(t_list *lst, void (*f)(void *));
/*return last element*/
t_list		*ft_lstlast(t_list *lst);
/* apply f() and return the list of elements on which
the function was applied*/
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/*content = contenu du nouvel element, la fonction
renvoie le nouvel element*/
t_list		*ft_lstnew(void *content);
/*return the len of the list*/
int			ft_lstsize(t_list *lst);
/*print list of ints*/
void		ft_lst_int_print(t_list list);
/*look for a int and return the addres of the list containing it*/
t_list		*ft_lst_int_search(t_list list, int nb);
/*look for a int and return the index, start by 0, if not return size lst */
int			ft_lst_int_search_index(t_list list, int nb);
/*return the occurence of nb in list*/
int			ft_lst_int_occurence(t_list list, long nb);
/*check if list is in anscending order*/
int			ft_lst_int_check_order(t_list list);
/*check if list is in anscending order*/
int			ft_lst_long_check_order(t_list list);

/*return lst filled with a longs thanks to a given str(separated by spaces)*/
t_list		*ft_lst_long_fill(int ac, char **list);

/*find int median*/
long		ft_lst_get_median(t_list list);
/*print str*/
void		ft_lst_str_print(const t_list list);

int			ft_min(int a, int b);

#endif
