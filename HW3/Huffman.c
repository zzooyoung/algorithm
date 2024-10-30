#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "Huffman_input.txt"
#define MAX_TREE_HT 100
#define CHAR_SET_SIZE 256

// 빈도수를 저장하는 배열
int frequency[CHAR_SET_SIZE] = {0};

// 허프만 코드를 저장할 문자열 배열
char codeA[MAX_TREE_HT] = "";
char codeT[MAX_TREE_HT] = "";
char codeG[MAX_TREE_HT] = "";
char codeC[MAX_TREE_HT] = "";

// 구조체 정의: 허프만 트리의 노드
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// 노드 생성 함수
struct MinHeapNode* createNode(char data, unsigned freq) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

// 파일에서 빈도수 계산
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

// 최소 힙 구조체
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
};

// 최소 힙 생성 함수
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// 두 노드 교환 함수
void swapNodes(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

// 최소 힙 유지 함수
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

// 최소 노드 추출 함수
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// 노드 삽입 함수
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* node) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// 단일 노드 확인 함수
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// 최소 힙 생성 및 초기화 함수
struct MinHeap* buildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], freq[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 2) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

// 허프만 트리 구축 함수
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

// Huffman 코드를 저장하는 함수
void storeCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1);
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

// Huffman 코드 생성 함수
void generateHuffmanCodes(struct MinHeapNode* root) {
    int arr[MAX_TREE_HT], top = 0;
    storeCodes(root, arr, top);
}

int main() {
    // Calculate character frequencies
    calculateFrequency(FILENAME);

    // Create arrays for characters and their frequencies
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

    // Generate Huffman Codes for specific characters
    generateHuffmanCodes(root);

    // Print the Huffman codes in the specified format
    printf("Huffman code (‘A’ = %s, ‘T’ = %s, ‘G’ = %s, ‘C’ = %s)\n", codeA, codeT, codeG, codeC);

    return 0;
}
