#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Cấu trúc điểm
typedef struct {
    char name;
    int x;
    int y;
} Point;

// Cấu trúc node của danh sách liên kết
typedef struct Node {
    Point data;
    struct Node* next;
} Node;

// Cấu trúc danh sách liên kết
typedef struct {
    Node* head;
} List;

// Khởi tạo danh sách rỗng
void InitList(List* L) {
    L->head = NULL;
}

// Tạo node mới
Node* CreateNode(Point p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Loi cap phat bo nho!\n");
        return NULL;
    }
    newNode->data = p;
    newNode->next = NULL;
    return newNode;
}

// Thêm điểm vào cuối danh sách
void AddTail(List* L, Point p) {
    Node* newNode = CreateNode(p);
    if (newNode == NULL) return;
    
    if (L->head == NULL) {
        L->head = newNode;
    } else {
        Node* current = L->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Đọc dữ liệu từ file và tạo danh sách
void CreateList(List* L, char fname[]) {
    FILE* f = fopen(fname, "r");
    if (f == NULL) {
        printf("Khong the mo file %s\n", fname);
        return;
    }
    
    InitList(L);
    Point p;
    
    // Đọc từng dòng: tên, x, y
    while (fscanf(f, " %c %d %d", &p.name, &p.x, &p.y) == 3) {
        AddTail(L, p);
    }
    
    fclose(f);
}

// Xuất danh sách các điểm
void PrintList(List L) {
    Node* current = L.head;
    while (current != NULL) {
        printf("%c(%2d,%2d) ", current->data.name, current->data.x, current->data.y);
        current = current->next;
    }
    printf("\n");
}

// Tính khoảng cách giữa 2 điểm
double Distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Tìm cặp điểm có khoảng cách xa nhất
void FindMaxDistance(List L) {
    if (L.head == NULL || L.head->next == NULL) {
        printf("Danh sach khong du diem de tinh khoang cach!\n");
        return;
    }
    
    double maxDist = 0;
    Point p1Max, p2Max;
    
    Node* current1 = L.head;
    while (current1 != NULL) {
        Node* current2 = current1->next;
        while (current2 != NULL) {
            double dist = Distance(current1->data, current2->data);
            if (dist > maxDist) {
                maxDist = dist;
                p1Max = current1->data;
                p2Max = current2->data;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    
    printf("dmax = %.2f\n", maxDist);
    printf("%c(%2d,%2d) %c(%2d,%2d)\n", p1Max.name, p1Max.x, p1Max.y, 
           p2Max.name, p2Max.x, p2Max.y);
}

// Giải phóng bộ nhớ
void FreeList(List* L) {
    Node* current = L->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    L->head = NULL;
}

int main() {
    char fname[] = "XY1.txt";
    List L;
    
    CreateList(&L, fname);
    
    printf("Result:\n");
    PrintList(L);
    FindMaxDistance(L);
    
    FreeList(&L);
    
    return 0;
}
