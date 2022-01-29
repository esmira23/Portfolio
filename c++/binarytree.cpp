//
//  binarytree.cpp
//  binary tree
//
//  Created by Esmira Abdullaieva on 15.05.2021.
//

#include <iostream>
#include <iomanip>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
};

struct Tree {
    Node* root;
    Tree();
    Tree(int num);
    Node* Search(Node* r, int key);
    void Insert(int num); // додавання елемента
    Node* Find_Min(Node* node); // пошук мінімального
    Node* Find_Max(Node* node); // пошук максимальнного
    void Print(); // вивід
    void Show(Node* p, int indent);
    Node* Delete(Node *root, int key); //видалення
};

Tree::Tree(int num) {
    root = new Node;
    root->data = num;
    root->left = NULL;
    root->right = NULL;
}

Tree:: Tree() {
    root = NULL;
}

Node* Tree::Search(Node* r, int key) {
    if (root == NULL){
      return root;
    }
    else if ((r->data > key && r->left == NULL) || (r->data < key && r->right == NULL)) {
        return r;
    }
    else if (r->data == key) {
        return r;
    }
    else if (key > r->data) {
        Search(r->right, key);
    }
    else if (key < r->data) {
        Search(r->left, key);
    }
    return 0;
}

void Tree::Insert(int num) {
  Node* node = new Node;
  if (root == nullptr) {
      new Tree(num);
  } else {
//    node->parent = Search(root, num);
//    node->left = node->right = nullptr;
//    node->data = num;
    if (num >= node->parent->data)
      node->parent->right = node;
    else if (num < node->parent->data)
      node->parent->left = node;
  }
}


Node* Tree::Find_Min(Node* node) {
    Node* current = node;
    while(current->left!= NULL){
        current=current->left;
    }
    return current;
}

Node* Tree::Find_Max(Node* node) {
    Node* current = node;
    while(current->right!= NULL){
        current = current->right;
    }
    return current;
}

void Tree::Print() {        //вивід на екран
    Show(root,10);    //код не мій
}

void Tree::Show(Node* p, int indent) {
    if (p != NULL) {
        if (p->right) {
            Show(p->right, indent + 4);
        }
        if (indent) {
            cout << setw(indent) << ' ';
        }
        if (p->right) cout << " /\n" << setw(indent) << ' ';
        cout << p->data << "\n ";
        if (p->left) {
            cout << setw(indent) << ' ' << " \\\n";
            Show(p->left, indent + 4);
        }
    }
}

 Node* Tree:: Delete(Node *root, int key) {
    if(root == NULL) {
        return root;
    }
    else if(key < root->data) {                 //у якому піддереві робити видалення
        root->left = Delete(root->left, key);
    }
    else if (key > root->data) {
        root->right = Delete(root->right, key);
    }
    else {
        // Випадок 1 - немає дітей
        if(root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }
            //Є 1 дитина
        else if(root->left == NULL) {
            Node *temp = root;
            root = root->right;
            delete temp;
        }
        else if(root->right == NULL) {
            Node *temp = root;
            root = root->left;
            delete temp;
        }
            //2 дитини
        else {
            Node* temp = Find_Min(root->right);
            root->data = temp->data;
            root->right = Delete(root->right,temp->data);
        }
    }
    return root;
}
int main(){
    Tree tree(13);
    tree.Insert(12);
    tree.Insert(4);
//    tree.Insert(9);
//    tree.Insert(3);
//    tree.Insert(5);
//    tree.Insert(8);
//    tree.Insert(11);
    tree.Print();
    cout<<"_______________________"<<endl;
    tree.Delete(tree.root,4);
    tree.Print();

    return 0;
}
