#include <iostream>
#include <vector>
#include <iomanip>
#include "que_disk.h"

using namespace std;

class work
{
private:
    int N;
    que waitq;
    node *r;
    int now_num; //��ǰ�ŵ�
    double ave_num;
    int f; //����

public:
    work();
    void run(int);
};

work::work()
{
    r = NULL;
    N = 14;
    char name[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N'}; //��ҵ����
    int num[N] = {30, 50, 100, 180, 20, 90, 150, 70, 80, 10, 160, 120, 40, 110};           //����ʱ��
    for (int i = 0; i < N; i++)
    {
        waitq.push(name[i], num[i]);
    }
}

void work::run(int type)
{
    f = 1; //������ķ����ƶ�
    ave_num = 0;
    now_num = 90;
    while (waitq.v.size())
    {
        //ѡ����һ��Ҫ����Ĵŵ�
        switch (type)
        {
        case 0:
            break;
        case 1:
            waitq.choose_short(now_num);
            break;
        case 2:
            waitq.choose_elevator(now_num, f);
            break;
        default:
            break;
        }
        node d = waitq.pop();
        r = &d;
        int mov_num = abs(now_num - r->num);
        ave_num += mov_num;
        cout << setw(3) << now_num << " -> " << r->name << setw(5) << r->num
             << "  mov " << setw(3) << mov_num << endl;
        now_num = r->num;
    }
    ave_num /= N;
    cout << "average mov: " << ave_num << endl;
}

int main()
{
    while (1)
    {
        int type;
        cout << "0: �����ȷ���" << endl
             << "1: ���Ѱ������" << endl
             << "2: ���ݵ���" << endl
             << "����Ҫʹ�õķ�����";
        cin >> type;
        work w;
        w.run(type);
    }
    return 0;
}