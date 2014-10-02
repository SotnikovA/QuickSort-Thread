#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void qs(int* s_arr, int first, int last)
{
    int i = first, j = last, x = s_arr[(first + last) / 2],buf;

    do {
        while (s_arr[i] < x) i++;
        while (s_arr[j] > x) j--;

        if(i <= j) {
            if (s_arr[i] > s_arr[j])
            {
                buf=s_arr[i];
                s_arr[i]=s_arr[j];
                s_arr[j]=buf;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        qs(s_arr, i, last);
    if (first < j)
        qs(s_arr, first,j);
}
void printArray(int* s_arr,int size)
{
    for (int i = 0; i < size; i++)
        std::cout<<s_arr[i]<<' ';
        std::cout << endl;
}
void RandCreate(int* s_arr,int size)
{
    for (int i = 0; i < size; i++)
        s_arr[i] = rand()%10000;
}

int main()
{
    srand(time(0));
    int size;
    std::cout<<"Enter a size: ";
    std::cin>>size;
    int *array = new int[size];
    RandCreate(array,size);
    printArray(array,size);
    qs(array,0,size-1);
    printArray(array,size);
    return 0;
}


