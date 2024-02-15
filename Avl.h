#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<queue>

using namespace std;

class Node{ //Constructor for the node class, which stores a name, ufid, left, right, and height
    public:

        Node() : name(""), ufid(), left(nullptr), right(nullptr), height(0){} //default constructor

        Node(string name, string ufid, int height){ //constructor initalizes the creation of a new node
            this->name = name;
            this->ufid = ufid;
            this->height = height;
            left = nullptr;
            right = nullptr;
        }
        //Getters and Setters to establish modularity and protect values in the Node class
        string getufid(){
            return ufid;
        }
        string getName(){
            return name;
        }
        int getHeight(){
            return height;
        }
        Node* getRight(){
            return right;
        }
        Node* getLeft(){
            return left;
        }
        void setRight(Node* node){
            right = node;
        }
        void setLeft(Node* node){
            left = node;
        }
        void setufid(string id){
            ufid = id;
        }
        void setHeight(int x){
            height = x;
        }
        void setName(string x){
            name = x;
        }

        ~Node(){
        }

    private: //Node class attributes for an example node, height allows for faster calculations
        string name;
        string ufid;
        Node* left;
        Node* right;
        int height;

};



class Avl{

    public:
        

        int balanceFactor(Node* node){ //balance factor calculated by node left - node right. Inspired by the example given in lecture
            if(node == nullptr){
                return 0;
            }
            return getHeight(node->getLeft()) - getHeight(node->getRight());
        }


        void printLevelCount(){ //Prints the root height, as it measures the longest path of nodes within the tree, which is equal to the height of the root node
            if(root == nullptr){
                cout << 0 << endl;
                return;
            }
            cout << root->getHeight() << endl;
        }
      // Utilizes the inOrder() function as a helper function, to gain access to the list of all the nodes in order, where it can remove the specified node at the spot N
        void removeInorder(unsigned int x){
            idInOrder = getInNumber();
            if(idInOrder.empty() || idInOrder.size() <= x ){
                cout << "unsuccessful" << endl;
                return;
            }
            remove(idInOrder.at(x));
        }

        void insert(string name, string ufid){
            //Checks if valid name with quotes
            if(name[0] != '\"' || name[name.length()-1] != '\"'){
                cout << "unsuccessful" << endl;
                return;
            }
            //Checks if valid name with quotes and atleast one letter
            if(name.length() < 3){
                cout << "unsuccessful" << endl;
                return;
            }
            //Checks if valid id with 8 numbers
            if(ufid.length() > 8 ){
                cout << "unsuccessful" << endl;
                return;
            }
            //Checks if id is not already in the AVL tree by using the search function as a helper
            if(searchhelp(root,ufid) != nullptr){
                cout << "unsuccessful" << endl;
               return;
            }
            //Regex to establish a sequence of letters, capital and lowercase and space
            regex obj = regex(R"(^\"[A-Za-z\s]+\"$)");\
            //Regex to establish a sequence of 8 numbers from 0-9
            regex ob = regex("[0-9]{8,8}");
            //Checks if Regex is valid and calls the insert help
            if(regex_match(name,obj) && regex_match(ufid,ob)){
                this->root = InsertHelper(this->root, name, ufid, 1);
                cout << "successful" << endl;
                return;
            }

            cout << "unsuccessful" << endl;
        }

    //Checks if valid id that is in the tree
        void remove(string ufid){
            if(searchhelp(root, ufid) == nullptr ){
                cout << "unsuccessful"<<endl;
                return;
            }
            //Calls the remove function
            root = RemoveHelper(root, ufid);
            cout << "successful" <<endl;
        }

    //Travels through all nodes recursively to identify the node where the id resides, returns the name of that id
        void search(string ufid){
            Node* sol = searchhelp(root, ufid);
            if(sol == nullptr){ //verifies if the node is present first
                cout<< "unsuccessful" <<endl;
                return;
            }
            cout<< sol->getName() << endl;
        }

