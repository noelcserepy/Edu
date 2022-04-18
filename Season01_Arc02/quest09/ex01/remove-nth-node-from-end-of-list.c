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

listnode *remove_nth_node_from_end_of_list(listnode *head, int n)
{
    if (head == NULL)
    {
        return head;
    }

    listnode *current = head;
    int item_count = 1;

    while (current->next != NULL)
    {
        current = current->next;
        item_count++;
    }

    int remove_index = item_count - (n - 1);
    if (remove_index == 1)
    {
        return head->next;
    }

    int counter = 1;
    current = head;
    listnode *previous;
    while (counter != remove_index)
    {
        previous = current;
        current = current->next;
        counter++;
    }
    previous->next = current->next;
    return head;
}

int main()
{
    listnode *head = create_new_head();

    for (int i = 1; i < 2; i++)
    {
        append(head, i);
    }

    print_linked_list(head);
    listnode *new = remove_nth_node_from_end_of_list(head, 2);
    print_linked_list(new);

    return 0;
}