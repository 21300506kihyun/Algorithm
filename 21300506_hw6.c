#define _GNU_SOUCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_SIZE 1000

void removeSpaces(char *str)
{
    int count = 0;
    // Traverse the given string. If current character
    // is not space or tab, then place it at index 'count++'
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ' && str[i] != '\t')  // 왜 || 이 들어가면 안되는 걸까 ?
            str[count++] = str[i];
    str[count] = '\0'; // 문자열의 마지막에 \0 넣기(NULL)
}


struct node {
  int vertex;
  struct node* next; // linked list
};
struct node* createNode(int);

struct Graph {
  int numVertices;
  struct node** adjLists;
};

// Create a node
struct node* createNode(int v) {
  struct node* newNode = (struct node*)malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

struct Graph* createAGraph(int vertices) {
  struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

  graph->numVertices = vertices;

  graph->adjLists = (struct node**)malloc(vertices * sizeof(struct node*));

  int i;
  for (i = 0; i < vertices; i++)
    graph->adjLists[i] = createNode(i);

  return graph;
}


void addEdge(struct Graph* graph, int s, int d) {
  // Add edge from s to d
  struct node* newNode = createNode(d);
  struct node* temp;

  newNode->next = NULL;
  temp = graph->adjLists[s];

  // Traverse to the last node
  while(temp->next != NULL)
      temp = temp->next;

  temp->next = newNode; // Link address part
}

int main (){
  int count = 0;
  int i,j,v = 0;
  char str[MAX_STR_SIZE];
  char arr[20][20];

  FILE * fp = fopen("hw6_data.txt","r");  // 성공시 file을 가르키는 포인터 반환, 실패시 NULL 반환
  if(fp == NULL){
    printf("%s\n", "fopen error");
  }
  while(fgets(str,MAX_STR_SIZE,fp)){
    //printf("num : %d, line :%s\n", count,str);
    removeSpaces(str); // space와 tab 제거
    strcpy(arr[count],str); // string을 array에 넣어줄때에는 '=' 가 아니라 strcpy를 써야한다
    count++;
    //printf("num : %d, line2 :%s\n", count,str);
  }

  // create graph
  struct Graph* graph = createAGraph(strlen(arr[0])-1);

  // 1일 경우 Edge 생성
  // Edge 생성과정
  for(i = 0; i < strlen(arr[0])-1; i++){  // vertex의 갯수만큼 loop
    for(j = 0; j < strlen(arr[0])-1; j++){  // vertex의 갯수만큼 loop -> 행렬이므로
      if(arr[i+1][j+1] == '1'){ // 문자열은 "" 로 표시하고 , char 은 ''로 표시해야 한다.
        addEdge(graph, i, j);
      }
    }
  }

  // print Graph
  printf("Original Graph\n");
  for (v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjLists[v]->next;
    printf("\n Vertex %c\n: ", arr[0][v]);
    while (temp) {
      printf("-> %c", arr[0][temp->vertex]);
      temp = temp->next;
    }
  }

  // create transposed graph
  struct Graph* trans_graph = createAGraph(strlen(arr[0])-1);

  for(i = 0; i < strlen(arr[0])-1; i++ ){
    struct node* temp = graph->adjLists[i];  //기존의 graph
    if(temp->next == NULL){
      continue;
    }
    while(temp->next != NULL){ // adjLists기준으로 각 adjLists[i]에 있는 node들의 방향을 반대로 해서 새로운 graph만들기
      int verx = temp->next->vertex; // 각 node의 vertex값
      addEdge(trans_graph,verx,i);
      temp = temp->next;
    }
  }


  printf("\n\n%s\n", "Transposed Graph : " );
  // print trans_Graph
  for (v = 0; v < trans_graph->numVertices; v++) {
    struct node* temp = trans_graph->adjLists[v]->next;
    printf("\n Vertex %c\n: ", arr[0][v]);
    while (temp) {
      printf("-> %c", arr[0][temp->vertex]);
      temp = temp->next;
    }
  }

  fclose(fp); // file close





}
