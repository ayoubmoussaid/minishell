/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 22:40:30 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/19 18:31:15 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *dele;
	t_list *next;

	next = *lst;
	while (next != NULL)
	{
		dele = next;
		next = next->next;
		del(dele->content);
		free(dele);
	}
	*lst = NULL;
}
