// MoPhongSapXep.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <graphics.h>
#include <iostream>
#include <time.h>

void TextColor(int color);
void gotoXY(int i, int j);

using namespace std;
bool complete = false;
bool ASC = true;
int n = 10, choice;

int screenWidth = 1100;
int screenHeight = 600;
int startX = 100;
int startY = 200;
int MAX_VALUE = 100;
int circleRadius = 50;


void initCicre(int x, int y, int r, string s, int color){
    //if(r <= circleRadius)
    r = circleRadius*0.8;
    setcolor(color);
    circle(x, y, r);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(14); // Màu vàng
    int textHeight = 100; // Chiều cao của văn bản bên trong hình tròn

    int textWidth = s.length() * 15; // Độ rộng của văn bản
    int textX = x - textWidth / 2;
    int textY = y - textHeight / 8; // Điều chỉnh vị trí văn bản bên trong hình tròn
    outtextxy(textX, textY, const_cast<char*>(s.c_str())); // Vẽ văn bản lên màn hình
}
void clearCircle(int x, int y, int r, string s) {
    //if(r <= circleRadius)
    r = circleRadius*0.8;
    setcolor(BLACK);
    circle(x, y, r);
    setcolor(BLACK); // Màu vàng
    int textHeight = 100; // Chiều cao của văn bản bên trong hình tròn

    int textWidth = s.length() * 16; // Độ rộng của văn bản
    int textX = x - textWidth / 2;
    int textY = y - textHeight / 2; // Điều chỉnh vị trí văn bản bên trong hình tròn
    outtextxy(textX, textY, const_cast<char*>(s.c_str())); // Vẽ văn bản lên màn hình
}

void swap(int* arr, int i, int j, int color1, int color2, bool one = true) {
    int len = circleRadius * (j - i);
    std::string text1 = std::to_string(arr[i]);
    std::string text2 = std::to_string(arr[j]);
    // Vẽ hình tròn mới tại vị trí mới
        initCicre(startX + i * circleRadius * 2, startY, circleRadius * arr[i] / MAX_VALUE, text1, color1);
        if(one)
            initCicre(startX + j * circleRadius * 2, startY, circleRadius * arr[j] / MAX_VALUE, text2, color2);
    int N = 40;
    for (int k = 1; k <= N; k++) {
        // Xóa hình tròn tại vị trí cũ
        clearCircle(startX + i * circleRadius * 2 + len * (k - 1) / N, startY, circleRadius * arr[i] / MAX_VALUE, text1);
        if(one)
            clearCircle(startX + j * circleRadius * 2 - len * (k - 1) / N, startY, circleRadius * arr[j] / MAX_VALUE, text2);

        // Vẽ hình tròn mới tại vị trí mới
        initCicre(startX + i * circleRadius * 2 + len * k / N, startY, circleRadius * arr[i] / MAX_VALUE, text1, color1);
        if(one)
            initCicre(startX + j * circleRadius * 2 - len * k / N, startY, circleRadius * arr[j] / MAX_VALUE, text2, color2);
        // tốc độ delay: = 500/số lượng frame khi mà chưa di chuyển đc 1 nửa,  = 200/ khi đi qua nhau
        Sleep(k < N/2 ? 500/N : 200/N);
    }

    int t = arr[i];
    if(one)
        arr[i] = arr[j];
    arr[j] = t;
}

void visualize(int* arr, int x = -1, int y = -1, int z = -1) {
    cleardevice();
    int color;
    for (int i = 0; i < n; i++) {
        int circleX = startX + i * circleRadius * 2; // *2 để tạo khoảng cách giữa các hình tròn
        int circleY = startY;

        if (complete || i == x || i == z) {
            color = GREEN;// Màu xanh lá cây
        } else if (i == y) {
            color = MAGENTA; // Màu tím
        } else {
            color = LIGHTGRAY; // Màu xám
        }
        std::string text = std::to_string(arr[i]);
        initCicre(circleX, circleY, circleRadius*arr[i]/MAX_VALUE, text, color);
    }
}

void inplace
    (int* input, int n)
{
    for (int i = 1; i < n; i++)
    {
        int childIndex = i;
        int parentIndex = (childIndex - 1) / 2;

        while (childIndex > 0)
        {
            if (input[childIndex] > input[parentIndex] == ASC)
            {
                swap(input, parentIndex, childIndex, GREEN, MAGENTA);
            }
            else
            {
                break;
            }

            visualize(input, parentIndex, childIndex);
            Sleep(200);

            childIndex = parentIndex;
            parentIndex = (childIndex - 1) / 2;
        }
    }

    for (int heapLast = n - 1; heapLast >= 0; heapLast--)
    {
        int temp = input[0];
        input[0] = input[heapLast];
        input[heapLast] = temp;

        int parentIndex = 0;
        int leftChildIndex = 2 * parentIndex + 1;
        int rightChildIndex = 2 * parentIndex + 2;

        while (leftChildIndex < heapLast == ASC)
        {
            int maxIndex = parentIndex;

            if (input[leftChildIndex] > input[maxIndex] == ASC)
            {
                maxIndex = leftChildIndex;
            }
            if ((rightChildIndex < heapLast == ASC) && (input[rightChildIndex] > input[maxIndex] == ASC))
            {
                maxIndex = rightChildIndex;
            }
            if (maxIndex == parentIndex)
            {
                break;
            }
            visualize(input, maxIndex, parentIndex, heapLast);
            swap(input, parentIndex, maxIndex, GREEN, MAGENTA);
            //Sleep(200);

            parentIndex = maxIndex;
            leftChildIndex = 2 * parentIndex + 1;
            rightChildIndex = 2 * parentIndex + 2;
        }
    }
}

