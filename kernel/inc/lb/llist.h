#pragma once

#include "cdef.h"

struct dlist_node
{
    struct dlist_node *prev;
    struct dlist_node *next;
};

struct llist
{
    struct dlist_node *head;
    struct dlist_node *tail;
    uint32 size;
};

void
lb_llist_init(struct llist *list);

uint32
lb_llist_size(struct llist *list);

void
lb_llist_insert(struct llist *list, struct dlist_node *cur_node, struct dlist_node *new_node);


struct dlist_node *
lb_llist_remove(struct llist *list, struct dlist_node *node);


struct dlist_node *
lb_llist_next(struct dlist_node *node);


struct dlist_node *
lb_llist_prev(struct dlist_node *node);


struct dlist_node *
lb_llist_first(struct llist *list);


struct dlist_node *
lb_llist_last(struct llist *list);
