/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 21:18:08 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/19 18:31:00 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*start;

	i = 0;
	start = lst;
	while (start != NULL)
	{
		start = start->next;
		i++;
	}
	return (i);
}
