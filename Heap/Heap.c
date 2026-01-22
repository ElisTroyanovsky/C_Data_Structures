//
// Created by Elis Troyanovsky on 04/11/2025.
//

#include "Heap.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

int H_init(Heap *H, int N) {
    if (!H || N <= 0) return 0;

    H->keys = (int*)malloc(sizeof(int) * (N + 1));
    if (!H->keys) return 0;

    H->count = 0;
    H->N = N;
    return 1;
}

void swap(Heap *H, int i, int j) {
    int temp = H->keys[i];
    H->keys[i] = H->keys[j];
    H->keys[j] = temp;
}
int father(int i) {
    return i / 2;
}
int left_son(int i) {
    return i * 2;
}
int right_son(int i) {
    return i * 2 + 1;
}

int find_max(Heap* H) {
    if (!H || !H->keys || H->count == 0) return 0;
    return H->keys[1];
}

int sift_up(Heap* H, int i) {
    if (!H || !H->keys) return 0;

    while (i > 1) {
        int parent = i / 2;
        if (H->keys[parent] >= H->keys[i]) break;

        int tmp = H->keys[parent];
        H->keys[parent] = H->keys[i];
        H->keys[i] = tmp;

        i = parent;
    }
    return 1;
}

int sift_down(Heap* H, int i) {
    if (!H || !H->keys) return 0;

    while (1) {
        int left = 2 * i;
        int right = left + 1;
        int largest = i;

        if (left <= H->count && H->keys[left] > H->keys[largest]) largest = left;
        if (right <= H->count && H->keys[right] > H->keys[largest]) largest = right;

        if (largest == i) break;

        int tmp = H->keys[i];
        H->keys[i] = H->keys[largest];
        H->keys[largest] = tmp;

        i = largest;
    }
    return 1;
}

int H_insert(Heap *H, int x) {
    if (!H || !H->keys) return 0;
    if (H->count >= H->N) return 0;

    H->count++;
    H->keys[H->count] = x;
    return sift_up(H, H->count);
}


int del_max(Heap *H) {
    if (!H || !H->keys || H->count == 0) return 0;

    int maxv = H->keys[1];
    H->keys[1] = H->keys[H->count];
    H->count--;

    if (H->count > 0) sift_down(H, 1);
    return maxv;
}

int Build_Heap(Heap *H, int* values) {
    int i;
    if ((!H) || !H_init(H, sizeof(values) / sizeof(int)))
        return -1;
    H->count = sizeof(values) / sizeof(int);
    memcpy(H->keys + 1, values, sizeof(values));
    for (i = sizeof(values) / sizeof(int) / 2; i > 0; i--) sift_down(H, i);
}