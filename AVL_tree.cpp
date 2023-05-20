#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Lớp Node đại diện cho một nút trong cây AVL
class Node {
public:
    double data;           // Dữ liệu của nút
    int height;         // Chiều cao của nút
    Node* left;         // Con trỏ trái của nút
    Node* right;        // Con trỏ phải của nút

    // Hàm tạo Node mới với dữ liệu cho trước
    Node(double data) {
        this->data = data;
        height = 1;
        left = nullptr;
        right = nullptr;
   }
};

// Lớp AVLTree đại diện cho cây AVL
class AVLTree {
public:
    Node* root;         // Con trỏ đến nút gốc của cây AVL

    // Hàm tạo cây AVL mới
    AVLTree() {
        root = nullptr;
    }

    // Hàm huỷ cây AVL
    ~AVLTree() {
        deleteTree(root);
    }

    // Hàm chèn một nút mới vào cây AVL
    void insert(double data) {
        root = insertHelper(root, data);
    }

    // Hàm đọc dữ liệu từ tệp văn bản và chèn các nút vào cây AVL
    void insertFromFile(string filename) {
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            double data;
            while (inputFile >> data) {
                insert(data);
            }
            inputFile.close();
        }
        else {
            cout << "Không thể mở tệp!" << endl;
        }
    }

    // Hàm xoay trái tại nút x
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* z = y->left;
        y->left = x;
        x->right = z;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    // Hàm xoay phải tại nút x
    Node* rotateRight(Node* x) {
        Node* y = x->left;
        Node* z = y->right;
        y->right = x;
        x->left = z;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    

    // Hàm đếm chiều cao của cây AVL
    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    // Hàm tính độ chênh lệch giữa chiều cao của hai nhánh con của một nút
    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    // Hàm chèn một nút mới vào cây AVL
    Node* insertHelper(Node* node, double data) {
        // Nếu cây rỗng, tạo nút mới và trả về
        if (node == nullptr) {
            return new Node(data);
        }

        // Chèn nút mới vào cây
        if (data < node->data) {
            node->left = insertHelper(node->left, data);
        }
        else if (data > node->data) {
            node->right = insertHelper(node->right, data);
        }
        else {
            return node;
        }

        // Cập nhật chiều cao của nút
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        // Cân bằng cây AVL
        int balance = getBalance(node);

        // TH1: cây mất cân bằng về bên trái
        if (balance > 1 && data < node->left->data) {
            return rotateRight(node);
        }

        // TH2: cây mất cân bằng về bên phải
        if (balance < -1 && data > node->right->data) {
            return rotateLeft(node);
        }

        // TH3: cây mất cân bằng về bên trái-phải
        if (balance > 1 && data > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // TH4: cây mất cân bằng về bên phải-trái
        if (balance < -1 && data < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Hàm xoá cây AVL
    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    
};


int main() {
    for (int i=1; i<=10; i++){
        string filename = "data" + to_string(i) + ".txt";
        AVLTree tree  ;
        tree.insertFromFile(filename);
        cout<<"height of AVL tree "<<i<<": "<<tree.getHeight(tree.root)<<endl;
        
    }
    
    
    return 0;
}