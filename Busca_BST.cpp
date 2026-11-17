#include <iostream>
using namespace std;

struct NoArvore {
    int data;
    NoArvore* esquerda;
    NoArvore* direita;
};

NoArvore* inserirBST(NoArvore*& raiz, int chave) {
    if (raiz == NULL) {
        NoArvore* novoNo = new NoArvore;
        novoNo->data = chave;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;

        raiz = novoNo;
        return raiz;
    }

    if (chave > raiz->data) {
        raiz->direita = inserirBST(raiz->direita, chave);
    }

    if (chave < raiz->data) {
        raiz->esquerda = inserirBST(raiz->esquerda, chave);
    }

    return raiz;
}

void emOrdem(NoArvore* raiz) {
    if (raiz == NULL) {
        return;
    }

    emOrdem(raiz->esquerda);
    cout << raiz->data << " ";
    emOrdem(raiz->direita);
}

int main() {
    NoArvore* raiz = NULL;

    inserirBST(raiz, 29);
    inserirBST(raiz, 20);
    inserirBST(raiz, 40);
    inserirBST(raiz, 10);
    inserirBST(raiz, 35);

    emOrdem(raiz);
    cout << endl;

    return 0;
}