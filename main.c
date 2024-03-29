#include <stdio.h>
#include <stdlib.h>

#define MAX 3000  /*massima lunghezza riga input*/
#define INT_MAXIMUM 2147483647

/* ___ DATA STRUCTURES ___ */
typedef struct{
    int ID;
    int score; //serve long int? qual è massimo raggiungibile?
} graph;
typedef graph *P_GRAPH;

/*
typedef struct{
    int number;
    long distance;
    int predecessor;
}node;
typedef node *P_NODE;
*/

typedef struct{
    int length;
    int size;
} max_heap;
typedef max_heap *P_MAX_HEAP;

/*
typedef struct{
    int length;
    int size;
} min_heap;
typedef min_heap *P_MIN_HEAP;
*/

/* ___ HEAP ___ */

void swap_graph(P_GRAPH a, P_GRAPH b)
{
    graph temp = *b;
    *b = *a;
    *a = temp;
}

/*
void swap_nodes(P_NODE a, P_NODE b){
    node temp = *b;
    *b = *a;
    *a = temp;
}
*/

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

/*
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
*/

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

/*
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
*/

void insert_max_heap(P_GRAPH *heap_array, P_MAX_HEAP heap, graph *graph_to_add){

    heap->size++;
    heap_array[heap->size-1] = graph_to_add;
    int i=heap->size-1;
    while(i>0 && heap_array[(i-1)/2]->score<heap_array[i]->score){
        swap_graph(heap_array[(i-1)/2],heap_array[i]);
        i=(i-1)/2;
    }

}


void replace_max(P_GRAPH heap_array[], P_MAX_HEAP heap, int new_score, int new_ID){
    heap_array[0]->score = new_score;
    heap_array[0]->ID = new_ID;
    max_heapify(heap_array, heap, 0);
}


/*
void insert_max_heap_better(P_GRAPH *heap_array, P_MAX_HEAP heap, graph *graph_to_add){
    if (heap->size == 0){
        heap_array[0]=graph_to_add;
        heap->size++;
    }
    else{
        heap_array[heap->size] = graph_to_add;
        heap->size++;
        int i = heap->size;
        while(i>0 || heap_array[(i-1)/2]<heap_array[i]){
            swap_graph(heap_array[i], heap_array[(i-1)/2]);
            i=(i-1)/2;
        }
    }
}
*/

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
    fputs("\n", stdout);
}


void print_heap_debug(P_GRAPH heap_Array[], P_MAX_HEAP heap){
    if(heap->size>0){
        int i=0;
        do{
            printf("%d: %d", heap_Array[i]->ID, heap_Array[i]->score);
            i++;
        }while(i<heap->size && fputs(" \n", stdout));
    }
    printf("\n");
}


/*
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
*/

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
 /*
int is_comma (char x){
    if (x==44) return 1;
    else return 0;
}
*/

/**
 * method to check if a char given as parameter is a comma
 * @param x is the char given
 * @return 1 if x is a comma, 0 otherwise
 */
 /*
int is_endOfLine (char x){
    if (x=='\n') return 1;
    else return 0;
}
*/


int is_number (char x){
    if (x>47 && x<58) return 1;
    else return 0;
}

/**
 * Method to read the first line containing d and k
 * @param dimension is a pointer to an int into which to store d
 * @param leaderBoardDimension is a pointer to an int into which to store k
 */
 /*
void readFirstLine( int *dimension, int *leaderBoardDimension){ //DEVONO ESSERE SEPARATI DA SPAZIO O DA VIRGOLA?? su slides esempio diverso da spiegazione
    char input[200], *result;
    result = fgets(input, 200, stdin);

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
  */

/*
int dijkstra_matrix(int dimension, int (*p_matrix)[dimension]){     //oppure long p_matrix[MAX][MAX]

    int distance[dimension], minimum_distance;
    //int predecessor[dimension];
    int visited[dimension],  next_node=0;

    int i,j;

    for(i=0; i < dimension; i++)
        for(j=0; j < dimension; j++){
            if(p_matrix[i][j] == 0)
                p_matrix[i][j] = INT_MAXIMUM;
        }
    for(i=0; i < dimension; i++){
        distance[i]= p_matrix[0][i];
        //predecessor[i]=0;
        visited[i]=0;
    }
    distance[0]=0;
    visited[0]=1;

    int current=1;
    while(current < dimension - 1){
        minimum_distance=INT_MAXIMUM;
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
    int total=0;
    for(i=1; i<dimension; i++){
        if(distance[i]!=INT_MAXIMUM)
            total+=distance[i];
    }
    return total;
}
*/

