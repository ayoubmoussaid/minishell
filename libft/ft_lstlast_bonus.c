/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 21:21:43 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/19 18:30:58 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstlast(t_list *lst)
{
	t_list *start;

	start = NULL;
	if (lst)
	{
		start = lst;
		while (start->next != NULL)
			start = start->next;
	}
	return (start);
}