int partition_array(int *a, int si, int ei)
{
    int count_small = 0;

    for (int i = (si + 1); i <= ei; i++)
    {
        if (a[i] <= a[si] == ASC)
        {
            count_small++;
        }
    }
    int c = si + count_small;
    visualize(a, c, si);
    swap(a, c, si, GREEN, MAGENTA);
    int i = si, j = ei;

    while (i<c && j>c)
    {
        if (a[i] <= a[c] == ASC)
        {
            i++;
        }
        else if (a[j] > a[c] == ASC)
        {
            j--;
        }
        else
        {
            visualize(a, i, j);
            swap(a, i, j, GREEN, MAGENTA);
            //Sleep(200);

            i++;
            j--;
        }
    }
    return c;
}

void quickSort(int *a, int si, int ei)
{
    if (si >= ei)
    {
        return;
    }

    int c = partition_array(a, si, ei);
    quickSort(a, si, c - 1);
    quickSort(a, c + 1, ei);

}

void merge2SortedArrays(int *a, int si, int ei)
{
    int size_output = (ei - si) + 1;
    int* output = new int[size_output];

    int mid = (si + ei) / 2;
    int i = si, j = mid + 1, k = 0;
    while (i <= mid && j <= ei)
    {
        if (a[i] <= a[j] == ASC)
        {
            output[k] = a[i];
            visualize(a, i, j);
            i++;
            k++;
        }
        else
        {
            output[k] = a[j];
            visualize(a, i, j);
            j++;
            k++;
        }

    }
    while (i <= mid)
    {
        output[k] = a[i];
        visualize(a, -1, i);
        i++;
        k++;
    }
    while (j <= ei)
    {
        output[k] = a[j];
        visualize(a, -1, j);
        j++;
        k++;
    }
    int x = 0;
    for (int l = si; l <= ei; l++)
    {
        a[l] = output[x];
        visualize(a, l);
        Sleep(200);
        x++;
    }
    delete[]output;
}

void mergeSort(int *a, int si, int ei)
{
    if (si >= ei)
    {
        return;
    }
    int mid = (si + ei) / 2;

    mergeSort(a, si, mid);
    mergeSort(a, mid + 1, ei);

    merge2SortedArrays(a, si, ei);
}

void bubbleSort(int* arr)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j + 1] < arr[j] == ASC)
            {
                //int temp = arr[j];
                //arr[j] = arr[j + 1];
                //arr[j + 1] = temp;
                visualize(arr, j + 1, j, n - i);
                swap(arr, j, j + 1, GREEN, MAGENTA);
            }
            //Sleep(200);
        }
    }
}

void insertionSort(int* arr) {
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        int temp = arr[i];

        while (j >= 0 && arr[j] > temp == ASC) {
            arr[j + 1] = arr[j];
            visualize(arr, n, i, j + 1);
            // Thực hiện swap và ngủ 50ms sau mỗi bước di chuyển
            swap(arr, j, j + 1, MAGENTA, GREEN, false);
            Sleep(50);
            j--;
        }

        arr[j + 1] = temp;

        // Hiển thị trạng thái của mảng sau mỗi bước hoàn tất
        visualize(arr);
    }
}


void selectionSort(int* arr)
{
    int minIndex;
    for (int i = 0; i < n - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex] == ASC)
            {
                minIndex = j;
                visualize(arr, n, i, minIndex);
            }
            Sleep(200);
        }
        swap(arr, i, minIndex, GREEN, MAGENTA);
    }
}
int* generateRandomArray(int size, int minVal, int maxVal) {
    srand(time(0));
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (maxVal - minVal + 1) + minVal;
    }
    return arr;
}

// Hàm nhập mảng từ bàn phím
int* inputArray(int size) {
    int* arr = new int[size];
    std::cout << "Nhap mang " << size << " so nguyen: ";
    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }
    return arr;
}

