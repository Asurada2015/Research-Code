#include"Elevator.h"

int main() {
	long int time = 0;
	int a = 0, j = 1;
	cout << "�����빲�м�λ�˿�ʹ�õ��ݣ�";
	cin >> a;
	Passenger *people = new Passenger[a + 1];
	for (int i = 1; i < a + 1; i++) {
		people[i].setData(i);
		cout << endl;
	}
	Elevator x;
	long int Time = 0;
	
	Time = a * 1000;//�˴������ò��������Ž⣬Ŀǰ��û���ҵ�һ���ȽϺ��ʵ�ֵ����
	for (; time < Time; time++) {
		cout << time << "tʱ��  ";
		for (int i = 1; i < a + 1; i++) {
			if (people[i].getWhenWait() == time)x.addPassenger(people[i]);
		}
		cout << "������" << x.getFloor() << "��  ";
		x.judgeGiveUp(time);
		cout << endl;
	}
	delete[]people;
	system("pause");
	return 0;
}