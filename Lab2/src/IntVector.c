#include "IntVector.h"

vector *int_vector_new(size_t initial_capacity)
{
    vector *bob;
    bob = malloc(sizeof(vector));
    if (bob == NULL || initial_capacity <= 0)
    {
        printf("Не удалось выделить память под структуру\n");
        return NULL;
    }
    bob->data = malloc(sizeof(int) * initial_capacity);
    if (bob->data != NULL)
    {
       return bob;
    }
    else
    {
        printf("Не удалось выделить память под массив\n");
        return NULL;
    }
}

vector *int_vector_copy(const vector *v)
{
    vector *bob;
    bob = malloc(sizeof(vector));
    if (bob == NULL)
    {
        printf("Не удалось выделить память под структуру\n");
        return NULL;
    }
    bob->size = v->size;
    bob->capacity = v->capacity;
    bob->data = malloc(sizeof(int) * bob->capacity);
    if (bob->data != NULL)
    {
        for (int i = 0; i < bob->capacity; i++)
        {
            bob->data[i] = v->data[i];
        }
        return bob;
    }
    else 
    {
        printf("Не удалось выделить память под массив\n");
        return NULL;
    }
}

void int_vector_free(vector *v)
{
    if (v->data != NULL && v != NULL)
    {
        free(v->data);
        free(v);
    }
}

int int_vector_get_item(const vector *v, size_t index)
{
    if (index <= v->size && index >= 0)
        return *(v->data + index);
    else
        return -1;
}

void int_vector_set_item(vector *v, size_t index, int item)
{
    if (index <= v->size && index >= 0)
        *(v->data + index) = item;
}

size_t int_vector_get_size(const vector *v)
{
    return v->size;
}

size_t int_vector_get_capacity(const vector *v)
{
    return v->capacity;
}

int int_vector_push_back(vector *v, int item)
{
    short flag;
    if (v->size >= v->capacity)
    {
        flag = int_vector_reserve(v, v->capacity * 2);
        if (flag == -1)
        {
            return -1;
        }
    }
    v->data[v->size] = item;
    v->size += 1;
    return 0;
}

void int_vector_pop_back(vector *v)
{
    if (v->size != 0)
        v->size--;
}

int int_vector_shrink_to_fit(vector *v)
{
    vector *temp;
    if (v->size != 0 && v->capacity != 0)   
    { 
        temp = int_vector_new(v->capacity);
        v->capacity = v->size;
        temp->data = realloc(v->data, v->capacity * sizeof(int));
        if (temp->data != NULL)
        {
            v->data = temp->data;
            return 0;
        }
        else
        {
            printf("Не удалось выделить память под массив!\n");
            return -1;
        }
    }
    else
        return -1;
}

int int_vector_resize(vector *v, size_t new_size)
{
    short flag;
    if (new_size > v->size)
    {
        if (new_size > v->capacity)
        {
            flag = int_vector_reserve(v, new_size);
            if (flag != -1)
            {
                for (int i = v->size; i < v->capacity; i++)
                {
                    v->data[i] = 0;
                }
            }
            else   
                return -1;
        }
        v->size = new_size;
        return 0;
    }
    if (new_size < v->size)
    {
        v->size = new_size;
        return 0;
    }
    return 0;
}

int int_vector_reserve(vector *v, size_t new_capacity)
{
    vector *temp;
    if (new_capacity > v->capacity && new_capacity > 0)
    {
        temp = int_vector_new(new_capacity);
        v->capacity = new_capacity;
        temp->data = realloc(v->data, new_capacity * sizeof(int));
        if (temp->data != NULL)
        {
            v->data = temp->data;
            return 0;
        }
        else
            printf("Не удалось выделить память под массив!\n");
            return -1;
    }
    else
    {
        return -1;
    }
}