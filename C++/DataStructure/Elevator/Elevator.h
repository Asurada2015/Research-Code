#ifndef ELEVATOR_H
#define ELEVATOR_H

#include"PList.h"
#include"Passenger.h"

enum state {
	Opening,
	Opened,
	Closing,
	Closed,
	Waiting,
	Up,
	Down,
	In,
	Out,
	Accelerate,
	Decelerate
};

int holdtime = 0, record = 0, near = 0;

enum timeX {
	test = 40, // ����������ϵ��ݵĳ˿�
	open = 20, // ����
	close = 20, // ����
	in = 25, // ��
	out = 25, // ��
	accelerate = 15, //����
	up = 51, // ����һ��
	updecelerate = 14, //��������
	down = 61, // ����һ��
	downdecelerate = 23, //�½�����
	wait = 300 // ��ֹʱ��
};

class Elevator {
private:
	state stateNow;
	int floor;
	PList *pList;
	Node *waitP;
	int inElevator[10];
	int all;
	int dir; // �ж����µ����

public:
	Elevator();
	~Elevator() {delete pList;}
	state getNowState()const {return stateNow;}
	void setNowState(state t) {stateNow = t;}
	int getFloor()const {return floor;}
	void setfloor(int floor1) {floor = floor1;}
	int getAll()const {return all;}
	void setAll(int num); {all += num;} // numΪ�ⲿ�ϵ��ݵ�����
	int getDir()const {return dir;}
	void setDir(int x) {dir = num;}
	void addPassenger(const Passenger &x);// ��ӳ˿�
	bool noPassenger(); // �ж��Ƿ��г˿�����
	void judgeDirction(); // �жϵ������߷���
	bool judgeOpen(); // �ж��Ƿ���
	void OPEN(); // �����Ŵ�
	bool judgeOut(); // �жϳ˿ͳ�ȥ
	void OUT(); // �˿ͳ�ȥ
	bool judgeIn(); // �жϳ˿ͽ���
	void IN(); // �˿ͽ���
	void CLOSE(); // ����
	void moveUp(); // �����ƶ�
	void moveDown(); // �����ƶ�
	void judgeClose(); // 40tʱ�����ж��Ƿ����
	void moveDirction(const int floor1); // �����ı���ݵ�״̬
	void judgeGiveUp(int waittime); // �ж��Ƿ����˷��������ں����ʼ
};

Elevator::Elevator() {
	stateNow = Waiting;
	floor = 1;
	pList = new PList();
	waitP = pList->getHead();
	for (int i=0; i<10; i++)inElevator[i] = 0;
	all = 0;
	dir = -1;
}

void Elevator::addPassenger(const Passenger &x) {
	pList->append(x);
	cout << " ��" << x.getID() << "���˿ͽ���ȴ����� ";
}

bool Elevator::noPassenger() {
	//�����жϵ����Ƿ���ճ˿͵�����
	if (getNowState() == Waiting) {
		if (holdtime == 300 && floor != 1) {
			//����ȹ���300t���Ҳ���1¥�Ļ�����ʼ����
			setNowState(Down);
			setDir(0);
			holdtime = 0;
			moveDown();
			return true;
		} else if (holdtime == 300 && floor == 1) {
			//������ݱ�����һ¥����Ҫ���в���
			cout << "���ݿ������ˣ����ڵȴ�";
			holdtime = 0;
			return true;
		} else if (all == 0 && pList->empty() == true) {
			cout << "���ݿ������ˣ����ڵȴ�";
			holdtime++;
			return true;
		} else {
			judgeDirction();
			return false;
		}
	} else {
		judgeDirction();
		return false;
	}
}

