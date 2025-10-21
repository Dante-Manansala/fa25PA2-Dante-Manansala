# CipherText: Variable-Bit (Frequency-Based) Encoding

## Submission Details

For this programming assignment, you will create your own **public GitHub repository**.  
Your repository should contain the three required files: `main.cpp`, `heap.h`, and `input.txt`.

### Repository Requirements

- The repository **must be public** so it can be accessed for grading.  
- Include a clear commit history showing your progress.  
- You must have a **minimum of five commits** spread over at least **two weeks**. Commits should reflect incremental work such as implementing heap operations, debugging traversal, or updating documentation.  
- Do not upload compiled binaries or object files.

### Canvas Submission

A public **template repository** has been provided for you to fork and begin your work:  
**https://github.com/profmanjupriya/fa25PA2**

1. Fork the template repository to your own GitHub account.  
2. Complete your work within your forked repository, ensuring all three files (`main.cpp`, `heap.h`, and `input.txt`) are included.  
3. Maintain a clear commit history with a minimum of five commits over two weeks.  
4. Make sure your repository remains public.  
5. Once finished, submit the **URL** of your public repository in the Canvas text box.

---

## Overview

An intercepted text has arrived in your system. As a newly appointed **Cybersecurity Specialist**, your job is to design a simple encoding module that converts readable text into a variable-bit cipher. Frequent letters must be represented with shorter bit patterns to minimize transmission size, while rare letters use longer ones. This is your first step toward building efficient, adaptive encryption systems.

You will:

- Read a text file and analyze how often each character appears.  
- Build a **frequency-ordered min heap** using arrays to prioritize the most common symbols.  
- Combine symbols into an encoding structure that produces **variable-length bit codes**.  
- Use an **iterative traversal** with a stack to assign these bit sequences.  
- Print the resulting code table and the encoded cipher message.

This assignment brings together array data structures, heap operations, and iterative traversal logic—all under the applied context of secure text encoding.

---

## Learning Goals

- Implement an **array-based min heap** for organizing frequency data.  
- Apply a **stack** for iterative traversal without recursion.  
- Understand how greedy strategies lead to efficient encodings.  
- Practice clean modular design with multiple source files.

---

## Problem Statement

You are given a plain-text file containing intercepted communication. Your task is to encode it into a compact cipher using variable bit lengths per symbol.  
The goal is to represent frequent letters with shorter binary codes and rare letters with longer ones.

### Step-by-Step Example

Suppose the intercepted text is:

```
banana
```

**Step 1: Frequency Analysis**  
Count how many times each lowercase letter appears.

| Character | Frequency |
|------------|------------|
| b | 1 |
| a | 3 |
| n | 2 |

**Step 2: Frequency Heap Building**  
Store these letters and their frequencies in a **min heap**, where the smallest weights rise to the top.

- Initial heap (by frequency): `[1(b), 2(n), 3(a)]`
- Remove the two smallest values: `1(b)` and `2(n)`.  
- Combine them into a new parent node with weight `3` (`1 + 2 = 3`).  
- Insert this new node back into the heap.

Now the heap contains: `[3(a), 3(parent)]`.

- Remove both `3` values.  
- Combine them into a final parent with weight `6`.  
- Insert that node back. Only one node remains—the **root** of your encoding structure.

**Step 3: Variable Bit Assignment**  
Traverse the structure:

- Moving **left** adds a `0`.  
- Moving **right** adds a `1`.

| Character | Code |
|------------|------|
| a | 0 |
| b | 10 |
| n | 11 |

**Step 4: Encoding**  
Replace each letter in the input text with its code.

```
banana → b(10) a(0) n(11) a(0) n(11) a(0)
```

Encoded message:

```
100110110
```

This example demonstrates how frequency affects code length: the most common letter (`a`) gets a 1-bit code, while less common letters (`b` and `n`) get longer codes.  
Your program will automate this process for any text in `input.txt`.

---

## Deliverables

You will submit three files:

```
main.cpp
heap.h
input.txt
```

Do not add additional files.

---

## Constraints and Tools

- The min heap must be implemented manually using arrays.  
- Allowed headers: `<iostream>`, `<fstream>`, `<stack>`, `<string>`.  
- `std::stack` may be used for traversal. Other STL containers are **not allowed**.  
- Recursion is not allowed.  
- Compile and run with:

```bash
g++ -std=c++17 main.cpp -o encoder
./encoder
```

---

## File Breakdown

### 1) `input.txt`

**Purpose:** The intercepted text that you will encode. Start with short words for testing.  
**What’s given:** A small example text file.  
**What you do:** Modify the text as desired to test your encoder.

---

### 2) `heap.h`

**Purpose:** Build the **array-based min heap** that will manage symbol frequencies.  

**What’s given:**  
A `MinHeap` structure with `data[]`, `size`, and placeholder methods `push`, `pop`, `upheap`, and `downheap`.

**What you do:**  
- Complete the four heap methods to maintain proper ordering by weight.  
- Remember, the heap stores **indices** of nodes, not weights themselves.  
- Use the global array `weightArr[]` for comparisons.

**Tips:**  
- Parent: `(i - 1) / 2`, children: `2*i + 1`, `2*i + 2`.  
- Use `upheap` when inserting and `downheap` after removal.

---

### 3) `main.cpp`

**Purpose:** Coordinate reading, building, and encoding.

**What’s given:**
- The file already reads `input.txt` and counts frequencies for lowercase letters.  
- It normalizes uppercase letters to lowercase and stores counts in `freq[26]`.  
- The function `createLeafNodes` is provided and demonstrates how characters with nonzero frequency are converted into nodes by initializing global arrays (`charArr[]`, `weightArr[]`, `leftArr[]`, `rightArr[]`).  
- The main function calls each step in order, so students can follow the logical flow from file reading to encoding.

**What you will implement:**
- **`buildEncodingTree(int nextFree)`**  
  Use the custom heap from `heap.h` to combine nodes based on their weights. Pop the two smallest nodes, create a new parent node, assign its children and combined weight, and push it back into the heap until one node remains. Return the index of the final root node.

- **`generateCodes(int root, string codes[])`**  
  Perform an **iterative traversal** to assign binary bit strings to each character. This function will need a **stack** to keep track of nodes and partial paths as you move through the structure. Assign shorter bit codes to more frequent letters and longer codes to less frequent ones.

- **`encodeMessage(const string& filename, string codes[])`**  
  Reopen the same input file, convert characters to lowercase, and print two sections:  
  1. The code table (`Character : Code`).  
  2. The encoded message, which is the sequence of bits corresponding to the original file’s text.

These functions complete the encoding pipeline after the file is read and leaf nodes are created.

---

## Execution Flow

1. Read the file and build the frequency table.  
2. Create leaf nodes in parallel arrays.  
3. Use the heap to construct the encoding structure.  
4. Traverse iteratively (using a stack) to assign bit codes.  
5. Print the results.

---

## Output Format

```
Character : Code
a : 0
b : 10
n : 11

Encoded message:
100110110
```

---

## Grading Outline (100 points)

| Component | Points |
|------------|--------|
| Heap push/pop correctness | 30 |
| Tree building logic | 25 |
| Iterative traversal with stack | 20 |
| Output format | 15 |
| Comments and clarity | 10 |

---

## Final Notes

Think of yourself as designing a basic ciphering algorithm.  
The more frequent a symbol, the shorter its binary key.  
Efficient encoders like this are the backbone of secure and compressed data transfer systems.
