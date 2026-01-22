#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void queue_init(queue *q)
{
    q->head = q->rear = NULL;
}
void enqueue(queue *q, queue_item x)
{
    queue_node *a = (queue_node*)malloc(sizeof(queue_node));
    a->info = x;
    a->next = NULL;
    if (queue_empty(*q))
        q->head = q->rear = a;
    else// סוף תור
    {
        q->rear->next = a;
        q->rear = a;
    }
}
queue_item dequeue(queue *q)
{
    queue_item x = q->head->info;
    queue_node *a = q->head;
    q->head = q->head->next;
    if (q->head == NULL)
        q->rear = NULL;
    free(a);
    return x;
}
queue_item queue_top(queue q)
{
    return q.head->info;
}
int queue_empty(queue q)
{
    return q.head == NULL;
}
void queue_print(queue *q)
{
    queue temp;
    queue_init(&temp);
    while (!queue_empty(*q))
    {
        printf("%d", queue_top(*q));
        enqueue(&temp, dequeue(q));
    }
    while (!queue_empty(temp))
        enqueue(q, dequeue(&temp));
    puts("");
}
void copy(queue *q , queue *cop)
{
    queue temp;
    queue_init(&temp);
    while (!queue_empty(*q))
    {
        enqueue(&temp, dequeue(q));
    }
    while (!queue_empty(temp))
    {
        enqueue(q, queue_top( temp));
        enqueue(cop, dequeue(&temp));
    }
}