void Elevator::judgeDirction() {
	//ʹ�øú��������жϵ��ݵ�����
	near = floor;//��ʼ��near��ֵ��Ϊ��ֹ�������������������ʱ���ɿ���ʹ��MoveDirction����
	int upoutfar = 0, downoutfar = 10;//����2����¼���³�ȥ��Զ����ı���
	int upinfar = 0, downinfar = 10;//����2����¼���½�����Զ����ı���
	if (stateNow == Closed) {
		if (getAll() == 0 && pList->empty() == true) {
			setNowState(Waiting);
			return;
		}
		if (floor == 1) {
			setNowState(Up); setDir(1);
		}
		if (floor == 9) {
			setNowState(Down); setDir(0);
		}
		if (getAll() != 0) {//��������������
			//��ʱ��Ҫ���ֵ��ݵ����з��򣬷��������������Ŀǰ��δ����
			for (int i = 1; i < 10; i++) {
				if (inElevator[i] != 0) {
					near = i;
					if (i > floor) {
						upinfar = i;
						setNowState(Up);
						setDir(1);
						break;
					} else if (i < floor) {
						downinfar = i;
						setNowState(Down);
						setDir(0);
						break;
					}
				}
			}
		}
		if (pList->empty() == false) {//������ȴ����˲�Ϊ��
			Node * ptemp = pList->getHead()->next;
			while (ptemp != NULL) {
				if (getDir() == 1) {//ֻ�����г˿�
					if (ptemp->data.getNowFloor() > floor) {//�˿�����¥���ڵ���¥���ϣ��������п��ܵ���ǰ������
						//��ʼ�����������еĳ˿ͣ����ҽ����ж��Ƿ���Ҫ���е�
						if (ptemp->data.getGoFloor() > ptemp->data.getNowFloor()) {
							//������������У��������ڵ������з����¥�ϣ���Ҫǰ������
							if (ptemp->data.getGoFloor() > upoutfar)upoutfar = ptemp->data.getGoFloor();
						}
						if (ptemp->data.getGoFloor() < ptemp->data.getNowFloor()) {
							if (ptemp->data.getNowFloor() > upoutfar)upoutfar = ptemp->data.getNowFloor();
						}
					}
					if (upinfar == 0 && upoutfar == 0) { setNowState(Down); setDir(0); }
					if (upinfar <= upoutfar)near = upoutfar;
					else near = upinfar;
				} else if (getDir() == 0) {//ֻ�����г˿�
					if (ptemp->data.getNowFloor() < floor) {//�˿�����¥���ڵ���¥���£��������п��ܵ���ǰ������
						//��ʼ�����������еĳ˿ͣ����ҽ����ж��Ƿ���Ҫ���е�
						if (ptemp->data.getGoFloor() < ptemp->data.getNowFloor()) {
							//������������У��������ڵ������з����¥�£���Ҫǰ������
							if (ptemp->data.getGoFloor() < downoutfar)downoutfar = ptemp->data.getGoFloor();
						}
						if (ptemp->data.getGoFloor() > ptemp->data.getNowFloor()) {
							if (ptemp->data.getNowFloor() < downoutfar)downoutfar = ptemp->data.getNowFloor();
						}
					}
					if (downinfar == 10 && downoutfar == 10) { setNowState(Up); setDir(1); }
					if (downinfar <= downoutfar)near = downinfar;
					else near = downoutfar;
				}
				ptemp = ptemp->next;
			}
		}

	}
	if (stateNow == Waiting) {
		Node * ptemp = pList->getHead()->next;
		int time_now = 0;
		while (ptemp != NULL) {
			int Time_now = ptemp->data.getWhenWait();//���ڼ�¼���Ȱ�����
			time_now = Time_now;
			if (ptemp->data.getWhenWait() < time_now){//��ѡ�����Ȱ������ˣ�Ȼ����иı���ݵķ���
				time_now = ptemp->data.getWhenWait();
			}
			ptemp = ptemp->next;
		}
		ptemp = pList->getHead()->next;
		while (ptemp != NULL) {
			int up(floor), down(floor);
			if (ptemp->data.getWhenWait() == time_now) {
				int x = ptemp->data.getGoFloor() - ptemp->data.getNowFloor();
				//��ʱ�����4�����������ֻ����2���ǵ������У�2���ǵ�������
				if ((x > 0 && (ptemp->data.getNowFloor() > floor)) || (x<0 && (ptemp->data.getNowFloor()>floor))) {
					setNowState(Up);
					setDir(1);
					upinfar = ptemp->data.getNowFloor();
					if (up < upinfar) {
						up = upinfar;
					}
				} else if ((x > 0 && (ptemp->data.getNowFloor() < floor)) || (x < 0 && (ptemp->data.getNowFloor() < floor))) {
					setNowState(Down);
					setDir(0);
					downinfar = ptemp->data.getNowFloor();
					if (down > downinfar) {
						down = downinfar;
					}
				}
				if (down != floor&&up != floor) {//������ͬʱ��������ʱ���������ϵ�ԭ��
					setNowState(Up); near = upinfar; setDir(1);
				} else if (up != floor) {//ֻ�����е�����
					setNowState(Up); near = upinfar; setDir(1);
				} else if (down != floor) {//ֻ�����е�����
					setNowState(Down); near = downinfar; setDir(0);
				}
				if (floor == 1) { setNowState(Up); setDir(1); }
			}
			ptemp = ptemp->next;
		}
		if (near == floor)  OPEN();
	}
	if (stateNow == Up) {
		if (getAll() != 0) {//����������
			for (int i = 1; i < 10; i++) {
				if (inElevator[i] != 0) {
					if (i >= near) {
						upinfar = i;
					}
				}
			}
		}
		if (pList->empty() == false) {
			Node * ptemp = pList->getHead()->next;
			while (ptemp != NULL) {
				if (ptemp->data.getNowFloor() >= near) {
					if (ptemp->data.getGoFloor() >= upoutfar) {
						upoutfar = ptemp->data.getGoFloor();
					}
					if (ptemp->data.getNowFloor() >= upoutfar) {
						upoutfar = ptemp->data.getNowFloor();
					}
				}
				ptemp = ptemp->next;
			}
		}
		if (upinfar >= upoutfar)near = upinfar;
		else near = upoutfar;
	}
	if (stateNow == Down) {
		//downinfar = 10, downoutfar = 10;
		if (getAll() != 0) {//����������
			for (int i = 1; i < 10; i++) {
				if (inElevator[i] != 0) {
					if (i <= near) {
						downinfar = i;
						break;
					}
				}
			}
		}
		if (pList->empty() == false) {
			Node * ptemp = pList->getHead()->next;
			while (ptemp != NULL) {
				if (ptemp->data.getNowFloor() <= near) {
					if (ptemp->data.getNowFloor() <= downoutfar) {
						downoutfar = ptemp->data.getNowFloor();
					}
					if (ptemp->data.getGoFloor() <= downoutfar) {
						downoutfar = ptemp->data.getGoFloor();
					}
				}
				ptemp = ptemp->next;
			}
		}
		if (getAll() == 0 && pList->empty() == true)near = 1;
		else if (downinfar >= downoutfar)near = downoutfar;
		else near = downinfar;
	}
	moveDirction(near);
}

