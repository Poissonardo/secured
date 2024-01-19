/*
** EPITECH PROJECT, 2024
** SecuredBS
** File description:
** ht_delete.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "../../includes/hashtable.h"
#include "../../includes/my.h"
#include "../linked_list/linked_list.h"

static void delete_head(hashtable_t *ht, int index, list_node *temp)
{
    if (!ht->table[index]->next) {
        ht->table[index]->hash_id = -1;
        ht->table[index]->value = NULL;
        ht->table[index]->next = NULL;
        return;
    }
    ht->table[index] = temp->next;
}

static void delete_element(list_node *temp)
{
    list_node *to_delete = temp->next;

    temp->next = temp->next->next;
    free(to_delete);
}

int ht_delete(hashtable_t *ht, char *key)
{
    int key_hash = ht->hash_fn(key, ht->len);
    int index = key_hash % ht->len;
    list_node *temp;

    if (key_hash == -1)
        return -1;
    temp = ht->table[index];
    if (temp->key && my_strcmp(temp->key, key) == 0) {
        delete_head(ht, index, temp);
        return 0;
    }
    while (temp->next != NULL) {
        if (temp->next->key && my_strcmp(temp->next->key, key) == 0) {
            delete_element(temp);
            return 0;
        }
        temp = temp->next;
    }
    return -1;
}
