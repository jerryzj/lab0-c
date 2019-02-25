/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = (queue_t *) malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *temp = NULL;
    if (!q) {
        return;
    }
    while (q->head != NULL) {
        temp = q->head;
        q->head = q->head->next;
        free(temp->value);
        free(temp);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *new_node = NULL;
    char *new_val = NULL;
    if (!q) {
        return false;
    } else {
        new_node = (list_ele_t *) malloc(sizeof(list_ele_t));
        new_val = (char *) malloc((strlen(s) + 1) * sizeof(char));
        if (!new_node || !new_val) {
            if (new_node)
                free(new_node);
            if (new_val)
                free(new_val);
            return false;
        }
        sprintf(new_val, "%s", s);
        new_node->value = new_val;
        new_node->next = q->head;
        if (!q->head) {
            q->tail = new_node;
        }
        q->head = new_node;
        ++q->size;
        return true;
    }
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *new_node = NULL;
    char *new_val = NULL;
    if (!q) {
        return false;
    } else {
        new_node = (list_ele_t *) malloc(sizeof(list_ele_t));
        new_val = (char *) malloc((strlen(s) + 1) * sizeof(char));
        if (!new_node || !new_val) {
            if (new_node)
                free(new_node);
            if (new_val)
                free(new_val);
            return false;
        }
        sprintf(new_val, "%s", s);
        new_node->value = new_val;
        new_node->next = NULL;
        if (!q->tail) {
            q->head = new_node;
            q->tail = new_node;
        }
        q->tail->next = new_node;
        q->tail = new_node;
        ++q->size;
        return true;
    }
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *temp = NULL;
    if (q && q->head) {
        temp = q->head;
        if (sp) {
            snprintf(sp, bufsize, "%s", temp->value);
        }
        q->head = q->head->next;
        if (temp->value)
            free(temp->value);
        if (temp)
            free(temp);
        --q->size;
        return true;
    } else {
        return false;
    }
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q) {
        return q->size;
    } else {
        return 0;
    }
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *forward = NULL;
    list_ele_t *backward = NULL;
    if (q && q->head && q->head->next) {
        backward = q->head;
        q->tail = q->head;
        q->head = q->head->next;
        forward = q->head->next;
        backward->next = NULL;
        while (forward != NULL) {
            q->head->next = backward;
            backward = q->head;
            q->head = forward;
            forward = forward->next;
        }
        q->head->next = backward;
    } else
        return;
}
