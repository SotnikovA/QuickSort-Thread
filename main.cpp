#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <tgmath.h>
#include <pthread.h>

using namespace std;

struct Arguments
{
    int head;
    int tail;
    int *array;
};

int threadsMax = 0; //макс число потокoв
long threadsNow = 0;

bool IsSorted(int *a, int s);
void *qs(void *MainArg);
void RandCreate(int* s_arr,int size);
void printArray(int* s_arr,int size);

int main()
{

    srand(time(0));
    int size;
    std::cout<<"Enter a size: ";
    std::cin>>size;
    int *array = new int[size];
    RandCreate(array,size);
    threadsMax = 3;
    threadsNow = 1;

    std::cout<<"\nWorking with "<<threadsMax<<" thread(s):"<<std::endl;
    std::cout<<"Before sorting: ";
    if (!IsSorted(array, size))
        std::cout<<"not sorted."<<std::endl;
    else
        std::cout<<"sorted."<<std::endl;
    printArray(array,size);

    Arguments *MainArg;
    MainArg = (Arguments*)malloc(sizeof(Arguments));
    MainArg->head = 0;
    MainArg->tail = size-1;
    MainArg->array = array;
    //printArray(MainArg->array,size);
    (void*)qs((void*)MainArg);

    printArray(MainArg->array,size);
    return 0;
}



void *qs(void *MainArg)
{


    Arguments *p,*p1,*p2;
    p = (Arguments*)malloc(sizeof(Arguments));
    p = (Arguments*)MainArg;
    int buf;
    int i = p->head;
    int j = p->tail;

    int x = p->array[(i+j)/2];
    std::cout<<i<<std::endl;
    std::cout<<j<<std::endl;
    std::cout<<x<<std::endl;



    do {
        while (p->array[i] < x) i++;
        while (p->array[j] > x) j--;

        if(i <= j) {
            if (p->array[i] > p->array[j])
            {
                buf=p->array[i];
                p->array[i]=p->array[j];
                p->array[j]=buf;
            }
            i++;
            j--;
        }
       printArray(p->array,p->tail+1);
       std::cout<<"цикл наш тут"<<std::endl;
    } while (i <= j);

    p1 = (Arguments*)malloc(sizeof(Arguments));
    p1->head =i;
    p1->tail =p->tail;
    p1->array = p->array;

    p2 = (Arguments*)malloc(sizeof(Arguments));
    p2->head =p->head;
    p2->tail =j;
    p2->array = p->array;

    if (threadsNow < threadsMax)
    {
        pthread_t thread[threadsNow];
        threadsNow++;
        if (i < p->tail)
            pthread_create(&thread[threadsNow], NULL, &qs, (void *)p1 );
        if (p->head < j)
            pthread_create(&thread[threadsNow], NULL, &qs, (void *)p2 );
    }
    else
    {
        if (i < p->tail)
            (void*)qs((void*)p1);
        if (p->head < j)
            (void*)qs((void*)p2);
    }
}
//вывод массива
void printArray(int* s_arr,int size)
{
    for (int i = 0; i < size; i++)
        std::cout<<s_arr[i]<<' ';
        std::cout << endl;
}
//создание массива
void RandCreate(int* s_arr,int size)
{
    for (int i = 0; i < size; i++)
        s_arr[i] = rand()%10000;
}
//проверка
bool IsSorted(int *a, int s)
{
    for (int i = 0; i < s - 1; i++)
        if (a[i] < a[i + 1])
            return false;
    return true;
}
