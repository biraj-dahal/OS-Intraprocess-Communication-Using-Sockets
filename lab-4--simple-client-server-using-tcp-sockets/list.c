// list/list.c
// 
// Implementation for linked list.
//
// Biraj Dahal

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  node_t* cur = l->head;
  node_t* tmp;
  while(cur != NULL) {
    tmp = cur->next;
    free(cur);
    cur = tmp;
  }
  free(l);
}

void list_print(list_t *l) {
  node_t* cur = l->head;
  while(cur != NULL) {
    printf("%d -> ", cur->value);
    cur = cur->next;
  }
  printf("NULL\n");    
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 1024);
  buf[0] = '\0';
  char tbuf[20];

  node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) { 
  int len = 0;
  node_t* curr = l->head;
  while(curr != NULL) {
    len++;
    curr = curr->next;
  }
  return len; 
}

void list_add_to_back(list_t *l, elem value) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;
  if (l->head == NULL) {
    l->head = new_node;
  } else {
    node_t *current = l->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
}

void list_add_to_front(list_t *l, elem value) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = l->head;
  l->head = new_node;
}

void list_add_at_index(list_t *l, elem value, int index) {
  if (index < 1) return;  // Index must be >= 1 for 1-based indexing
  if (index == 1) {
    list_add_to_front(l, value);
    return;
  }

  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;
  node_t *current = l->head;
  int i;
  for (i = 1; i < index - 1; i++) {
    if (current == NULL) {
      free(new_node);  // Index out of bounds
      return;
    }
    current = current->next;
  }
  if (current == NULL) {
    free(new_node);
    return;
  }
  new_node->next = current->next;
  current->next = new_node;
}

elem list_remove_from_back(list_t *l) {
  if (l->head == NULL) return -1; // List is empty

  node_t *current = l->head;
  if (current->next == NULL) {
    elem value = current->value;
    free(current);
    l->head = NULL;
    return value;
  }

  while (current->next->next != NULL) {
    current = current->next;
  }

  elem value = current->next->value;
  free(current->next);
  current->next = NULL;
  return value;
}

elem list_remove_from_front(list_t *l) {
  if (l->head == NULL) return -1; // List is empty

  node_t *node_to_remove = l->head;
  elem value = node_to_remove->value;
  l->head = node_to_remove->next;
  free(node_to_remove);
  return value;
}

elem list_remove_at_index(list_t *l, int index) {
  if (index < 1 || l->head == NULL) return -1; // Invalid index or empty list

  if (index == 1) {
    return list_remove_from_front(l);
  }

  node_t *current = l->head;
  int i;
  for (i = 1; i < index - 1; i++) {
    if (current == NULL || current->next == NULL) return -1;
    current = current->next;
  }

  node_t *node_to_remove = current->next;
  if (node_to_remove == NULL) return -1;
  elem value = node_to_remove->value;
  current->next = node_to_remove->next;
  free(node_to_remove);
  return value;
}

bool list_is_in(list_t *l, elem value) {
  node_t *current = l->head;
  while (current != NULL) {
    if (current->value == value) return true;
    current = current->next;
  }
  return false;
}

elem list_get_elem_at(list_t *l, int index) {
  if (index < 1) return -1;  // Invalid index

  node_t *current = l->head;
  int i;
  for (i = 1; i < index; i++) {
    if (current == NULL) return -1;  // Index out of bounds
    current = current->next;
  }
  return (current == NULL) ? -1 : current->value;
}

int list_get_index_of(list_t *l, elem value) {
  node_t *current = l->head;
  int index = 1;  // Start from 1 for 1-based indexing
  while (current != NULL) {
    if (current->value == value) return index;
    current = current->next;
    index++;
  }
  return -1;
}
