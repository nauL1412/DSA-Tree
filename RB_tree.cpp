#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum Color
{
    RED,
    BLACK
};

class Node
{
public:
    int key;
    Color color;
    Node *left, *right, *parent;

    Node(int key)
    {
        this->key = key;
        this->color = RED;
        left = right = parent = nullptr;
    }
};

class RedBlackTree
{
public:
    Node *root;

    void deleteTree(Node *node)
    {
        if (node != nullptr)
        {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
    void insertFixup(Node *node)
    {
        while (node != root && node->parent->color == RED)
        {
            if (node->parent == node->parent->parent->left)
            {
                Node *uncle = node->parent->parent->right;
                if (uncle && uncle->color == RED)
                {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else
                {
                    if (uncle == nullptr || uncle->color == BLACK)
                    {
                        if (node == node->parent->right)
                        {
                            node = node->parent;
                            leftRotate(node);
                        }
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        rightRotate(node->parent->parent);
                    }
                }
            }
            else
            {
                Node *uncle = node->parent->parent->left;
                if (uncle && uncle->color == RED)
                {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else
                {
                    if (uncle == nullptr || uncle->color == BLACK)
                    {
                        if (node == node->parent->left)
                        {
                            node = node->parent;
                            rightRotate(node);
                        }
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        leftRotate(node->parent->parent);
                    }
                }
            }
        }
        root->color = BLACK;
    }

    void leftRotate(Node *node)
    {
        Node *rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != nullptr)
        {
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;
        if (node->parent == nullptr)
        {
            root = rightChild;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = rightChild;
        }
        else
        {
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }

    void rightRotate(Node *node)
    {
        Node *leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != nullptr)
        {
            leftChild->right->parent = node;
        }
        leftChild->parent = node->parent;
        if (node->parent == nullptr)
        {
            root = leftChild;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = leftChild;
        }
        else
        {
            node->parent->right = leftChild;
        }
        leftChild->right = node;
        node->parent = leftChild;
    }

    void inorderTraversal(Node *node)
    {
        if (node != nullptr)
        {
            inorderTraversal(node->left);
            cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

    int height(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

public:
    RedBlackTree()
    {
        root = nullptr;
    }

    void insert(int key)
    {
        Node *node = new Node(key);
        Node *parent = nullptr;
        Node *current = root;
        while (current != nullptr)
        {
            parent = current;
            if (key < current->key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        node->parent = parent;
        if (parent == nullptr)
        {
            root = node;
        }
        else if (key < parent->key)
        {
            parent->left = node;
        }
        else
        {
            parent->right = node;
        }
        insertFixup(node);
    }
    void insert_file(string filename)
    {
        ifstream inputFile(filename);
        if (inputFile.is_open())
        {
            double data;
            while (inputFile >> data)
            {
                insert(data);
            }
            inputFile.close();
        }
        else
        {
            cout << "Không thể mở tệp!" << endl;
        }
    }

    void inorder()
    {
        inorderTraversal(root);
    }

    int getHeight()
    {
        return height(root);
    }
};

int main()
{
    for (int i = 1; i <= 10; i++)
    {
        string filename = "data" + to_string(i) + ".txt";
        RedBlackTree tree;
        tree.insert_file(filename);
        cout << "height of RB tree " << i << ": " << tree.getHeight() << endl;
        tree.deleteTree(tree.root);
    }
}