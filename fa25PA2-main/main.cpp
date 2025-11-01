//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)

    ///NOTE: assuming each char is only in leaf

    // if empty, return -1, invalid input
    if(nextFree <= 0) return -1;

    MinHeap heap;

    ///NOTE: nextFree is ammount of leaf nodes, currently. will be used to count total nodes
    // adds/push ammount of leaf nodes into heap
    for (int i = 0; i < nextFree; ++i) heap.push(i, weightArr);

    // pop if 1, just root
    if (heap.size == 1) return heap.pop(weightArr);

    while(heap.size > 1){
        //pops 2 smallest nodes
        int nodeOne = heap.pop(weightArr);  // smallest node
        int nodeTwo = heap.pop(weightArr);  // next smallest node

        //create new parent node, increment nextFree (due to adding new node)
        int parent  = nextFree;
        nextFree++; //TODO (Optional): maybe check for overflow if nextFree passes MAX_NODES, that should exist. note that createLeafNodes doesn't have a check.
        weightArr[parent] = weightArr[nodeOne] + weightArr[nodeTwo];

        //DONE: check proper say to set left/right pointers for parent
        ///NOTE: assuming left and right array are the "pointers" for parent
        ///      assuming parent spot won't be overriden
        //create left/right pointers from parent node
        leftArr[parent] = nodeOne;
        rightArr[parent] = nodeTwo;
        //charArr[parent]   = '\0'; // clear char at node

        //add new parent node to heap
        heap.push(parent,weightArr);
    }

    return heap.pop(weightArr); // returns last remaining node index in heap
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    //TODO: replace input.txt with "cybersecurity", once test with "banana" is done
    ///NOTE:yses "input.txt" in debug folder and NOT IN MAIN FOLDER
    ///     not clear what is defined as edge

    if (root <= 0) return; // nothing in tree

    // check for single node/only root
    if (leftArr[root] == -1 && rightArr[root] == -1) {
        //check if within char bounds
        if (charArr[root] >= 'a' && charArr[root] <= 'z') codes[charArr[root] - 'a'] = "0";
        return;
    }

    //load root into stack for while loop
    stack<pair<int, string>> stack;
    stack.push(make_pair(root, "")); // lets while loop run initially

    while (!stack.empty()) {
        //load next char to be processed from stack
        pair<int, string> topPair = stack.top(); // next node from stack
        stack.pop(); // remove from stack

        int node = topPair.first;
        string path = topPair.second;

        //children of node
        int left = leftArr[node];
        int right = rightArr[node];

        //set/check if leaf node
        //else check if single or double noded from parent
        if (left == -1 && right == -1) {
            //check if char within bounds
            if (charArr[node] >= 'a' && charArr[node] <= 'z'){
                codes[charArr[node] - 'a'] = path; // update code for char
                }
        } else {
            ///NOTE: left process first
            ///      load path with direction taken
            // check if node exists, pushes and adds bit, ammount depends on how deep leaf are
            if (right != -1) stack.push(make_pair(right, path + "1"));
            if (left != -1) stack.push(make_pair(left, path + "0"));
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}