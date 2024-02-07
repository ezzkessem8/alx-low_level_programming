#include "hash_tables.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * shash_table_create - Creates a sorted hash table
 * @size: The size of the array
 *
 * Return: A pointer to the created sorted hash table, or NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
    shash_table_t *ht = malloc(sizeof(shash_table_t));
    if (ht == NULL)
        return (NULL);

    ht->size = size;
    ht->array = malloc(sizeof(shash_node_t *) * size);
    if (ht->array == NULL)
    {
        free(ht);
        return (NULL);
    }

    for (unsigned long int i = 0; i < size; i++)
        ht->array[i] = NULL;

    ht->shead = NULL;
    ht->stail = NULL;

    return (ht);
}

/**
 * shash_table_set - Adds an element to the sorted hash table
 * @ht: The sorted hash table
 * @key: The key
 * @value: The value associated with the key
 *
 * Return: 1 if successful, 0 otherwise
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
    if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
        return (0);

    unsigned long int idx = key_index((const unsigned char *)key, ht->size);
    shash_node_t *new_node = malloc(sizeof(shash_node_t));
    if (new_node == NULL)
        return (0);

    new_node->key = strdup(key);
    if (new_node->key == NULL)
    {
        free(new_node);
        return (0);
    }

    new_node->value = strdup(value);
    if (new_node->value == NULL)
    {
        free(new_node->key);
        free(new_node);
        return (0);
    }

    new_node->next = ht->array[idx];
    ht->array[idx] = new_node;

    if (ht->shead == NULL)
    {
        ht->shead = new_node;
        ht->stail = new_node;
    }
    else if (strcmp(new_node->key, ht->shead->key) < 0)
    {
        new_node->snext = ht->shead;
        ht->shead->sprev = new_node;
        ht->shead = new_node;
    }
    else
    {
        shash_node_t *current = ht->shead;
        while (current->snext != NULL && strcmp(new_node->key, current->snext->key) > 0)
            current = current->snext;

        new_node->snext = current->snext;
        if (current->snext != NULL)
            current->snext->sprev = new_node;
        else
            ht->stail = new_node;

        new_node->sprev = current;
        current->snext = new_node;
    }

    return (1);
}

/**
 * shash_table_get - Retrieves a value associated with a key from the sorted hash table
 * @ht: The sorted hash table
 * @key: The key to search for
 *
 * Return: The value associated with the given key, or NULL if key couldn't be found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
    if (ht == NULL || key == NULL || *key == '\0')
        return (NULL);

    unsigned long int idx = key_index((const unsigned char *)key, ht->size);
    shash_node_t *node = ht->array[idx];

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
            return (node->value);
        node = node->next;
    }

    return (NULL);
}

/**
 * shash_table_print - Prints the sorted hash table
 * @ht: The sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
    if (ht == NULL)
        return;

    printf("{");
    shash_node_t *node = ht->shead;
    while (node != NULL)
    {
        printf("'%s': '%s'", node->key, node->value);
        if (node->snext != NULL)
            printf(", ");
        node = node->snext;
    }
    printf("}\n");
}

/**
 * shash_table_print_rev - Prints the sorted hash table in reverse order
 * @ht: The sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
    if (ht == NULL)
        return;

    printf("{");
    shash_node_t *node = ht->stail;
    while (node != NULL)
    {
        printf("'%s': '%s'", node->key, node->value);
        if (node->sprev != NULL)
            printf(", ");
        node = node->sprev;
    }
    printf("}\n");
}

/**
 * shash_table_delete - Deletes a sorted hash table
 * @ht: The sorted hash table to delete
 */
void shash_table_delete(shash_table_t *ht)
{
    if (ht == NULL)
        return;

    for (unsigned long int i = 0; i < ht->size; i++)
    {
        shash

