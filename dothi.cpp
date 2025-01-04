#include <iostream>
using namespace std;
//Viết chương trình cài đặt đồ thị cho như trên bảng theo hai cấu trúc lưu trữ 
//Sử dụng ma trận lân cận -> nhập thông tin đồ thị 
void nhapmatran(char **a, int n){    // **a: con trỏ cấp 2 -> mảng 2 chiều
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
    }
}
//Sử dụng danh sách lân cận  -> nhập thông tin đồ thị 
struct Node{
    char vertex;
    Node *next;
};
struct Graph{
    int numVertices; // số đỉnh
    Node **adjLists; // mảng cac danh sách lân cận
};
//tao moi 1 node
Node *createNode(char vertex){
    Node *newNode = new Node;
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}
//tao 1 đồ thị
Graph *createGraph(int vertices){
    Graph *graph = new Graph;   // tạo 1 biến con trỏ trỏ đến 1 biến kiểu Graph
    graph->numVertices = vertices; //gsn thong tin so dinh cho do thi
    graph->adjLists = new Node*[vertices]; //cap phat bo nho cho mang cac danh sach ke
    
    for(int i = 0; i < vertices; i++){
        //tao dau danh sach chua thong tin cac dinh 
        graph->adjLists[i] = createNode(i+'a');
    }
    return graph;
}
//tao ket noi giua 2 dinh
void addEdge(Graph *g, char src, char dest){
    //chuyen dinh thanh chi so
    int srcIndex = src - 'a';
    int destIndex = dest - 'a';
    //them ket noi tu dinh src den dinh dest
    Node *newNode = createNode(dest);
    //node moi chen vao dau dslk cho nhanh
    //vi chen vao cuoi phai duyet toi cuoi
    newNode->next = g->adjLists[srcIndex]->next;
    g->adjLists[srcIndex]->next = newNode; //cap nhat lai node dau tien
    //ket thuc them ket noi tu src den dest

    //them ket noi tu dest den src
    newNode = createNode(src);
    newNode->next = g->adjLists[destIndex]->next;
    g->adjLists[destIndex]->next = newNode;
}

//duyệt theo BFS
void BFS(Graph *g, char start){
    //chuyen dinh thanh chi so
    int startIndex = start - 'a';
    //tao mang kiem tra dinh da duyet hay chua
    bool *visited = new bool[g->numVertices];
    for(int i = 0; i < g->numVertices; i++){
        visited[i] = false;
    }
    //tao hang doi
    Node *queue = NULL;
    //dua dinh start vao hang doi
    visited[startIndex] = true;
    cout << start << " ";
    Node *p = g->adjLists[startIndex]->next;
    while(p){
        if(!visited[p->vertex - 'a']){
            visited[p->vertex - 'a'] = true;
            cout << p->vertex << " ";
            //dua dinh p vao hang doi
            Node *newNode = createNode(p->vertex);
            newNode->next = queue;
            queue = newNode;
        }
        p = p->next;
    }
    //duyet cac dinh con lai trong hang doi
    while(queue){
        Node *top = queue;
        queue = queue->next;
        int u = top->vertex - 'a';
        p = g->adjLists[u]->next;
        while(p){
            if(!visited[p->vertex - 'a']){
                visited[p->vertex - 'a'] = true;
                cout << p->vertex << " ";
                //dua dinh p vao hang doi
                Node *newNode = createNode(p->vertex);
                newNode->next = queue;
                queue = newNode;
            }
            p = p->next;
        }
    }
}
//duyet theo DFS
void DFS(Graph *g, char start){
    //chuyen dinh thanh chi so
    int startIndex = start - 'a';
    //tao mang kiem tra dinh da duyet hay chua
    bool *visited = new bool[g->numVertices];
    for(int i = 0; i < g->numVertices; i++){
        visited[i] = false;
    }
    //tao stack
    Node *stack = NULL;
    //dua dinh start vao stack
    visited[startIndex] = true;
    cout << start << " ";
    Node *p = g->adjLists[startIndex]->next;
    while(p){
        if(!visited[p->vertex - 'a']){
            visited[p->vertex - 'a'] = true;
            cout << p->vertex << " ";
            //dua dinh p vao stack
            Node *newNode = createNode(p->vertex);
            newNode->next = stack;
            stack = newNode;
            p = g->adjLists[p->vertex - 'a']->next;
        }
        else{
            p = p->next;
        }
    }
    //duyet cac dinh con lai trong stack
    while(stack){
        Node *top = stack;
        stack = stack->next;
        int u = top->vertex - 'a';
        p = g->adjLists[u]->next;
        while(p){
            if(!visited[p->vertex - 'a']){
                visited[p->vertex - 'a'] = true;
                cout << p->vertex << " ";
                //dua dinh p vao stack
                Node *newNode = createNode(p->vertex);
                newNode->next = stack;
                stack = newNode;
                p = g->adjLists[p->vertex - 'a']->next;
            }
            else{
                p = p->next;
            }
        }
    }
}

int main(){
    int n;
    cout << "Nhap so dinh cua do thi: ";
    cin >> n;
    char **a = new char*[n];   // tạo mảng 2 chiều
    for(int i = 0; i < n; i++){
        a[i] = new char[n]; 
    }
    nhapmatran(a, n);
    //tao do thi tu ma tran
    Graph *g = createGraph(n);
    addEdge(g, 'a','b');
    addEdge(g, 'a','c');
    addEdge(g, 'a','d');
    addEdge(g, 'b', 'e');
    addEdge(g, 'e', 'c');
    addEdge(g, 'e', 'g');
    addEdge(g, 'd', 'f');
    addEdge(g, 'd', 'e');
    addEdge(g, 'e', 'f');
    addEdge(g, 'g', 'b');
    addEdge(g, 'g', 'f');
    
    return 0;
}