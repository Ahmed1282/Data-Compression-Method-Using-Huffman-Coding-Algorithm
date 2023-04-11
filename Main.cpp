/* Project File - Data Structures (Section C) Spring 2022
*  Created by Naufil Moten (20I-0642) & Ahmed Baig (20I-1884)
*  This Code compresses a string from a file using Huffman Optimal Coding
*  It has 3 classes: Node, Tree, Priority Queue and a Main
*  All of the coding is in the same file
*/

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

// Global Variable to find the total length of a string

int compress = 0; // total length of COMPRESSED string taken from file
int uncompress = 0; // total length of UNCOMPRESSED string taken from file

// Node Class

struct Node
{
    // Used for Tree
    Node* left;
    Node* right;

    //For Priority Queue
    Node* next;


    char ch; // stores Character in a node
    int freq; // stores Frequency of a Character
    string code; // stores Binary Code of a Character 
    int codelen; // stores Length of the Binary Code

    //Tree Traversal
    void preorder(struct Node* node)
    {
        if (node != NULL)
        {
            //cout << "  " << node->ch << endl;
            cout << "  " << node->ch << " " << node->freq << endl;
            preorder(node->left);
            preorder(node->right);
        }
    }

    // Traverse the tree to generate binary code, code length and total length of a compressed (Huffman) file
    void traversalbinary(struct Node* root, string todu) { // Todu is an empty string passed

        if (root->left == NULL && root->right == NULL)
        {
            root->code = todu; // saves binary code
            root->codelen = todu.length(); // finds binary code length and saves
            compress += root->codelen; // adds total length
            cout << "   " << root->ch << "\t\t" << root->code << "\t\t    " << root->codelen << endl;
            return;
        }

        if (root->left != NULL)
        {
            traversalbinary(root->left, todu + "0");
        }

        if (root->right != NULL)
        {
            traversalbinary(root->right, todu + "1");
        }
    }

    // Traverse the tree to generate binary code, code length and total length of a Uncompressed (Normal) file
    void traversalbinarynew(struct Node* root, string todu) {

        if (root->left == NULL && root->right == NULL)
        {
            root->code = todu;
            root->codelen = todu.length();
            uncompress += root->codelen;
            cout << "   " << root->ch << "\t\t" << root->code << "\t\t    " << root->codelen << endl;
            return;
        }

        if (root->left != NULL)
        {
            traversalbinarynew(root->left, todu + "0");
        }

        if (root->right != NULL)
        {
            traversalbinarynew(root->right, todu + "1");
        }
    }

    // Finding BitRate of each node and then adding/returning it to the total Bit Rate of the string
    int* BitRate(Node* root) {

        static int totalbitrate = 0;

        if (root->left == NULL && root->right == NULL)
        {
            totalbitrate = totalbitrate + ((root->freq) * (root->codelen));

            return &totalbitrate;
        }

        if (root->left != NULL) BitRate(root->left);
        if (root->right != NULL) BitRate(root->right);

    }

    // Finding Average Bit Rate by dividing Length of File by Total Bit Rate of Characters
    float avgBitRate(int* TotalBitrate, int length) {

        float abr = static_cast<float>(*TotalBitrate) / static_cast<float>(length); // Finds Average Bit Rate
        cout << "Average Bit Rate of File: " << abr << endl;
        return abr;
    }

    // Finding Compression Ratio by Using Optimal Huffman Code
    float compressionRatio(float abr1, float abr2) {

        float ratio = abr1 / abr2;
        cout << "\n\n|-------------------FINAL RESULT-----------------------|" << endl;
        cout << "\nCompression Ratio using optimal Huffman Code is: " << ratio << endl;
        return ratio;
    }
};


// Tree class
class Tree
{
public:

    Node* root;

    Tree() // Constructor
    {
        root = NULL;
    }

