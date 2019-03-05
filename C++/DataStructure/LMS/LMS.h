#ifndef LMS_H
#define LMS_H

#include "BTree.h"
#include "Book.h"

class LMS {
public:
    LMS();
    ~LMS();

    void insert(); // �ɱ����
    void remove(); // ������
    void lend(); // ����
    void back(); // �黹
    void show(); // ��ʾ

    void showAuthor(); // �г�ĳ����ȫ������
    void showBook(); // �г�ĳ��״̬
    void subscribe(); // ԤԼ����

private:
    BTree<Book> *lms;
};

LMS::LMS() {
    lms = new BTree<Book>();
}

LMS::~LMS() {
    delete lms;
}

void LMS::insert() {

}

void LMS::remove() {

}

void LMS::lend() {

}

void LMS::back() {

}

void LMS::show() {

}

void LMS::showAuthor() {

}

void LMS::showBook() {

}

void LMS::subscribe() {

}

#endif // LMS_H