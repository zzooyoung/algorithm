#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TREE_HT 100
#define CHAR_SET_SIZE 256

// to save frequency
int frequency[CHAR_SET_SIZE] = {0};

// to save huffman code
char codeA[MAX_TREE_HT] = "";
char codeT[MAX_TREE_HT] = "";
char codeG[MAX_TREE_HT] = "";
char codeC[MAX_TREE_HT] = "";

// Huffman Tree Node
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};


struct MinHeapNode* createNode(char data, unsigned freq) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

// calculataion frequency
void calculateFrequency(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Cannot open file");
        exit(1);
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        frequency[(unsigned char)ch]++;
    }

    fclose(file);
}


struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
};


struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Swap
void swapNodes(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}


void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// min Heap Node
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* node) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// MinHeap Func
struct MinHeap* buildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], freq[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 2) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

// Build Tree
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = buildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = createNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void saveCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        saveCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        saveCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        char code[MAX_TREE_HT];
        for (int i = 0; i < top; i++)
            code[i] = arr[i] + '0';
        code[top] = '\0';

        // Save codes for specific characters
        if (root->data == 'A')
            strcpy(codeA, code);
        else if (root->data == 'T')
            strcpy(codeT, code);
        else if (root->data == 'G')
            strcpy(codeG, code);
        else if (root->data == 'C')
            strcpy(codeC, code);
    }
}

// generate huffmancodes
void generateHuffmanCodes(struct MinHeapNode* root) {
    int arr[MAX_TREE_HT], top = 0;
    saveCodes(root, arr, top);
}

int main() {

    // start time
    clock_t start = clock();

    // Calculate character frequencies
    calculateFrequency("Huffman_input.txt");

    // Create arrays for characters, frequencies
    char data[CHAR_SET_SIZE];
    int freq[CHAR_SET_SIZE];
    int index = 0;

    for (int i = 0; i < CHAR_SET_SIZE; i++) {
        if (frequency[i] > 0) {
            data[index] = i;
            freq[index] = frequency[i];
            index++;
        }
    }

    // Build Huffman Tree
    struct MinHeapNode* root = buildHuffmanTree(data, freq, index);

    // Generate Huffman Codes 
    generateHuffmanCodes(root);

    // Print the Huffman codes in the specified format
    printf("Huffman code (‘A’ = %s, ‘T’ = %s, ‘G’ = %s, ‘C’ = %s)\n", codeA, codeT, codeG, codeC);
    
    
    // print execution time 
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_spent);


    return 0;
}