        //Breadth First Search function to traverse through the AVL tree and identify the node where name reside
        void searchName(string name) {
            bool found = false;
            queue<Node *> q; //stores the nodes in level by level case
            if(root == nullptr){
                cout << "unsuccessful" <<endl;
                return;
            }
            q.push(root);
            while(!q.empty()){
               Node* node = q.front();
               q.pop();

               if(node->getName() == name){ //checks if the name is the current node's name
                   cout << node->getufid() << endl;
                   found = true;
               } //if not, then traverses through to the node's children
               if(node->getLeft() != nullptr){
                   q.push(node->getLeft());
               }
               if( node->getRight() != nullptr){
                   q.push(node->getRight());
               }
            }
            if(!found){
                cout << "unsuccessful"<<endl;
            }
        }
    //Getter for the root node
        Node* getRoot(){
            return root;
        }
//Getter for the nodes in preorder, calls on the clear function clearing all of the saved nodes within the vectors that store the nodes in in order, post order, and pre order
        vector<string> getPreOrder(){
            clearhelper();
            PreOrder(root);
            return namesPreOrder;
        }
    //Getter for the nodes in Postorder, calls on the clear function clearing all of the saved nodes within the vectors that store the nodes in in order, post order, and pre order

    vector<string> getPostOrder(){
            clearhelper();
            PostOrder(root);
            return namesPostOrder;
        }
//Getter for the nodes in inorder, calls on the clear function clearing all of the saved nodes within the vectors that store the nodes in in order, post order, and pre order

        vector<string> getInOrder(){
            clearhelper();
            InOrder(root);
            return namesInOrder;
        }
    //Getter for the nodes in Inorder but ids instead of names, calls on the clear function clearing all of the saved nodes within the vectors that store the nodes in in order, post order, and pre order

    vector<string> getInNumber(){
            clearhelper();
            InOrder(root);
            return idInOrder;
        }

    //default constructor
        Avl() : root(nullptr){}

        private:
  //private attributes for the AVL class
        Node* root;
        vector<string> namesInOrder;
        vector<string> namesPostOrder;
        vector<string> namesPreOrder;
        vector<string> idInOrder;

        //Helper function for removal of nodes, help given by the starter video by Andrew Penton https://youtu.be/BjH_Pdu_2W4
        Node* RemoveHelper(Node* node, string ufid){
            if(node == nullptr) { //if the recursion has reached the bottom, traverse back to the top
                return node;
            }
            if(node->getufid() > ufid) { // if the current root is greater than ufid, then traverse to left node
                node->setLeft(RemoveHelper(node->getLeft(), ufid))  ;
            }
            else if(node->getufid() < ufid) { // if the current root is less than ufid, then traverse to right node
                node->setRight(RemoveHelper(node->getRight(), ufid));
            }
            else{
                if(node->getLeft() == nullptr || node->getRight() == nullptr){ //Checks if node doesn't have two children to become the successor
                    Node* temp = (node->getLeft()) ? node->getLeft() : node->getRight(); //Learned Ternary operators from GeeksForGeeks https://www.geeksforgeeks.org/conditional-or-ternary-operator-in-c/
                    if(temp == nullptr){
                        temp = node;
                        node = nullptr;
                    }
                    else{
                        *node = *temp;
                    }

                    delete temp;
                }
                else{ // if the root has two children, find in order successor to replace it
                    Node* temp = inOrderSuccessor(node->getRight());
                    node->setufid(temp->getufid());
                    node->setName(temp->getName());
                    node->setRight(RemoveHelper(node->getRight(), temp->getufid())) ;
                }

            }
            if(node == nullptr){ // if the node is nullptr after deletion, return the node
                return node;
            } //else, set the height of the new node and update all nodes that the function has traversed through
            node->setHeight(1 + max(getHeight(node->getLeft()), getHeight(node->getRight())));
            return node;
        }
    //Helper function for finding in order succcessor, concept provided by AbdulBari on youtube https://www.youtube.com/watch?v=jDM6_TnYIqE
        Node* inOrderSuccessor(Node* node) {
            Node* temp = node; //traverse to the right node of the node for deletion, then traverse to the left most node.
            while (temp && temp->getLeft() != nullptr) {
            temp = temp->getLeft();
        }
        return temp;
    }
    //Insertion helper function, help provided by the starter video by Andrew Penton https://youtu.be/BjH_Pdu_2W4
        Node* InsertHelper(Node* node, string name, string ufid, int height){ //The insertion function
            
            if(node == nullptr){ //checking if the end of the tree is reached
                return new Node(name.substr(1,name.length()-2), ufid, height);
            }
            else if(ufid < node->getufid()){
                node->setLeft(InsertHelper(node->getLeft(), name, ufid, height++)); //checking if key is greater than node to be put on the left
            }
            else if (ufid > node->getufid()){
                node->setRight(InsertHelper(node->getRight(), name, ufid, height++)); //checking if key is greater than node to be put on the right
            }
            else{
                return node; //checking for duplicate keys
            }
            node->setHeight(1 + max(getHeight(node->getLeft()), getHeight(node->getRight()))) ;
            int balance = balanceFactor(node);

            //check if the right node is right heavy for L rotation
            if(balance < -1 && ufid > node->getRight()->getufid()){
                return rotateLeft(node);
            }
             //check if the left node is left heavy for R rotation
            if( balance > 1 && ufid < node->getLeft()->getufid()){
                return rotateRight(node);
            }
            //check if the left node is right heavy for  LR rotation
            if(balance > 1 && ufid > node->getLeft()->getufid()){
               return rotateLeftRight(node);
            }
            //check if the right node is left heavy for  RL rotation
            if(balance < -1 && ufid < node->getRight()->getufid()){
               return rotateRightLeft(node);
            }
            return node;
        }

