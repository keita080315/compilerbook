#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  TK_RESERVED, // 記号
  TK_NUM,      // 整数トークン
  TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;

typedef struct Node {
  TokenKind kind;
  struct Node* next;
  int data_num;
  char data_sym;
} Node;

typedef struct {
  Node* first;
  Node* last;
} LinkedList;

Node* tokenize(char *p) {
  LinkedList* linkedList = calloc(1, sizeof(LinkedList));

  while(*p) {
    if(isblank(*p)) {
        p++;
        continue;
    }

    Node* node = calloc(1, sizeof(Node));
    node->next = NULL;

    // 記号を連結リストに格納
    if(*p == '+' || *p == '-') {
      node->data_sym = *p;
      node->kind = TK_RESERVED;
      p++;
    }
    // 数字を連結リストに格納
    else if(isdigit(*p)) {
      node->data_num = strtol(p,&p,10);
      node->kind = TK_NUM;
    }

    if(linkedList->last != NULL) {
        linkedList->last->next = node;
    } else {
        linkedList->first = node;
    }

    linkedList->last = node;
  }
  return linkedList->first;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "引数の個数が正しくありません\n");
    return 1;
  }

  printf(".globl main\n");
  printf("main:\n");
  char *p = argv[1];

  Node *token = tokenize(p);
  if(token->kind != TK_NUM) {
    fprintf(stderr, "1文字目に数字以外が与えられています: '%c'\n", token->data_sym);
    return -1;
  }
  printf("  mov x0, %d\n", token->data_num);

  while(token->next != NULL) {
    token = token->next;
    if(token->kind == TK_RESERVED) {
        if(token->data_sym == '+') {
            token = token->next;
            printf("  add x0, x0, %d\n", token->data_num);
        }
        if(token->data_sym == '-') {
            token = token->next;
            printf("  sub x0, x0, %d\n", token->data_num);
        }
        continue;
    }

    fprintf(stderr, "予期しない文字です: '%d'\n", token->data_num);
    return -1;
  }

  printf("  ret\n");
  return 0;
}