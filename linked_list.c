#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node;

static node *head;

void print_linked_list(node *head)
{
    node *current_node = head;

    while (current_node->next)
    {
        printf("%d\n", current_node->val);
        current_node = current_node->next;
    }
    printf("%d\n", current_node->val);
}


void add_to_linked_list(node *head, int val)
{
    node *current_node = head;

    while (current_node->next)
    {
        current_node = current_node->next;
    }

    node *new_node = malloc(sizeof(node));

    new_node->val = val;
    new_node->next = NULL;

    current_node->next = new_node;
}


void remove_from_linked_list(node *n)
{
    // Node is at the front of the list.
    if (n == head)
    {
        n = n->next;
        head->next = NULL;
        head = n;
    }
    // Node is in the middle of the list
    else if (n->next)
    {
        node *current = head;
        while (current->next != n)
        {
            current = current->next;
        }
        current->next = n->next;
    }
    // Node is at the end of the list.
    else if (!n->next)
    {
        node *current = head;
        while (current->next != n)
        {
            current = current->next;
        }
        current->next = NULL;
    }
}


void remove_dups(node *head)
{
    node *runner1 = head;
    node *runner2 = head->next;
    // Keep track of first instance of each value
    while (runner1->next)
    {
        // Runner 2 finds duplicate values
        while (runner2)
        {
            // If duplicate value is found, remove it.
            if (runner1->val == runner2->val)
            {
                node *temp = runner2;
                remove_from_linked_list(runner2);
                runner2 = temp->next;
                continue;
            }

            runner2 = runner2->next;
        }
        runner1 = runner1->next;
        runner2 = runner1->next;
    }
}

int main()
{
    head = NULL;
    head = malloc(sizeof(node));
    head->val = 1;
    head->next = NULL;

    add_to_linked_list(head, 2);
    add_to_linked_list(head, 3);
    add_to_linked_list(head, 3);
    add_to_linked_list(head, 4);
    add_to_linked_list(head, 5);
    add_to_linked_list(head, 2);

    printf("Before...\n");
    print_linked_list(head);

    remove_dups(head);

    printf("After...\n");
    print_linked_list(head);

    return 0;
}

