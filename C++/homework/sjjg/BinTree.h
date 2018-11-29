#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <typename T>
struct BTNode {
    T data;
    BTNode<T> *lc, *rc;
    BTNode(): lc(NULL), rc(NULL) {}
    BTNode(T x, BTNode<T> *l=NULL, BTNode<T> *r=NULL)
        :data(x), lc(l), rc(r) {}
};

template <typename T>
class BinTree {
public:
    BinTree() {root=NULL; CreateBinTree();}
    ~BinTree() {destory();}
    void destory() {return destory(root);} //ɾ�����нڵ�
    void CreateBinTree() {CreateBinTree(root);} // ǰ���������������
    void CreateBinTree_1(){CreateBinTree_1(root);} // �������������
    bool IsEmpty() {return (!root)?true:false;} // �ж��Ƿ�Ϊ��
    int Height() {return Height(root);} // ��ȡ�������߶�
    int Size() {return Size(root);} // ��ȡ�������������
    int getLevel(BTNode<T> *current); // ��ȡ��ǰ�ڵ�߶�
    BTNode<T> *Parent(BTNode<T> *current) { // ��ȡ��ǰ�ڵ�ĸ��ڵ�ָ��
        return (!root || root==current)?NULL:Parent(root, current);
    }
    BTNode<T> *getRoot()const {return root;} // ��ȡ���ڵ�ָ��
    void preOrder() { // ǰ�����
        vector<T> vec;
        preOrder(root, vec);
        for (int i=0; i<vec.size(); i++) cout << vec[i];
        cout << endl;
    }
    void inOrder() { // �������
        vector<T> vec;
        inOrder(root, vec);
        for (int i=0; i<vec.size(); i++) cout << vec[i];
        cout << endl;
    }
    void postOrder() { // �������
        vector<T> vec;
        postOrder(root, vec);
        for (int i=0; i<vec.size(); i++) cout << vec[i];
        cout << endl;
    }
    void Print() {Print(root);} // ���뷨���������

    int LeafNodeNum() {return LeafNodeNum(root);} // 5-23(1)��ȡҶ�������
    void Conversion() {return Conversion(root);} // 5-23(2)��ת���������������Һ��ӣ�
    bool Find_PrintAncestor(T x); // 5-26���ҽ�㲢����������Ƚڵ�
    BTNode<T> *Find(T x) {return Find(root ,x);} //���ҽ�㲢���ؽ��ָ��
    void PrintAncestor(BTNode<T> *subTree); // ����������Ƚ��

protected:
    BTNode<T> *root;
    void CreateBinTree_1(BTNode<T> *&subTree);
    void CreateBinTree(BTNode<T> *&subTree);
    void destory(BTNode<T> *subTree);
    int Height(BTNode<T> *subTree);
    int Size(BTNode<T> *subTree);
    BTNode<T> *Parent(BTNode<T> *subTree, BTNode<T> *current);
    void preOrder(BTNode<T> *subTree, vector<T> &out);
    void inOrder(BTNode<T> *subTree, vector<T> &out);
    void postOrder(BTNode<T> *subTree, vector<T> &out);
    void Print(BTNode<T> *subTree);

    int LeafNodeNum(BTNode<T> *subTree);
    void Conversion(BTNode<T> *subTree);
    BTNode<T> *Find(BTNode<T> *subTree, T x);
};

template <typename T>
void BinTree<T>::destory(BTNode<T> *subTree) {
    if (subTree) {
        destory(subTree->lc);
        destory(subTree->rc);
        delete subTree;
    }
};

template <typename T>
void BinTree<T>::CreateBinTree(BTNode<T> *&subTree) {
    
};

