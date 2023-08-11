#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct DoublyLinkedList {
    struct Node* head;
};

void append(struct DoublyLinkedList* list, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        struct Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
    }
}

int find_element_at_position(struct DoublyLinkedList* list, int position) {
    struct Node* current = list->head;
    int index = 1;
    while (current != NULL) {
        if (index == position) {
            return current->data;
        }
        current = current->next;
        index++;
    }
    return -1;  // Element not found
}

void persist_to_text_file(struct DoublyLinkedList* list, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    struct Node* current = list->head;
    while (current != NULL) {
        fprintf(file, "%d\n", current->data);
        current = current->next;
    }

    fclose(file);
}

void persist_to_binary_file(struct DoublyLinkedList* list, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    struct Node* current = list->head;
    while (current != NULL) {
        fwrite(&(current->data), sizeof(int), 1, file);
        current = current->next;
    }

    fclose(file);
}

int main() {
    struct DoublyLinkedList linked_list;
    linked_list.head = NULL;

    // Creating the linked list
    append(&linked_list, 10);
    append(&linked_list, 20);
    append(&linked_list, 30);
    append(&linked_list, 40);

    int position = 4;
    int element_at_position = find_element_at_position(&linked_list, position);
    printf("Element at position %d is: %d\n", position, element_at_position);

    persist_to_text_file(&linked_list, "linked_list.txt");
    persist_to_binary_file(&linked_list, "linked_list.bin");

    // Free allocated memory for nodes
    struct Node* current = linked_list.head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}