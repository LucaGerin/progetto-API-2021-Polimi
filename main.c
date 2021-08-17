#include <stdio.h>
#include <stdlib.h>

#define MAX 3000  /*massima lunghezza riga input*/

enum command {aggiungiGrafo, TopK};

/* ___ DATA STRUCTURES ___ */
typedef struct{
    int ID;
    long score; //serve long int? qual è massimo raggiungibile?
} graph;
typedef graph *P_GRAPH;

typedef struct{
    int length;
    int size;
} max_heap;
typedef max_heap *P_MAX_HEAP;

typedef struct{
    int length;
    int size;
} min_heap;
typedef min_heap *P_MIN_HEAP;


/* ___ HEAP ___ */

void swap_graph(P_GRAPH a, P_GRAPH b)
{
    P_GRAPH temp = b;
    b = a;
    a = temp;
}

void swap_long_int(long *a, long *b){
    int temp = *b;
    *b = *a;
    *a = temp;

}

void max_heapify(P_GRAPH heap_array[], P_MAX_HEAP heap, int n){
    int left = 2*n+1;
    int right = 2*n+2;
    int maximum_pos;
    if(left<heap->size && heap_array[left]->score > heap_array[n]->score)
        maximum_pos=left;
    else maximum_pos=n;
    if(right<heap->size && heap_array[right]->score > heap_array[maximum_pos]->score)
        maximum_pos=right;
    if (maximum_pos!=n){
        swap_graph(heap_array[n], heap_array[maximum_pos]);
        max_heapify(heap_array,heap,maximum_pos);
    }
}

void min_heapify(long distances[], P_MIN_HEAP heap, int n){
    int left = 2*n+1;
    int right = 2*n+2;
    int minimum_pos;
    if (left < heap->size && distances[left] < distances[n])
        minimum_pos = left;
    else minimum_pos=n;
    if (right < heap->size && distances[right] < distances[minimum_pos])
        minimum_pos = right;
    if (minimum_pos != n){
        swap_long_int(&distances[n], &distances[minimum_pos]);
        min_heapify(distances, heap, minimum_pos);
    }
}

P_GRAPH getMax (P_GRAPH heap_array[]){
    return heap_array[0];
}

long getMin (long distances[]){
    return distances[0];
}

long removeMin (long distances[], P_MIN_HEAP heap){
    if(heap->size<1){
        //return ??? cosa returno?
    }
    long minimum = distances[0];
    distances[0]=distances[heap->size-1];
    heap->size--;
    min_heapify(distances,heap, 0);
    return minimum;

}

P_GRAPH removeMax (P_GRAPH heap_array[], P_MAX_HEAP heap) {
    if(heap->size<1){
        // si verifica mai questo caso? lo controllo qui o fuori dalla funzione?
        //return ...
    }
    P_GRAPH maximum = heap_array[0];
    heap_array[0]=heap_array[heap->size - 1];
    heap->size--;
    max_heapify(heap_array, heap, 0);
    return maximum;
}

void insert_max_heap(P_GRAPH *heap_array, P_MAX_HEAP heap, graph *graph_to_add){
    if (heap->size == 0){
        heap_array[0]=graph_to_add;
        heap->size++;
    }
    else
    {
        heap_array[heap->size] = graph_to_add;
        heap->size++;
        for (int i = heap->size / 2 - 1; i >= 0; i--){
            max_heapify(heap_array, heap, i);
        }
    }
}

void insert_min_heap(long *distances, P_MIN_HEAP heap, long long_to_add){
    distances[heap->size]=long_to_add;
    heap->size++;

    int current=heap->size;
    while(current!=0 && distances[(current-1)/2] > distances[current]){
        swap_long_int(&distances[current], &distances[(current-1)/2]);
        current=(current-1)/2;
    }
}

void print_heap(P_GRAPH heap_Array[], int size){
    putchar_unlocked(heap_Array[0]->ID);
    for(int i=1; i<size; i++){
        putchar_unlocked(' ');
        putchar_unlocked(heap_Array[i]->ID);
    }
}

void print_heap_safe(P_GRAPH heap_Array[], int size){
    for(int i=0; i<size; i++){
        printf("%d ",heap_Array[i]->ID);
    }
}

