/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 08:20:32 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/25 17:51:50 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list_ptr;
	t_list	*new;
	t_list	*alist;

	alist = NULL;
	list_ptr = lst;
	while (list_ptr)
	{
		new = ft_lstnew((*f)(list_ptr->content));
		if (new == NULL)
		{
			ft_lstclear(&alist, del);
			return (NULL);
		}
		ft_lstadd_back(&alist, new);
		list_ptr = list_ptr->next;
	}
	return (alist);
}
