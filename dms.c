#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEQUENCE 100

// Function to swap characters
void swap(char* x, char* y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

// Function to generate all permutations of a DNA sequence
void generatePermutations(char* sequence, int start, int end, FILE* outputFile) {
    if (start == end) {
        fprintf(outputFile, "%s\n", sequence); // Save to file
        return;
    }

    for (int i = start; i <= end; i++) {
        swap(&sequence[start], &sequence[i]); // Swap the characters
        generatePermutations(sequence, start + 1, end, outputFile); // Recurse
        swap(&sequence[start], &sequence[i]); // Backtrack
    }
}

// Function to validate a DNA sequence
int validateSequence(const char* sequence) {
    for (int i = 0; i < strlen(sequence); i++) {
        if (sequence[i] != 'A' && sequence[i] != 'T' && sequence[i] != 'G' && sequence[i] != 'C') {
            return 0; // Invalid character found
        }
    }
    return 1;
}

// Function to calculate nucleotide frequencies
void calculateFrequencies(const char* sequence) {
    int countA = 0, countT = 0, countG = 0, countC = 0;
    int j = strlen(sequence);

    for (int i = 0; i < j ; i++) {
        switch (sequence[i]) {
            case 'A': countA++; break;
            case 'T': countT++; break;
            case 'G': countG++; break;
            case 'C': countC++; break;
        }
    }

    printf("\n--- Nucleotide Frequencies ---\n");
    printf("A: %d\nT: %d\nG: %d\nC: %d\n", countA, countT, countG, countC);
}

// Function to generate the reverse complement of the DNA sequence
void generateReverseComplement(const char* sequence) {
    int length = strlen(sequence);
    char reverseComplement[MAX_SEQUENCE];

    for (int i = 0; i < length; i++) {
        switch (sequence[length - i - 1]) {
            case 'A': reverseComplement[i] = 'T'; break;
            case 'T': reverseComplement[i] = 'A'; break;
            case 'G': reverseComplement[i] = 'C'; break;
            case 'C': reverseComplement[i] = 'G'; break;
        }
    }
    reverseComplement[length] = '\0';

    printf("\n--- Reverse Complement ---\n");
    printf("%s\n", reverseComplement);
}

// Function to search for a subsequence
void searchSubsequence(const char* sequence, const char* subsequence) {
    if (strstr(sequence, subsequence)) {
        printf("Subsequence '%s' found in the DNA sequence.\n", subsequence);
    } else {
        printf("Subsequence '%s' not found in the DNA sequence.\n", subsequence);
    }
}

int main() {
    char dnaSequence[MAX_SEQUENCE];
    char subsequence[MAX_SEQUENCE];
    int choice;

    printf("Enter a DNA sequence (using A, T, G, C): ");
    scanf("%s", dnaSequence);

    // Validate the input DNA sequence
    if (!validateSequence(dnaSequence)) {
        printf("Invalid DNA sequence. Please use only A, T, G, C.\n");
        return 1;
    }

    do {
        printf("\n--- DNA Sequencing Menu ---\n");
        printf("1. Generate Permutations\n");
        printf("2. Calculate Nucleotide Frequencies\n");
        printf("3. Generate Reverse Complement\n");
        printf("4. Search Subsequence\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                FILE* outputFile = fopen("permutations.txt", "w");
                if (!outputFile) {
                    printf("Error opening file.\n");
                    break;
                }
                printf("Generating permutations... Check 'permutations.txt' for results.\n");
                generatePermutations(dnaSequence, 0, strlen(dnaSequence) - 1, outputFile);
                fclose(outputFile);
                break;
            }
            case 2:
                calculateFrequencies(dnaSequence);
                break;

            case 3:
                generateReverseComplement(dnaSequence);
                break;

            case 4:
                printf("Enter the subsequence to search: ");
                scanf("%s", subsequence);
                searchSubsequence(dnaSequence, subsequence);
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}