#include "IntVector.h"

void vector_out(vector *v);

int main()
{
    vector *viktor, *duplicat;
    int capacity, choice, item, index, result, flag, new_size, new_capacity;
    flag = 1;
    capacity = 10;
    viktor = int_vector_new(capacity);
    viktor->capacity = capacity;
    viktor->size = 5;
    for (int i = 0; i < viktor->size; i++)
    {
        viktor->data[i] = i;
    }
    vector_out(viktor);
    while (flag != 0)
    {
        printf("Выберите операцию: \n");
        printf("1. Копировать вектор \n 2. Получить значение элемента \n 3. Присвоить элементу значение \n 4. Узнать размер вектора \n 5. Узнать емкость вектора \n 6. Добавить элемент в конец \n 7. Удалить последний элемент \n 8. Уменьшить емкость до размера \n 9. Изменить размер \n 10. Изменить емкость \n 11. Выход\n");
        printf("Введите номер операции: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            duplicat = int_vector_copy(viktor);
            vector_out(duplicat);
            break;
        case 2:
            printf("Введите номер элемента: ");
            scanf("%d", &index);
            item = int_vector_get_item(viktor, index);
            printf("Значение найденного элемента %d\n", item);
            break;
        case 3:
            printf("Введите номер и значение элемента через пробел: ");
            scanf("%d %d", &index, &item);
            int_vector_set_item(viktor, index, item);
            vector_out(viktor);
            break;
        case 4:
            result = int_vector_get_size(viktor);
            printf("Размер вектора %d\n", result);
            break;
        case 5:
            result = int_vector_get_capacity(viktor);
            printf("Емкость вектора %d\n", result);
            break;
        case 6:
            printf("Введите значение элемента: ");
            scanf("%d", &item);
            int_vector_push_back(viktor, item);
            vector_out(viktor);
            break;
        case 7:
            int_vector_pop_back(viktor);
            vector_out(viktor);
            break;
        case 8:
            int_vector_shrink_to_fit(viktor);
            vector_out(viktor);
            break;
        case 9:
            printf("Введите новый размер: ");
            scanf("%d", &new_size);
            int_vector_resize(viktor, new_size);
            vector_out(viktor);
            break;
        case 10:
            printf("Введите новую емкость: ");
            scanf("%d", &new_capacity);
            int_vector_reserve(viktor, new_capacity);
            vector_out(viktor);
            break;
        case 11:
            flag = 0;
            break;
        default:
            flag = 0;
            break;
        }
    }
    if (viktor != NULL)
        int_vector_free(viktor);
    if (duplicat != NULL)
        int_vector_free(duplicat);
}

void vector_out(vector *v)
{
    printf("\n");
    printf("Размер вектора = %d\n", v->size);
    printf("Емкость вектора = %d\n", v->capacity);
    printf("Элементы в векторе:");
    for (int i = 0; i < v->size; i++)
    {
        printf(" %d", v->data[i]);
    }
    printf("\n\n");
}