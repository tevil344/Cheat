#include<iostream>
#include<queue>
using namespace std;

class node{
public:
    int data;
    node* left;
    node* right;

    node(int val){
        data = val;
        left = NULL;
        right = NULL;
    }
};

node* createBST(node* root){
    int data;
    cout << "Enter data to insert into BST (-1 to stop): ";
    cin >> data;
    while(data != -1){
        root = insertIntoBst(root, data);
        cout << "Enter data to insert into BST (-1 to stop): ";
        cin >> data;
    }
    return root;
}


node* insertIntoBst(node* root, int d){
    if(root == NULL){
        return new node(d);
    }
    if(d < root->data){
        root->left = insertIntoBst(root->left, d);
    } else {
        root->right = insertIntoBst(root->right, d);
    }
    return root;
}

node* deleteFromBst(node* root, int v){
    if(root == NULL){
        return NULL;
    }
    if(v < root->data){
        root->left = deleteFromBst(root->left, v);
    } else if(v > root->data){
        root->right = deleteFromBst(root->right, v);
    } else {
        // Node found
        if(root->left == NULL && root->right == NULL){
            delete root;
            return NULL;
        } else if(root->left == NULL){
            node* temp = root->right;
            delete root;
            return temp;
        } else if(root->right == NULL){
            node* temp = root->left;
            delete root;
            return temp;
        } else {
            node* minNode = miniVal(root->right);
            root->data = minNode->data;
            root->right = deleteFromBst(root->right, minNode->data);
        }
    }
    return root;
}

node* miniVal(node* root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

node* searchBst(node* root, int key){
    if(root == NULL){
        return NULL;
    }
    if(root->data == key){
        return root;
    } else if(key < root->data){
        return searchBst(root->left, key);
    } else {
        return searchBst(root->right, key);
    }
}

void inorderTraversal(node* root){
    if(root == NULL){
        return;
    }
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

node* mirrorBst(node* root){
    if(root == NULL){
        return NULL;
    }
    node* newRoot = new node(root->data);
    newRoot->left = mirrorBst(root->right);
    newRoot->right = mirrorBst(root->left);
    return newRoot;
}

node* copyBst(node* root){
    if(root == NULL){
        return NULL;
    }
    node* newRoot = new node(root->data);
    newRoot->left = copyBst(root->left);
    newRoot->right = copyBst(root->right);
    return newRoot;
}

void levelWiseTraversal(node* root){
    if (root == NULL) return;

    cout << "Level-wise traversal: \n";
    queue<node*> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        node* temp = q.front();
        q.pop();
        if(temp == NULL){
            cout << endl;
            if(!q.empty()){
                q.push(NULL);
            }
        } else {
            cout << temp->data << " ";
            if(temp->left != NULL){
                q.push(temp->left);
            }
            if(temp->right != NULL){
                q.push(temp->right);
            }
        }
    }
}

int main(){
    node* root = NULL;
    int c = 0;

    cout << "Enter 1 to create a BST" << endl;
    cout << "Enter 2 to insert data into BST" << endl;
    cout << "Enter 3 to delete data from BST" << endl;
    cout << "Enter 4 to search data in BST" << endl;
    cout << "Enter 5 to perform inorder traversal" << endl;
    cout << "Enter 6 to create a mirror BST" << endl;
    cout << "Enter 7 to copy a BST" << endl;
    cout << "Enter 8 for level-wise traversal" << endl;
    cout << "Enter 9 to exit" << endl;

    while(true){
        cout << "Enter your choice: ";
        cin >> c;
        
        switch(c){
            case 1:
                root = createBST(root);
                cout << "BST created successfully!" << endl;
                break;
            case 2:
                int data;
                cout << "Enter data to insert: ";
                cin >> data;
                root = insertIntoBst(root, data);
                cout << "Data inserted successfully!" << endl;
                break;
            case 3:
                int delData;
                cout << "Enter data to delete: ";
                cin >> delData;
                root = deleteFromBst(root, delData);
                cout << "Data deleted successfully!" << endl;
                break;
            case 4: 
                int searchData;
                cout << "Enter data to search: ";
                cin >> searchData;
                node* foundNode = searchBst(root, searchData);
                if(foundNode != NULL){
                    cout << "Data found: " << foundNode->data << endl;
                } else {
                    cout << "Data not found!" << endl;
                }
                break;
            case 5:
                cout << "Inorder Traversal: ";
                inorderTraversal(root);
                cout << endl;
                break;
            case 6:
                node* mirrorRoot = mirrorBst(root);
                cout << "Mirror BST created successfully!" << endl;
                cout << "Inorder Traversal of Mirror BST: ";
                inorderTraversal(mirrorRoot);
                cout << endl;
                break;
            case 7:
                node* copiedRoot = copyBst(root);
                cout << "BST copied successfully!" << endl;
                cout << "Inorder Traversal of Copied BST: ";
                inorderTraversal(copiedRoot);
                cout << endl;
                break;
            case 8:
                levelWiseTraversal(root);
                break;
            case 9:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
}
