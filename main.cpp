#include <stdio.h>
#include <stdlib.h>

#define LH +1   //左子树比右子树高：左高
#define EH 0    //等高
#define RH -1   //右高

#define TRUE 1;
#define FALSE 0;
#define OK 1;
#define ERROR 0;
#define OVERFLOW 1;
typedef int Status;

//树节点
typedef struct BBSTNode {
    int data;   //数据域
    int bf;     //节点平衡因子
    struct BBSTNode *lchild, *rchild;
}*BBSTree;

//右旋调整
void R_Rotate(BBSTree &p){
    BBSTree lc = p->lchild;     //对最小失衡子树 p 作右旋调整
    p->lchild = lc->lchild;     //lc 指向 p 节点的左孩子
    lc->rchild = p;             //将 p 作为 lc 的右孩子
    p = lc;                     //p 指向新的节点
}

//左旋调整
void L_Rotate(BBSTree &p){
    BBSTree rc = p->rchild;     //对最小失衡子树 p 作左旋调整
    p->rchild = rc->rchild;     //rc 指向 p 节点的左孩子
    rc->rchild = p;             //将 p 作为 rc 的左孩子
    p = rc;                     //p 指向新的节点
}

//LR调整
void LeftBalance(BBSTree &T){
    BBSTree lc,rd;
    lc = T->lchild;
    switch (lc->bf) {
        case LH:
            T->bf = lc->bf = EH;    R_Rotate(T);    break;
        case RH:
            rd = lc->rchild;
            switch (rd->bf) {
                case LH: T->bf = RH;    lc->bf = EH;    break;
                case EH: T->bf = lc->bf = EH;           break;
                case RH: T->bf = EH;    lc->bf = LH;    break;
            }
            rd->bf = EH;
            L_Rotate(T->lchild);    //对T的左子树 左旋调整
            R_Rotate(T);            //对T作右旋调整
            break;
    }
}

//RL调整
void RightBalance(BBSTree &T){
    BBSTree lc,rd;
    lc = T->rchild;
    switch (lc->bf) {
        case LH:
            T->bf = lc->bf = EH;
            R_Rotate(T);
            break;
        case RH:
            rd = lc->lchild;
            switch (rd->bf) {
                case LH: T->bf = RH;    lc->bf = EH;    break;
                case EH: T->bf = lc->bf = EH;           break;
                case RH: T->bf = EH;    lc->bf = LH;    break;
            }
            rd->bf = EH;
            L_Rotate(T->rchild);    //对T的左子树 左旋调整
            R_Rotate(T);            //对T作右旋调整
            break;
    }
}

//插入
Status InsertAVL(BBSTree &T, int e,  Status &taller){
    if(NULL == T){
        T = (BBSTree) malloc(sizeof(BBSTNode));
        T->bf = EH;
        T->lchild = NULL;
        T->rchild = NULL;
        taller = TRUE;
    } else if(e == T->data){
        taller = FALSE;
        return FALSE;//未插入
    }else if(e < T->data){
        if(FALSE == InsertAVL(T->lchild, e, taller)) return FALSE;
        if(TRUE == taller){
            switch ( T->bf) {
                case LH:
                    LeftBalance(T);
                    taller = FALSE;
                    break;
                case EH:
                    T->bf = LH;
                    taller = TRUE;
                    break;
                case RH:
                    T->bf = EH;
                    taller = FALSE;
                    break;
            }
        }
    } else{ //插入右子树
        if(FALSE == InsertAVL(T->rchild, e, taller)) return FALSE;
         if(TRUE == taller){
            switch (T->bf) { //检查平衡因子
                case LH:
                    T->bf = EH;
                    taller = FALSE;
                    break;
                case EH:
                    T->bf = RH;
                    taller = TRUE;
                    break;
                case RH:
                    RightBalance(T);
                    taller = FALSE;
                    break;
            }
         }

    }
    return TRUE;
}

int main(){

}
