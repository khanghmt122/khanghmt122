#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Cấu trúc dữ liệu cho một điểm
typedef struct Point {
    char name;
    double x, y;
} Point;

// Node của danh sách liên kết đơn
typedef struct Node {
    Point data;
    struct Node* next;
} Node;

// Cấu trúc danh sách liên kết
typedef struct {
    Node* head;
    int size;
} List;

// Khởi tạo danh sách rỗng
void initList(List* L) {
    L->head = NULL;
    L->size = 0;
}

// Thêm điểm vào cuối danh sách
void addPoint(List* L, Point p) {
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
    L->size++;
}

// Hàm đọc file và tạo danh sách
void CreatList(List* L, char* fname) {
    FILE* file = fopen(fname, "r");
    if (file == NULL) {
        printf("Không thể mở file %s\n", fname);
        return;
    }
    
    initList(L);
    char line[1000];
    
    if (fgets(line, sizeof(line), file)) {
        int i = 0;
        while (i < strlen(line)) {
            Point p;
            char temp[50];
            int j = 0;
            
            // Tìm ký tự đầu tiên của điểm (A-Z)
            while (i < strlen(line) && (line[i] < 'A' || line[i] > 'Z')) {
                i++;
            }
            
            if (i >= strlen(line)) break;
            
            // Đọc từ ký tự này đến hết dấu )
            while (i < strlen(line) && line[i] != ')') {
                temp[j++] = line[i++];
            }
            if (i < strlen(line) && line[i] == ')') {
                temp[j++] = line[i++];
            }
            temp[j] = '\0';
            
            // Parse định dạng A(-3, 6) hoặc A(-3,-6)
            if (sscanf(temp, "%c(%lf,%lf)", &p.name, &p.x, &p.y) == 3) {
                addPoint(L, p);
            }
        }
    }
    
    fclose(file);
}

// Tính khoảng cách giữa hai điểm
double calculateDistance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Tìm khoảng cách lớn nhất và các điểm tương ứng
void findMaxDistance(List* L, double* maxDist, Point* point1, Point* point2) {
    *maxDist = 0;
    Node* current1 = L->head;
    
    while (current1 != NULL) {
        Node* current2 = current1->next;
        while (current2 != NULL) {
            double dist = calculateDistance(current1->data, current2->data);
            if (dist > *maxDist) {
                *maxDist = dist;
                *point1 = current1->data;
                *point2 = current2->data;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
}

// In danh sách các điểm
void printList(List* L) {
    Node* current = L->head;
    while (current != NULL) {
        printf("%c(%.0f,%2.0f) ", current->data.name, current->data.x, current->data.y);
        current = current->next;
    }
    printf("\n");
}

// Giải phóng bộ nhớ danh sách
void freeList(List* L) {
    Node* current = L->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    L->head = NULL;
    L->size = 0;
}

int main() {
    char fname[] = "XY1.txt";
    List L;
    
    // Tạo danh sách từ file
    CreatList(&L, fname);
    
    // In danh sách các điểm
    printList(&L);
    
    // Tìm khoảng cách lớn nhất
    double maxDist;
    Point point1, point2;
    findMaxDistance(&L, &maxDist, &point1, &point2);
    
    // In kết quả
    printf("dmax = %.2f\n", maxDist);
    printf("%c(%.0f,%.0f) %c(%.0f,%.0f)\n", 
           point1.name, point1.x, point1.y,
           point2.name, point2.x, point2.y);
    printf("in C\n");
    
    // Giải phóng bộ nhớ
    freeList(&L);
    
    return 0;
}