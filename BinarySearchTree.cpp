//Implementation completed by Ismael Souf, last modification 17/04/2018
//
//You will need to ensure that your compiler is operating to the C++ 2011 standard for the coursework files to compile.
//

#include "bst.h"

using namespace std;

// Creates an empty binary tree
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

// Creates a binary tree with an initial value to store
BinarySearchTree::BinarySearchTree(string word)
{
    Node* newNode = new Node;
    newNode->data = word;
    newNode->left = nullptr;
    newNode->right = nullptr;
    root = newNode;
}

//Create a helper for copying an existing Tree
void copyTree(Node* &copy, const Node* rhs)
{
    if(rhs == nullptr)
    {
        //Copy empty tree
        copy = nullptr;
    }
    else
    {
        //Creates new Node object for copy
        copy = new Node;
        //Set data to be the same
        copy->data = rhs->data;
        copyTree(copy->left, rhs->left);
        copyTree(copy->right, rhs->right);
    }
    
}

// Creates a binary tree by copying an existing tree
BinarySearchTree::BinarySearchTree(const BinarySearchTree &rhs)
{
        copyTree(root,rhs.root);
}

void delete_tree(Node* &tree)
{
    if(tree == nullptr)
        return;
    //Clean left sub-tree
    delete_tree(tree->left);
    //Clean right sub-tree
    delete_tree(tree->right);
    //Destroy this node
    delete tree;
}

// Destroys (cleans up) the tree
BinarySearchTree::~BinarySearchTree()
{
    delete_tree(root);
}

void insertHelper(Node *root, string word)
{
   
    if(word < root->data)
    {
        if(root->left != nullptr)
        {
            insertHelper(root->left, word);
        }
        else
        {
            root->left = new Node;
            root->left->data = word;
            root->left->left = nullptr;
            root->left->right = nullptr;
        }
    }
    
    if(word >= root->data)
    {
        if(root->right != nullptr)
        {
            insertHelper(root->right, word);
        }
        else
        {
            root->right = new Node;
            root->right->data = word;
            root->right->left = nullptr;
            root->right->right = nullptr;
        }
    }
}

// Adds a word to the tree
void BinarySearchTree::insert(string word)
{

    if(word != string(""))
    {
        if(root == nullptr)
        {
            root = new Node;
            root->data = word;
        }
        else
        {
            insertHelper(root, word);
        }
    }
   
}

