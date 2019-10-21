#include <iostream>
#include <vector>
using namespace std;

class node
{
public:
    char name;
    int num;

    node() : name('*'), num(0){};
    node(char na, int nu) : name(na), num(nu){};
    void operator=(const node &d)
    {
        this->name = d.name;
        this->num = d.num;
    }
};

class que
{
public:
    vector<node> v;
    void push(char, int);
    node pop();
    void choose_short(int);
    void choose_elevator(int, int &);
};

void que::push(char na, int nu)
{
    v.push_back(node(na, nu));
}

node que::pop()
{
    node d = v[0];
    v.erase(v.begin());
    return d;
}

void que::choose_short(int now_num)
{ //��̾������ȣ�����̾���Ĵŵ����ڶ��п�ʼ
    int n = v.size();
    int j = 0;
    int min = 999;
    for (int i = 0; i < n; i++)
    {
        int min_now = abs(v[i].num - now_num);
        if (min_now <= min)
        {
            j = i;
            min = min_now;
        }
    }
    node d = v[j];
    v[j] = v[0];
    v[0] = d;
}

void que::choose_elevator(int now_num, int &f)
{ //���ݵ���ѡ��ѡ�������з��������
    int n = v.size();
    if (f == 1)
    {
    f1:
        int j = 0;
        int min = 999;
        int min_t = min;
        for (int i = 0; i < n; i++)
        {
            int min_now = v[i].num - now_num;
            if (min_now >= 0 && abs(min_now) <= abs(min))
            {
                j = i;
                min = abs(min_now);
            }
        }
        if (min == min_t)
        { //�ı䷽��
            f = 0;
            goto f2;
        }
        node d = v[j];
        v[j] = v[0];
        v[0] = d;
    }
    else
    {
    f2:
        int j = 0;
        int min = 999;
        int min_t = min;
        for (int i = 0; i < n; i++)
        {
            int min_now = v[i].num - now_num;
            if (min_now <= 0 && abs(min_now) <= abs(min))
            {
                j = i;
                min = abs(min_now);
            }
        }
        if (min == min_t)
        { //�ı䷽��
            f = 1;
            goto f1;
        }
        node d = v[j];
        v[j] = v[0];
        v[0] = d;
    }
}
