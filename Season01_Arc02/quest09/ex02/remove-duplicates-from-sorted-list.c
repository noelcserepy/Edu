#include <stdlib.h>
#include <stdio.h>

#ifndef STRUCT_LISTNODE
#define STRUCT_LISTNODE
typedef struct s_listnode
{
    int val;
    struct s_listnode *next;
} listnode;
#endif

listnode *create_new_head()
{
    listnode *head = (listnode *)malloc(sizeof(listnode));
    head->val = 0;
    head->next = NULL;
    return head;
}

listnode *append(listnode *head, int val)
{
    listnode *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    listnode *new = (listnode *)malloc(sizeof(listnode));
    new->next = NULL;
    new->val = val;
    current->next = new;

    return head;
};

listnode *prepend(listnode *head, int val)
{
    listnode *new = (listnode *)malloc(sizeof(listnode));
    new->next = head;
    new->val = val;
    return new;
}

listnode *reverse_linked_list(listnode *head)
{
    listnode *new_head = create_new_head();
    new_head->val = head->val;

    listnode *current = head;
    while (current->next != NULL)
    {
        current = current->next;
        new_head = prepend(new_head, current->val);
    }
    head = new_head;
    return new_head;
}

void print_linked_list(listnode *head)
{
    while (head != NULL)
    {
        printf("%d-", head->val);
        head = head->next;
    }
    printf("\n");
}

listnode *remove_nth_node_from_end_of_list(listnode *head, int n)
{
    listnode *current = head;
    int counter = 1;

    while (current->next != NULL)
    {
        current = current->next;
        counter++;
    }

    int remove_index = counter - (n - 1);
    counter = 1;
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

listnode *remove_duplicates_from_sorted_list(listnode *head)
{
    listnode *current = head;
    listnode *previous = head;
    while (current->next != NULL)
    {
        while ((current != NULL) && (previous->val == current->val))
        {
            current = current->next;
        }

        previous->next = current;

        if (current == NULL)
        {
            return head;
        }

        previous = current;
    }
    return head;
}

int main()
{
    listnode *head = create_new_head();
    head->val = 1;
    append(head, 1);
    append(head, 2);
    append(head, 3);
    append(head, 3);

    print_linked_list(head);
    listnode *new = remove_duplicates_from_sorted_list(head);
    print_linked_list(new);

    return 0;
}