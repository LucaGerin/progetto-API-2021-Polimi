#include <stdio.h>
#include <stdlib.h>

#define MAX 3000  /*massima lunghezza riga input*/
#define LONG_MAXIMUM 2147483647

/* ___ DATA STRUCTURES ___ */
typedef struct{
    int ID;
    long score; //serve long int? qual è massimo raggiungibile?
} graph;
typedef graph *P_GRAPH;

typedef struct{
    int number;
    long distance;
    int predecessor;
}node;
typedef node *P_NODE;

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
    graph temp = *b;
    *b = *a;
    *a = temp;
}

void swap_nodes(P_NODE a, P_NODE b){
    node temp = *b;
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

void min_heapify(P_NODE nodes[], P_MIN_HEAP heap, int n){
    int left = 2*n+1;
    int right = 2*n+2;
    int minimum_pos;
    if (left < heap->size && nodes[left]->distance < nodes[n]->distance)
        minimum_pos = left;
    else minimum_pos=n;
    if (right < heap->size && nodes[right]->distance < nodes[minimum_pos]->distance)
        minimum_pos = right;
    if (minimum_pos != n){
        swap_nodes(nodes[n], nodes[minimum_pos]);
        min_heapify(nodes, heap, minimum_pos);
    }
}

P_GRAPH getMax (P_GRAPH heap_array[]){
    return heap_array[0];
}
/*
P_NODE getMin (P_NODE nodes[]){
    return nodes[0];
}
 */

/*
P_NODE removeMin (P_NODE nodes[], P_MIN_HEAP heap){
    if(heap->size<1){
        //return ??? cosa returno?
    }
    P_NODE minimum = nodes[0];
    nodes[0]=nodes[heap->size - 1];
    heap->size--;
    min_heapify(nodes, heap, 0);
    return minimum;

}
*/


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

/*
void insert_min_heap(P_NODE *nodes, P_MIN_HEAP heap, P_NODE node_to_add){
    nodes[heap->size]=node_to_add;
    heap->size++;

    int current=heap->size;
    while(current!=0 && nodes[(current - 1) / 2]->distance > nodes[current]->distance){
        swap_nodes(nodes[current], nodes[(current - 1) / 2]);
        current=(current-1)/2;
    }
}
 */


/*
void decrease_distance(P_NODE *nodes, P_MIN_HEAP heap, int index, int new_distance){
    nodes[index]->distance = new_distance;
    while (index != 0 && nodes[(index-1)/2] > nodes[index])
    {
        swap_nodes(nodes[index], nodes[(index-1)/2]);
        index = (index-1)/2;
    }
}
*/

void print_heap(P_GRAPH heap_Array[], P_MAX_HEAP heap){
    if(heap->size>0){
        int i=0;
        do{
            printf("%d", heap_Array[i]->ID);
            i++;
        }while(i<heap->size && fputs(" ", stdout));
    }
}

void print_heap_debug(P_GRAPH heap_Array[], P_MAX_HEAP heap){
    if(heap->size>0){
        int i=0;
        do{
            printf("%d: %ld", heap_Array[i]->ID, heap_Array[i]->score);
            i++;
        }while(i<heap->size && fputs(" \n", stdout));
    }
    printf("\n");
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
    return 0;
}

/*
int search_min_heap(P_NODE heap_array[], min_heap heap, int root_index, long distance){
    if(root_index < 0 || root_index > heap.size - 1) return 0;
    else{
        long current_distance = heap_array[root_index]->distance;
        if(current_distance == distance) return 1;
        else {
            if(current_distance > distance) return 0;
            if(search_min_heap(heap_array, heap, root_index * 2 + 1, distance)) return 1;
            if(search_min_heap(heap_array, heap, root_index * 2 + 2, distance)) return 1;
        }
    }
    return 0;
}
 */

/* ___ FUNCTIONS ___*/

/**
 * method to check if a char given as parameter is a space
 * @param x is the char given
 * @return 1 if x is a space, 0 otherwise
 */
int is_space (char x){
    if (x==32) return 1;
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
 * method to check if a char given as parameter is a comma
 * @param x is the char given
 * @return 1 if x is a comma, 0 otherwise
 */
int is_endOfLine (char x){
    if (x=='\n') return 1;
    else return 0;
}


/**
 * Method to read the first line containing d and k
 * @param dimension is a pointer to an int into which to store d
 * @param leaderBoardDimension is a pointer to an int into which to store k
 */
void readFirstLine( int *dimension, int *leaderBoardDimension){ //DEVONO ESSERE SEPARATI DA SPAZIO O DA VIRGOLA?? su slides esempio diverso da spiegazione
    char input[MAX], *result;
    result = fgets(input, MAX, stdin);

    int res=0, i=0;

    for(; !is_space(result[i]); i++){
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
 /*
int readCommand(){
    char line[15];
    char* result = fgets(line, 15, stdin);
    return line[0];
}
*/

/*
void dijkstra_min_heap(void *matrix, int dimension){

    int (*p_matrix)[dimension][dimension] = (int (*)[dimension][dimension]) matrix;
    long score=0;
    P_MIN_HEAP q = malloc(sizeof (min_heap));
    P_NODE q_vector[dimension];
    q->size=0;
    q->length=dimension;
    for(int i=1; i<dimension; i++){
        P_NODE v_node = malloc(sizeof(node));
        v_node->number=i;
        v_node->distance=-1;
        v_node->predecessor=-1;
        insert_min_heap(q_vector, q, v_node);
    }

    while (q->size>0){
        P_NODE u = removeMin(q_vector, q);
        for(int succ=0; succ<dimension && p_matrix[u->number][succ]>0 ;succ++){
            long new_distance = u->distance + (long)(int)*p_matrix[u->number][succ];
            //if v:dist > ndis
            //  succ:dist  = ndis
            //  succ:prev  ) u
            //  DecrementaPri(Q; v; ndis)
        }
    }
}
*/

//TO REMOVE!!!!
void quicksort(int a[MAX],int primo,int ultimo){
    int i, j, pivot, temp;
    /*pivot -- inizialmente il pivot è il primo elemento
    primo e ultimo sono le due variabili che servono per scorrere l'array
    */
    if(primo<ultimo){
        pivot=primo;
        i=primo;
        j=ultimo;

        while(i<j){
            while(a[i]<=a[pivot]&&i<ultimo)
                i++;
            while(a[j]>a[pivot])
                j--;
            if(i<j){
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }

        temp=a[pivot];
        a[pivot]=a[j];
        a[j]=temp;
        quicksort(a,primo,j-1);
        quicksort(a,j+1,ultimo);
    }
}

long dijkstra_matrix(int dimension, long (*p_matrix)[dimension]){     //oppure long p_matrix[MAX][MAX]

    long distance[dimension], minimum_distance;
    //int predecessor[dimension];
    int visited[dimension],  next_node=0;

    int i,j;

    for(i=0; i < dimension; i++)
        for(j=0; j < dimension; j++){
            if(p_matrix[i][j] == 0)
                p_matrix[i][j] = LONG_MAXIMUM;
        }
    for(i=0; i < dimension; i++){
        distance[i]= (long) p_matrix[0][i];
        //predecessor[i]=0;
        visited[i]=0;
    }
    distance[0]=0;
    visited[0]=1;

    int current=1;
    while(current < dimension - 1){
        minimum_distance=LONG_MAXIMUM;
        for(i=0; i < dimension; i++){
            if((distance[i] < minimum_distance) && !visited[i]){
                minimum_distance=distance[i];
                next_node=i;
            }
        }
        visited[next_node]=1;
        for(i=0; i < dimension; i++)
            if(!visited[i])
                if(minimum_distance + p_matrix[next_node][i] < distance[i]){
                    distance[i]= minimum_distance + p_matrix[next_node][i];
                    //predecessor[i]=next_node;
                }
        current++;
    }
    long total=0;
    for(i=1; i<dimension; i++){
        if(distance[i]!=LONG_MAXIMUM)
            total+=distance[i];
    }
    return total;
}



/* ___ MAIN ___*/


int main() {

    int matrix_dimension;

    P_MAX_HEAP heap = malloc(sizeof(max_heap));
    heap->size=0;

    readFirstLine(&matrix_dimension, &heap->length);

    P_GRAPH heap_array[heap->length];
    long matrix[matrix_dimension][matrix_dimension];

    int ID_counter=0;

    char line[MAX];

    while((fgets(line, 15, stdin)) != NULL){

        if(line[0]==84){ //TopK

            //printf("DEBUG: letto TopK\n");
            print_heap(heap_array, heap);

        }
        else{ //AggiungiGrafo

            //printf("DEBUG: letto AggiungiGrafo\n");

            //Read the matrix from input
            int res;
            int index;
            char *result;
            for(int l=0; l < matrix_dimension; l++){
                result = fgets(line, MAX, stdin);
                index=0;
                for(int c=0; c < matrix_dimension; c++){
                    res=0;
                    for(; !is_comma(result[index]) && !is_endOfLine(line[index]); index++){
                        res=res*10+(line[index]-48);
                    }
                    matrix[l][c]= (long) res;
                    index++;
                }
            }
            //DEBUG

            printf("DEBUG_MAIN: Ecco la matrice del grafico numero %d:\n", ID_counter);
            for(int j=0; j < matrix_dimension; j++){
                for(int k=0; k < matrix_dimension; k++){
                    if(k==0) printf("|   ");
                    printf("%ld ", matrix[j][k]);
                }
                printf("\n");
            }


            long score = dijkstra_matrix(matrix_dimension, matrix);
            printf("Lo score del grafico numero %d è di %ld\n", ID_counter, score);

            if(heap->size < heap->length){
                P_GRAPH new_graph = malloc(sizeof (graph));
                new_graph->ID=ID_counter;
                new_graph->score=score;
                insert_max_heap(heap_array, heap, new_graph);
                printf("DEBUG: Aggiungo alla classifica il grafico %d in quanto non piena\n", ID_counter);
            }
            else if(score < getMax(heap_array)->score){
                P_GRAPH removed = removeMax(heap_array, heap);
                printf("DEBUG: Aggiungo alla classifica il grafico %d sostituendo il max che era il numero %d con score %ld\n", ID_counter, removed->ID, removed->score);
                free(removed);

                P_GRAPH new_graph = malloc(sizeof (graph));
                new_graph->ID=ID_counter;
                new_graph->score=score;
                insert_max_heap(heap_array, heap, new_graph);
            }

            ID_counter++;

            //DEBUG:
            printf("DEBUG: ecco la TopK...\n");
            print_heap_debug(heap_array, heap);
            printf("\n---------\n");


        }

    }
    free(heap);
    return 0;
}