bool Elevator::judgeOpen() {//�жϴ�¥���Ƿ�������Ҫ����
	if (judgeIn() || judgeOut()) {
		OPEN();
		return true;
	}
	else return false;
}

void Elevator::OPEN() {
	if (getNowState() != Opening) {
		setNowState(Opening);
		record = 0;
		return;
	}
	if (record < open) {
		record++;
		cout << "���ݿ�����";
		return;
	} else {//������ɺ�
		record = 0;
		cout << "�������";
		setNowState(Opened);
		if (judgeOut())OUT();
		if (judgeIn())IN();
		judgeClose();
	}
}

bool Elevator::judgeOut() {
	if (getAll() != 0) {
		int j = floor;
		if (inElevator[j] != 0)return true;
	}
	return false;
}

void Elevator::OUT() {
	if (record < out) {
		if (getNowState() == Opened) {
			record++;
			cout << "�˿������µ���";
			if (inElevator[floor] != 0) {
				cout << "�ڸò�һ����ȥ" << inElevator[floor] << "����";
				setAll(-inElevator[floor]);
				inElevator[floor] = 0;
			}
			setNowState(Out);
			return;
		}
		if (getNowState() == Out) {
			record++;
			cout << "�˿������µ���";
			return;
		}
	} else {
		cout << "��������Ҫ�µĳ˿Ͷ�����ȥ";
		record = 0;
		setNowState(Opened);
	}
}

