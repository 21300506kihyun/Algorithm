#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void max_heapify (int Arr[ ], char *Arr2[ ], int i, int n)
{
    int largest;
    int left = 2*i  ;                   //left child
    int right = 2*i +1 ;           //right child
    if(left<= n && Arr[left] > Arr[i] ){
          largest = left;
    }else
         largest = i;
    if(right <= n && Arr[right] > Arr[largest] )
        largest = right;
    if(largest != i )
    {
        int temp = Arr[i]; //  key 위치 swap
        Arr[i] = Arr[largest]; //
        Arr[largest] = temp;


        char * temp2 = Arr2[i]; // value 위치 swap
        Arr2[i] = Arr2[largest]; //
        Arr2[largest] = temp2;
        max_heapify (Arr, Arr2 ,largest,n);
    }
 }

void build_maxheap (int Arr[], char *Arr2[] , int n)  // max-prioty-queue 구현
{
    //printf("%d\n", n );
    for(int i = n/2 ; i >= 1 ; i-- )
    {
        max_heapify (Arr, Arr2, i, n) ;
    }
}


#define Max 100
int main(){

    int idx;
    int new;
       int array[Max];
       int Num = 1;
       int arraySize = 10; // 문자열 배열의 크기
        char * names[arraySize];
        char buffer[30]; // 입력을 위한 버퍼. 입력받는 이름의 최대 길이는 99바이트 이내
        int n = 0;
        int l = 0;


      char menu;
      char menu2;
      char element[100];
      int key;

      do{

      printf("%s\n", "**************menu***************" );
      printf("%s\n", "I : insert new element into queue" );
      printf("%s\n", "D : delete element with largest key from queue" );
      printf("%s\n", "R : Retrieve element with largest key from queue " );
      printf("%s\n", "K : increse key of element in queue" );
      printf("%s\n", "P : print out all elements in queue" );
      printf("%s\n", "Q : Quit" );

      printf("%s\n", "Choose menu :" );

      scanf(" %c", &menu);
      getchar();
      //printf("%c\n", menu );

      switch (menu) {
        case 'i' :
        case 'I' :
            printf("%s\n", "Enter name element :" );
            scanf("%s", buffer);
            // 버퍼에 문자열을 입력받은 후, 그 길이 만큼 새 문자열을 위한 메모리를 할당한다.
            // 새로 할당된 메모리에 버퍼의 내용을 복사하고, 그 시작 위치를 배열에 추가한다.
            l = strlen(buffer);
            if (l > 0){
                char* newstrptr = (char*)malloc(sizeof(char) * (l + 1));
                strcpy(newstrptr, buffer);
                names[Num] =  newstrptr;
            } else {
                break;
            }
            printf("%s\n", "Enter Key value of element :" );
            scanf("%d", &key );

            // printf("%s\n", names[Num]);
            // printf("%d\n", key);

            array[Num] = key;
            // int N = sizeof(array) / sizeof(int);
            // int *a1 = array - 1;  // index를 1부터 시작하기 위해서
            build_maxheap(array, names , Num);
            Num++;
            break;


        case 'd' :
        case 'D' :
            printf("[");
            printf("%s ,", names[1]);
            printf("%d ", array[1]);
            printf("] is deleted\n");
            array[1] = array[Num-1];
            names[1] = names[Num-1];
            Num = Num -1;
            build_maxheap(array, names , Num);
            break;

        case 'p' :
        case 'P' :
            for(int i = 1; i < Num ; i++){
              printf("[");
              printf("%s ,", names[i]);
              printf("%d ", array[i]);
              printf("]");
          }
          printf("\n");
          break;
        case 'r' :
        case 'R' :
              printf("[");
              printf("%s ,", names[1]);
              printf("%d ", array[1]);
              printf("]\n");
              break;
        case 'K' :
        case 'k' :


            printf("Enter index of element :");
            scanf("%d", &idx);
            getchar(); // scanf buffer값을 없애기 위해서
            printf("Enter new key value ");
            scanf("%d", &new);
            getchar();

            array[idx] = new;
            build_maxheap(array, names , Num -1 );
            break;

      }

    } while(menu != 'q' && menu != 'Q' );


}
