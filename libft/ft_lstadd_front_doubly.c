#include "libft.h"
#include <stdio.h>
void ft_addfront_doubly(t_doubly_list **list)
{
    t_doubly_list *test_previous;
    test_previous = malloc(sizeof(t_doubly_list));
    test_previous->string = "Test previous";

    t_doubly_list *new_node;
    new_node = malloc(sizeof(t_doubly_list));
    new_node->string = "New first";
    new_node->previous = test_previous; //NULL here instead test_previous

    if (*list)
    {
        new_node->next = *list;
        *list = new_node;
    }
    else
        *list = new_node;

    t_doubly_list *node;
    node = *list;
    while (node)
    {
        char *cast;
        cast = (char *)node->string;
        printf("Current node content: %s\n", cast);
        node = node->previous;
    }
}

int main(void)
{
    t_doubly_list **lista;
    t_doubly_list *node1;
    t_doubly_list *node2;
    t_doubly_list *node3;
    lista = malloc(sizeof(t_doubly_list));
    node1 = malloc(sizeof(t_doubly_list));
    node2 = malloc(sizeof(t_doubly_list));
    node3 = malloc(sizeof(t_doubly_list));

    node1->string = "First";
    node1->next = node2;

    node2->string = "Second";
    node2->next = node3;

    node3->string = "Third";
    node3->next = NULL;
    lista = &node1;

    ft_addfront_doubly(lista);
}