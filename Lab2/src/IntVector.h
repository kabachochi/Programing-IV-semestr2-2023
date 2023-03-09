#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct IntVector
{
    int *data;
    int size;
    int capacity;
} vector;

vector *int_vector_new(size_t initial_capacity); // создание массива нулевого размера

vector *int_vector_copy(const vector *v); // копия вектора

void int_vector_free(vector *v); // освобождение памяти

int int_vector_get_item(const vector *v, size_t index); // получение элемента под номером index

void int_vector_set_item(vector *v, size_t index, int item); // присваивание значения item элементу массива под номером index

size_t int_vector_get_size(const vector *v); // получение размера вектора

size_t int_vector_get_capacity(const vector *v); // получение емкости вектора

int int_vector_push_back(vector *v, int item); // добавление элемента в конец массива

void int_vector_pop_back(vector *v); // удаление последнего элемента массива

int int_vector_shrink_to_fit(vector *v); // уменьшение емкости массива до его размера

int int_vector_resize(vector *v, size_t new_size); // изменение размера массива

int int_vector_reserve(vector *v, size_t new_capacity); // изменение емкости массива