    // Insertion Code to insert Characters to a Normal Tree. This simple add characters to leaf nodes without huffman code
    void insert(char chr, Node* currNode, int f) // currNode is Current Node
    {
        //New Node and storing all the relevant data
        Node* newNode = new Node;
        newNode->ch = chr;
        newNode->freq = f;
        newNode->left = newNode->right = NULL;

        //Temporary Nodes
        Node* temp1 = new Node;
        Node* temp2 = new Node;

        if (currNode == NULL) //If Current Node is Empty
        {
            temp1->left = newNode;
            temp1->right = NULL;
            root = currNode = temp1;
        }

        else if (currNode->right == NULL) //If Right of Current Node is Empty
        {
            currNode->right = newNode;
            root = currNode;
        }
        else if (currNode->left == NULL) //If Left of Current Node is Empty
        {
            currNode->left = newNode;
            root = currNode;
        }
        else if (currNode->right != NULL && currNode->left != NULL) //If Both Left and Right are not Empty
        {
            temp1->left = currNode;
            temp1->right = newNode;
            temp2 = temp1;

            temp1 = currNode;
            currNode = temp2;

            root = currNode;
        }
    }

    // Displays all the nodes of a tree
    void show(Node* root)
    {
        cout << root->ch << endl;
        if (root->left != NULL)
        {
            cout << "The Left  child of " << root->ch << " is :\t ";
            show(root->left);

        }
        if (root->right != NULL)
        {
            cout << "The Right child of " << root->ch << " is :\t ";
            show(root->right);

        }
    }

};

// Priority Queue Class
class Priority_Queue
{
public:
    Node* head;

    Priority_Queue()
    {
        head = NULL;
    }

    //Add to Queue
    void enqueue(Node* newNode)
    {

        Node* temp;

        if (head == NULL || newNode->freq < head->freq) // Enquening on the basis of frequency
        {
            newNode->next = head;
            head = newNode;
        }

        else
        {
            temp = head;

            while (temp->next != NULL && temp->next->freq <= newNode->freq) // Traversing the queue until suitable node is found
                temp = temp->next;

            newNode->next = temp->next;
            temp->next = newNode;
        }

    }

    //Remove from Queue
    Node* dequeue()
    {
        Node* ptr;
        ptr = head;

        if (head == NULL)
            cout << "Queue is empty\n";
        else
        {
            head = ptr->next;
        }

        return ptr;
    }

    //Remove from Queue
    bool isEmpty() {

        if (head == NULL) return true;
        else return false;
    }
};


// Function to perform Huffman Coding on the basis of Priority Queue
Node* huffmanCode(Priority_Queue PQ) {


    Node* min1 = new Node;
    Node* min2 = new Node;

    while (!PQ.isEmpty()) {

        min1 = PQ.dequeue();

        if (PQ.isEmpty())    break;

        min2 = PQ.dequeue();

        // Showing the 2 minimum nodes getting picked
        // cout << "Minimum 1 Picked " << min1->ch << " " << min1->freq << "\n Minimum 2 Picked " << min2->ch << " " << min2->freq << endl;

        Node* parent = new Node;
        parent->freq = min1->freq + min2->freq; // Adding frequences of 2 minimum nodes to a parent node
        parent->ch = '~';
        if (min1 > min2) {
            parent->left = min2;
            parent->right = min1;
            parent->next = NULL;
        }
        else {
            parent->left = min1;
            parent->right = min2;
            parent->next = NULL;
        }
        PQ.enqueue(parent); // Adding parent node back to queue

    }

    return min1;
}


