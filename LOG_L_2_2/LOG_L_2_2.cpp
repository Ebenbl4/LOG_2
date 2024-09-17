#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Size 150000

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void shell(int* items, int count, double* time_spent)
{
    int i, j, gap, k;
    int x, a[5];
    clock_t sort_start, sort_end;
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;
    sort_start = clock();
    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
    sort_end = clock();
    *time_spent = ((double)(sort_end - sort_start)) / CLOCKS_PER_SEC * 1000;
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;
    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

void Fill_rand(int* mass, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        mass[i] = rand() % 1000;
    }
}

void Fill_ascending(int* mass, int size) {
    for (int i = 0; i < size; i++) {
        mass[i] = i;
    }
}

void Fill_descending(int* mass, int size) {
    for (int i = 0; i < size; i++) {
        mass[i] = size - i - 1;
    }
}

void Fill_asc_desc(int* mass, int size) {
    int half = size / 2;
    for (int i = 0; i < half; i++) {
        mass[i] = i;
    }
    for (int i = half; i < size; i++) {
        mass[i] = size - (i - half) - 1;
    }
}

int main() {
    printf(" +-----------+----------------+----------------+----------------+----------------+\n");
    printf(" | Func/set  |   Random       |   Ascending    |   Descending   |   Asc-Desc     |\n");
    printf(" +-----------+----------------+----------------+----------------+----------------+\n");

    int* Mass = (int*)malloc(Size * sizeof(int));
    clock_t sort_start, sort_end;
    double time_spent_rand, time_spent_asc, time_spent_desc, time_spent_asc_desc;

    // Shell sort
    Fill_rand(Mass, Size);
    shell(Mass, Size, &time_spent_rand);
    Fill_ascending(Mass, Size);
    shell(Mass, Size, &time_spent_asc);
    Fill_descending(Mass, Size);
    shell(Mass, Size, &time_spent_desc);
    Fill_asc_desc(Mass, Size);
    shell(Mass, Size, &time_spent_asc_desc);
    printf(" | Shell     | %-14.2f | %-14.2f | %-14.2f | %-14.2f |\n", time_spent_rand, time_spent_asc, time_spent_desc, time_spent_asc_desc);
    printf(" +-----------+----------------+----------------+----------------+----------------+\n");

    // Quick sort
    Fill_rand(Mass, Size);
    sort_start = clock();
    qs(Mass, 0, Size - 1);
    sort_end = clock();
    time_spent_rand = ((double)(sort_end - sort_start)) / CLOCKS_PER_SEC * 1000;

    Fill_ascending(Mass, Size);
    sort_start = clock();
    qs(Mass, 0, Size - 1);
    sort_end = clock();
    time_spent_asc = ((double)(sort_end - sort_start)) / CLOCKS_PER_SEC * 1000;

    Fill_descending(Mass, Size);
    sort_start = clock();
    qs(Mass, 0, Size - 1);
    sort_end = clock();
    time_spent_desc = ((double)(sort_end - sort_start)) / CLOCKS_PER_SEC * 1000;

    Fill_asc_desc(Mass, Size);
    sort_start = clock();
    qs(Mass, 0, Size - 1);
    sort_end = clock();
    time_spent_asc_desc = ((double)(sort_end - sort_start)) / CLOCKS_PER_SEC * 1000;

    printf(" | qs        | %-14.2f | %-14.2f | %-14.2f | %-14.2f |\n", time_spent_rand, time_spent_asc, time_spent_desc, time_spent_asc_desc);
    printf(" +-----------+----------------+----------------+----------------+----------------+\n");

    // default qsort
    Fill_rand(Mass, Size);
    sort_start = clock();
    qsort(Mass, Size, sizeof(int), compare);
    sort_end = clock();
    time_spent_rand = ((double)(sort_end - sort_start)) / CLOCKS_PER_SEC * 1000;

    Fill_ascending(Mass, Size);
    sort_start = clock();
    qsort(Mass, Size, sizeof(int), compare);
    sort_end = clock();
    time_spent_asc = ((double)(sort_end - sort_start)) / CLOCKS_PER_SEC * 1000;

    Fill_descending(Mass, Size);
    sort_start = clock();
    qsort(Mass, Size, sizeof(int), compare);
    sort_end = clock();
    time_spent_desc = ((double)(sort_end - sort_start)) / CLOCKS_PER_SEC * 1000;

    Fill_asc_desc(Mass, Size);
    sort_start = clock();
    qsort(Mass, Size, sizeof(int), compare);
    sort_end = clock();
    time_spent_asc_desc = ((double)(sort_end - sort_start)) / CLOCKS_PER_SEC * 1000;

    printf(" | qsort     | %-14.2f | %-14.2f | %-14.2f | %-14.2f |\n", time_spent_rand, time_spent_asc, time_spent_desc, time_spent_asc_desc);
    printf(" +-----------+----------------+----------------+----------------+----------------+\n");

    free(Mass);
    return 0;
}