#include <stdlib.h>
#include <assert.h>
#include "vector.h"



//Constructor
vector vector_init(){
    vector thing;
    thing.size = 100;
    thing.count = 0;
    thing.data = (int*)malloc(thing.size * sizeof(int));
    return thing;
}
  
//Internal function to double capacity when full  
void __vector_resize(vector* info){
    //Create new array to store data
    int* resized = (int*)malloc(info->size*2*sizeof(int));
    info->size = info->size * 2;
    //Copy data
    for(int i = 0;i < info->count;i++){
        resized[i] = info->data[i];
    }
    free(info->data);
    info->data = resized;
    return;
}
//Push
void vector_push(vector* info,int data){
   
    if(info->count == info->size)
        __vector_resize(info);
    info->data[info->count] = data;
    info->count++;
    return;
}
//Pop - Also returns element popped
int vector_pop(vector* info){
    if(info->count < 1)
        assert(info->count && "**POP OPERATION FAILED, VECTOR EMPTY**");
    else{
        info->count -= 1;
        return info->data[info->count];
    }
    return 0;
}

int vector_get_index(vector* info,unsigned int index){
    if(index > info->count - 1)
        assert(!"**INDEX OUT OF RANGE**");
    return info->data[index];
}

void decon_vector(vector* info){
    free(info->data);
    return;
}

void vector_insert(vector* info, int data, unsigned int index){
    if(info->count == info->size)
        __vector_resize(info);
    if(index > info->count)
        assert(!"**INDEX OUT OF RANGE**");
    if(index == info->count){
        vector_push(info,data);
        return;}
    for(unsigned int i = info->count;i >= index + 1;i--){
        info->data[i] = info->data[i - 1];
    }
    info->data[index] = data;
    info->count++;
    return;
}

vector vector_copy(vector* info){
    vector return_vector;
    return_vector.size = info->size;
    return_vector.count = info->count;
    int* new_array = (int*)malloc(return_vector.size * sizeof(int));
    for(int i = 0;i < info->count;i++){
            new_array[i] = info->data[i];
    }
    
    return_vector.data = new_array;
    return return_vector;
    
}

vector intarr_to_vector(int* arr,unsigned int count){
    vector ret_val;
    ret_val.count = count;
    ret_val.size = count + 100;
    int* new_arr = (int*)malloc(ret_val.size * sizeof(int));
    for(int i = 0;i < count;i++){
        new_arr[i] = arr[i];
    }
    ret_val.data = new_arr;
    return ret_val;
}

void vector_sort(vector* info){
    int* heap_arr = (int*)malloc((info->count + 1) * sizeof(int));
    heap_arr[0] = 1; //Set Size to 1, ignoring 0
    for(int i = 0;i < info->count;i++){
        insert_heap(heap_arr,info->data[i]);
    }
    for(int i = 0;i < info->count;i++){
        info->data[i] = pop_min_heap(heap_arr);
    }
   
    free(heap_arr);
    return;
}



void swap(int* a,int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void insert_heap(int* heap,int data){
    heap[0]++;
    //printf("heap size = %d\n",heap[0]);
    unsigned int index = heap[0] - 1;
    heap[index] = data;
    while(index > 0 && heap[(index)/2] > data && (index)/2 != 0){
        swap(&heap[index],&heap[(index)/2]);
        index = (index)/2;        
    }
    return;
}

int pop_min_heap(int* heap){
    int ret_val = heap[1];
    int index = 1;
    int l = 2 * index;
    int r = 2 * index + 1;
    heap[0]--;
    heap[index] = heap[heap[0]];
    while(heap[index] > heap[l] || heap[index] > heap[r]){
        if(heap[l] < heap[index] && heap[l] <= heap[r] && l <= heap[0]){
            swap(&heap[l],&heap[index]);
            index = l;
            l = 2 * index;
            r = 2 * index + 1;
        }
        else if(heap[index] > heap[r] && r <= heap[0]){
            swap(&heap[index],&heap[r]);
            index = r;
            l = 2 * index;
            r = 2 * index + 1;
        }
        else
            break;
    }
    return ret_val;
}