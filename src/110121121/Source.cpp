#include<SDL.h>
#include<iostream>
#include<limits>
#include<time.h>
#include<string>
using namespace std;

const int SCREEN_WIDTH=910;
const int SCREEN_HEIGHT=750;

const int arrSize=130;
const int rectSize=7;

int arr[arrSize];
int Barr[arrSize];

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;

bool complete=false;
// Khoi tao SDL
bool init()
{
    bool success=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout<<"Khong the khoi tao SDL. SDL_Error: "<<SDL_GetError();
        success=false;
    }
    else
    {
        if(!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")))
        {
            cout<<"Canh Bao: Bo loc tuyen tinh kh duoc bat.\n";
        }

        window=SDL_CreateWindow("Thuat toan sap xep", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            cout<<"Khong the thoi tao Window. SDL_Error: "<<SDL_GetError();
            success=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                cout<<"Khong the tao renderer. SDL_Error: "<<SDL_GetError();
                success=false;
            }
        }
    }

    return success;
}
//Mo dau
void intro()
{
    cout << "==============================Thuat toan sap xep==============================\n\n"
        << "Truc quan hoa cac thuat toan sap xep khac nhau trong C++ voi Thu vien SDL2. Thuat toan sap xep la thuat toan sap xep cac phan tu cua danh sach theo mot thu tu nhat dinh.\n"
        << "Trong qua trinh trien khai trinh hien thi sap xep nay, chung ta se xem xet mot so thuat toan sap xep nay va hieu ro hoat dong cua chung mot cach truc quan.\n"
        << "Cac trinh sap xep bao gom Selection Sort, Insertion Sort, Bubble Sort, Merge Sort, Quick Sort va Heap Sort.\n"
        << "Kich thuoc danh sach duoc co dinh o muc 130 phan tu. Co the chon ngau nhien danh sach va chon bat ky loai thuat toan sap xep nao de goi vao danh sach tu cac tuy chon da cho.\n\n"
        << "Bam ENTER de chon dieu khien...";

    string s;
    getline(cin, s);
    if (s == "\n")
    {
        return;
    }
}

bool controls()
{
    
   cout <<"Cac dieu khien co san ben trong Trinh hien thi sap xep:-\n"
        << " Su dung 0 de tao danh sach ngau nhien khac.\n"
        << " Su dung 1 de bat dau SELECTION SORT.\n"
        << " Su dung 2 de bat dau INSERTION SORT.\n"
        << " Su dung 3 de bat dau BUBBLE SORT.\n"
        << " Su dung 4 de bat dau MERGE SORT.\n"
        << " Su dung 5 de bat dau QUICK SORT.\n"
        << " Su dung 6 de bat dau HEAP SORT.\n"
        << " Su dung q de thoat khoi Trinh hien thi sap xep\n\n"
        << "NHAN ENTER DE BAT DAU SAP ...\n\n"
        << "Hoac go -1 va nhan ENTER de thoat khoi chuong trinh.";
    string s;
    getline(cin, s);
    if(s=="-1")
    {
        return false;
    }
    //else if(s=="\n")
    //{
    //    return true;
    //}
    return true;
}

