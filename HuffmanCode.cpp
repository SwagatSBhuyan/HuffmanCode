#include <bits/stdc++.h>

using namespace std;

#define MAX 10
#define TRIALS 3

class CharcTreeNode
{ 
    public:
        char ch;
        unsigned freq; 
        CharcTreeNode *left, *right;
        CharcTreeNode(char ch, unsigned freq) 
        {  
            left = right = NULL; 
            this->ch = ch; 
            this->freq = freq; 
        } 
};

class CmpCharcNodes 
{ 
    public: 
        bool operator()(CharcTreeNode* a, CharcTreeNode* b) 
        { return a->freq > b->freq; } 
}; 


//Given Algorithm to Generate Huffman Encoding Tree
CharcTreeNode* HuffmanTree(priority_queue<CharcTreeNode*, vector<CharcTreeNode*>, CmpCharcNodes> PriorityHuffmanQ)
{
    while (PriorityHuffmanQ.size() != 1) 
    { 
        //EXTRACT-MIN(Q)
        CharcTreeNode* left = PriorityHuffmanQ.top(); 
        PriorityHuffmanQ.pop(); 
        //EXTRACT-MIN(Q)
        CharcTreeNode* right = PriorityHuffmanQ.top(); 
        PriorityHuffmanQ.pop(); 

        //Creating new Charc node 'z' and inserting to PriorityHuffmanQueue
        CharcTreeNode* z = new CharcTreeNode('.', left->freq + right->freq); 
        z->left = left; 
        z->right = right; 

        PriorityHuffmanQ.push(z); 
    } 
  
    //Returning Last node left in PriorityQueue, root of HuffmanTree
    return PriorityHuffmanQ.top();    
} 


void DisplayHuffmanCodes(CharcTreeNode* root, int freq[], int arr[], int top) 
{ 
    // Assigning 0 to the left node
    if (root->left) 
    { 
        arr[top] = 0; 
        DisplayHuffmanCodes(root->left, freq, arr, top + 1); 
    } 
  
    // Assigning 1 to the right node
    if (root->right) 
    { 
        arr[top] = 1; 
        DisplayHuffmanCodes(root->right, freq, arr, top + 1); 
    } 
  
    //Leaf Node Printing
    if (!root->left && !root->right) 
    { 
        cout << root->ch << " "; 
        for (int i = 0; i < top; i++)  
            cout << arr[i]; 
        cout << "\n"; 
    } 
} 


void Huffman(char ch[], int freq[], int size) 
{ 
    //Initializing Huffman Min-Priority Queue with CharcTreeNodes using STL
    priority_queue<CharcTreeNode*, vector<CharcTreeNode*>, CmpCharcNodes> PriorityHuffmanQ; 
    for (int i = 0; i < size; i++)
    { 
        CharcTreeNode* newNode = new CharcTreeNode(ch[i], freq[i]); 
        PriorityHuffmanQ.push(newNode); 
    } 

    //Generating HuffmanTree
    CharcTreeNode* root = HuffmanTree(PriorityHuffmanQ); 
  
    //Displaying Huffman Codes 
    int arr[100], top = 0;    
    cout << "\nRequired Huffman Codes:\n";
    DisplayHuffmanCodes(root, freq, arr, top); 
} 
  
string GetRandomString(char ch[], int n, int size) 
{ 
    string res = ""; 
    for (int i = 0; i < n; i++)  
        res = res + ch[rand() % size]; 
     
    return res; 
} 

void FrequencyFinder(int freq[], string txt)
{ 
    int n = txt.size(); 
    for (int i = 0; i < n; i++) freq[txt[i] - 'a']++; 
    for (int i = 0; i < n; i++) { 
        if (freq[txt[i] - 'a'] != 0) { 
            cout << txt[i] << ": " << freq[txt[i] - 'a'] << "\n"; freq[txt[i] - 'a'] = 0; } 
    } 
}

int main() 
{ 
    //To randomize seed
    srand(time(NULL)); 
    char ch[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'}; 
    int size = sizeof(ch) / sizeof(ch[0]), mulx = 100; 
    int freq[10] = {0};
    int T = TRIALS;

    while (T--)
    {
        cout << "\n\nTEXT-" << 3-T;
        string txt = GetRandomString(ch, mulx, size);
        cout << "\nRandomly Generated String: \n" << txt;       
        cout << "\nFrequencies of characters in generated text: \n";
        int a = 0, b;
        while (txt[a]!='\0')
        {
            if (txt[a] >= 'a' && txt[a] <= 'z')
            {
                b = txt[a] - 'a';
                ++freq[b];
            }
            ++a;
        }
        for (int i = 0; i < 10; i++)
        {
            cout << ch[i] << ": " << freq[i] << "\n";
        }

        Huffman(ch, freq, 10); 
        mulx *= 10;
    }
    return 0; 
} 