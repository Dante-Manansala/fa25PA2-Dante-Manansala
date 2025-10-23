//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()


        return -1; // something wrong has happened
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent

        ///NOTE: refer pos as child
        // loop till gone through heap
        while (pos > 0) {
            int parent = (pos - 1) / 2;

            /// NOTE: if some how positions are same, check the values for child < parent
            // if locationChild < locationParent or (locationChild == locationParent and valueChild < valueParent), swap
            // else, break while-loop early
            if ((weightArr[data[pos]] <  weightArr[data[parent]]) ||
                (weightArr[data[pos]] == weightArr[data[parent]] && data[pos] < data[parent])) {

                //swap value positions
                int temp = data[pos];
                data[pos] = data[parent];
                data[parent] = temp;

                pos = parent; // update
            } else break; // stop swaping
        }
    }

    //move down the tree till at leaf
    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        int left;
        int right;
        int smallest;

        ///NOTE: moving down heap, number increases, prevent going over heap size
        //loop
        while (true) {
            // child of current node
            left = 2 * pos + 1;
            right = left + 1;

            smallest = pos; // set smallest to current node

            /// NOTE: look at upheap for each weight checks for more information
            // make sure it within range/size
            if (left < size) {
                // if left < smallest, smallest = left
                // expanded: if locationLeft < locationSmallest or (locationLeft == locationSmallest and valueLeft < valueSmallest), replace smallest
                if ((weightArr[data[left]] <  weightArr[data[smallest]]) ||
                    (weightArr[data[left]] == weightArr[data[smallest]] && data[left] < data[smallest]))
                    smallest = left;
            }

            // make sure it within range/size
            if (right < size) {
                // if right < smallest, smallest = right
                // expanded: if locationRight < locationSmallest or (locationRight == locationSmallest and valueRight < valueSmallest), replace smallest
                if ((weightArr[data[right]] <  weightArr[data[smallest]]) ||
                    (weightArr[data[right]] == weightArr[data[smallest]] && data[right] < data[smallest]))
                    smallest = right;
            }

            // if smallest was updated, swap and update current node for next loop (we have moved down the heap)
            // else exit loop
            if (smallest != pos) {
                //swap
                int temp = data[pos];
                data[pos] = data[smallest];
                data[smallest] = temp;

                pos = smallest; // update new current node
            } else break;
        }
    }
};

#endif