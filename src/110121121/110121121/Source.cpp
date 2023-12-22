#include <SDL.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Kích thước cửa sổ SDL
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Số lượng phần tử trong mảng
const int ARRAY_SIZE = 10;

// Mảng chứa các số cần sắp xếp
std::vector<int> numbers;

// Đối tượng SDL
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool sorted = false;

// Khởi tạo SDL
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Sorting Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// Tạo mảng số từ bàn phím
void inputArray() {
    std::cout << "Enter " << ARRAY_SIZE << " numbers:\n";
    numbers.clear();

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        std::cout << "Enter number " << i + 1 << "\n";
        int num;
        std::cin >> num;
        numbers.push_back(num);
    }
}

// Tạo mảng số ngẫu nhiên
void generateRandomArray() {
    numbers.clear();
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        numbers.push_back(rand() % SCREEN_HEIGHT);
    }
}

// Vẽ mảng
void renderArray() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (sorted) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    }

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        SDL_Rect rect = { i * (SCREEN_WIDTH / ARRAY_SIZE), SCREEN_HEIGHT - numbers[i], SCREEN_WIDTH / ARRAY_SIZE, numbers[i] };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

// Nổi bọt sắp xếp
void bubbleSort() {
    for (int i = 0; i < ARRAY_SIZE - 1; ++i) {
        for (int j = 0; j < ARRAY_SIZE - i - 1; ++j) {
            if (numbers[j] > numbers[j + 1]) {
                std::swap(numbers[j], numbers[j + 1]);
                renderArray();
                SDL_Delay(500);
            }
        }
    }
}

// Sắp xếp chèn (Insertion Sort)
void insertionSort() {
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        int key = numbers[i];
        int j = i - 1;

        while (j >= 0 && numbers[j] > key) {
            numbers[j + 1] = numbers[j];
            --j;
        }

        numbers[j + 1] = key;
        renderArray();
        SDL_Delay(500);
    }
}

// Sắp xếp chọn (Selection Sort)
void selectionSort() {
    for (int i = 0; i < ARRAY_SIZE - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < ARRAY_SIZE; ++j) {
            if (numbers[j] < numbers[min_index]) {
                min_index = j;
            }
        }

        std::swap(numbers[i], numbers[min_index]);
        renderArray();
        SDL_Delay(500);
    }
}

// Giải phóng bộ nhớ và đóng SDL
void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    srand(static_cast<unsigned>(time(nullptr)));

    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return -1;
    }
    // Chọn cách tạo mảng (ngẫu nhiên hoặc nhập từ bàn phím)
    std::cout << "Choose how to generate the array:\n";
    std::cout << "1. Random\n";
    std::cout << "2. Input from keyboard\n";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        generateRandomArray();
    }
    else if (choice == 2) {
        inputArray();
    }
    else {
        std::cerr << "Invalid choice. Using Random by default.\n";
        generateRandomArray();
    }

    renderArray();
    SDL_Delay(500);

    // Chọn thuật toán sắp xếp
    std::cout << "Choose a sorting algorithm:\n";
    std::cout << "1. Bubble Sort\n";
    std::cout << "2. Insertion Sort\n";
    std::cout << "3. Selection Sort\n";

    std::cin >> choice;

    switch (choice) {
    case 1:
        bubbleSort();
        break;
    case 2:
        insertionSort();
        break;
    case 3:
        selectionSort();
        break;
    default:
        std::cerr << "Invalid choice. Using Bubble Sort by default.\n";
        bubbleSort();
        break;
    }

    SDL_Delay(100);
    sorted = true;
    renderArray();

    SDL_Delay(1000);

    closeSDL();

    return 0;
}