/*
 * file : priority_queue.c
 * implementazione funzioni e procedure per code di priorita
 */
#include "priority_queue.h"

int isEmptyPriorityQueue(priorityQueue q){
    return (q->size == 0);
}

priorityQueue initPriorityQueue(int heapSize){
    priorityQueue tmp;

    tmp = (priorityQueue)malloc(sizeof(struct T_priority_queue));
    tmp->size = 0;
    tmp->heap = (item *)malloc(heapSize * sizeof(item));
    for(int i=0;i<heapSize;i++)
        tmp->heap[i].priority = (double)999999;

    return tmp;
}

void printPriorityQueue(priorityQueue q){
    printf("\n Stampa coda di pririta' :\n\n");
    for(int i=0;i<q->size;i++){
        printf("\n valore : %d\t priorita : %.2lf", q->heap[i].value, q->heap[i].priority);
    }
}

int left(int index){
    return 2 * index + 1;
}

int right(int index){
    return (2 * index) + 2;
}

int father(int index){
    return index/2;
}

void swap(item *a, item *b){
    item tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(priorityQueue A, int index){
    int sx = left(index);
    int dx = right(index);
    int min;

    if( sx < A->size && A->heap[sx].priority < A->heap[index].priority)
        min = sx;
    else
        min = index;

    if( dx < A->size && A->heap[dx].priority < A->heap[min].priority)
        min = dx;

    if( min != index ){
        swap(&A->heap[index], &A->heap[min]);
        heapify(A, min);
    }
}

void buildHeap(priorityQueue A){
    int i;

    for(i = A->size/2; i >= 0; i--){
        heapify(A, i);
    }
}

int minPriorityQueue(priorityQueue q){
    if(q->size < 0){
        printf("\n\n ERRORE ! Dimensione coda minore di 0...\n");
        exit(-1);
    }

    return q->heap[0].value;
}

int exstractMinPriorityQueue(priorityQueue q){
    if(q->heap < 0){
        printf("\n\n ERRORE ! Dimensione coda minore di 0...\n");
        exit(-1);
    }

    int max = q->heap[0].value;
    q->heap[0] = q->heap[q->size - 1];
    q->size = q->size - 1;
    heapify(q, 0);

    return max;
}

int decreaseKey(priorityQueue q, int index, double newPriority){
    int ret;

    if(newPriority < q->heap[index].priority){
        ret = -1;
    }else{
        q->heap[index].priority = newPriority;
        heapify(q, index);
        ret = 0;
    }

    return ret;
}

int increaseKey(priorityQueue q, int index, double newPriority){
    int ret;

    if(!isEmptyPriorityQueue(q)){
        if(newPriority >= q->heap[index].priority){
            ret = -1;
        }else{
            q->heap[index].priority = newPriority;
            while(index > 0 && q->heap[father(index)].priority > q->heap[index].priority){
                swap(&q->heap[index], &q->heap[father(index)]);
                index = father(index);
            }
            ret = 0;
        }
    }

    return ret;
}

void insertNewElementInPriorityQueueu(priorityQueue q, int newValue, int priority){
    q->size +=  1;
    q->heap[q->size - 1].value = newValue;
    increaseKey(q, q->size - 1, priority);
}

void freePriorityQueue(priorityQueue Q){
    free(Q->heap);
    free(Q);
}

int getPositionOfKey(priorityQueue q, int key){
    int i = 0, found = -1;

    if(!isEmptyPriorityQueue(q)){
        while(i < q->size && found == -1){
            if(q->heap[i].value == key){
                found = i;
            }else{
                i += 1;
            }
        }
    }

    return found;
}
