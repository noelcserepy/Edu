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

#ifndef STRUCT_LISTNODE_ARRAY
#define STRUCT_LISTNODE_ARRAY
typedef struct s_listnode_array
{
    int size;
    listnode **array;
} listnode_array;
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
    head = new;
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

listnode *insert(listnode *prev, listnode *current, int value)
{
    listnode *new = (listnode *)malloc(sizeof(listnode));
    new->value = value;
    prev->next = new;
    new->next = current;
    return new;
}

listnode *merge_k_sorted_lists(listnode_array *arr)
{
    listnode *new = create_new_head();
    new = arr->array[0];

    // Loop through each list and slot them into the new list based on their value
    for (int i = 1; i < arr->size; i++)
    {
        // Loop through return list and insert at correct location
        listnode *current = arr->array[i];
        listnode *current_new = new;
        listnode *previous;
        while (current != NULL)
        {
            // Insert value in new list
            current_new = new;
            while (current_new != NULL)
            {
                if (current->value <= current_new->value)
                {
                    if (current_new == new)
                    {
                        new = prepend(new, current->value);
                    }
                    else
                    {
                        insert(previous, current_new, current->value);
                    }
                    break;
                }
                if (current_new->next == NULL)
                {
                    new = append(new, current->value);
                    break;
                }
                previous = current_new;
                current_new = current_new->next;
            }
            current = current->next;
        }
    }
    return new;
}

int main()
{
    listnode_array *arr = malloc(sizeof(listnode_array));
    arr->array = malloc(sizeof(listnode_array));

    for (int i = 0; i < 3; i++)
    {
        listnode *head = create_new_head();
        for (int i = 1; i < 3; i++)
        {
            append(head, i);
        }
        arr->array[i] = head;
        arr->size = i + 1;
    }

    for (int i = 0; i < arr->size; i++)
    {
        printf("Array %d: ", i);
        print_linked_list(arr->array[i]);
    }

    listnode *new = merge_k_sorted_lists(arr);
    print_linked_list(new);

    // insert(arr->array[0], arr->array[0]->next, 8);
    // print_linked_list(arr->array[0]);

    return 0;
}