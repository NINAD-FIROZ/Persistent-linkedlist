#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *new_node(int data, Node *next) {
    Node *n = malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(1); }
    n->data = data;
    n->next = next;
    return n;
}

Node *prepend(Node *head, int data) {
    return new_node(data, head);
}
Node *insert_at(Node *head, int index, int data) {
    if (index <= 0)
        return new_node(data, head);

    Node *new_head = new_node(head->data, head->next);
    Node *tail      = new_head;
    Node *cur       = head->next;
    int   i         = 1;

    while (cur && i < index) {
        tail->next = new_node(cur->data, cur->next);
        tail = tail->next;
        cur  = cur->next;
        i++;
    }
    tail->next = new_node(data, cur);
    return new_head;
}

Node *remove_val(Node *head, int data) {
    if (!head) return NULL;

    if (head->data == data)
        return head->next;

    Node *new_head = new_node(head->data, head->next);
    Node *tail     = new_head;
    Node *cur      = head->next;

    while (cur) {
        if (cur->data == data) {
            tail->next = cur->next;
            return new_head;
        }
        tail->next = new_node(cur->data, cur->next);
        tail = tail->next;
        cur  = cur->next;
    }
    return new_head;               
}
void print_list(const char *label, Node *head) {
    printf("%s: ", label);
    while (head) {
        printf("%d", head->data);
        if (head->next) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}
#define MAX_VERSIONS 64

void print_all_versions(Node *versions[], int count) {
    printf("\n--- All versions ---\n");
    for (int i = 0; i < count; i++) {
        char label[16];
        sprintf(label, "v%d", i);
        print_list(label, versions[i]);
    }
    printf("--------------------\n\n");
}

void print_menu(void) {
    printf("1. Prepend value\n");
    printf("2. Insert at index\n");
    printf("3. Remove value\n");
    printf("4. Show all versions\n");
    printf("5. Switch active version\n");
    printf("0. Quit\n");
    printf("> ");
}

/* ---------- main ---------- */
int main(void) {
    Node  *versions[MAX_VERSIONS];
    int    ver_count = 0;
    int    active    = 0;
    int    choice, val, idx;

    /* start with one empty version */
    versions[ver_count++] = NULL;

    printf("=== Persistent Linked List ===\n");
    printf("Each operation creates a new version; old ones are never modified.\n\n");

    while (1) {
        char label[16];
        sprintf(label, "v%d (active)", active);
        print_list(label, versions[active]);
        printf("\n");
        print_menu();

        if (scanf("%d", &choice) != 1) break;

        if (choice == 0) {
            printf("Bye!\n");
            break;
        }

        if (ver_count >= MAX_VERSIONS) {
            printf("Version limit reached (%d).\n", MAX_VERSIONS);
            break;
        }

        switch (choice) {

        case 1:
            printf("Value to prepend: ");
            scanf("%d", &val);
            versions[ver_count] = prepend(versions[active], val);
            printf("Created v%d\n", ver_count);
            active = ver_count++;
            break;

        case 2:
            printf("Index: ");
            scanf("%d", &idx);
            printf("Value: ");
            scanf("%d", &val);
            versions[ver_count] = insert_at(versions[active], idx, val);
            printf("Created v%d\n", ver_count);
            active = ver_count++;
            break;

        case 3:
            printf("Value to remove: ");
            scanf("%d", &val);
            versions[ver_count] = remove_val(versions[active], val);
            printf("Created v%d\n", ver_count);
            active = ver_count++;
            break;

        case 4:
            print_all_versions(versions, ver_count);
            break;

        case 5:
            printf("Switch to version (0-%d): ", ver_count - 1);
            scanf("%d", &idx);
            if (idx >= 0 && idx < ver_count) {
                active = idx;
                printf("Active version is now v%d\n", active);
            } else {
                printf("Invalid version number.\n");
            }
            break;

        default:
            printf("Unknown option.\n");
        }

        printf("\n");
    }
    for (int i = 0; i < ver_count; i++)
        free(versions[i]);   /* free only the head; rest may be shared */

    return 0;
}