int main()
{
    Priority_Queue Q; //Declaring Priority Queue

    string str, str2, str3, str4;
    /*
    Str reads string from the file
    Str3 makes a copy of Str1 which will be used later, and to save orignal copy
    Str2 saves a string without duplications
    Str4 used to insert the character in a tree
    */

    char c;
    fstream in; // File Reading Object

    Node* huffmanTreeHead = new Node; // Huffman Tree Intializer

    Tree obj; // Tree Object

    string filename;

    cout << "\n*************Welcome to the Optimal Huffman Coding Program*************\n";

    cout << "\n\n - Enter The File Name you want to Read From: ";
    cin >> filename;

    in.open(filename); // Opening the File

    if (!in)
    {
        cout << "File could not open\n";
    }
    while (!in.eof()) // Reading till end of the file
    {
        c = in.get();
        if (in.eof()) break;
        str += c;
    }

    in.close();

    cout << "\nString Read from the file: " << str << endl;

    int length = size(str); // Calculating length of the string

    for (int i = 0; i < length; i++) { // Making a copy of orignal string
        str3 += str[i];
    }

    // This Loop is removing duplicates from the String
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (str[i] == str[j])
            {
                str[j] = '~';
            }
        }
    }

    // This Loop is also helping rearranging the string after removing duplication
    for (int i = 0; i < length; i++) {
        if (str[i] != '~') {
            str2 += str[i];
        }
    }

    cout << "\n.......Duplication Removed & Frequency Calculated";
    //cout << "\nString After Removing Duplcation: " << str2 << endl;

    int length2 = size(str2); // Length of Unduplicated String

    for (int i = 0; i < length2; i++) { // Making a copy of this string
        str4 += str2[i];
    }

    int* frequency;
    frequency = new int[length2]; // Making an dymanic array to store frequencies

    for (int i = 0; i < length2; i++) {
        frequency[i] = 0;
    }

    // Loop to store the no. of frequencies of each character in the file
    for (int i = 0; i < length2; i++) {
        for (int j = 0; j < length; j++) {
            if (str2[i] == str3[j]) {
                frequency[i]++;
            }
        }
    }

    // Displaying Frequences
    cout << "\n\nCharacter\tFrequencies" << endl;
    for (int i = 0; i < length2; i++) {
        cout << "\n    " << str2[i] << "\t\t    " << frequency[i];
    }

    // Creating a normal tree out of a string
    cout << "\n\nInserting Characters to Tree......." << endl;
    for (int i = 0; i < length2; i++) {
        obj.insert(str4[i], obj.root, frequency[i]);
    }
    
    // Displaying Tree = is garbage value
    obj.show(obj.root);

    cout << "\n\nBinary Codes for Simple Code Tree.....Done";
    cout << "\n\nCharacter\tBinary Code\tCode Length\n" << endl;
    obj.root->traversalbinarynew(obj.root, "");


    // Huffman Coding Begins here
    // String is now being insert into Priority Queue
    for (int i = 0; i < length2; i++)
    {
        //New Node to Insert in Queue
        Node* temp = new Node;
        temp->freq = frequency[i]; // Frequency
        temp->ch = str2[i]; // Character
        temp->left = temp->right = temp->next = NULL;

        //Enqueue
        Q.enqueue(temp);
    }

    //Calling Huffman Code
    huffmanTreeHead = huffmanCode(Q);

    cout << endl << "\n\nHUFFMAN Tree (Traversing in PreOrder, ~ is garbage)" << endl;
    huffmanTreeHead->preorder(huffmanTreeHead);

    cout << "\n\nBinary Codes for Optimal Huffman Tree.....Generation Done" << endl;
    cout << "\nCharacter\tBinary Code\tCode Length\n" << endl;
    huffmanTreeHead->traversalbinary(huffmanTreeHead, "");

    //---------------------------------------

    cout << "\nTotal Uncompressed Length of the string: " << uncompress << endl;

    // Finding Cumulative Bit Rate of (Original String) through a bitrate Function
    int* totalbitrate1 = obj.root->BitRate(obj.root);
    int* tree1bitrate = totalbitrate1;
    cout << "Cumulative Bit Rate of Original String is: " << *tree1bitrate << endl;

    // Finding Average Bit Rate of (Original String) by Dividing it by Length of String
    float abruncomp = obj.root->avgBitRate(tree1bitrate, uncompress);

    *totalbitrate1 = 0; // Total Bit Rate is reset to 0 since we are using function again.

    cout << endl << "Total Compressed Length of the String: " << compress << endl;

    // Finding Cumulative Bit Rate of (Compressed String) through a bitrate Function
    int* totalbitrate2 = huffmanTreeHead->BitRate(huffmanTreeHead);
    cout << "Cumulative Bit Rate of Compressed String is: " << *totalbitrate2 << endl;


    // Finding Average Bit Rate of (Compressed String) by Dividing it by Length of String
    float abrcomp = huffmanTreeHead->avgBitRate(totalbitrate2, compress);

    // Finding Compression Ratio by Comparing Average Bit Rates of Both the Files
    huffmanTreeHead->compressionRatio(abruncomp, abrcomp);

    cout << "\n\nThankyou For Using this Program..... made by Naufil Moten & Ahmed Baig" << endl;

    return 0;
}