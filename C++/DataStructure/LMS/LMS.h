#ifndef LMS_H
#define LMS_H

#include "BTree.h"
#include "Book.h"
#include "LInfo.h"

class LMS {
public:
    LMS();
    ~LMS();

    void setTime(); // ���õ�ǰʱ��
    void insert(); // �ɱ����
    void remove(); // ������
    void lend(); // ����
    void back(); // �黹
    void show(); // ��ʾ

    void showAuthor(); // �г�ĳ����ȫ������
    void showBook(); // �г�ĳ��״̬
    void subscribe(); // ԤԼ����

    void run();

private:
    BTree<Book> *bt;
    LInfo *linfo;
    int datenow;
};

LMS::LMS() {
    bt = new BTree<Book>();
    linfo = new LInfo();
    datenow  = 0;
}

LMS::~LMS() {
    delete bt;
    delete linfo;
}

void LMS::setTime() {
    cout << "�����뵱ǰʱ�䣺";
    cin >> datenow;
    cout << "Success!" << endl;
}

void LMS::insert() {
    cout << "������Ҫ���������š����������ߡ�������";
    int k; string n; string a; int as;
    cin >> k >> n >> a >> as;
    Book *t = new Book(k,n,a,as,as);
    Book *b;
    if (bt->get(*t, b)) {
        if (b->name != n || b->author != a) {
            cout << "������Ϣ������" << endl << "Faild!" << endl;
            return;
        }
        b->amountNow += as;
        b->amountSum += as;
        cout << "Success!" << endl;
        return;
    }
    bt->insert(*t)? cout << "Success!" << endl: cout << "Faild!" << endl;
}

void LMS::remove() {
    cout << "������Ҫ���������ţ�";
    int k;
    cin >> k;
    Book b(k);
    bt->remove(b)? cout << "Success!" << endl: cout << "Faild!" << endl;
}

void LMS::lend() {
    cout << "��������ĵ���š�ͼ��֤�š��黹���ޣ�AABBCC����";
    int k, n, d;
    cin >> k >> n >> d;
    Book b(k);
    if (bt->contain(b)) {
        Book *book;
        bt->get(b, book);
        if (book->amountNow <= 0) {
            cout << "��ͼ����û�п�棡" << endl;
        } else {
            book->amountNow--;
            linfo->add(k, n, d);
            cout << "���ĳɹ���" << endl;
        }
    } else {
        cout << "�ֿ�û�и��飡" << endl;
    }
}

void LMS::back() {
    cout << "������Ҫ�黹����š�ͼ��֤�ţ�";
    int k, n;
    cin >> k >> n;
    Book b(k);
    if (!bt->contain(b)) {
        cout << "��Ŵ��󣬲ֿ�û�и��飡" << endl;
    } else {
        if (!linfo->contain(k, n)) {
            cout << "�黹��Ϣ���󣨹黹�����޴���Ϣ��!" << endl;
        } else {
            Book *book;
            bt->get(b, book);
            if (book->amountNow >= book->amountSum) {
                cout << "�黹��Ϣ���󣨸������������ޣ���" << endl;
            } else {
                Info *info;
                linfo->search(n, info);
                if (datenow > info->date) {
                    cout << "�����ڣ��븶���ڽ�" << (datenow-info->date)*1 << "Ԫ��" << endl << "�黹�ɹ���";
                } else {
                    cout << "�黹�ɹ���" << endl;
                }
                linfo->del(n);
                book->amountNow++;
            }
        }
    }
}

void LMS::show() {
    bt->display();
}

void LMS::showAuthor() {

}

void LMS::showBook() {

}

void LMS::subscribe() {

}

void LMS::run() {
    cout << "������ͼ�����ϵͳ������" << endl;
    while(1) {
        cout << "1.�ɱ���� 2.������ 3.����ͼ�� 4.�黹ͼ��" << endl
            << "5.��ʾ��� 6.�������� 7.ͼ��״̬ 8.ԤԼ����" << endl
            << "0.����ʱ�� -1.�˳�    ������Ҫʹ�õĹ��ܣ�";
        int input1;
        cin >> input1;
        if(-1 == input1) break;
        switch (input1)
        {
            case 0:
                setTime();
                break;
            case 1:
                insert();
                break;
            case 2:
                remove();
                break;
            case 3:
                lend();
                break;
            case 4:
                back();
                break;
            case 5:
                show();
                break;
            case 6:
                showAuthor();
                break;
            case 7:
                showBook();
                break;
            case 8:
                subscribe();
                break;
            default:
                cout << "��������ȷѡ�" << endl;
                break;
        }
        system("pause");
    }
}

#endif // LMS_H