void execute()
{
    if(!init())
    {
        cout<<"SDL Khoi tao khong thanh cong";
    }
    else
    {
        randomizeAndSaveArray();
        loadArr();

        SDL_Event e;
        bool quit=false;
        while(!quit)
        {
            while(SDL_PollEvent(&e)!=0)
            {
                if(e.type==SDL_QUIT)
                {
                    quit=true;
                    complete=false;
                }
                else if(e.type==SDL_KEYDOWN)
                {
                    switch(e.key.keysym.sym)
                    {
                        case(SDLK_q):
                            quit=true;
                            complete=false;
                            cout<<"\nThoat cong cu sap xep.\n";
                            break;
                        case(SDLK_0):
                            randomizeAndSaveArray();
                            complete=false;
                            loadArr();
                            cout<<"\nTao danh sach ngau nhien moi.\n";
                            break;
                        case(SDLK_1):
                            loadArr();
                            cout<<"\nBat dau SELECTION SORT.\n";
                            complete=false;
                            selectionSort();
                            complete=true;
                            cout<<"\nSELECTION SORT Hoan thanh.\n";
                            break;
                        case(SDLK_2):
                            loadArr();
                            cout<<"\nBat dau INSERTION SORT.\n";
                            complete=false;
                            insertionSort();
                            complete=true;
                            cout<<"\nINSERTION SORT Hoan thanh.\n";
                            break;
                        case(SDLK_3):
                            loadArr();
                            cout<<"\nBat dau BUBBLE SORT.\n";
                            complete=false;
                            bubbleSort();
                            complete=true;
                            cout<<"\nBUBBLE SORT Hoan thanh.\n";
                            break;
                        case(SDLK_4):
                            loadArr();
                            cout<<"\nBat dau MERGE SORT.\n";
                            complete=false;
                            mergeSort(arr, 0, arrSize-1);
                            complete=true;
                            cout<<"\nMERGE SORT Hoan thanh.\n";
                            break;
                        case(SDLK_5):
                            loadArr();
                            cout<<"\nBat dau QUICK SORT.\n";
                            complete=false;
                            quickSort(arr, 0, arrSize-1);
                            complete=true;
                            cout<<"\nQUICK SORT Hoan thanh.\n";
                            break;
                        case(SDLK_6):
                            loadArr();
                            cout<<"\nBat dau HEAP SORT.\n";
                            complete=false;
                            inplaceHeapSort(arr, arrSize);
                            complete=true;
                            cout<<"\nHEAP SORT Hoan thanh.\n";
                            break;
                    }
                }
            }
            visualize();
        }
        close();
    }
}

void close()
{
    SDL_DestroyRenderer(renderer);
    renderer=NULL;

    SDL_DestroyWindow(window);
    window=NULL;

    SDL_Quit();
}

// Khoi tao do thi
void visualize(int x=-1, int y=-1, int z=-1)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    int j=0;
    for(int i=0; i<=SCREEN_WIDTH-rectSize; i+=rectSize)
    {
        SDL_PumpEvents();

        SDL_Rect rect={i, 0, rectSize, arr[j]};
        if(complete)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else if (j == x || j == z)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else if (j == y)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        j++;
    }
    SDL_RenderPresent(renderer);
}

// Heap sort
void inplaceHeapSort(int* input, int n)
{
    for(int i=1; i<n; i++)
    {
       int childIndex=i;
       int parentIndex=(childIndex-1)/2;

       while(childIndex>0)
       {
           if(input[childIndex]>input[parentIndex])
           {
               int temp=input[parentIndex];
               input[parentIndex]=input[childIndex];
               input[childIndex]=temp;

           }
           else
           {
               break;
           }

           visualize(parentIndex, childIndex);
           SDL_Delay(40);

           childIndex=parentIndex;
           parentIndex=(childIndex-1)/2;
       }
    }

    for(int heapLast=n-1; heapLast>=0 ; heapLast--)
    {
        int temp=input[0];
        input[0]=input[heapLast];
        input[heapLast]=temp;

        int parentIndex=0;
        int leftChildIndex=2*parentIndex + 1;
        int rightChildIndex=2*parentIndex + 2;

        while(leftChildIndex<heapLast)
        {
            int maxIndex=parentIndex;

            if(input[leftChildIndex]>input[maxIndex])
            {
                maxIndex=leftChildIndex;
            }
            if(rightChildIndex<heapLast && input[rightChildIndex]>input[maxIndex])
            {
                maxIndex=rightChildIndex;
            }
            if(maxIndex==parentIndex)
            {
                break;
            }

            int temp=input[parentIndex];
            input[parentIndex]=input[maxIndex];
            input[maxIndex]=temp;

            visualize(maxIndex, parentIndex, heapLast);
            SDL_Delay(40);

            parentIndex=maxIndex;
            leftChildIndex=2*parentIndex + 1;
            rightChildIndex=2*parentIndex + 2;
        }
    }
}