// Hàm hiển thị mảng
void displayArray(int* arr) {
    visualize(arr);
}
void ShowMenu(int type = 0) {
    system("cls");
    std::cout << "===== MENU =====" << std::endl;
    if (type == 0) {
        std::cout << "1. Tao mang ngau nhien" << std::endl;
        std::cout << "2. Nhap mang" << std::endl;
    }
    else if(type == 1){
        std::cout << "1. Sap xep su dung Bubble Sort" << std::endl;
        std::cout << "2. Sap xep su dung Insertion Sort" << std::endl;
        std::cout << "3. Sap xep su dung Selection Sort" << std::endl;
        std::cout << "4. Sap xep su dung Quick Sort" << std::endl;
        std::cout << "5. Sap xep su dung Merge Sort" << std::endl;
        std::cout << "6. Hien thi mang" << std::endl;
    }
    else {
        std::cout << "1. Tang dan" << std::endl;
        std::cout << "2. Giam dan" << std::endl;
    }
    std::cout << "0. Thoat" << std::endl;
    std::cout << "================" << std::endl;
    std::cout << "Nhap chuc nang: ";
}
void Show(int* arr) {
    do {
        ShowMenu(1);
        cin >> choice;
        switch (choice) {
        case 0: {
            return;
        }
        case 1: {
            if (arr != nullptr) {
                int choice2;
                do {
                    ShowMenu(2);
                    cin >> choice2;
                    if (choice2 == 1) {
                        ASC = true;
                    }
                    else if (choice2 == 2) {
                        ASC = false;
                    }
                } while (choice2 < 0 || choice2 > 2);
                complete = false;
                bubbleSort(arr);
                complete = true;
                visualize(arr);
                std::cout << "Mang da duoc sap xep su dung Bubble Sort." << std::endl;
            }
            else {
                std::cout << "Mang chua duoc khoi tao." << std::endl;
            }
            break;
        }
        case 2: {
            if (arr != nullptr) {
                int choice2;
                do {
                    ShowMenu(2);
                    cin >> choice2;
                    if (choice2 == 1) {
                        ASC = true;
                    }
                    else if (choice2 == 2) {
                        ASC = false;
                    }
                } while (choice2 < 0 || choice2 > 2);
                complete = false;
                insertionSort(arr);
                complete = true;
                visualize(arr);
                std::cout << "Mang da duoc sap xep su dung Insertion Sort." << std::endl;
            }
            else {
                std::cout << "Mang chua duoc khoi tao." << std::endl;
            }
            break;
        }
        case 3: {
            if (arr != nullptr) {
                int choice2;
                do {
                    ShowMenu(2);
                    cin >> choice2;
                    if (choice2 == 1) {
                        ASC = true;
                    }
                    else if (choice2 == 2) {
                        ASC = false;
                    }
                } while (choice2 < 0 || choice2 > 2);
                complete = false;
                selectionSort(arr);
                complete = true;
                visualize(arr);
                std::cout << "Mang da duoc sap xep su dung Selection Sort." << std::endl;
            }
            else {
                std::cout << "Mang chua duoc khoi tao." << std::endl;
            }
            break;
        }
        case 4: {
            if (arr != nullptr) {
                int choice2;
                do {
                    ShowMenu(2);
                    cin >> choice2;
                    if (choice2 == 1) {
                        ASC = true;
                    }
                    else if (choice2 == 2) {
                        ASC = false;
                    }
                } while (choice2 < 0 || choice2 > 2);
                complete = false;
                quickSort(arr, 0, n - 1);
                complete = true;
                visualize(arr);
                std::cout << "Mang da duoc sap xep su dung Quick Sort." << std::endl;
            }
            else {
                std::cout << "Mang chua duoc khoi tao." << std::endl;
            }
            break;
        }
        case 5: {
            if (arr != nullptr) {
                int choice2;
                do {
                    ShowMenu(2);
                    cin >> choice2;
                    if (choice2 == 1) {
                        ASC = true;
                    }
                    else if (choice2 == 2) {
                        ASC = false;
                    }
                } while (choice2 < 0 || choice2 > 2);
                complete = false;
                mergeSort(arr, 0, n - 1);
                complete = true;
                visualize(arr);
                std::cout << "Mang da duoc sap xep su dung Merge Sort." << std::endl;
            }
            else {
                std::cout << "Mang chua duoc khoi tao." << std::endl;
            }
            break;
        }
        case 6: {
            if (arr != nullptr) {
                std::cout << "Array: ";
                displayArray(arr);
                system("pause");
            }
            else {
                std::cout << "Mang chua duoc khoi tao." << std::endl;
            }
            break;
        }
        default: {
            std::cout << "Gia tri khong hop le. Vui long kiem tra lai!" << std::endl;
            break;
        }
        }
        if (choice > 0 && choice < 6) {
            delete[] arr;
            arr = nullptr;
            //getch();
            return;
        }

    } while (choice != 0);
}
int main() {
    initwindow(screenWidth, screenHeight, "Do hoa", 50, 30);
    int* arr = nullptr;
    do {
        ShowMenu(0);
        std::cin >> choice;
        switch (choice) {
        case 0: {
            std::cout << "_______EXIT________";
            return 0;
        }
        case 1: {
            arr = generateRandomArray(n, 0, MAX_VALUE);
            std::cout << "Tao mang thanh cong." << std::endl;
            system("pause");
            Show(arr);
            break;
        }
        case 2: {
            arr = inputArray(n);
            Show(arr);
            break;
        }
        default: {
            std::cout << "Gia tri khong hop le. Vui long kiem tra lai!" << std::endl;
            break;
        }
        }
    } while (true);

    delete[] arr;
    closegraph(); // Đóng cửa sổ đồ họa
    return 0;
}

