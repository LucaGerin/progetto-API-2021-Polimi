#include <stdio.h>

#define MAX 3000  /*massima lunghezza riga input*/

enum command {aggiungiGrafo, TopK};

/* ___ DATA STRUCTURES ___ */
typedef struct{
    int ID;
    int score; //serve long int? qual è massimo raggiungibile?
} *graph;

typedef struct{
    int length;
    int heapSize;
} *maxHeap;


/* ___ HEAP ___ */

void swap(graph *a, graph *b)
{
    graph temp = *b;
    *b = *a;
    *a = temp;
}

//CONTROLLARE INDICI (IN PSEUDODODICE INDICI PARTONO DA 1 MA QUI DA 0

void max_heapify(graph heap_array[], maxHeap heap, int n){
    int left = 2*n+1;
    int right = 2*n+2;
    int maximum_pos;
    if(left<heap->heapSize && heap_array[left]->score > heap_array[n]->score)
        maximum_pos=left;
    else maximum_pos=n;
    if(right<heap->heapSize && heap_array[right]->score > heap_array[maximum_pos]->score)
        maximum_pos=right;
    if (maximum_pos!=n){
        swap(&heap_array[n], &heap_array[maximum_pos]);
        max_heapify(heap_array,heap,maximum_pos);
    }
}

graph getMax (graph heap_array[]){
    return heap_array[0];
}

graph removeMax (graph heap_array[], maxHeap heap){
    //if(heap->heapSize<1) si verifica mai questo caso?
    if(heap->heapSize<1){
        graph maximum = heap_array[0];
        heap_array[0]=heap_array[heap->heapSize-1];
        heap->heapSize--;
        max_heapify(heap_array, heap, 0);
        return maximum;
    }
}

void insert(graph heap_array[], maxHeap heap, graph graph_to_add){
    if (heap->heapSize==0){
        heap_array[0]=graph_to_add;
        heap->heapSize++;
    }
    else
    {
        heap_array[heap->heapSize] = graph_to_add;
        heap->heapSize++;
        for (int i = heap->heapSize/2-1; i >= 0; i--){
            max_heapify(heap_array, heap, i);
        }
    }

}

void print_heap(graph heap_Array[], int size){
    putchar_unlocked(heap_Array[0]->ID)
    for(int i=1; i<size; i++){
        putchar_unlocked(' ');
        putchar_unlocked(heap_Array[i]->ID);
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
void readFirstLine( int *dimension, int *leaderBoardDimension){
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

    int dimension, k, command;
    int matrix[dimension][dimension];

    readFirstLine(&dimension, &k);
    printf("DEBUG: la prima riga contiene %d,%d", dimension, k);

    while(1){

        if(readCommand()==84){ //TopK

            readMatrix(dimension, matrix);

        }
        else{ //AggiungiGrafo

        }

        break; //TO REMOVE

    }

    return 0;
}