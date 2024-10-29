#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "Huffman_input.txt"
#define MAX_TREE_HT 100
#define CHAR_SET_SIZE 256

// 빈도수를 저장하는 배열
int frequency[CHAR_SET_SIZE] = {0};

// 노드 구조 정의
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// 최소 힙 구조 정의
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
};

// 새 노드 생성
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// 최소 힙 생성
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// 두 노드 간 빈도 비교
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// 최소 힙 재정렬
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 최소 힙에서 최저 빈도 노드 추출
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// 최소 힙 삽입
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// 단일 노드인지 확인
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// 최소 힙 초기화
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 2) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

// 허프만 트리 구축
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// Huffman 코드를 저장하여 형식에 맞게 출력하는 함수
void printCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        printf("'%c' = ", root->data);
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// Huffman 코드 생성 및 출력
void HuffmanCodes(char data[], int freq[], int size) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}

// 파일에서 빈도수 계산
void calculateFrequency(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("파일을 열 수 없습니다.");
        exit(1);
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        frequency[(unsigned char)ch]++;
    }

    fclose(file);
}

// 압축 해제 함수
void decodeHuffman(struct MinHeapNode* root, const char* encodedStr) {
    struct MinHeapNode* current = root;
    printf("Decoded String: ");
    for (int i = 0; encodedStr[i] != '\0'; i++) {
        if (encodedStr[i] == '0')
            current = current->left;
        else
            current = current->right;

        if (!current->left && !current->right) {
            printf("%c", current->data);
            current = root;
        }
    }
    printf("\n");
}

int main() {
    // 파일에서 빈도수 계산
    calculateFrequency(FILENAME);

    // 빈도수가 0이 아닌 문자만을 포함하는 데이터 배열과 빈도수 배열을 동적으로 생성
    int unique_char_count = 0;
    for (int i = 0; i < CHAR_SET_SIZE; i++) {
        if (frequency[i] > 0)
            unique_char_count++;
    }

    char *data = (char*)malloc(unique_char_count * sizeof(char));
    int *freq = (int*)malloc(unique_char_count * sizeof(int));
    int index = 0;
    for (int i = 0; i < CHAR_SET_SIZE; i++) {
        if (frequency[i] > 0) {
            data[index] = i;
            freq[index] = frequency[i];
            index++;
        }
    }

    // 빈도수 출력
    printf("문자 빈도수:\n");
    for (int i = 0; i < unique_char_count; i++) {
        printf("%c: %d\n", data[i], freq[i]);
    }

    // Huffman 코드 생성
    printf("\nHuffman Codes:\n");
    HuffmanCodes(data, freq, unique_char_count);

    // 압축 해제 예제
    const char* encodedStr = "10110010001110101010100";
    printf("\n압축 해제:\n");
    decodeHuffman(root, encodedStr);

    // 동적 메모리 해제
    free(data);
    free(freq);

    return 0;
}