int dijkstra_matrix_2(int dimension, int (*p_matrix)[dimension]){
    int distance[dimension], alt, min_distance;
    int visited[dimension];
    int i;

    for(i=0; i<dimension; i++){
        distance[i]=INT_MAXIMUM;
        visited[i]=0;
    }
    distance[0]=0;

    int cnt=0;
    while(cnt<dimension-1){

        int u=0;
        min_distance=INT_MAXIMUM;
        for(i=0; i<dimension; i++){
            if(distance[i]<min_distance && visited[i]==0){
                min_distance=distance[i];
                u=i;
            }
        }
        visited[u]=1;
        if(distance[u] == INT_MAXIMUM) break;

        for(i=0; i<dimension; i++){
            if(p_matrix[u][i]>0){
                alt = distance[u] + p_matrix[u][i];
                if(alt < distance[i]){
                    distance[i] = alt;

                }
            }
        }
        cnt++;
    }

    int total=0;
    for(i=1; i<dimension; i++){
        if(distance[i] != INT_MAXIMUM)
            total+=distance[i];
    }
    return total;

}



/* ___ MAIN ___*/


int main() {

    int matrix_dimension;

    max_heap maxHeap;
    P_MAX_HEAP heap = &maxHeap;
    heap->size=0;

    //readFirstLine(&matrix_dimension, &heap->length);

    char input[200];
    int res=0, i=0;
    if(fgets(input, 200, stdin)){
        for(; !is_space(input[i]); i++){
            res=res*10+(input[i]-48);
        }
    }

    matrix_dimension=res;

    i++;
    res=0;
    for(;is_number(input[i]);i++){
        res=res*10+(input[i]-48);
    }
    heap->length=res;
    //

    P_GRAPH heap_array[heap->length];
    int matrix[matrix_dimension][matrix_dimension];

    //printf("DEBUG: nella prima linea ho letto: %d, %d\n\n", matrix_dimension, heap->length);

    int ID_counter=0;

    char line[MAX];

    while((fgets(line, 15, stdin))){

        if(line[0]==84){ //TopK

            print_heap(heap_array, heap);

        }
        else{ //AggiungiGrafo

            //Read the matrix from input
            int index;
            //char *result;
            for(int l=0; l < matrix_dimension; l++){
                if(fgets(line, MAX, stdin)){
                    index=0;
                    for(int c=0; c < matrix_dimension; c++){
                        res=0;
                        for(; is_number(line[index]); index++){
                            res=res*10+(line[index]-48);
                        }
                        matrix[l][c]= res;
                        index++;
                    }
                }

            }
            //DEBUG
            /*
            printf("DEBUG_MAIN: Ecco la matrice del grafico numero %d:\n", ID_counter);
            for(int j=0; j < matrix_dimension; j++){
                for(int k=0; k < matrix_dimension; k++){
                    if(k==0) printf("|   ");
                    printf("%ld ", matrix[j][k]);
                }
                printf("\n");
            }
            */

            int score = dijkstra_matrix_2(matrix_dimension, matrix);
            //printf("Lo score del grafico numero %d è di %d\n", ID_counter, score);

            if(heap->size < heap->length){
                P_GRAPH new_graph = malloc(sizeof (graph));
                new_graph->ID=ID_counter;
                new_graph->score=score;
                insert_max_heap(heap_array, heap, new_graph);
                //printf("DEBUG: Aggiungo alla classifica il grafico %d in quanto non piena\n", ID_counter);
            }
            else if(score < getMax(heap_array)->score){
                //DEBUG
                //int max_ID = getMax(heap_array)->ID;
                //long max_score = getMax(heap_array)->score;

                replace_max(heap_array, heap, score, ID_counter);
                /*
                P_GRAPH removed = removeMax(heap_array, heap);
                 */

                //DEBUG
                //printf("DEBUG: Aggiungo alla classifica il grafico %d sostituendo il max che era il numero %d con score %ld\n", ID_counter, max_ID, max_score);

                /*
                removed->ID=ID_counter;
                removed->score=score;
                insert_max_heap(heap_array, heap, removed);
                 */
            }

            ID_counter++;

            //DEBUG:
            /*
            printf("DEBUG: ecco la TopK...\n");
            print_heap_debug(heap_array, heap);
            printf("\n---------\n");
            */

        }

    }

    //free(heap);

    return 0;
}