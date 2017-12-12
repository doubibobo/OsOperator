#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 100             // 定义最大值宏常量
struct PROHAVING {
    int memoryNumber;
    int memoryHaving;
};

int processNum;             // 设置进程的数目
int memoryNum;              // 设置分区的数目

int processMemoryNeed[MAX]; // 进程需要的分区大小
PROHAVING processMemoryHaving[MAX];   // 进程所占有的空间大小
PROHAVING memoryRestHaving[MAX];          // 空闲区块空间大小

int memory[MAX];        // 每一个分区的大小
int memoryRest[MAX];    // 每个分区剩余的空间

int increaseRestMemory[MAX];    // 按照从小到大的顺序排列的数组


// 初始化方法，设置每一个空闲区域的大小为50K
void memoryInit() {
    cout << "请输入进程的数目" << endl;
    cin >> processNum;
    cout << "请输入分区的数目" << endl;
    cin >> memoryNum;
    cout << "请输入ABCDEFG每一个进程所需要的内存大小" << endl;
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

// 首次适应算法
void firstAdapt() {
    for (int i = 0; i < processNum; i++) {
        for (int j = 0; j < memoryNum; j++) {
            if (processMemoryNeed[i] <=memoryRest[j]) {
                // 当进程所需要的空间大小小于剩余的空间，可以分配
                memoryRest[j] -= processMemoryNeed[i];
                processMemoryHaving[i].memoryNumber = j;
                processMemoryHaving[i].memoryHaving = processMemoryNeed[i];
                break;
            }
        }
    }
}

// 设置比较函数
bool compare(PROHAVING a, PROHAVING b) {
    return a.memoryHaving < b.memoryHaving;   // 进行降序排列
}

// 最佳分配算法：每一次检查最小的空闲区块
void bestDistrabute() {
    // 首先对内存空间数组进行排序
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

// 查询分配的结果
void display() {
    cout << "需要分配的进程序列：     \t";
    for (int i = 0; i < processNum; i++) {
        cout << i+1 << "\t";
    }
    cout << endl;

    cout << "每个进程需要分配的空间大小\t";
    for (int i = 0; i < processNum; i++) {
        cout << processMemoryNeed[i] << "\t";
    }
    cout << endl;

    cout << "分区序号\t";
    for (int i = 0; i < memoryNum; i++) {
        cout << "分区" << i+1 << "\t";
    }
    cout << endl;

    cout << "分区大小\t";
    for (int i = 0; i < memoryNum; i++) {
        cout << "50\t";
    }
    cout << endl;

    cout << "剩余大小\t";
    for (int i = 0; i < memoryNum; i++) {
        cout << memoryRest[i] << "\t";
    }
    cout << endl;

    cout << "进程分配资源情况" << endl;
    for (int i = 0; i < processNum; i++) {
        cout << i+1 << "进程:";
        cout << "分区" << processMemoryHaving[i].memoryNumber + 1 << endl;
    }
}

int main() {
    char which;
    while (true) {
        cout << "请输入要选择的算法" << endl;
        cout << "A：首次适应算法" << endl;
        cout << "B：最佳适应算法" << endl;
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