#include <stdlib.h>
#include <stdio.h>

typedef struct s_listnode
{
    int value;
    struct s_listnode *next;
} listnode;

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
        while (previous->value == current->value)
        {
            current = current->next;
        }

        previous->next = current;
        previous = current;
        current = current->next;
    }
    previous->next = NULL;
    return head;
}

int main()
{
    listnode *head = create_new_head();

    for (int i = 0; i < 10; i++)
    {
        append(head, i);
        append(head, i);
    }

    print_linked_list(head);
    listnode *new = remove_duplicates_from_sorted_list(head);
    print_linked_list(new);

    return 0;
}