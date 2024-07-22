/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:11:28 by ssibai            #+#    #+#             */
/*   Updated: 2024/07/22 19:58:18 by ssibai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_nodeclear(t_node **lst, void (*del)(void*))
{
	t_node	*current;
	t_node	*next;

	if (!lst || !del)
		return ;
	current = *lst;
	next = NULL;
	while (current)
	{
		next = current->next;
		ft_nodedelone(current, free);
		current = next;
	}
	*lst = NULL;
}

void	ft_nodeadd_front(t_node **lst, t_node *new)
{
	new->next = *lst;
	*lst = new;
}

t_node	*ft_nodenew(int value)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->value = value;
	new->next = NULL;
	return (new);
}


void	ft_nodeadd_back(t_node **lst, t_node *new)
{
	t_node	*last;

	last = ft_nodelast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

void	ft_nodeadd_back(t_node **lst, t_node *new)
{
	t_node	*last;

	last = ft_nodelast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

//ear for a specific content through the list

void	find_node(t_node **lst, int dir)
{
	int	i;
	t_node	*temp;
	t_node	*prev;

	i = 0;
	temp = *lst;
	prev = *lst;
	while (temp)
	{
		if (temp->value == dir)
		{
			if (temp == prev) // temp is in the first node
			{
				lst = temp->next;
				temp->next = NULL;
				free(temp);
				ft_nodeadd_back(lst, ft_nodenew(0));
			}
			else
			{
				
			}
			// if (temp->next->next)
			// {
			// 	prev = temp->next;
			// 	temp->next = temp->next->next;
			// 	free(prev);
			// }
			//connect the previous node to the one after
			//remove node from list
			
		}
		temp = temp->next;
	}
}
