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
    head = new;
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
        while (previous->val == current->val)
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

listnode *insert(listnode *prev, listnode *current, int val)
{
    listnode *new = (listnode *)malloc(sizeof(listnode));
    new->val = val;
    prev->next = new;
    new->next = current;
    return new;
}

listnode_array *remove_empty_lists(listnode_array *arr)
{
    listnode_array *cleaned = (listnode_array *)malloc(sizeof(listnode_array));
    // cleaned->size = (int)malloc(sizeof(int));
    cleaned->size = 0;
    cleaned->array = malloc(sizeof(listnode *) * 100);

    for (int i = 0; i < arr->size; i++)
    {
        if (arr->array[i] != NULL)
        {
            cleaned->array[cleaned->size] = arr->array[i];
            cleaned->size++;
        }
    }

    return cleaned;
}

listnode *merge_k_sorted_lists(listnode_array *arr)
{
    listnode *new;
    arr = remove_empty_lists(arr);
    new = arr->array[0];

    // Loop through each list and slot them into the new list based on their val
    for (int i = 1; i < arr->size; i++)
    {
        // Loop through return list and insert at correct location
        listnode *current = arr->array[i];
        listnode *current_new = new;
        listnode *previous;
        while (current != NULL)
        {
            // Insert val in new list
            current_new = new;
            while (current_new != NULL)
            {
                if (current->val <= current_new->val)
                {
                    if (current_new == new)
                    {
                        new = prepend(new, current->val);
                    }
                    else
                    {
                        insert(previous, current_new, current->val);
                    }
                    break;
                }
                if (current_new->next == NULL)
                {
                    new = append(new, current->val);
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
    arr->array = malloc(sizeof(listnode *) * 100);
    listnode *empty = NULL;
    arr->array[0] = empty;

    for (int i = 1; i < 3; i++)
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