bool Elevator::judgeIn() {//�������δ�����򷵻�true�����Լ�������
	//Ŀǰ��Ҫ���ƣ���Ϊ���Ȱ���ɾ����������飬������Ҫ�����и��ж�
	if (getAll() != 13) {
		if (!pList->empty()) {//��Ϊ����ִ��if���
			Node * ptemp = pList->getHead()->next; int upnum1 = 0, downnum1 = 0;
			while (ptemp != NULL) {
				if (ptemp->data.getNowFloor() == floor) {
					if ((ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) && (getDir() > 0)) {
						//�˿��������ߵ�
						return true;
					}
					if ((ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) && (getDir() == 0)) {
						//�˿�����
						return true;
					}
					if (near == ptemp->data.getNowFloor()) {
						//�ﵽ���������¥�㣬���������ݷ���ͬ���򲻸ı䷽�򣬲����������
						//����������ͬ����ı䷽���������������У�����������ͬ�����
						if (getDir() == 1) {
							if (ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) {
								setDir(1); upnum1++;
							}
							if (ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) {
								setDir(0); downnum1++;
							}
							if (upnum1 != 0 && downnum1 != 0)setDir(1);
						} else if (getDir() == 0) {
							if (ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) {
								setDir(1); upnum1++;
							}
							if (ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) {
								setDir(0);  downnum1++;
							}
							if (upnum1 != 0 && downnum1 != 0)setDir(0);
						}
						return true;
					}
				}
				ptemp = ptemp->next;
			}
		}
	}
	return false;
}

void Elevator::IN() {
	if (getAll() < 13) {
		if (record < in)
		{
			if (getNowState() == Opened) {
				record++;
				Node * ptemp = pList->getHead()->next;
				while (ptemp != NULL) {
					if (ptemp->data.getNowFloor() == floor){//�����˵��ڵ���¥�㣬����ܽ����ж�
						if ((ptemp->data.getNowFloor() < ptemp->data.getGoFloor()) && (getDir() > 0)) {
							//�˿��������ߵ�
							cout << "��" << ptemp->data.getID() << "���˿����ڽ������";
							inElevator[ptemp->data.getGoFloor()] += 1;
							setAll(1);
							pList->remove(ptemp->data.getID());
							setNowState(In);
							return;
						}
						if ((ptemp->data.getNowFloor() > ptemp->data.getGoFloor()) && (getDir() == 0)) {
							//�˿�����
							cout << "��" << ptemp->data.getID() << "���˿����ڽ������";
							inElevator[ptemp->data.getGoFloor()] += 1;
							setAll(1);
							pList->remove(ptemp->data.getID());
							setNowState(In);
							return;
						}
					}
					ptemp = ptemp->next;
				}
			}
			if (getNowState() == In) {
				record++;
				cout << "�˿����ڽ������";
				return;
			}
		} else {
			cout << "�˿��Ѿ��������";
			record = 0;
			setNowState(Opened);
		}
	} else {
		cout << "�����������Ѿ��ﵽ���ֵ";
		setNowState(Closing);
	}
}

