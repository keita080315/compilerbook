#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  TK_ADD,
  TK_SUB,
  TK_MUL,
  TK_DIV,
  TK_NUM,
  TK_EOF,
} TokenKind;

typedef struct Node {
  TokenKind kind;
  struct Node* leftNode;
  struct Node* rightNode;
  int data_num;
} Node;

typedef struct List {
  struct List* next;
  char data_sym;
  int data_num;
} List;

Node* primary();
Node* mul();
Node* expr();

List *list;

List* tokenize(char *p) {
  List head;
  head.next = NULL;
  List* list = &head;

  while(*p) {
    if(isblank(*p)) {
        p++;
        continue;
    }
    List* tmp = calloc(1, sizeof(List));
    if(isdigit(*p)) {
      tmp->data_num = strtol(p,&p,10);
    } else {
      tmp->data_sym = *p;
      p++;
    }

    list->next = tmp;
    list = tmp;
  }
  return head.next;
}

Node* addNode(TokenKind dataKind, Node* leftNode, Node* rightNode) {
    Node* node = calloc(1, sizeof(Node));
    node->kind = dataKind;
    node->leftNode = leftNode;
    node->rightNode = rightNode;
    return node;
}

Node* addNumNode(TokenKind dataKind, int num) {
    Node* node = calloc(1, sizeof(Node));
    node->kind = dataKind;
    node->data_num = num;
    return node;
}

Node* expr() {
    Node* node = mul();
    for(;;) {
        if(list->data_sym == '+') {
            list = list->next;
            node = addNode(TK_ADD, node, mul());
        } else if(list->data_sym == '-') {
            list = list->next;
            node = addNode(TK_SUB, node, mul());
        } else {
            return node;
        }
    }
}

Node* mul() {
    Node* node = primary();
    for(;;) {
        if(list->data_sym == '*') {
            list = list->next;
            node = addNode(TK_MUL, node, primary());
        } else if(list->data_sym == '/') {
            list = list->next;
            node = addNode(TK_DIV, node, primary());
        } else {
            return node;
        }
    }    
}

Node* primary() {
    Node* node;
    if(list->data_sym == '(') {
        list = list->next;
        node = expr();
        if(list->data_sym != ')') {
            fprintf(stderr, "()が正しく使用されていません\n");
        } else {
            list = list->next;
        }
    } else {
        node = addNumNode(TK_NUM, list->data_num);
        if(list->next != NULL) {
            list = list->next;
        }
    }
    return node;
}

void move(Node* node) {
    if(node->kind == TK_NUM) {
        // PUSH処理
        printf("  mov x0, %d\n", node->data_num);
        printf("  stp x0, xzr, [sp, #-16]!\n");
        return;
    } else {
        move(node->leftNode);
        move(node->rightNode);
        // 演算処理
        printf("  ldp x1, xzr, [sp], #16\n");
        printf("  ldp x0, xzr, [sp], #16\n");
        switch (node->kind)
        {
        case TK_ADD:
            printf("  add x0, x0, x1\n");
            break;
        case TK_SUB:
            printf("  sub x0, x0, x1\n");
            break;            
        case TK_MUL:
            printf("  mul x0, x0, x1\n");
            break;
        case TK_DIV:
            printf("  div x0, x0, x1\n");
            break;       
        default:
            fprintf(stderr, "演算子が正しくありません\n");
            break;
        }
        printf("  stp x0, xzr, [sp, #-16]!\n");
    }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "引数の個数が正しくありません\n");
    return 1;
  }

  printf(".globl main\n");
  printf("main:\n");
  char *p = argv[1];

  list = tokenize(p);
  Node * node = expr();

  printf("  stp x29, x30, [sp, #-16]!\n");
  printf("  mov x29, sp\n");
  move(node);
  printf("  mov sp, x29\n");
  printf("  ldp x29, x30, [sp], #16\n");

  printf("  ret\n");
  return 0;
}