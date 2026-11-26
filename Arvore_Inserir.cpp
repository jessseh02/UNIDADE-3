#include <iostream>

using namespace std;

struct No {
    int matricula;
    char nome[50];
    float nota;
    No* esq;
    No* dir;
};

No* inserir(No* raiz, int matricula, const char nome[], float nota) {
    if (raiz == NULL) {
        No* novo = new No;
        novo->matricula = matricula;
        int i = 0;
        while (nome[i] != '\0' && i < 49) {
            novo->nome[i] = nome[i];
            i++;
        }
        novo->nome[i] = '\0';
        novo->nota = nota;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    if (matricula < raiz->matricula)
        raiz->esq = inserir(raiz->esq, matricula, nome, nota);
    else if (matricula > raiz->matricula)
        raiz->dir = inserir(raiz->dir, matricula, nome, nota);

    return raiz;
}

No* buscar(No* raiz, int matricula) {
    if (raiz == NULL || raiz->matricula == matricula)
        return raiz;

    if (matricula < raiz->matricula)
        return buscar(raiz->esq, matricula);
    else
        return buscar(raiz->dir, matricula);
}

No* remover(No* raiz, int matricula) {
    if (raiz == NULL)
        return NULL;

    if (matricula < raiz->matricula) {
        raiz->esq = remover(raiz->esq, matricula);
    }
    else if (matricula > raiz->matricula) {
        raiz->dir = remover(raiz->dir, matricula);
    }
    else {
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            delete raiz;
            return temp;
        }
        if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            delete raiz;
            return temp;
        }

        No* sucessor = raiz->dir;
        while (sucessor->esq != NULL)
            sucessor = sucessor->esq;

        raiz->matricula = sucessor->matricula;
        int i = 0;
        while (sucessor->nome[i] != '\0') {
            raiz->nome[i] = sucessor->nome[i];
            i++;
        }
        raiz->nome[i] = '\0';
        raiz->nota = sucessor->nota;
        raiz->dir = remover(raiz->dir, sucessor->matricula);
    }
    return raiz;
}

No* inserirIterativo(No* raiz, int matricula, const char nome[], float nota) {
    No* novo = new No;
    novo->matricula = matricula;
    int i = 0;
    while (nome[i] != '\0' && i < 49) {
        novo->nome[i] = nome[i];
        i++;
    }
    novo->nome[i] = '\0';
    novo->nota = nota;
    novo->esq = NULL;
    novo->dir = NULL;

    if (raiz == NULL)
        return novo;

    No* atual = raiz;
    No* pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (matricula < atual->matricula)
            atual = atual->esq;
        else if (matricula > atual->matricula)
            atual = atual->dir;
        else {
            delete novo;
            return raiz;
        }
    }

    if (matricula < pai->matricula)
        pai->esq = novo;
    else
        pai->dir = novo;

    return raiz;
}

bool ehBST(No* raiz, No* min, No* max) {
    if (raiz == NULL)
        return true;

    if (min != NULL && raiz->matricula <= min->matricula)
        return false;
    if (max != NULL && raiz->matricula >= max->matricula)
        return false;

    return ehBST(raiz->esq, min, raiz) &&
           ehBST(raiz->dir, raiz, max);
}

bool todosEstaoEm(No* a, No* b) {
    if (a == NULL)
        return true;
    if (buscar(b, a->matricula) == NULL)
        return false;
    return todosEstaoEm(a->esq, b) && todosEstaoEm(a->dir, b);
}

bool mesmoConjunto(No* a, No* b) {
    return todosEstaoEm(a, b) && todosEstaoEm(b, a);
}