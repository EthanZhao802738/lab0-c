#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *new_node =
        (struct list_head *) malloc(sizeof(struct list_head));

    if (new_node == NULL)
        return NULL;

    INIT_LIST_HEAD(new_node);

    return new_node;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (head == NULL)
        return;

    element_t *p_entry, *p_safe;
    list_for_each_entry_safe (p_entry, p_safe, head, list)
        q_release_element(p_entry);

    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    element_t *p_node = malloc(sizeof(element_t));
    if (p_node == NULL)
        return false;

    p_node->value = strdup(s);
    if (p_node->value == NULL) {
        free(p_node);
        return false;
    }

    list_add(&p_node->list, head);

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    element_t *p_node = malloc(sizeof(element_t));
    if (p_node == NULL)
        return false;

    p_node->value = strdup(s);
    if (p_node->value == NULL) {
        free(p_node);
        return false;
    }

    list_add_tail(&p_node->list, head);

    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL || list_empty(head))
        return NULL;

    element_t *p_node = list_first_entry(head, element_t, list);

    if (sp != NULL) {
        sp[bufsize - 1] = '\0';
        strncpy(sp, p_node->value, bufsize - 1);
    }

    list_del(head->next);

    return p_node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (head == NULL || list_empty(head))
        return NULL;

    element_t *p_node = list_last_entry(head, element_t, list);


    if (sp != NULL) {
        sp[bufsize - 1] = '\0';
        strncpy(sp, p_node->value, bufsize - 1);
    }

    list_del(head->prev);


    return NULL;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (head == NULL)
        return 0;

    int number_of_elements = 0;
    struct list_head *node = NULL;

    list_for_each (node, head)
        number_of_elements++;

    return number_of_elements;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (head == NULL)
        return false;

    struct list_head *p_slow = head->next;

    for (struct list_head *p_fast = head->next;
         p_fast != head && p_fast->next != head; p_fast = p_fast->next->next) {
        p_slow = p_slow->next;
    }

    list_del(p_slow);
    q_release_element(list_entry(p_slow, element_t, list));

    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    if (head == NULL)
        return false;

    bool b_duplicate = false;
    element_t *p_entry, *p_next_entry;

    list_for_each_entry_safe (p_entry, p_next_entry, head, list) {
        if (&p_next_entry->list != head &&
            !strcmp(p_entry->value, p_next_entry->value)) {
            b_duplicate = true;
            list_del(&p_entry->list);
            q_release_element(p_entry);
        } else if (b_duplicate) {
            b_duplicate = false;
            list_del(&p_entry->list);
            q_release_element(p_entry);
        }
    }


    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    if (head == NULL)
        return;

    struct list_head *p_swap_1, *p_swap_2;

    p_swap_1 = head->next;
    p_swap_2 = p_swap_1->next;

    while (p_swap_1 != head && p_swap_2 != head) {
        list_move(p_swap_2, p_swap_1->prev);
        p_swap_1 = p_swap_1->next;
        p_swap_2 = p_swap_1->next;
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (head == NULL)
        return;

    struct list_head *p_node, *p_next_node;

    list_for_each_safe (p_node, p_next_node, head) {
        list_move(p_node, head);
    }
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
