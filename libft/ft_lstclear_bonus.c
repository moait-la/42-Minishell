/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochenna <mochenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:48:26 by moait-la          #+#    #+#             */
/*   Updated: 2024/08/24 17:37:22 by mochenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*store;

	if (!del || !lst || !*lst)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		store = temp->next;
		del(temp->str);
		free(temp);
		temp = store;
	}
	*lst = NULL;
}
