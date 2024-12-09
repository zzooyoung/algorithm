/*
    File Name : BinPacking.c
    Description : 강의 노트 Chapter 8-1, 32p에 정의된 C=10, 물건의 크기 = [7, 5, 6, 4, 2, 3, 7, 5]
    input: input.txt
    output1: First Fit에 의한 결과
    output2: Next Fit에 의한 결과
    output3: Best Fit에 의한 결과
    output4: Worst Fit에 의한 결과
*/


#include <stdio.h>

#define MAX_BINS 100  
#define MAX_ITEMS 100 

// Print Bin's content
void printBins(int bins[MAX_BINS][MAX_ITEMS], int binCount, int binSizes[MAX_BINS]) {
    for (int i = 0; i < binCount; i++) {
        printf("bin%d = [", i + 1);
        int first = 1;
        for (int j = 0; j < binSizes[i]; j++) {
            if (first) {
                printf("%d", bins[i][j]);
                first = 0;
            } else {
                printf(", %d", bins[i][j]);
            }
        }
        printf("]\n");
    }
}

// First Fit Func
void firstFit(int items[], int itemCount, int binCapacity) {
    int bins[MAX_BINS][MAX_ITEMS] = {0}; // Each Bin's Item
    int binSizes[MAX_BINS] = {0};
    int binCount = 0;  // amount of Bin
    
    for (int i = 0; i < itemCount; i++) {
        int placed = 0;
        
        for (int j = 0; j < binCount; j++) {
            int binLoad = 0;
            // Calulating
            for (int k = 0; k < binSizes[j]; k++) {
                binLoad += bins[j][k];
            }
            if (binLoad + items[i] <= binCapacity) {
                bins[j][binSizes[j]] = items[i];  // Put Item
                binSizes[j]++;
                placed = 1;
                break;
            }
        }
        
        if (!placed) {  // New Bin
            bins[binCount][0] = items[i];
            binSizes[binCount] = 1;
            binCount++;
        }
    }
    
    printf("Output1 (First Fit):\n");
    printBins(bins, binCount, binSizes);
}

// Next Fit Func
void nextFit(int items[], int itemCount, int binCapacity) {
    int bins[MAX_BINS][MAX_ITEMS] = {0}; // Each Bin's Item
    int binSizes[MAX_BINS] = {0};
    int binCount = 1;  // Start First bin
    int binIndex = 0; 
    
    for (int i = 0; i < itemCount; i++) {
        int binLoad = 0;
        // Calulating
        for (int j = 0; j < binSizes[binIndex]; j++) {
            binLoad += bins[binIndex][j];
        }
        
        if (binLoad + items[i] <= binCapacity) {
            bins[binIndex][binSizes[binIndex]] = items[i];  // Put item 
            binSizes[binIndex]++;
        } else {  // New Bin
            binIndex++;
            bins[binIndex][0] = items[i];
            binSizes[binIndex] = 1;
            binCount++;
        }
    }
    
    printf("Output2 (Next Fit):\n");
    printBins(bins, binCount, binSizes);
}

// Best Fit Func
void bestFit(int items[], int itemCount, int binCapacity) {
    int bins[MAX_BINS][MAX_ITEMS] = {0}; // Each Bin's Item
    int binSizes[MAX_BINS] = {0};
    int binCount = 0;  
    
    for (int i = 0; i < itemCount; i++) {
        int bestFitBin = -1;
        int minSpaceLeft = binCapacity + 1;  
        
        // Calulating
        for (int j = 0; j < binCount; j++) {
            int binLoad = 0;
            for (int k = 0; k < binSizes[j]; k++) {
                binLoad += bins[j][k];
            }
            
            if (binLoad + items[i] <= binCapacity) {
                int spaceLeft = binCapacity - (binLoad + items[i]);
                if (spaceLeft < minSpaceLeft) {
                    minSpaceLeft = spaceLeft;
                    bestFitBin = j;
                }
            }
        }
        
        if (bestFitBin == -1) {  // New Bin
            bins[binCount][0] = items[i];
            binSizes[binCount] = 1;
            binCount++;
        } else {  
            int binLoad = binSizes[bestFitBin];
            bins[bestFitBin][binLoad] = items[i];
            binSizes[bestFitBin]++;
        }
    }
    
    printf("Output3 (Best Fit):\n");
    printBins(bins, binCount, binSizes);
}

// Worst Fit Func
void worstFit(int items[], int itemCount, int binCapacity) {
    int bins[MAX_BINS][MAX_ITEMS] = {0}; // Each Bin's Item
    int binSizes[MAX_BINS] = {0}; 
    int binCount = 0;
    
    for (int i = 0; i < itemCount; i++) {
        int worstFitBin = -1;
        int maxSpaceLeft = -1;  //
        
        // Calulating
        for (int j = 0; j < binCount; j++) {
            int binLoad = 0;
            for (int k = 0; k < binSizes[j]; k++) {
                binLoad += bins[j][k];
            }
            
            if (binLoad + items[i] <= binCapacity) {
                int spaceLeft = binCapacity - (binLoad + items[i]);
                if (spaceLeft > maxSpaceLeft) {
                    maxSpaceLeft = spaceLeft;
                    worstFitBin = j;
                }
            }
        }
        
        if (worstFitBin == -1) {  // New Bin
            bins[binCount][0] = items[i];
            binSizes[binCount] = 1;
            binCount++;
        } else {  // 넣을 수 있는 상자에 넣음
            int binLoad = binSizes[worstFitBin];
            bins[worstFitBin][binLoad] = items[i];
            binSizes[worstFitBin]++;
        }
    }
    
    printf("Output4 (Worst Fit):\n");
    printBins(bins, binCount, binSizes);
}

int main() {  
    int items[] = {7, 5, 6, 4, 2, 3, 7, 5};  // Item Size
    int itemCount = sizeof(items) / sizeof(items[0]);  // amount of Items
    int binCapacity = 10;

    // First Fit
    firstFit(items, itemCount, binCapacity);
    
    // Next Fit
    nextFit(items, itemCount, binCapacity);
    
    // Best Fit
    bestFit(items, itemCount, binCapacity);
    
    // Worst Fit
    worstFit(items, itemCount, binCapacity);
    
    return 0;
}