template <typename T>
void BinTree<T>::CreateBinTree_1(BTNode<T> *&subTree) {
    stack<BTNode<T> *> s;
    subTree = NULL;
    BTNode<T> *p, *t; int k;
    T c;
    cin >> c;
    while (';' != (char)c) {
        switch ((char)c) {
            case '(': s.push(p); k=1; break;
            case ')': t=s.top(); s.pop(); break;
            case ',': k=2; break;
            default: p = new BTNode<T>(c);
                if (NULL == subTree) subTree = p;
                else if (1 == k) {
                    t = s.top(); t->lc = p;
                } else {
                    t = s.top(); t->rc = p;
                }
        }
        cin >> c;
    }
};

template <typename T>
int BinTree<T>::Height(BTNode<T> *subTree) {
    if (!subTree) return 0;
    else {
        int i = Height(subTree->lc);
        int j = Height(subTree->rc);
        return (i<j)? j+1: i+1;
    }
};

template <typename T>
int BinTree<T>::Size(BTNode<T> *subTree) {
    if (!subTree) return 0;
    else return 1+Size(subTree->lc)+Size(subTree->rc);
};

template <typename T>
int BinTree<T>::getLevel(BTNode<T> *current) {
    if (root == current) return 1;
    else return 1 + getLevel(Parent(current));
};

template <typename T>
BTNode<T> *BinTree<T>::Parent(BTNode<T> *subTree, BTNode<T> *current) {
    if (!subTree) return NULL;
    if (subTree->lc == current || subTree->rc == current) return subTree;
    BTNode<T> *p = Parent(subTree->lc, current);
    if (p) return p;
    else return Parent(subTree->rc, current);
};

template <typename T>
void BinTree<T>::preOrder(BTNode<T> *subTree, vector<T> &out) {
    if (subTree) {
        out.push_back(subTree->data);
        preOrder(subTree->lc, out);
        preOrder(subTree->rc, out);
    }
};

template <typename T>
void BinTree<T>::inOrder(BTNode<T> *subTree, vector<T> &out) {
    if (subTree) {
        inOrder(subTree->lc, out);
        out.push_back(subTree->data);
        inOrder(subTree->rc, out);
    }
};

template <typename T>
void BinTree<T>::postOrder(BTNode<T> *subTree, vector<T> &out) {
    if (subTree) {
        postOrder(subTree->lc, out);
        postOrder(subTree->rc, out);
        out.push_back(subTree->data);
    }
};

template <typename T>
void BinTree<T>::Print(BTNode<T> *subTree) {
    if (!subTree) return;
    Print(subTree->lc);
    int x = getLevel(subTree) - 1;
    while (x--) cout << '\t';
    cout << subTree->data << endl;
    Print(subTree->rc);
};

template <typename T>
int BinTree<T>::LeafNodeNum(BTNode<T> *subTree) {
    if (!subTree) return 0;
    else if (!subTree->lc && !subTree->rc) return 1;
    else {
        int i = LeafNodeNum(subTree->lc);
        int j = LeafNodeNum(subTree->rc);
        return i+j;
    }
};

template <typename T>
void BinTree<T>::Conversion(BTNode<T> *subTree) {
    if (subTree) {
        BTNode<T> *p = subTree->lc;
        subTree->lc = subTree->rc;
        subTree->rc = p;
        Conversion(subTree->lc);
        Conversion(subTree->rc);
    }
};

template <typename T>
bool BinTree<T>::Find_PrintAncestor(T x) {
    BTNode<T> *p = Find(root, x);
    if (!p) return false;
    PrintAncestor(p);
};

template <typename T>
BTNode<T> *BinTree<T>::Find(BTNode<T> *subTree, T x) {
    if (!subTree) return NULL;
    if (x == subTree->data) return subTree;
    else {
        BTNode<T> *p = Find(subTree->lc, x);
        if (p) return p;
        else return Find(subTree->rc, x);
    }
};

template <typename T>
void BinTree<T>::PrintAncestor(BTNode<T> *subTree) {
    if (!subTree) return;
    BTNode<T> *p = Parent(root, subTree);
    if (p != root) {
        cout  << " <- " << p->data;
        PrintAncestor(p);
    }
    else if (p == root) cout << " <- "<< p->data << endl;
};