// Qick Sort
void quickSort(int a[], int si, int ei)
{
    if(si>=ei)
    {
        return;
    }

    int c=partition_array(a, si, ei);
    quickSort(a, si, c-1);
    quickSort(a, c+1, ei);

}

// Phan tach 2 mang
int partition_array(int a[], int si, int ei)
{
    int count_small=0;

    for(int i=(si+1);i<=ei;i++)
    {
        if(a[i]<=a[si])
        {
            count_small++;
        }
    }
    int c=si+count_small;
    int temp=a[c];
    a[c]=a[si];
    a[si]=temp;
    visualize(c, si);

    int i=si, j=ei;

    while(i<c && j>c)
    {
        if(a[i]<= a[c])
        {
            i++;
        }
        else if(a[j]>a[c])
        {
            j--;
        }
        else
        {
            int temp_1=a[j];
            a[j]=a[i];
            a[i]=temp_1;

            visualize(i, j);
            SDL_Delay(70);

            i++;
            j--;
        }
    }
    return c;
}

// Hop nhat 2 mang
void merge2SortedArrays(int a[], int si, int ei)
{
    int size_output=(ei-si)+1;
    int* output=new int[size_output];

    int mid=(si+ei)/2;
    int i=si, j=mid+1, k=0;
    while(i<=mid && j<=ei)
    {
        if(a[i]<=a[j])
        {
            output[k]=a[i];
            visualize(i, j);
            i++;
            k++;
        }
        else
        {
            output[k]=a[j];
            visualize(i, j);
            j++;
            k++;
        }

    }
    while(i<=mid)
    {
        output[k]=a[i];
        visualize(-1, i);
        i++;
        k++;
    }
    while(j<=ei)
    {
        output[k]=a[j];
        visualize(-1, j);
        j++;
        k++;
    }
    int x=0;
    for(int l=si; l<=ei; l++)
    {
        a[l]=output[x];
        visualize(l);
        SDL_Delay(15);
        x++;
    }
    delete []output;
}

// Merge Sort
void mergeSort(int a[], int si, int ei)
{
    if(si>=ei)
    {
        return;
    }
    int mid=(si+ei)/2;

    mergeSort(a, si, mid);
    mergeSort(a, mid+1, ei);

    merge2SortedArrays(a, si, ei);
}

// Bubble Sort
void bubbleSort()
{
    for(int i=0; i<arrSize-1; i++)
    {
        for(int j=0; j<arrSize-1-i; j++)
        {
            if(arr[j+1]<arr[j])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;

                visualize(j+1, j, arrSize-i);
            }
            SDL_Delay(1);
        }
    }
}

// Insertion Sort
void insertionSort()
{
    for(int i=1; i<arrSize; i++)
    {
        int j=i-1;
        int temp=arr[i];
        while(j>=0 && arr[j]>temp)
        {
            arr[j+1]=arr[j];
            j--;

            visualize(i, j+1);
            SDL_Delay(5);
        }
        arr[j+1]=temp;
    }
}

// Selection Sort
void selectionSort()
{
    int minIndex;
    for(int i=0;i<arrSize-1;i++)
    {
        minIndex=i;
        for(int j=i+1;j<arrSize;j++)
        {
            if(arr[j]<arr[minIndex])
            {
                minIndex=j;
                visualize(i, minIndex);
            }
            SDL_Delay(1);
        }
        int temp=arr[i];
        arr[i]=arr[minIndex];
        arr[minIndex]=temp;
    }
}

void loadArr()
{
    memcpy(arr, Barr, sizeof(int)*arrSize);
}

void randomizeAndSaveArray()
{
    unsigned int seed=(unsigned)time(NULL);
    srand(seed);
    for(int i=0; i<arrSize; i++)
    {
        int random=rand()%(SCREEN_HEIGHT);
        Barr[i]=random;
    }
}





int main(int argc, char* args[])
{
    intro();

    while(1)
    {
        cout<<'\n';
        if(controls())
            execute();
        else
        {
            cout<<"\nThoat khoi chuong trinh.\n";
            break;
        }
    }

    return 0;
}
