#include "binary_tree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *valor_par = (KeyValPair *)calloc(1,sizeof(KeyValPair));
    valor_par->key = key;
    valor_par->value = val;
    return valor_par; 
}

void key_val_pair_destroy(KeyValPair *kvp){
    free(kvp);
}

Node *node_construct(void *key, void *value, Node *left, Node *right){
    Node *no = (Node *)calloc(1,sizeof(Node));
    no->val = key_val_pair_construct(key,value);
    no->left = left;
    no->right = right;
    return no;
}

void node_destroy(Node *node){
    free(node);
}

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn){
    BinaryTree *arvore = (BinaryTree *)calloc(1,sizeof(BinaryTree));
    arvore->root = NULL;
    arvore->cmp_fn = cmp_fn;
    arvore->key_destroy_fn = key_destroy_fn;
    arvore->val_destroy_fn = val_destroy_fn;
    return arvore;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value){
    if(binary_tree_empty(bt)){
        Node *novo = node_construct(key,value,NULL,NULL);
        bt->root = novo;
    }else{
        Node *pai = NULL, *atual = bt->root;
        Node *novo = node_construct(key,value,NULL,NULL);
        while(atual != NULL){
            pai = atual;
            if(bt->cmp_fn(key,pai->val->key) > 0){
                atual = pai->right;
                if(atual == NULL){
                    pai->right = novo;
                }
            }else{
                if(bt->cmp_fn(key,pai->val->key) == 0){
                    bt->val_destroy_fn(atual->val->value);
                    bt->key_destroy_fn(key);
                    atual->val->value = value;
                    key_val_pair_destroy(novo->val);
                    node_destroy(novo);
                    break;
                }
                atual = pai->left;
                if(atual == NULL){
                    pai->left = novo;
                }
            }
            pai = atual;
        }
    }
}

int binary_tree_empty(BinaryTree *bt){
    return bt->root == NULL;
}


void *binary_tree_get(BinaryTree *bt, void *key){
    Node *atual = bt->root;
    while(atual != NULL){
        if(bt->cmp_fn(key,atual->val->key) > 0){
            atual = atual->right;
        }else{
            if(bt->cmp_fn(key,atual->val->key) == 0){
                return atual->val->value;
                break;
            }else{
                atual = atual->left;
            }
        }
    }
    return NULL;
}

void binary_tree_destroy(BinaryTree *bt){
    KeyValPair *pair = NULL; 
    while(!binary_tree_empty(bt)){
        pair = binary_tree_remove(bt,bt->root->val->key);
        bt->key_destroy_fn(pair->key);
        bt->val_destroy_fn(pair->value);
        key_val_pair_destroy(pair);
    }

    bt->root = NULL;
    free(bt);
}

void _trasplante(BinaryTree *bt, Node *pai_removendo, Node *mudando, Node *removendo){
    if(pai_removendo == NULL){
        bt->root = mudando;
    }else{
        if(pai_removendo->left == removendo){
            pai_removendo->left = mudando;
        }else{
            pai_removendo->right = mudando;
        }
    }
}

KeyValPair *binary_tree_remove(BinaryTree *bt, void *key){

    Node *atual = bt->root, *pai = NULL;
    while(atual != NULL){
        if(bt->cmp_fn(key,atual->val->key) > 0){
            pai = atual;
            atual = atual->right;
        }else{
            if(bt->cmp_fn(key,atual->val->key) == 0){
                break;
            }else{
                pai = atual;
                atual = atual->left;
            }
        }
    }

    if(atual != NULL){
        if((atual->right == NULL) &&(atual->left == NULL)){
            _trasplante(bt,pai,NULL,atual);
        }else{
            if((atual->right != NULL)&&(atual->left == NULL)){
                _trasplante(bt,pai,atual->right,atual);
            }else{
                if((atual->left != NULL)&&(atual->right == NULL)){
                    _trasplante(bt,pai,atual->left,atual);
                }else{
                    Node *minimo = atual->right, *minimo_pai = atual;
                    while(minimo->left != NULL){
                        minimo_pai = minimo;
                        minimo = minimo_pai->left;
                    }

                    if(minimo_pai == atual){
                        _trasplante(bt,pai,minimo,atual);
                        minimo->left = atual->left;
                    }else{
                        _trasplante(bt,minimo_pai,minimo->right,minimo);
                        minimo->right = atual->right;
                        minimo->left = atual->left;
                        _trasplante(bt,pai,minimo,atual);
                    }
                }
            }
        }
        KeyValPair *pair = atual->val;
        node_destroy(atual);
        return pair;
    }
    return NULL;
}

