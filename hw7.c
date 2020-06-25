#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>    // atoi 함수가 선언된 헤더 파일
#include <time.h>

#define MAX_STR_SIZE 5000
#define INF 10000
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



int minDistance(int dist[], int sptSet[],int city_num)
{
    int vertex = city_num;

    int min = INT_MAX, min_index;

    for (int v = 0; v < vertex; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[], int city_num)
{
    int v = city_num;
    for (int i = 0; i < v; i++)
        printf("%-10d", dist[i]);
    printf("\n");
}




void dijkstra(int graph[30][30], int src, int city_num)
{
    int vertex = city_num;
    int dist[vertex];
    // distance from src to i
    //printf("%d\n",city_num );

    int sptSet[vertex];



    for (int i = 0; i < vertex; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;
    dist[src] = 0;


    for (int count = 0; count < vertex - 1; count++) {
        int u = minDistance(dist, sptSet,vertex);

        sptSet[u] = 1;


        for (int v = 0; v < vertex; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    printSolution(dist,vertex);
}
void split_string(char * s1){
char *ptr = strtok(s1, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
    printf("%s\n", ptr);          // 자른 문자열 출력
}

void floydWarshall(int graph[30][30], int city_num, char city[30][MAX_STR_SIZE])
{
    int V = city_num;

    int dist[V][V], i, j, k;

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
    for (k = 0; k < V; k++)
    {

        for (i = 0; i < V; i++)
        {

            for (j = 0; j < V; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    printf("\n\n" );
    for(int k = 0; k < V; k++){
      printf("%-10s", city[k]);
      for(int i = 0; i < V; i++)
        printf("%-10d ",dist[k][i]);
      printf("\n");
    }
}


// driver program to test above function
int main()
{
    clock_t start,end;
    float res;

    int count = 0;
    int i,j,v = 0;
    char str[MAX_STR_SIZE];
    char arr[30][MAX_STR_SIZE];
    char arr_cp[30][MAX_STR_SIZE]; // 복사본

    int graph[30][30];
    int graph_floyd[30][30];
    char city[30][MAX_STR_SIZE]; //도시이름 저장
    //char city[30][MAX_STR_SIZE]; //도시이름 저장
    int city_num = 0; // 도시 갯수

    FILE * fp = fopen("hw7_data.txt","r");  // 성공시 file을 가르키는 포인터 반환, 실패시 NULL 반환
    if(fp == NULL){
      printf("%s\n", "fopen error");
    }

    while(fgets(str,MAX_STR_SIZE,fp)){
      strcpy(arr[count],str); // string을 array에 넣어줄때에는 '=' 가 아니라 strcpy를 써야한다
      strcpy(arr_cp[count],str); // 복사본
      count++;
    }

    // 도시 이름 array
    char *ptr = strtok(arr[0], "\t");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
    while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
    {
        strcpy(city[city_num],ptr);
        //printf("%s\n", city[city_num]);
        ptr = strtok(NULL, "\t");      // 다음 문자열을 잘라서 포인터를 반환
        city_num++;
    }
    city_num--;
    ptr = strtok(city[city_num], " ");
    while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
    {
        strcpy(city[city_num],ptr);
        //printf("%s\n", city[city_num - 1]);
        ptr = strtok(NULL, " ");      // 다음 문자열을 잘라서 포인터를 반환
        city_num++;
    }
    strcpy(city[city_num-1],strtok(city[city_num-1], "\n"));

    // dijkstra 알고리즘풀기 위한 각각의 node값 받기
    for(int k = 1; k <= city_num; k++){
      ptr = strtok(arr[k], "\t");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
      ptr = strtok(NULL, "\t"); // 앞의 도시이름 지우기
      int node = 0;
      while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
      {
          if(!strcmp(ptr,"INF")){
            graph[k-1][node] = 0;
          }
          else{
            graph[k-1][node] = atoi(ptr);
          }
          ptr = strtok(NULL, "\t");
          node++;
      }
  }

  // Print dijkstra Alorithm
   start = clock();
   printf("\t");
   for(int i = 0; i < city_num; i++){
     printf("%-10s", city[i]);
   }
   printf("\n");
   for(int i = 0; i < city_num; i++){
     printf("%-10s", city[i]);
     dijkstra(graph, i, city_num);
   }
   printf("\n");
   end = clock();
   res = (float)(end - start)/CLOCKS_PER_SEC;
   printf("It took %.3f seconds to compute shortest path between cities with Dijkstra's algorithm\n\n\n",res );



   //floydWarshall 알고리즘 풀기

   for(int k = 1; k <= city_num; k++){
     ptr = strtok(arr_cp[k], "\t");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
     ptr = strtok(NULL, "\t"); // 앞의 도시이름 지우기
     int node = 0;
     while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
     {
         if(!strcmp(ptr,"INF")){
           graph_floyd[k-1][node] = INF;
         }
         else{
           graph_floyd[k-1][node] = atoi(ptr);
         }
         ptr = strtok(NULL, "\t");
         node++;
     }
 }

  for(int k = 0; k < city_num; k++){
    for(int i = 0; i < city_num; i++){
      if(i != k && graph_floyd[k][i] == 0){
        graph_floyd[k][i] = INF;
      }
    }
  }

  //printf("%d\n", INT_MAX + INT_MAX );

   //print  Floyd Alorithm
   start = clock();
   printf("\t");
   for(int i = 0; i < city_num; i++){
     printf("%-10s", city[i]);
   }
   floydWarshall(graph_floyd,city_num,city);

   printf("\n");
   end = clock();
   res = (float)(end - start)/CLOCKS_PER_SEC;
   printf("It took %.3f seconds to compute shortest path between cities with floydWarshall's algorithm\n",res );

    return 0;
}
