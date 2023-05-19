
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <iostream>


struct Node {
    char* data;
    struct Node* prev;
    struct Node* next;
};

struct Node* sh = NULL;

int get_ascii(const char symbol) {
    return (int)symbol;
}

void insertNode(struct Node** headRef, char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*headRef == NULL) {
        newNode->prev = NULL;
        *headRef = newNode;
    }
    else {
        struct Node* current = *headRef;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
        newNode->prev = current;
    }
}

void displayList(struct Node* head) {
    struct Node* current = head;
    if (current == NULL) {
        printf("no words");
    }
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

void writeFile(struct Node* head) {
    FILE* fp;
    fp = fopen("C://users//админ//desktop//output.txt", "w");
    struct Node* current = head;
    if (current == NULL) {
        printf("Nothing to write into the file!\n");
    }
    int c = true;
    while (current != NULL) {
        if (c == 1) {
            printf("Successfully written data to file!\n");
            c = 0;
        }
        c += 1;
        fprintf(fp, "%s\n", current->data);
        current = current->next;
    }
    fclose(fp);
}

void freeList(struct Node** headRef) {
    struct Node* current = *headRef;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    *headRef = NULL;
}

void removeShortWords(struct Node** headRef, struct Node** shRef) {
    struct Node* current = *headRef;
    while (current != NULL) {
        if (strlen(current->data) < 3) {
            char* newWord = (char*)malloc(strlen(current->data) + 1);
            strcpy(newWord, current->data);
            insertNode(shRef, newWord);
            if (current->prev == NULL) {
                *headRef = current->next;
                if (*headRef != NULL)
                    (*headRef)->prev = NULL;
            }
            else {
                current->prev->next = current->next;
                if (current->next != NULL)
                    current->next->prev = current->prev;
            }

            struct Node* temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
        }
        else {
            current = current->next;
        }
    }
}

void inputWords(struct Node** headRef) {
    char c, word[100] = { 0 };
    int i = 0;
    while ((c = getchar()) != '\n') {
        if (isalpha(c)) {
            word[i++] = c;
        }
        if (isspace(c)) {
            word[i - 1] = '\0';
            char* newWord = (char*)malloc(strlen(word) + 1);
            strcpy(newWord, word);
            insertNode(headRef, newWord);
            i = 0;
        }
    }
    if (i != 0) {
        word[i] = '\0';
        char* newWord = (char*)malloc(strlen(word) + 1);
        strcpy(newWord, word);
        insertNode(headRef, newWord);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    struct Node* head = NULL;

    inputWords(&head);

    printf("List before deleting short words: ");
    displayList(head);

    removeShortWords(&head, &sh);

    printf("List after deleting short words: ");
    displayList(head);

    writeFile(head);

    printf("Deleted words: ");
    displayList(sh);

    freeList(&head);

    return 0;
}
