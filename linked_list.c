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
        printf("%d -> ", current_node->val);
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


void partition_list(node *head, int val)
{
    int temp;
    node *runner1 = head;
    node *runner2 = head;
    node *prev_runner2;

    while (runner1 && runner2)
    {
        // Runner 1 finds values that are greater than or equal to the partition val.
        while (runner1 && runner1->val < val)
        {
            runner1 = runner1->next;
        }

        // Then, runner 2 finds values that are less than the partition val.
        runner2 = runner1;
        while (runner2 && runner2->val >= val)
        {
            prev_runner2 = runner2;
            runner2 = runner2->next;
        }

        if (!runner2 && prev_runner2->val == val)
        {
            temp = prev_runner2->val;
            prev_runner2->val = runner1->val;
            runner1->val = temp;
        }

        // Switch the values.
        if (runner1 && runner2)
        {
            temp = runner2->val;
            runner2->val = runner1->val;
            runner1->val = temp;
        }
    }
}


node *sum_linked_list_reverse(node *head1, node* head2)
{
    int sum, carry, val;
    // Head of list to be returned.
    node *sum_head = malloc(sizeof(node));
    sum_head->val = 0;
    sum_head->next = NULL;

    node *current_node = sum_head;
    node *n1 = head1;
    node *n2 = head2;
    node *previous_node;

    // Sum nodes while both are not null.
    while (n1 && n2)
    {
        if (n1 == head1 && n2 == head2)
        {
            sum = n1->val + n2->val;
        }
        else
        {
            sum = carry + n1->val + n2->val;
        }

        val = sum % 10;
        carry = sum / 10;

        current_node->val = val;

        n1 = n1->next;
        n2 = n2->next;

        if (n1 && n2)
        {
            node *new_node = malloc(sizeof(node));
            new_node->val = 0;
            new_node->next = NULL;

            current_node->next = new_node;
            previous_node = current_node;
            current_node = current_node->next;
        }
    }

    // If lists are not the same size, clean up the rest.
    if (n1)
    {
        while (n1)
        {
            node *new_node = malloc(sizeof(node));
            sum = carry + n1->val;
            val = sum % 10;
            carry = sum / 10;
            new_node->val = val;
            new_node->next = NULL;

            current_node->next = new_node;
            previous_node = current_node;
            current_node = current_node->next;

            n1 = n1->next;
        }
    }
    else if (n2)
    {
        while (n2)
        {
            node *new_node = malloc(sizeof(node));
            sum = carry + n2->val;
            val = sum % 10;
            carry = sum / 10;
            new_node->val = val;
            new_node->next = NULL;

            current_node->next = new_node;
            previous_node = current_node;
            current_node = current_node->next;

            n2 = n2->next;
        }
    }

    if (carry)
    {
        node *new_node = malloc(sizeof(node));
        new_node->val = carry;
        new_node->next = NULL;
        current_node->next = new_node;
    }

    return sum_head;
}

node *sum_linked_list(node *head1, node *head2)
{
    int sum, carry, val, found_carry, n1_len, n2_len, diff, i;
    // Head of list to be returned.
    node *sum_head = malloc(sizeof(node));
    sum_head->val = 0;
    sum_head->next = NULL;

    node *current_node = sum_head;
    node *n1 = head1;
    node *n2 = head2;

    n1_len = 0;
    n2_len = 0;

    // Check if n1 and n2 are the same length.
    while (n1)
    {
        n1_len++;
        n1 = n1->next;
    }
    while (n2)
    {
        n2_len++;
        n2 = n2->next;
    }

    n1 = head1;
    n2 = head2;

    // Take care of inequal length lists.
    if (n2_len > n1_len)
    {
        diff = n2_len - n1_len;
        while (diff > 0)
        {
            current_node->val = n2->val;

            node *new_node = malloc(sizeof(node));
            new_node->val = 0;
            new_node->next = NULL;

            current_node->next = new_node;
            current_node = current_node->next;

            n2 = n2->next;
            diff--;
        }
    }
    else if (n2_len > n1_len)
    {
        diff = n1_len - n2_len;
        while (diff > 0)
        {
            current_node->val = n1->val;

            node *new_node = malloc(sizeof(node));
            new_node->val = 0;
            new_node->next = NULL;

            current_node->next = new_node;
            current_node = current_node->next;

            n1 = n1->next;
            diff--;
        }
    }

    // Sum all of the nodes in each list, not worrying about carries.
    while (n1 && n2)
    {
        current_node->val = n1->val + n2->val;

        n1 = n1->next;
        n2 = n2->next;

        if (n1 && n2)
        {
            node *new_node = malloc(sizeof(node));
            new_node->val = 0;
            new_node->next = NULL;

            current_node->next = new_node;
            current_node = current_node->next;
        }
    }

    // Go through the sum list until no nodes are greater than 9.
    found_carry = 1;
    current_node = sum_head;

    // Continue while carries are found in the list.
    while (found_carry)
    {
        while (current_node)
        {
            // Check if there is a carry on the next node.
            if (current_node->next && current_node->next->val >= 10)
            {
                // Increment the number of carries by 1.
                found_carry += 1;
                val = current_node->next->val % 10;
                carry = current_node->next->val / 10;
                current_node->next->val = val;
                current_node->val += carry;
            }

            current_node = current_node->next;

        }

        // If number of carries did not increase, no carries were found.
        if (found_carry == 1)
        {
            found_carry = 0;
        }
        // Otherwise reset the carries.
        else
        {
            found_carry = 1;
        }

        // Start looking for any more carries from the beginning of the list.
        current_node = sum_head;
    }

    return sum_head;

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

    printf("\nPartition demo...\n");
    node *head3 = malloc(sizeof(node));
    head3->val = 3;
    head3->next = NULL;

    add_to_linked_list(head3, 2);
    add_to_linked_list(head3, 8);
    add_to_linked_list(head3, 5);
    add_to_linked_list(head3, 10);
    add_to_linked_list(head3, 5);
    add_to_linked_list(head3, 1);

    printf("List is:\n");
    print_linked_list(head3);

    int partition_val = 5;
    printf("Partition on %d...\n", partition_val);

    partition_list(head3, partition_val);
    print_linked_list(head3);

    printf("\nReverse sum demo...\n");
    printf("Summing 7 + 95\n");

    node *head4 = malloc(sizeof(node));
    head4->val = 7;
    head4->next = NULL;

    node *head5 = malloc(sizeof(node));
    head5->val = 5;
    head5->next = NULL;
    add_to_linked_list(head5, 9);

    printf("List 1:\t");
    print_linked_list(head4);
    printf("List 2:\t");
    print_linked_list(head5);

    node* sum_head = sum_linked_list_reverse(head4, head5);
    print_linked_list(sum_head);

    printf("\nNormal sum demo...\n");
    node *head6 = malloc(sizeof(node));
    head6->val = 9;
    head6->next = NULL;
    add_to_linked_list(head6, 9);
    //add_to_linked_list(head6, 9);

    node *head7 = malloc(sizeof(node));
    head7->val = 1;
    head7->next = NULL;
    add_to_linked_list(head7, 0);
    add_to_linked_list(head7, 1);

    print_linked_list(head6);
    print_linked_list(head7);
    node *sum_head2;
    sum_head2 = sum_linked_list(head6, head7);
    print_linked_list(sum_head2);

    return 0;
}

