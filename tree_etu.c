/* ---------------------------------------------------------------
    Log Mollo: compresseur de journaux en ligne
    Auteur: ENAUD Valentin 
    Mis à jour le: 15/11/2022
   ---------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "tree_etu.h"

// remet a zero le nombre d'occurrences des octets
void tree_resetByteOccurrence( struct byteCoding indexedCodeTable[256] ){   
    int i ; 
    for(i=0;i<256;i++){
        indexedCodeTable[i].occurrence = 0 ; //On donne la valeur 0 à tous les attributs "occurence" de tous les caractères 
    }
}

// remet a zero les codes octet
void tree_resetByteCoding( struct byteCoding indexedCodeTable[256] ) {
    int i ; 
    for(i=0;i<256;i++){
        indexedCodeTable[i].byte = i ;               //byte correspond au code ascii d'un caractère
        indexedCodeTable[i].huffmanCode = 0 ;        //On donne la valeur 0 à tous les attributs "huffmanCode" de tous les caractères 
        indexedCodeTable[i].nbBits = 0 ;             //On donne la valeur 0 à tous les attributs "nbBits" de tous les caractères 
    }
}

// compte de nombre d'occurrence des octets dans un tampon
void tree_countByteOccurrence( const t_byte * buffer, int size, struct byteCoding indexedCodeTable[256] ){
    int i =0; 
    while(i<size){  //Parcours du buffer 
        for(int j = 0;j<256;j++){ //Parcours de la table de codage 
            if(buffer[i]==indexedCodeTable[j].byte){ //Vérifie pour chaque caractère de la table de codage si il égal au caractère courant de la chaine (buffer[i])
                indexedCodeTable[j].occurrence++;    //Ajoute 1 si vrai 
            }
        }
        i++;
    }
}

// affiche la table de codage des valeurs d'octet pour debug
void tree_displayByteCoding(struct byteCoding indexedCodeTable[256]){
    int i ; 
    for(i=0;i<256;i++){ //Parcours de la table de codage 
        if(i%3==0){
            printf("\nCaractère: %c Code Ascii: %d  Occurence:%d)",indexedCodeTable[i].byte,indexedCodeTable[i].byte,indexedCodeTable[i].occurrence);  //Affichage à l'aide de printf des attributs d'un caractère
        }else{
            printf("            Caractère: %c Code Ascii: %d  Occurence:%d",indexedCodeTable[i].byte,indexedCodeTable[i].byte,indexedCodeTable[i].occurrence);
        }
    }
}

// creation d'un noeud
struct tree_node * tree_createNode (struct tree_node * father, int * value ) {
   struct tree_node * new_node = (struct tree_node * )malloc(sizeof(struct tree_node)); 
   new_node->valeur = value ;  
   new_node->pere = father ; 
   new_node->gauche = NULL ; 
   new_node->droite = NULL ;    
   return new_node ; 
}
 
 
// creation d'un noeud de codage et liaison avec ses fils
struct tree_node * tree_createCodingNode ( struct tree_node * left,struct tree_node * right ) {
    struct tree_node * new_node = (struct tree_node * )malloc(sizeof(struct tree_node));
    new_node->valeur = (int*)malloc(sizeof(int));
    *new_node->valeur = *left->valeur + *right->valeur;     //D'après les règles de l'arbre d'Huffman, la valeur du noeud est égale...
    new_node->pere = NULL ;                                //...à la somme des valeurs de ses noeuds fils
    new_node->gauche = left ; 
    new_node->droite = right ;
    left->pere = new_node ; 
    right->pere = new_node ; 
    return new_node ;  
}

int compareOcc(s_node * n, void * root) {
    struct tree_node * tn = (struct tree_node *) root;
    struct tree_node * tn2 = (struct tree_node *) (n->data);
    if(*tn->valeur==*tn2->valeur) return 0 ; 
    else if(*tn->valeur<*tn2->valeur) return 1; 
         else return -1 ; 
}

struct tree_node * tree_create ( struct byteCoding * indexedCodeTable ){
    struct tree_node * new_tree = (struct tree_node * )malloc(sizeof(struct tree_node));
    new_tree->valeur = (int*)malloc(sizeof(int));
    s_node * liste = list_create() ; 
    int max_oc = 0 ;
    for(int i = 0; i<256 ; i++){
        if(indexedCodeTable[i].occurrence>0){
            struct tree_node * feuille = tree_createNode (NULL, &indexedCodeTable[i].occurrence) ; 
            (void)list_orderedAppend(&liste, &compareOcc, feuille );
        }
    }

    return new_tree ;
}

// destruction d'un arbre et liberation des donnees 
// (sauf au niveau des feuilles)
void tree_destroy( struct tree_node * root ){

    struct tree_node * next ;
    if(root->pere==NULL){
        next = root ; 
        free(root);   
    }
    if(next->droite!=NULL){
        tree_destroy(next->droite); 
        tree_destroy(next->gauche); 
    }
 
}

/*
// construit les codes de huffman en parcourant l'arbre  
//Racine tree_buildHuffmanCode(tree,1,0)
void tree_buildHuffmanCode(struct tree_node * root, int level, int code){
    if(root->left!=NULL){
        tree_buildHuffmanCode(root->left,level*10,code+level); 
    }
        tree_buildHuffmanCode(root,level/10,code+level); 

}
 */