//Create minimum value of the node to remove two children
Node *minNode(Node *root)
{
    while(root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

void removeHelper(Node *root,string word)
{
   //Locate the element
    bool found = false;
    
    if(root == nullptr)
    {
        cout << "This tree is empty! " << endl;
        return;
    }
    Node* currentNode;
    Node* parent;
    currentNode = root;
    
    while(currentNode != nullptr)
    {
        if(currentNode->data == word)
        {
            found = true;
            break;
        }
        else
        {
            parent = currentNode;
            if(word > currentNode->data)
                currentNode = currentNode->right;
            else currentNode = currentNode->left;
        }
    }
    if(!found)
    {
        return;
    }
    
    //Remove check part 2 - leaf value
    if(currentNode->left == nullptr && currentNode->right == nullptr)
    {
        if(parent->left == currentNode) parent->left = nullptr;
        else parent->right = nullptr;
        delete currentNode;
        return;
    }
    
    //Remove check part 3 - node with one child
    if((currentNode->left == nullptr && currentNode->right != nullptr) || (currentNode->left != nullptr && currentNode->right == nullptr)){
        
        //If the right leaf is present and not the left leaf
        if(currentNode->left == nullptr && currentNode->right != nullptr)
        {
            //If parent's left tree is equal to currentNode
            if(parent->left == currentNode)
            {
                //parent's left tree becomes right currentNode and delete the currentNode
                parent->left = currentNode->right;
                delete currentNode;
            }
            //If parent's right tree is equal to currentNode
            else
            {
                //parent's right tree becomes right currentNode and delete the currentNode
                parent->right = currentNode->right;
                delete currentNode;
            }
        }
        //Left leaf is present and not the right leaf
        else
        {
            if(parent->left == currentNode)
            {
                parent->left = currentNode->left;
                delete currentNode;
            }
            else
            {
                parent->right = currentNode->left;
                delete currentNode;
            }
        }
        return;
    }
    //Remove check part 4 - node with two children
    else
    {
        if(currentNode->left && currentNode->right)
        {
            //Set the succesor of the Node as the minimum value in right subtree
            Node *succesor = minNode(currentNode->right);
            string value = succesor->data;
            //delete the successor
            removeHelper(root, succesor->data);
            currentNode->data = value;
        }
    }
}

//Removes a word from the tree
void BinarySearchTree::remove(string word)
{
    removeHelper(root, word);
}

//Checks if a word is in the tree
bool BinarySearchTree::exists(string word) const
{
    Node* temp = root;
    while(temp != nullptr)
    {
        if(temp->data == word)
        {
            return true;
        }
        else
        {
            if(word > temp->data)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }
    }
    return false;
}

void inorderHelper(Node* root, string *word)
{
    if(root->left != nullptr)
    {
        inorderHelper(root->left, word);
    }
    *word += root->data +" ";
    if(root->right != nullptr)
    {
        inorderHelper(root->right, word);
    }
}

// Prints the tree to standard out in numerical order
std::string BinarySearchTree::inorder() const
{
    
    string word = "";
    
    if(root == nullptr)
    {
        return word;
    }
    
    inorderHelper(root, &word);
    
    return std::string(word.substr(0,word.length()-1));;
}

void preHelper(Node *root, string *word)
{
   *word += root->data +" ";
    if(root->left != nullptr)
    {
        preHelper(root->left, word);
    }
   
    if(root->right != nullptr)
    {
        preHelper(root->right, word);
    }
}

// Prints the tree in pre-order
std::string BinarySearchTree::preorder() const
{
    string word = "";
    if(root == nullptr)
    {
        return word;
    }
    preHelper(root, &word);
    return std::string(word.substr(0,word.length()-1));;
}

void postHelper(Node *root, string *word){
    if(root->left != nullptr)
    {
        postHelper(root->left, word);
    }
    
    if(root->right != nullptr)
    {
        postHelper(root->right, word);
    }
     *word += root->data +" ";
}

// Prints the tree in post-order
std::string BinarySearchTree::postorder() const
{
    string word = "";
    if(root == nullptr)
    {
        return word;
    }
    postHelper(root, &word);
    return std::string(word.substr(0,word.length()-1));;
}

bool isEqual(const Node* tree1, const Node* tree2)
{
    
    if((tree1 != nullptr && tree2 != nullptr) && (tree1->data == tree2->data))
    {
        return true;
    }
    if((tree1 == nullptr)|| (tree2 == nullptr))
    {
        return false;
    }
       
       return ((tree1->data == tree2->data) && isEqual(tree1->left, tree2->right) && isEqual(tree1->left, tree2->right));
}

// Checks if two trees are equal
bool BinarySearchTree::operator==(const BinarySearchTree &other) const
{
    if(root == nullptr && other.root == nullptr)
    return true;
    else
        return isEqual(root, other.root);
}

// Checks if two trees are not equal
bool BinarySearchTree::operator!=(const BinarySearchTree &other) const
{
    if((root == nullptr && other.root != nullptr) || (root != nullptr && other.root == nullptr))
    return true;
    else
        return !(*this == other);
}


// Reads in words from an input stream into the tree
std::istream& operator>>(std::istream &in, BinarySearchTree &tree)
{
    string temp;
    
    while (in >> temp)
    {
    //Transform every words to lowercase
    transform(temp.begin(),temp.end(),temp.begin(), ::tolower);
    //Insert words in the tree
    tree.insert(temp);
    }
    return in;
}

// Writes the words, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const BinarySearchTree &tree)
{
    out << tree.inorder();
    return out;
}
