#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
const char* filename = "input.txt";

struct Point;
struct Matrix;
void file_to_matrix(FILE*, Matrix*); //считывание матрицы из файла
bool solve(Matrix& , Point); // решение задачи (по сути преобразование матрицы к решению)
void PrintSolve(Matrix&); // вывод на экран решения


struct Point {
    int x;
    int y;
};
struct Matrix {
    int lines = 0; //количество линий
    int columns = 0;  //количество колон
    unsigned** matrix;
};
void PrintMatrix(Matrix x) {
    for (int i = 0; i < x.lines; i++) {
        for (int j = 0; j < x.columns; j++) {
            cout << x.matrix[i][j] << ' ';
        }
        cout << endl;
    }
}
void file_to_matrix(FILE* f, Matrix*x) {
    char c;
    int lines = 0;
    int columns = 0;
    while (fscanf(f, "%c", &c) != -1) {
        if (c == '\n') {
            columns = -1;
            lines++;
        }
        columns++;
    }
    x->columns = columns;
    x->lines = lines + 1;
    x->matrix = new unsigned* [x->lines];
    for (int i = 0; i < x->lines; i++) {
        x->matrix[i] = new unsigned[x->columns];
    }
    fseek(f, 0, SEEK_SET);
    char k;
    for (int i = 0; i < x->lines; i++) {
        for (int j = 0; j < x->columns; j++) {
            if (fscanf(f, "%c", &k) == -1) {
                exit(1);
            }
            if ((k - 48 == 0) || (k - 48 == 1)) {
                x->matrix[i][j] = k - 48;
            }
            else {
                j -= 1;
            }
        }
    }
}
bool solve(Matrix &x,Point y) {
    if ((y.x == 0 || y.y == 0 || y.x == x.columns - 1 || y.y == x.lines - 1)&&x.matrix[y.y][y.x] == 0 ) {
        x.matrix[y.y][y.x] = 2;
        return true;
    }
    x.matrix[y.y][y.x] = 2;
    if ((y.y + 1 < x.lines) && (x.matrix[y.y + 1][y.x] == 0)) {
        if(solve(x, { y.x,y.y + 1 }))
            return true;
    }
    if ((y.x + 1 < x.columns) && (x.matrix[y.y][y.x + 1] == 0)) {
        if(solve(x, { y.x + 1,y.y }))
            return true;
    }
    if ((y.y - 1 >= 0) && (x.matrix[y.y - 1][y.x] == 0)) {
        if(solve(x, { y.x,y.y - 1 }))
            return true;
    }
    if ((y.x - 1 >= 0) && (x.matrix[y.y][y.x - 1] == 0)) {
        if(solve(x, { y.x - 1,y.y }))
            return true;
    }
    x.matrix[y.y][y.x] = 3;
    return false;
}

void PrintSolve(Matrix& x) {
    for (int i = 0; i < x.lines; i++) {
        for (int j = 0; j < x.columns; j++) {
            if (x.matrix[i][j] == 1) {
                cout << " % ";
            }
            if (x.matrix[i][j] == 3) {
                cout << "   ";
            }
            if (x.matrix[i][j] == 2) {
                cout << " . ";
            }
            if (x.matrix[i][j] == 0) {
                cout << "   ";
            }
            if (x.matrix[i][j] == 4) {
                cout << " ? ";
            }
        }
        cout << endl;
    }
}
int main()
{
    Matrix matrix;
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    { 
        cout << "file is not open" << endl;
        exit(1); 
    }
    Point x;
    char h;
    cin >> x.x >> x.y;
    file_to_matrix(file, &matrix);
    if ((x.y > matrix.lines) || (matrix.columns < x.x)) {
        cout << "x,y values it's so big" << endl;
        exit(1);
    }
    if (matrix.matrix[x.y][x.x] == 1) { cout << "is not empty!" << endl; }
    else {
        matrix.matrix[x.y][x.x] = 4;
        solve(matrix, x);
        matrix.matrix[x.y][x.x] = 4;
        PrintSolve(matrix);
    }
    return 0;
    

    


}

