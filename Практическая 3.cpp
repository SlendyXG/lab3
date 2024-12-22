#include <iostream>
#include <Windows.h>
#include <time.h>
#include <ctime>
#include <chrono>
#include <thread>
#include <math.h>
#include <cstdlib>
using namespace std;

int taskMenu()
{
    int variant;
    cout << "Выберите задание: " << endl;
    cout << "1) Вывести матрицу N*N\n"
        << "2) Перестановки матриц\n"
        << "3) Сортировка(shaker sort)\n"
        << "4) Уменьшение, увеличение, умножение или деление всех элементов матрицы на введенное пользователем число\n"
        << "5) IDZ" << endl;
    cout << "Задание: ";
    cin >> variant;
    return variant;
}

int const N = 6;

void ANACONDAoutput(int (*arr)[N]) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD destCoord;
    int top = 0, bottom = N - 1;
    int left = 0, right = N - 1;
    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) {
            destCoord.X = i * 3;
            destCoord.Y = top;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << *(*(arr + top) + i) << " ";
            Sleep(50);
        }
        top++;
        for (int i = top; i <= bottom; i++) {
            destCoord.X = right * 3;
            destCoord.Y = i;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << *(*(arr + i) + right) << " ";
            Sleep(50);
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                destCoord.X = i * 3;
                destCoord.Y = bottom;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << *(*(arr + bottom) + i) << " ";
                Sleep(50);
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                destCoord.X = left * 3;
                destCoord.Y = i;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << *(*(arr + i) + left) << " ";
                Sleep(50);
            }
            left++;
        }
    }

    destCoord.X = 0;
    destCoord.Y = N + 1;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void quicksort(int* begin, int* end) {
    if (begin >= end) return;

    int* f = begin;
    int* l = end;
    int mid = *(f + (l - f) / 2);

    while (f <= l) {
        while (*f < mid) f++;
        while (*l > mid) l--;
        if (f <= l) {
            swap(*f, *l);
            f++;
            l--;
        }
    }
    if (begin < l) quicksort(begin, l);
    if (f < end) quicksort(f, end);
}
void PITONoutput(int (*arr)[N]) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD destCoord;

    for (int stolb = 0; stolb < N; stolb++) {
        if (stolb % 2 == 0) {
            for (int row = 0; row < N; row++) {
                destCoord.X = (N * N) + (stolb * 3);
                destCoord.Y = row;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << *(*(arr + row) + stolb) << " ";
                Sleep(50);
            }
        }
        else {
            for (int row = N - 1; row >= 0; row--) {
                destCoord.X = (N * N) + (stolb * 3);
                destCoord.Y = row;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << *(*(arr + row) + stolb) << " ";
                Sleep(50);
            }
        }
    }
    destCoord.X = 0;
    destCoord.Y = N + 1;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void shakerSort(int* arr, int n) {
    bool swapped = true;
    int* start = arr;
    int* end = arr + n * n - 1;

    while (swapped) {
        swapped = false;

        for (int* i = start; i < end; ++i) {
            if (*i > *(i + 1)) {
                swap(*i, *(i + 1));
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }

        swapped = false;
        --end;

        for (int* i = end - 1; i >= start; --i) {
            if (*i > *(i + 1)) {
                swap(*i, *(i + 1));
                swapped = true;
            }
        }
        ++start;
    }
}
int determinant(int* matrix) {
    return *(matrix) * *(matrix + 4) * *(matrix + 8) + *(matrix + 1) * *(matrix + 5) * *(matrix + 6) + *(matrix + 2) * *(matrix + 3) * *(matrix + 7) -
        (*(matrix + 2) * *(matrix + 4) * *(matrix + 6) + *(matrix) * *(matrix + 7) * *(matrix + 5) + *(matrix + 1) * *(matrix + 3) * *(matrix + 8));
}
int main()
{
    srand(time(NULL));
    int maxvalue = N * N, minvalue = 1;
    int arr[N][N];
    int sortArr[N][N];
    int calcArr[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            arr[i][j] = rand() % (maxvalue - minvalue + 1) + minvalue;
            sortArr[i][j] = arr[i][j];
            calcArr[i][j] = arr[i][j];
        }
    }
    while (true) {
        setlocale(LC_ALL, "Russian");
        int variant = taskMenu();
        switch (variant) {
        case 1: {
            system("cls");
            ANACONDAoutput(arr);
            PITONoutput(arr);

        }
              break;
        case 2: {
            int step = N / 2;
            int abcd;
            cout << "Выберите тип перестановки: " << endl;
            cout << "1) a\n"
                << "2) b\n"
                << "3) c\n"
                << "4) d\n" << endl;
            cin >> abcd;
            switch (abcd) {
            case 1: {
                system("cls");
                int change[N][N];
                int* arr_ptr = *arr;
                int* change_ptr = *change;
                for (int i = 0; i < step; i++) {
                    for (int j = 0; j < step; j++) {
                        *(change_ptr + i * N + j) = *(arr_ptr + (i + step) * N + j);
                        *(change_ptr + i * N + (j + step)) = *(arr_ptr + i * N + j);
                        *(change_ptr + (i + step) * N + (j + step)) = *(arr_ptr + i * N + (j + step));
                        *(change_ptr + (i + step) * N + j) = *(arr_ptr + (i + step) * N + (j + step));
                    }
                }
                ANACONDAoutput(change);
                PITONoutput(arr);
            }
                  break;
            case 2: {
                system("cls");
                int change2[N][N];
                int* arr_ptr = *arr;
                int* change2_ptr = *change2;
                for (int i = 0; i < step; i++) {
                    for (int j = 0; j < step; j++) {
                        *(change2_ptr + i * N + j) = *(arr_ptr + (i + step) * N + (j + step));
                        *(change2_ptr + i * N + (j + step)) = *(arr_ptr + (i + step) * N + j);
                        *(change2_ptr + (i + step) * N + (j + step)) = *(arr_ptr + i * N + j);
                        *(change2_ptr + (i + step) * N + j) = *(arr_ptr + i * N + (j + step));
                    }
                }
                ANACONDAoutput(change2);
                PITONoutput(arr);
            }
                  break;
            case 3: {
                system("cls");
                int change3[N][N];
                int* arr_ptr = *arr;
                int* change3_ptr = *change3;
                for (int i = 0; i < step; i++) {
                    for (int j = 0; j < step; j++) {
                        *(change3_ptr + i * N + j) = *(arr_ptr + (i + step) * N + j);
                        *(change3_ptr + i * N + (j + step)) = *(arr_ptr + (i + step) * N + (j + step));
                        *(change3_ptr + (i + step) * N + j) = *(arr_ptr + i * N + j);
                        *(change3_ptr + (i + step) * N + (j + step)) = *(arr_ptr + i * N + (j + step));
                    }
                }
                ANACONDAoutput(change3);
                PITONoutput(arr);
            }
                  break;
            case 4: {
                system("cls");
                int change4[N][N];
                int* arr_ptr = *arr;
                int* change4_ptr = *change4;
                for (int i = 0; i < step; i++) {
                    for (int j = 0; j < step; j++) {
                        *(change4_ptr + i * N + j) = *(arr_ptr + i * N + (j + step));
                        *(change4_ptr + (i + step) * N + j) = *(arr_ptr + (i + step) * N + (j + step));
                        *(change4_ptr + i * N + (j + step)) = *(arr_ptr + i * N + j);
                        *(change4_ptr + (i + step) * N + (j + step)) = *(arr_ptr + (i + step) * N + j);
                    }
                }
                ANACONDAoutput(change4);
                PITONoutput(arr);
            }
                  break;
            }

        }
              break;
        case 3: {
            system("cls");
            quicksort(*sortArr, *sortArr + N * N);
            ANACONDAoutput(sortArr);
            PITONoutput(arr);
        }
              break;
        case 4: {
            int matANAL;
            cout << "Выберите тип действия: " << endl;
            cout << "1) Вычитание\n"
                << "2) Прибавление\n"
                << "3) Умножение\n"
                << "4) Деление\n" << endl;
            cin >> matANAL;
            switch (matANAL) {
            case 1: {
                int num;
                cout << "Введите число: " << endl;
                cin >> num;
                system("cls");
                int* start = *calcArr;
                int* end = *(calcArr + N * N - 1);
                for (int* ptr = start; ptr <= end; ++ptr) {
                    *ptr -= num;
                }
                ANACONDAoutput(calcArr);
                PITONoutput(arr);
            }
                  break;
            case 2: {
                int num;
                cout << "Введите число: " << endl;
                cin >> num;
                system("cls");
                int* start = *calcArr;
                int* end = *(calcArr + N * N - 1);
                for (int* ptr = start; ptr <= end; ++ptr) {
                    *ptr += num;
                }
                ANACONDAoutput(calcArr);
                PITONoutput(arr);
            }
                  break;
            case 3: {
                int num;
                cout << "Введите число: " << endl;
                cin >> num;
                system("cls");
                int* start = *calcArr;
                int* end = *(calcArr + N * N - 1);
                for (int* ptr = start; ptr <= end; ++ptr) {
                    *ptr *= num;
                }
                ANACONDAoutput(calcArr);
                PITONoutput(arr);
            }
                  break;
            case 4: {
                int num;
                cout << "Введите число: " << endl;
                cin >> num;
                system("cls");
                int* start = *calcArr;
                int* end = *(calcArr + N * N - 1);
                for (int* ptr = start; ptr <= end; ++ptr) {
                    *ptr /= num;
                }
                ANACONDAoutput(calcArr);
                PITONoutput(arr);
            }
                  break;
            }
            break;
        }
        case 5: {
            const int N = 3;
            int matrix[N][N];
            srand((time(0)));
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    *(*(matrix + i) + j) = rand() % 61 - 30;
                }
            }

            cout << "Сгенерированная матрица 3x3:" << endl;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    *(*(matrix + i) + j) = rand() % 61 - 30;
                    cout << *(*(matrix + i) + j) << '\t';
                }
                cout << endl;
            }
            int det = determinant(&matrix[0][0]);
            cout << "Определитель матрицы: " << det << endl;
        }
              break;
        }

    }
}