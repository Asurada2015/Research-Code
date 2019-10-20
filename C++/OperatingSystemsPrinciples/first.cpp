#include <iostream>
#include <vector>
#include "que.h"
using namespace std;

class work
{
private:
    int N;
    int now_t;
    que waitq;
    que readyq;
    node *r1, *r2;

    double zz_t;
    double dzz_t;

public:
    work();
    void run(int);
};

work::work()
{
    N = 10;
    char name[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'}; //��ҵ����
    int arr_t[N] = {0, 2, 5, 7, 12, 15, 4, 6, 8, 10}; //����ʱ��
    int run_t[N] = {7, 10, 20, 30, 40, 8, 8, 20, 10, 12};
    for (int i = 0; i < N; i++)
    {
        waitq.push(name[i], arr_t[i], run_t[i]);
    }
    // waitq.sort_sjf();
    // for (int i = 0; i < N; i++)
    // {
    //     cout << waitq.v[i].name << " " << waitq.v[i].arr_t << " " << waitq.v[i].run_t << endl;
    // }
}

void work::run(int type)
{
    r1 = NULL;
    r2 = NULL;
    zz_t = 0;
    dzz_t = 0;
    now_t = 0;
    waitq.sort_fcfs();
    for (now_t = 0; waitq.v.size() || readyq.v.size() || r1 || r2; now_t++)
    {
        //����ɵĽ����˳�
        if (r1)
        {
            if (r1->in_t + r1->run_t <= now_t)
            {
                int zz = now_t - r1->arr_t;
                zz_t += zz;
                dzz_t += (double)zz / (double)r1->run_t;
                cout << r1->name << "��" << now_t << "s�������" << endl;
                r1 = NULL;
            }
        }
        if (r2)
        {
            if (r2->in_t + r2->run_t <= now_t)
            {
                int zz = now_t - r2->arr_t;
                zz_t += zz;
                dzz_t += (double)zz / (double)r2->run_t;
                cout << r2->name << "��" << now_t << "s�������" << endl;
                r2 = NULL;
            }
        }

        //�ȴ���������ʱ��Ľ����������
        if (waitq.v[0].arr_t == now_t)
        {
            node d = waitq.pop();
            readyq.push(d.name, d.arr_t, d.run_t);
            cout << d.name << "�ڵ�" << now_t << "s�ȴ�" << endl;
        }

        //������������
        switch (type)
        {
        case 0:
            readyq.sort_fcfs();
            break;
        case 1:
            readyq.sort_sjf();
            break;
        case 2:
            readyq.sort_hrrn(now_t);
            break;
        default:
            break;
        }

        //����������ҵ��������
        if (readyq.v.size())
        {
            if (!r1)
            { //r1���̿���
                node d = readyq.pop();
                r1 = &d;
                r1->in_t = now_t;
                cout << r1->name << "�ڵ�" << now_t << "s��r1����" << endl;
                //�������̶��п����Ҿ�������������
                if (readyq.v.size())
                {
                    if (!r2)
                    {
                        node d = readyq.pop();
                        r2 = &d;
                        r2->in_t = now_t;
                        cout << r2->name << "�ڵ�" << now_t << "s��r2����" << endl;
                    }
                }
            }
            else if (!r2)
            { //r2���̿���
                node d = readyq.pop();
                r2 = &d;
                r2->in_t = now_t;
                cout << r2->name << "�ڵ�" << now_t << "s��r2����" << endl;
            }
        }
    }
    zz_t /= N;
    dzz_t /= N;
    cout << zz_t << " " << dzz_t << endl;
}

int main()
{
    while (1)
    {
        int type;
        cout << "0: �����ȷ���" << endl
             << "1: ����ҵ����" << endl
             << "2: ��Ӧ�ȸ�����" << endl
             << "����Ҫʹ�õķ�����";
        cin >> type;
        work w;
        w.run(type);
    }
    return 0;
}