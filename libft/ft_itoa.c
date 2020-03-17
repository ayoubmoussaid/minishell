/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:09:41 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/26 16:39:57 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	tab_size(int nb, int base)
{
	int i;

	i = 0;
	while (nb / base != 0)
	{
		nb = nb / base;
		i++;
	}
	return (i + 1);
}

static char	*ft_itoa_neg(int n)
{
	int		size;
	char	*tab;
	char	*tab_base;
	int		i;

	size = tab_size(n, 10);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	tab = (char*)malloc(size + 2);
	if (tab == NULL)
		return (NULL);
	tab_base = "0123456789ABCDEF";
	i = size;
	n = -n;
	while (i >= 1)
	{
		tab[i] = tab_base[n % 10];
		n = n / 10;
		i--;
	}
	tab[i] = '-';
	tab[size + 1] = '\0';
	return (tab);
}

char		*ft_itoa(int n)
{
	int		size;
	char	*tab;
	int		i;
	char	*tab_base;

	if (n < 0)
		return (ft_itoa_neg(n));
	size = tab_size(n, 10);
	tab = (char*)malloc(size + 1);
	if (tab == NULL)
		return (NULL);
	tab_base = "0123456789ABCDEF";
	i = size - 1;
	while (i >= 0)
	{
		tab[i] = tab_base[n % 10];
		n = n / 10;
		i--;
	}
	tab[size] = '\0';
	return (tab);
}
