/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 12:10:11 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/16 12:11:03 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<ssl.h>

t_stack		*init(void)
{
	t_stack	*in;
	in = (t_stack*)malloc(sizeof(struct s_stack));
	in->top = NULL;
	return (in);
}

struct s_node *pop(struct s_stack *stack){
	if (!stack->top)
		return (NULL);
	struct s_item *tf = stack->top;
	struct s_node *ret = stack->top->node;
	stack->top = stack->top->next;
	free(tf);
	return (ret);
}

void push(struct s_stack *stack, struct s_node *node){
	struct s_item *ret = (struct s_item *)malloc(sizeof(struct s_item));
	ret->node = node;
	if (stack->top){
		ret->next = stack->top;
		stack->top = ret;
	}
	else {
		stack->top = ret;
		ret->next = NULL;
	}
}

void findSpec(struct s_node *root, struct s_stack *stk, char *species){
	if (!root)
		return ;
	if (!strcmp(species, root->name)){
		push(stk, root);
		return ;
	}
	for (int i = 0; root->children[i]; i++){
		findSpec(root->children[i], stk, species);
		if (stk->top){
			push(stk, root);
			break ;
		}
	}
}