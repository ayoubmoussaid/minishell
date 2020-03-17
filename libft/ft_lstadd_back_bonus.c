/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 21:28:30 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/19 18:30:23 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *start;

	if (alst && *alst)
	{
		start = *alst;
		while (start->next != NULL)
			start = start->next;
		start->next = new;
	}
	else
		*alst = new;
}
