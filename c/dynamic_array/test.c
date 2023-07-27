#include <stdio.h>
#include "dynamic.c"

// Example to create a dynamic array of type float and struct Points with 100 elements.
void print_f(Array* ptr);
void print_p(Array* ptr);

struct Points{
   int x,y;
};

int main(){
    Array *a = INIT(float, 1);
    Array *b = INIT(struct Points, 1);
    float temp_i;
    struct Points temp_p;

    for(int i=0; i<100; i++){
        temp_i = i;
        push(a, &temp_i);
    }
    pop(a);

    for(int i=0; i<100; i++){
        temp_p.x = i;
        temp_p.y = i*i;
        push(b, &temp_p);
    }
    pop(b);

    printf("Float array:\n");
    print_f(a);
    printf("\nPoints array:\n");
    print_p(b);


    free_array(a);
    free_array(b);
    return 0;
}


void print_f(Array* ptr){
    printf("[");
    for(int i=0; i<ptr->len; i++){
        printf("%f, ", *(float*)get(ptr, i));
    }
    printf("\b\b]\n");
}

void print_p(Array* ptr){
    printf("[");
    for(int i=0; i<ptr->len; i++){
        struct Points tmp = get_value(ptr, i, struct Points);
        printf("(%d, %d), ", tmp.x, tmp.y);
    }
    printf("\b\b]\n");
}
