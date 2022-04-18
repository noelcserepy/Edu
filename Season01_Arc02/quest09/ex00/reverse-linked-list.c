#include <stdlib.h>
#include <stdio.h>

#ifndef STRUCT_LISTNODE
#define STRUCT_LISTNODE
typedef struct s_listnode
{
    int value;
    struct s_listnode *next;
} listnode;
#endif

listnode *create_new_head()
{
    listnode *head = (listnode *)malloc(sizeof(listnode));
    head->value = 0;
    head->next = NULL;
    return head;
}

listnode *append(listnode *head, int value)
{
    listnode *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    listnode *new = (listnode *)malloc(sizeof(listnode));
    new->next = NULL;
    new->value = value;
    current->next = new;

    return head;
};

listnode *prepend(listnode *head, int value)
{
    listnode *new = (listnode *)malloc(sizeof(listnode));
    new->next = head;
    new->value = value;
    return new;
}

listnode *reverse_linked_list(listnode *head)
{
    listnode *new_head = create_new_head();
    new_head->value = head->value;

    listnode *current = head;
    while (current->next != NULL)
    {
        current = current->next;
        new_head = prepend(new_head, current->value);
    }
    head = new_head;
    return new_head;
}

void print_linked_list(listnode *head)
{
    while (head != NULL)
    {
        printf("%d-", head->value);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    listnode *head = create_new_head();

    for (int i = 0; i < 10; i++)
    {
        append(head, i);
    }

    print_linked_list(head);
    listnode *new = reverse_linked_list(head);
    print_linked_list(new);

    return 0;
}