int search_max_heap(P_GRAPH heap_array[], max_heap heap, int root_index, long score){
    if(root_index < 0 || root_index > heap.size - 1) return 0;
    else{
        long current_score = heap_array[root_index]->score;
        if(current_score==score) return 1;
        else {
            if(current_score<score) return 0;
            if(search_max_heap(heap_array, heap, root_index * 2 + 1, score)) return 1;
            if(search_max_heap(heap_array, heap, root_index * 2 + 2, score)) return 1;
        }
    }
}



/* ___ FUNCTIONS ___*/




/**
 * method to check if a char given as parameter is a number
 * @param x is the char given
 * @return 1 if x is a number, 0 otherwise
 */
int is_num (char x){
    if (x>=48 && x<=57) return 1;
    else return 0;
}


/**
 * method to check if a char given as parameter is a comma
 * @param x is the char given
 * @return 1 if x is a comma, 0 otherwise
 */
int is_comma (char x){
    if (x==44) return 1;
    else return 0;
}


/**
 * Takes char array line and extracts 'amountOfNumbers' numbers and puts them in int array 'array_to_fill'
 * @requires amountOfNumbers=array_to_fill.length
 * @param line is the String from which to take the numbers
 * @param array_to_fill is the int array to fill
 * @param amountOfNumbers is the amount of numbers to extract
 */
void ConvertMatrixLine(char *line, int *array_to_fill, int amountOfNumbers){
    int i=0, index=0, res;

    for(; i<amountOfNumbers; i++){

        res=0;

        for(;!is_comma(line[index]);index++){
            res=res*10+(line[index]-48);
        }

        array_to_fill[i]=res;
        index++;

    }
}

/**
 * Reads a matrix from the input and puts it in the result
 * @param dimension
 * @param result
 */
void readMatrix(int dimension, void *result){

    int (*pointer)[dimension][dimension] = (int (*)[dimension][dimension]) result;

    char line[MAX];
    for(int i=0; i<dimension; i++){
        fgets(line, MAX, stdin);
        ConvertMatrixLine(line, *pointer[i], dimension);
    }
}

/**
 * MEthod to read the first line containing d and k
 * @param dimension is a pointer to an int into which to store d
 * @param leaderBoardDimension is a pointer to an int into which to store k
 */
void readFirstLine( int *dimension, int *leaderBoardDimension){ //DEVONO ESSERE SEPARATI DA SPAZIO O DA VIRGOLA?? su slides esempio diverso da spiegazione
    char input[MAX];
    fgets(input, MAX, stdin);

    int res=0, i=0;

    for(;!is_comma(input[i]);i++){
        res=res*10+(input[i]-48);
    }
    *dimension=res;

    i++;
    res=0;
    for(;input[i]!='\n';i++){
        res=res*10+(input[i]-48);
    }
    *leaderBoardDimension=res;
}

/**
 * Method to read a command
 * @return the first letter of the line on the stdin
 */
int readCommand(){
    char line[MAX];
    fgets(line, MAX, stdin);
    return line[0];
}


/* ___ MAIN ___*/
int main() {

    int dimension, command;

    P_MAX_HEAP heap = malloc(sizeof(heap));
    heap->size=0;
    heap->length=10;//line to remove


    readFirstLine(&dimension, &heap->length);
    printf("DEBUG: la prima riga contiene %d,%d", dimension, heap->length);


    P_GRAPH heap_array[heap->length];
    //int matrix[heap->length][heap->length];


    P_GRAPH graph1 = malloc(sizeof(graph));
    graph1->ID=0;
    graph1->score=100;

    P_GRAPH graph2 = malloc(sizeof(graph));
    graph2->ID=1;
    graph2->score=150;

    insert_max_heap(heap_array, heap, graph1);
    printf("size=%d, length=%d\n", heap->size, heap->length);
    print_heap_safe(heap_array, heap->size);

    insert_max_heap(heap_array, heap, graph2);
    printf("size=%d, length=%d\n", heap->size, heap->length);
    print_heap_safe(heap_array, heap->size);



/*

    while(1){

        if(readCommand()==84){ //TopK

            readMatrix(dimension, matrix);

        }
        else{ //AggiungiGrafo

        }

        break; //TO REMOVE

    }
*/
    return 0;
}