Node *_binary_tree_min(BinaryTree *bt){
    Node *atual = bt->root;
    while(atual->left != NULL){
        atual = atual->left;
    }
    return atual;
}

Node *_binary_tree_max(BinaryTree *bt){
    Node *atual = bt->root;
    while(atual->right != NULL){
        atual = atual->right;
    }
    return atual;
}

KeyValPair *binary_tree_min(BinaryTree *bt){
    Node *atual = _binary_tree_min((bt));
    return atual->val;
}

KeyValPair *binary_tree_max(BinaryTree *bt){
    Node *atual = _binary_tree_max(bt);
    return atual->val;
}

KeyValPair *binary_tree_pop_min(BinaryTree *bt){
    KeyValPair *pair = binary_tree_min(bt);
    return binary_tree_remove(bt,pair->key);
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt){
    KeyValPair *pair = binary_tree_max(bt); 
    return binary_tree_remove(bt,pair->key);
}

Vector *binary_tree_levelorder_traversal(BinaryTree *bt){
    Vector *fila = vector_construct();
    Vector *retorno = vector_construct();
    Node *atual = NULL;
    vector_push_back(fila,bt->root);
    while(vector_size(fila)){
        atual = (Node *)vector_pop_front(fila);
        if(atual != NULL){
            vector_push_back(retorno,atual->val);
            if(atual->left != NULL){
                vector_push_back(fila,atual->left);
            }
            if(atual->right != NULL){
                vector_push_back(fila,atual->right);
            }
        }
    }
    vector_destroy(fila);
    return retorno;
}

Vector *binary_tree_preorder_traversal(BinaryTree *bt){
    Vector *pilha = vector_construct();
    Vector *retorno = vector_construct();
    Node *atual = NULL;
    vector_push_back(pilha,bt->root);
    while(vector_size(pilha)){
        atual = (Node *)vector_pop_back(pilha);
        vector_push_back(retorno,atual->val);
        if(atual->right != NULL){
            vector_push_back(pilha,atual->right);
        }
        if(atual->left != NULL){
            vector_push_back(pilha, atual->left);
        }
    }
    vector_destroy(pilha);
    return retorno;
}

Vector *binary_tree_inorder_traversal(BinaryTree *bt){
    Vector *pilha = vector_construct();
    Vector *retorno = vector_construct();
    Node *atual = bt->root, *aux = NULL;
    while((vector_size(pilha))||(atual != NULL)){
        while(atual != NULL){
            vector_push_back(pilha,atual);
            atual = atual->left;
        }
        aux = vector_pop_back(pilha);
        vector_push_back(retorno,aux->val);
        atual = aux->right;
    }
    vector_destroy(pilha);
    return retorno;
}

Vector *binary_tree_postorder_traversal(BinaryTree *bt){
    Vector *Q1 = vector_construct();
    Vector *Q2 = vector_construct();
    vector_push_back(Q1,bt->root);
    Node *atual = NULL;
    while(vector_size(Q1)){
        atual = (Node *)vector_pop_back(Q1);
        if(atual->left != NULL){
            vector_push_back(Q1,atual->left);
        }
        if(atual->right != NULL){
            vector_push_back(Q1,atual->right);
        }
        vector_push_back(Q2,atual->val);
    }
    vector_destroy(Q1);
    int tam = vector_size(Q2);
    Vector *retorno = vector_construct();
    for(int i = tam - 1; i >= 0; i--){
        void *atual_val = vector_get(Q2,i);
        vector_push_back(retorno,atual_val);
    }
    vector_destroy(Q2);
    return retorno;
}

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt){
    return NULL;
}

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt){
    return NULL;
}

Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt){
    return NULL;
}