        //Helper Function for searching through AVL tree
        Node* searchhelp(Node* node, string ufid){
                if(node == nullptr) {
                    return nullptr;
                } //Traverse through tree recursively
                if (ufid == node->getufid()) { //return the node if the id is found
                    return node;
                } else if(node->getufid() > ufid) { //travel to the left node if the id is less than the current node's id
                   return searchhelp(node->getLeft(), ufid);
                } else if(node->getufid() < ufid) {//travel to the right node if the id is greater than the current node's id
                    return searchhelp(node->getRight(), ufid);
                }
                return nullptr;
        }

            //rotate left function
        Node* rotateLeft(Node *node){
            if(node == nullptr || node->getRight() == nullptr){
                return node;
            }
            //Store the right node as parent.
            Node* temp = node ->getRight();
            //Store new parent node
            node->setRight(temp->getLeft());
            //Make original parent the parent of the left child of new parent
            temp->setLeft(node) ;
            node->setHeight(1 + max(getHeight(node->getLeft()), getHeight(node->getRight()))) ;
            temp->setHeight(1 + max(getHeight(temp->getLeft()), getHeight(temp->getRight())));
            return temp;
        }

         //rotate right function
        Node* rotateRight(Node *node){
    
            if(node == nullptr || node->getLeft() == nullptr){
                return node;
            }
            Node* temp = node ->getLeft();
            //store the left node as parent
            node->setLeft(temp->getRight());
            //Make original parent the parent of the right child of new parent
            temp->setRight(node);
            //Make the new parent's child the old parent
            node->setHeight(1 + max(getHeight(node->getLeft()), getHeight(node->getRight())));
            temp->setHeight(1 + max(getHeight(temp->getLeft()), getHeight(temp->getRight()))) ;
            return temp;
        }

    //rotate left right function
        Node* rotateLeftRight(Node* node){
                    
            if(node == nullptr){//Check Root node availability
                return node;
            }
            node->setLeft(rotateLeft(node->getLeft())); //Rotate bottom Left

            return rotateRight(node); //Rotate Right
        }

    //rotate right left function
        Node* rotateRightLeft(Node* node){
            if(node == nullptr){//Check Root node availability
                // return node;
            }
            node->setRight(rotateRight(node->getRight())) ; //Rotate Right to bottom
            return rotateLeft(node); //Rotate Left
        }
    //returns the height of the node by getting the private value height
        int getHeight(Node* node){
            if(node == nullptr){
                return 0;
            }
            return node->getHeight();
        }
    //rotate helper function for traversing the tree in order
        void InOrder(Node* node){
            if(node == nullptr){
                return;
        }
            //Travel to the left Node, the root node, and Right Node
            InOrder(node->getLeft());
            namesInOrder.push_back(node->getName());
            idInOrder.push_back(node->getufid());
            InOrder(node->getRight());
        }

    //rotate helper function for traversing the tree post order
        void PostOrder(Node* node){
            if(node == nullptr){
                return;
        }
            //Travel to the left Node, the right node, and root Node
            PostOrder(node->getLeft());
            PostOrder(node->getRight());
            namesPostOrder.push_back(node->getName());
        }

    //rotate helper function for traversing the tree pre order
        void PreOrder(Node* node){
            if(node != nullptr){
                //Travel to the root Node, the left node, and right Node
                namesPreOrder.push_back(node->getName());
                PreOrder(node->getLeft());
                PreOrder(node->getRight());
            }

        }
    //clear the vectors that are stored
    void clearhelper(){
        namesInOrder.clear();
        namesPostOrder.clear();
        namesPreOrder.clear();
        idInOrder.clear();
        }
    };

