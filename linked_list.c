#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node;


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


node *add_to_linked_list(node *head, int val)
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

    return new_node;
}


void remove_from_linked_list(node *head, node *n)
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


/*
 * Remove a node from the list given access to only that node.
 */
void remove_from_middle_of_list(node *n)
{
   node *current = n;
   node *previous = NULL;

   // Make all nodes have the value of the node in front of them.
   while (current->next)
   {
        current->val = current->next->val;
        previous = current;
        current = current->next;
   }

   previous->next = NULL;
   free(current);
}


/*
 * Return the kth to last node in a linked list.
 */
node *return_kth_to_last(node *head, int k)
{
    // Ready runners.
    node *runner1 = head;
    node *runner2 = head;

    // Keep track of the list length.
    int list_len = 1;

    // nth node that runner1 is on.
    int n = 0;

    // Find the length of the list.
    while (runner2->next)
    {
        list_len++;
        runner2 = runner2->next;
    }

    // Check if a kth to last node exists.
    if (k > list_len)
    {
        return NULL;
    }

    // Iterate runner 1 up to the kth to last node.
    while (list_len - n > k)
    {
        runner1 = runner1->next;
        n++;
    }

    return runner1;
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
                remove_from_linked_list(head, runner2);
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
    printf("Remove duplicates demo...\n");
    node *head1 = NULL;
    head1 = malloc(sizeof(node));
    head1->val = 1;
    head1->next = NULL;

    add_to_linked_list(head1, 2);
    add_to_linked_list(head1, 3);
    add_to_linked_list(head1, 3);
    add_to_linked_list(head1, 4);
    add_to_linked_list(head1, 5);
    add_to_linked_list(head1, 2);

    printf("Before...\n");
    print_linked_list(head1);

    remove_dups(head1);

    printf("After...\n");
    print_linked_list(head1);

    printf("\nReturn kth to last demo...\n");
    node *head2 = malloc(sizeof(node));
    head2->next = NULL;
    head2->val = 1;
    int k;
    k = 2;

    add_to_linked_list(head2, 2);
    node* third = add_to_linked_list(head2, 3);
    add_to_linked_list(head2, 4);
    add_to_linked_list(head2, 5);

    printf("List is:\n");
    print_linked_list(head2);
    printf("k = %d\n", k);
    node *kth_to_last_node = return_kth_to_last(head2, k);
    printf("kth to last is: %d\n", kth_to_last_node->val);

    printf("\nDelete from middle demo...\n");
    printf("List is:\n");
    print_linked_list(head2);

    printf("Removing 3...\n");
    remove_from_middle_of_list(third);
    print_linked_list(head2);

    return 0;
}

