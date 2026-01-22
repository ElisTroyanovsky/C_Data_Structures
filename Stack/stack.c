#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void stack_init(stack *s)
{
    s->top = NULL;
}
int stack_empty(stack s)
{
    return(s.top == NULL);
}
int stack_full(stack s)
{
    return 0;
}
void stack_push(stack *s, stack_item x)
{
    struct stack_node *temp = (struct stack_node*)malloc(sizeof(struct stack_node));
    temp->info = x;
    temp->next = s->top;
    s->top = temp;
}
stack_item stack_pop(stack *s)
{
    if (!stack_empty(*s))
    {
        struct stack_node *temp = s->top;
        stack_item data = s->top->info;
        s->top = temp->next;
        free(temp);
        return data;
    }
}
stack_item stack_top(stack s)
{
    if (!stack_empty(s))
    {
        stack_item data = (s.top)->info;
        return data;
    }
}
void printstack(stack *s) {
    int x;
    stack s1;
    stack_init(&s1);
    while (!stack_empty(*s))
    {
        x = stack_pop(s);
        printf("%d ", x);
        stack_push(&s1,x);
    }
    printf("\n");
    while (!stack_empty(s1))
    {
        stack_push(s, stack_pop(&s1));
    }
}
stack turn(stack *s,stack s1) {
    stack s2;
    stack_init(&s2);
    while (!stack_empty(s1)) {
        stack_push(&s2, stack_top(*s));
        stack_push(&s1, stack_pop(s));
    }
    while (!stack_empty(s2)) {
        stack_push(s, stack_pop(&s2));
    }
    return s1;
}
