#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Cấu trúc điểm
typedef struct {
    char name;
    int x;
    int y;
} Point;

// Node của danh sách liên kết đơn
typedef struct Node {
    Point data;
    struct Node* next;
} Node;

// Danh sách liên kết
typedef struct {
    Node* head;
} List;

// Khởi tạo danh sách rỗng
void InitList(List* L) {
    L->head = NULL;
}

// Thêm điểm vào cuối danh sách
void AddTail(List* L, Point p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = p;
    newNode->next = NULL;
    
    if (L->head == NULL) {
        L->head = newNode;
    } else {
        Node* temp = L->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Đọc dữ liệu từ file và tạo danh sách
void CreatList(List* L, char fname[]) {
    InitList(L);
    FILE* f = fopen(fname, "r");
    if (f == NULL) {
        printf("Khong mo duoc file %s\n", fname);
        return;
    }
    
    Point p;
    while (fscanf(f, "%c,%d,%d\n", &p.name, &p.x, &p.y) == 3) {
        AddTail(L, p);
    }
    
    fclose(f);
}

// Tính khoảng cách giữa 2 điểm
double Distance(Point A, Point B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

// In danh sách các điểm
void PrintList(List L) {
    Node* temp = L.head;
    while (temp != NULL) {
        printf("%c(%2d,%2d) ", temp->data.name, temp->data.x, temp->data.y);
        temp = temp->next;
    }
    printf("\n");
}

// Tìm và in các cặp điểm có khoảng cách xa nhất
void FindMaxDistance(List L) {
    if (L.head == NULL || L.head->next == NULL) {
        printf("Danh sach khong du diem de tinh khoang cach\n");
        return;
    }
    
    double dmax = 0;
    Node* p1 = L.head;
    
    // Tìm khoảng cách xa nhất
    while (p1 != NULL) {
        Node* p2 = p1->next;
        while (p2 != NULL) {
            double d = Distance(p1->data, p2->data);
            if (d > dmax) {
                dmax = d;
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    
    printf("dmax = %.2f\n", dmax);
    
    // In tất cả các cặp điểm có khoảng cách bằng dmax
    p1 = L.head;
    while (p1 != NULL) {
        Node* p2 = p1->next;
        while (p2 != NULL) {
            double d = Distance(p1->data, p2->data);
            if (fabs(d - dmax) < 0.01) {  // So sánh với độ chính xác 0.01
                printf("%c(%d,%d) %c(%d,%d)\n", 
                       p1->data.name, p1->data.x, p1->data.y,
                       p2->data.name, p2->data.x, p2->data.y);
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
}

// Giải phóng bộ nhớ danh sách
void FreeList(List* L) {
    Node* temp = L->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    L->head = NULL;
}

int main() {
    char fname[] = "XY1.txt";
    List L;
    
    CreatList(&L, fname);
    
    // In danh sách các điểm
    PrintList(L);
    
    // Tìm và in khoảng cách xa nhất và các cặp điểm
    FindMaxDistance(L);
    
    // Giải phóng bộ nhớ
    FreeList(&L);
    
    return 0;
}
