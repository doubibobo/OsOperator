#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 100             // �������ֵ�곣��
struct PROHAVING {
    int memoryNumber;
    int memoryHaving;
};

int processNum;             // ���ý��̵���Ŀ
int memoryNum;              // ���÷�������Ŀ

int processMemoryNeed[MAX]; // ������Ҫ�ķ�����С
PROHAVING processMemoryHaving[MAX];   // ������ռ�еĿռ��С
PROHAVING memoryRestHaving[MAX];          // ��������ռ��С

int memory[MAX];        // ÿһ�������Ĵ�С
int memoryRest[MAX];    // ÿ������ʣ��Ŀռ�

int increaseRestMemory[MAX];    // ���մ�С�����˳�����е�����


// ��ʼ������������ÿһ����������Ĵ�СΪ50K
void memoryInit() {
    cout << "��������̵���Ŀ" << endl;
    cin >> processNum;
    cout << "�������������Ŀ" << endl;
    cin >> memoryNum;
    cout << "������ABCDEFGÿһ����������Ҫ���ڴ��С" << endl;
    for (int i = 0; i < processNum; i++) {
        cin >> processMemoryNeed[i];
    }
    for (int i = 0; i < memoryNum; i++) {
        memory[i] = 50;
        memoryRest[i] = 50;
        memoryRestHaving[i].memoryNumber = i;
        memoryRestHaving[i].memoryHaving = 50;
    }
}

// �״���Ӧ�㷨
void firstAdapt() {
    for (int i = 0; i < processNum; i++) {
        for (int j = 0; j < memoryNum; j++) {
            if (processMemoryNeed[i] <=memoryRest[j]) {
                // ����������Ҫ�Ŀռ��СС��ʣ��Ŀռ䣬���Է���
                memoryRest[j] -= processMemoryNeed[i];
                processMemoryHaving[i].memoryNumber = j;
                processMemoryHaving[i].memoryHaving = processMemoryNeed[i];
                break;
            }
        }
    }
}

// ���ñȽϺ���
bool compare(PROHAVING a, PROHAVING b) {
    return a.memoryHaving < b.memoryHaving;   // ���н�������
}

// ��ѷ����㷨��ÿһ�μ����С�Ŀ�������
void bestDistrabute() {
    // ���ȶ��ڴ�ռ������������
    for (int i = 0; i < processNum; i++) {
        sort(memoryRestHaving, memoryRestHaving + memoryNum, compare);
        for (int j = 0; j < memoryNum; j++) {
            if (processMemoryNeed[i] <= memoryRestHaving[j].memoryHaving) {
                memoryRestHaving[j].memoryHaving -= processMemoryNeed[i];
                memoryRest[j] -= processMemoryNeed[i];
                processMemoryHaving[i].memoryNumber = memoryRestHaving[j].memoryNumber;
                processMemoryHaving[i].memoryHaving = processMemoryNeed[i];
                break;
            }
        }
    }
}

// ��ѯ����Ľ��
void display() {
    cout << "��Ҫ����Ľ������У�     \t";
    for (int i = 0; i < processNum; i++) {
        cout << i+1 << "\t";
    }
    cout << endl;

    cout << "ÿ��������Ҫ����Ŀռ��С\t";
    for (int i = 0; i < processNum; i++) {
        cout << processMemoryNeed[i] << "\t";
    }
    cout << endl;

    cout << "�������\t";
    for (int i = 0; i < memoryNum; i++) {
        cout << "����" << i+1 << "\t";
    }
    cout << endl;

    cout << "������С\t";
    for (int i = 0; i < memoryNum; i++) {
        cout << "50\t";
    }
    cout << endl;

    cout << "ʣ���С\t";
    for (int i = 0; i < memoryNum; i++) {
        cout << memoryRest[i] << "\t";
    }
    cout << endl;

    cout << "���̷�����Դ���" << endl;
    for (int i = 0; i < processNum; i++) {
        cout << i+1 << "����:";
        cout << "����" << processMemoryHaving[i].memoryNumber + 1 << endl;
    }
}

int main() {
    char which;
    while (true) {
        cout << "������Ҫѡ����㷨" << endl;
        cout << "A���״���Ӧ�㷨" << endl;
        cout << "B�������Ӧ�㷨" << endl;
        cin >> which;
        memoryInit();
        if (which == 'A' || which == 'a') {
            firstAdapt();
        } else {
            bestDistrabute();
        }
        display();
    }
    return 0;
}