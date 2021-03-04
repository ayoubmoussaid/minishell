/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:02:01 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/18 11:50:27 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# define BUFFER_SIZE 50

int				get_next_line(int fd, char **line);
char			*ft_strjoin1(char *s1, char *s2);
size_t			ft_strlen1(const char *str);
char			*ft_substr1(char *s, unsigned int start,
						size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *src);
char			*str_checker(char *str, int nm);
int				does_it_end(char *str);
char			*read_buffer(int fd, char *buffer, char *line);
char			*verify_line(char **line, char *buffer, int x);

#endif
