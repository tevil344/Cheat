#include <iostream>
#include <string>
using namespace std;

// AVL Tree Node structure
struct Node {
    int player_id;  // key
    int score;      // value
    Node* left;
    Node* right;
    int height;     // height of the node
};

// Function to get the height of a node
int getHeight(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Function to calculate the balance factor
int getBalanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to create a new node
Node* createNode(int player_id, int score) {
    Node* newNode = new Node();
    newNode->player_id = player_id;
    newNode->score = score;
    newNode->left = newNode->right = nullptr;
    newNode->height = 1;  // new node starts at height 1
    return newNode;
}

// Right rotate operation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left rotate operation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Function to insert a player (Player Registration)
Node* insert(Node* root, int player_id, int score) {
    if (root == nullptr)
        return createNode(player_id, score);

    if (player_id < root->player_id)
        root->left = insert(root->left, player_id, score);
    else if (player_id > root->player_id)
        root->right = insert(root->right, player_id, score);
    else {
        cout << "Duplicate player_id is not allowed.\n";
        return root;
    }

    // Update height of current node
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // Check balance factor and perform rotations
    int balance = getBalanceFactor(root);
    if (balance > 1 && player_id < root->left->player_id)
        return rightRotate(root);
    if (balance < -1 && player_id > root->right->player_id)
        return leftRotate(root);
    if (balance > 1 && player_id > root->left->player_id) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && player_id < root->right->player_id) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to find the minimum node (used in deletion)
Node* findMin(Node* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

// Function to delete a player (Remove player from game)
Node* deleteNode(Node* root, int player_id) {
    if (root == nullptr)
        return root;

    if (player_id < root->player_id)
        root->left = deleteNode(root->left, player_id);
    else if (player_id > root->player_id)
        root->right = deleteNode(root->right, player_id);
    else {
        if (root->left == nullptr && root->right == nullptr) {
            // No children
            delete root;
            root = nullptr;
        } else if (root->left == nullptr || root->right == nullptr) {
            // One child
            Node* child = nullptr;
            if (root->left != nullptr)
                child = root->left;
            else
                child = root->right;
        
            Node* temp = root;
            root = child;
            delete temp;
        } else {
            // Two children
            Node* temp = findMin(root->right);
            root->player_id = temp->player_id;
            root->score = temp->score;
            root->right = deleteNode(root->right, temp->player_id);
        }
    }

    if (root == nullptr) return root;

    // Update height and balance
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// In-order traversal to display leaderboard
void displayLeaderboard(Node* root) {
    if (root == nullptr) return;
    displayLeaderboard(root->left);
    cout << "Player ID: " << root->player_id << ", Score: " << root->score << endl;
    displayLeaderboard(root->right);
}

// Main function
int main() {
    Node* root = nullptr;
    int choice, player_id, score;

    do {
        cout << "\nMultiplayer Game System:\n"
             << "1. Player Registration\n"
             << "2. Leaderboard Display\n"
             << "3. Remove Player from Game\n"
             << "4. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Player ID: ";
                cin >> player_id;
                cout << "Enter Score: ";
                cin >> score;
                root = insert(root, player_id, score);
                break;
            case 2:
                cout << "Leaderboard:\n";
                displayLeaderboard(root);
                break;
            case 3:
                cout << "Enter Player ID to remove: ";
                cin >> player_id;
                root = deleteNode(root, player_id);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}