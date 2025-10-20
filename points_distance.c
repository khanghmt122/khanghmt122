#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Cấu trúc điểm
typedef struct {
    char name;
    double x, y;
} Point;

// Cấu trúc danh sách
typedef struct {
    Point *points;
    int count;
    int capacity;
} List;

// Khởi tạo danh sách
void InitList(List *L) {
    L->capacity = 10;
    L->count = 0;
    L->points = (Point*)malloc(L->capacity * sizeof(Point));
}

// Thêm điểm vào danh sách
void AddPoint(List *L, char name, double x, double y) {
    if (L->count >= L->capacity) {
        L->capacity *= 2;
        L->points = (Point*)realloc(L->points, L->capacity * sizeof(Point));
    }
    L->points[L->count].name = name;
    L->points[L->count].x = x;
    L->points[L->count].y = y;
    L->count++;
}

// Đọc dữ liệu từ file
void CreatList(List *L, char fname[]) {
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        printf("Không thể mở file %s\n", fname);
        return;
    }
    
    InitList(L);
    char name;
    double x, y;
    
    // Đọc từng dòng trong file
    while (fscanf(file, " %c(%lf,%lf)", &name, &x, &y) == 3) {
        AddPoint(L, name, x, y);
    }
    
    fclose(file);
}

// Tính khoảng cách giữa hai điểm
double Distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Tìm cặp điểm có khoảng cách lớn nhất
void FindMaxDistance(List *L, Point *p1, Point *p2, double *maxDist) {
    *maxDist = 0;
    
    for (int i = 0; i < L->count; i++) {
        for (int j = i + 1; j < L->count; j++) {
            double dist = Distance(L->points[i], L->points[j]);
            if (dist > *maxDist) {
                *maxDist = dist;
                *p1 = L->points[i];
                *p2 = L->points[j];
            }
        }
    }
}

// In danh sách các điểm
void PrintList(List *L) {
    for (int i = 0; i < L->count; i++) {
        printf("%c(%.0f,%2.0f) ", L->points[i].name, L->points[i].x, L->points[i].y);
    }
    printf("\n");
}

// Giải phóng bộ nhớ
void FreeList(List *L) {
    free(L->points);
    L->points = NULL;
    L->count = 0;
    L->capacity = 0;
}

int main() {
    char fname[] = "XY1.txt";
    List L;
    
    // Tạo danh sách từ file
    CreatList(&L, fname);
    
    // In danh sách các điểm
    printf("Result:\n");
    PrintList(&L);
    
    // Tìm cặp điểm có khoảng cách lớn nhất
    Point p1, p2;
    double maxDist;
    FindMaxDistance(&L, &p1, &p2, &maxDist);
    
    // In kết quả
    printf("dmax = %.2f\n", maxDist);
    printf("%c(%.0f,%.0f) %c(%.0f,%.0f)\n", p1.name, p1.x, p1.y, p2.name, p2.x, p2.y);
    
    // Giải phóng bộ nhớ
    FreeList(&L);
    
    return 0;
}