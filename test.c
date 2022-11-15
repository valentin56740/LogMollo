#include "tree_etu.h"
#include <stdio.h>

int main(void){
    
    struct byteCoding Table[256] ; 

    //Test de la fonction tree_resetByteOccurence 
    printf("\nTest tree_resetByteOccurence:\n"); 
    tree_resetByteOccurrence(Table); 
    int i  ; 
    int res = 0 ; 
    for(i=0;i<256;i++){
        res += Table[i].occurrence ;
    }
    if(res!=0){
        printf("Erreur somme des occurence != 0\n");
    }else{
        printf("Nombre d'occurences ok\n");
    }

    //Test de la fonction tree_resetByteCoding  
    printf("\n\nTest tree_resetByteCoding:\n"); 
    tree_resetByteCoding(Table); 
    int res2 = Table[255].huffmanCode+Table[0].huffmanCode+Table[256/2].huffmanCode+Table[255].nbBits+Table[0].nbBits+Table[256/2].nbBits; 
    int res3 = 0 ; 
    for(i=0;i<256;i++){
        res2 += Table[i].huffmanCode+Table[i].nbBits ; 
        res3 = (Table[i].byte == i) ; 
    }
    if(res2 != 0 && res3) {
        printf("Erreur somme des codes != 0\n");
    }else{
        printf("Somme des codes ok\n\n");
    }
    


    tree_countByteOccurrence("aabc",4,Table);
    //tree_displayByteCoding(Table); 
 
    int x1 = 5 ; 
    int x2 = 3 ; 
    struct tree_node * node1 = tree_createNode(NULL,&x1); 
    struct tree_node * node2 = tree_createNode(NULL,&x2);
    printf("\n Valeur du node créé: %d",*node1->valeur);  
    printf("\n Valeur du node créé: %d \n",*node2->valeur);  
    struct tree_node * node3 = tree_createCodingNode(node1,node2); 
    printf("\n Valeur du node créé: %d \n",*node3->valeur);

    



    return 0 ; 
}