void Elevator::CLOSE() {
	if (record < close) {
		record++;
		setNowState(Closing);
		cout << "�������ڹ�����";
	} else {
		record = 0;
		cout << "�����Ѿ�����";
		setNowState(Closed);
		if (near == floor) {//�����Ѿ������������¥�㣬���ܻ����4�����
			if (pList->empty() == false || getAll() != 0) {//�ȴ��������˻������Ҳ����
				Node * ptemp = pList->getHead()->next; int OutPeople = 0;
				while (ptemp != NULL) {
					if (ptemp->data.getNowFloor() == floor)OutPeople += 1;
					if (getAll() != 0 && OutPeople != 0) {//���������ˣ���������       �ж�ȥ�ķ���
						if (getDir() == 1 && (ptemp->data.getGoFloor() > floor)) {//�������У��˿����У�����
							setNowState(Opening);
						} else if (getDir() == 0 && (ptemp->data.getGoFloor() < floor)) {//�������У��˿����У�����
							setNowState(Opening);
						}
					}
					if (getAll() == 0 && OutPeople != 0) {//����û�ˣ���������
						if (getDir() == 1) {//��������
							if (ptemp->data.getGoFloor() > floor)
								setNowState(Opening);
							else if (ptemp->data.getGoFloor() < floor) {
								setDir(0); setNowState(Opening);
							}
						}
						if (getDir() == 0) {//��������
							if (ptemp->data.getGoFloor() < floor)
								setNowState(Opening);
							else if (ptemp->data.getGoFloor() > floor) {
								setDir(1); setNowState(Opening);
							}
						}
					}
					if (getAll() != 0 && OutPeople == 0) {
						//���������ˣ�����û�ˣ���ʱӦ�÷��Ƿ�����ͳ˿����л������У����ȱ�������õ��˿�Ҫȥ����
						for (int i = 1; i < 10; i++) {
							if (inElevator[i] != 0) {
								if (i < floor) { setNowState(Down); setDir(0); }
								if (i > floor) { setNowState(Up); setDir(1); }
							}
						}

					}
					ptemp = ptemp->next;
				}
			} else if (pList->empty() == true && getAll() == 0){//�ȴ�����û�ˣ�����Ҳû��
				setNowState(Waiting); setDir(-1);
			}
		} else if (near != floor) {
			if (getDir() == 1) {
				setDir(1); setNowState(Up);
			}
			if (getDir() == 0) {
				setDir(0); setNowState(Down);
			}
		}
		noPassenger();
	}
}

void Elevator::moveUp() {
	if (record < up) {
		record++;
		cout << "����������¥";
		return;
	} else {
		floor++;
		record = 0;
		if (judgeOpen() == false)
			moveUp();
		else {
			cout << "����������¥";
			setNowState(Opening);
		}
	}

}

void Elevator::moveDown() {
	if (record < down) {
		record++;
		cout << "����������¥";
		return;
	} else {
		floor--;
		record = 0;
		if (judgeOpen() == false)moveDown();
		else {
			cout << "����������¥";
			setNowState(Opening);
		}
	}
}

void Elevator::judgeClose() {
	if (getNowState() == Opened){
		if (record < test) {
			record++;
			cout << "���ڹ��ż��";
			return;
		} else {
			cout << "���ż�����";
			if (getNowState() == Opened) {
				record = 0;
				CLOSE();
				return;
			} else {//���ƿ���ɾ��    
				record = 0;
				return;
			}
		}
	}
	else return;
}

void Elevator::moveDirction(const int near) {
	//nearΪ�˿͵�������Զ��¥��
	if (near < floor) {
		setNowState(Down);
		setDir(0);
		moveDown();
		return;
	}
	if (near > floor) {
		setNowState(Up);
		setDir(1);
		moveUp();
		return;
	}
	if (getNowState() == Opening) {
		OPEN();
		return;
	}
	if (getNowState() == In) {
		IN();
		judgeClose();
		return;
	}
	if (getNowState() == Out) {
		OUT();
		judgeClose();
		return;
	}
	if (getNowState() == Opened) {
		judgeClose();
		if (judgeOut())OUT();
		if (judgeIn())IN();
		return;
	}
	if (getNowState() == Closing) {
		CLOSE();
		return;
	}
	if (near == floor&&pList->empty() == true && getAll() == 0) {
		setNowState(Waiting);
		noPassenger();
		return;
	}
	if (near == floor) {
		setNowState(Opening);
		OPEN();
		return;
	}
}

void Elevator::judgeGiveUp(int waittime) {
	//һ����ϵͳ�����жϸ�ʱ���Ƿ����˷���
	//waittimeΪ���ڵ�ʱ�䣬���ںͳ˿͵ȴ���ʱ��+wait�������жϳ˿��Ƿ����
	Node * ptemp = pList->getHead()->next;
	while (ptemp != NULL) {
		if ((ptemp->data.getWhenWait() + ptemp->data.getWaitTime()) <= waittime) {
			cout << "��" << ptemp->data.getID() << "���˿��ѷ����ȴ�  ";
			pList->remove(ptemp->data.getID());
		}
		ptemp = ptemp->next;
	}
	noPassenger();
}

#endif // ELEVATOR_H