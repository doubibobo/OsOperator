#include <iostream>
#define N 30

using namespace std;

// 每一种资源现有实例的数量
int Available[N];

// 每一个进程的最大需求，i个进程请求j个资源
int Max[N][N];

// 定义每一个进程现有的实例数量
int Allocation[N][N];

// 定义每一个进程还需要的实例数量
int Need[N][N];

// 安全性算法中需要的中介资源数目等
int Work[N];

// 定义进程是否结束的标志
bool Finish[N];

// 资源的种类数目
int resourceSum = 3;
// 进程的数目
int processSum = 5;

// 提起资源分配请求的进程编号
int processNumber;
// 资源分配请求请求的各类资源
int Apply[N];

// 根据定义，可以得到如下的关系
// Max[i][j] = Allocation[i][j] + Need[i][j]

/*
 *函数功能：根据用户的输入对各项进行初始化
 */
void doInput(){
    for (int i = 0; i < resourceSum; i++){
        cout << "Please input the number of the 3 resources:" << endl;
        cin >> Available[i];
    }

    for (int i = 0; i < processSum; i++){
        cout << "Please input the number of the needed 3 resources of every process in the five" << endl;
        for (int j = 0; j < resourceSum; j++){
            cin >> Max[i][j];
        }
    }

    // 初始化开始状态
    for (int i = 0;i < processSum; i++){
        for (int j = 0; j < resourceSum; j++){
            Need[i][j] = Max[i][j];
            Allocation[i][j] = 0;
        }
    }
}

// 判断两个向量的关系
bool isLow(int n) {
    for (int j = 0; j < resourceSum; j++){
        if (Need[n][j] <= Work[j])  continue;
        else return false;
    }
    return true;
}

// 判断两个向量的关系
bool needLowThanApply(int n) {
    for (int j = 0; j < resourceSum; j++){
        if (Apply[j] <= Need[n][j])  continue;
        else return false;
    }
    return true;
}

bool ApplyLowThanAvailable(){
    for (int j = 0; j < resourceSum; j++){
        if (Apply[j] <= Available[j])  continue;
        else return false;
    }
    return true;
}

// 判断finish数组的状态,全为flase返回false ，有一个true则返回true
bool isSatisfy() {
    for (int i = 0; i < processSum; i++){
        if ((Finish[i] == false) && isLow(i)){
            return true;
        }
    }
    return false;
}

// 判断need数组状态


// 判断finish数组的状态,全部未true返回true，否则返回false
bool isAllTure() {
    for (int i = 0; i < processSum; i++){
        if (Finish[i] == true){
            continue;
        } else {
            return false;
        }
    }
    return true;
}

// 安全性检测算法，若安全则返回true，不安全则返回false
bool security() {
    int theCount;
    // 首先进行向量的初始化
    for (int i = 0; i < processSum; i++){
        Finish[i] = false;
        Work[i] = Available[i];
    }
    while(isSatisfy()) {
        for (int i = 0; i < processSum; i++){
            if ((Finish[i] == false) && isLow(i)){
                // 可以执行该进程且不会产生死锁
                for (int j = 0; j < resourceSum; j++){
                    Work[j] = Allocation[i][j] + Work[j];
                    Finish[j] = true;
                }
            }
        }
    }
    //
    if (isAllTure()) return true;
    else return false;
}

// 资源请求算法
void resourceRequest(){
    // 进行资源请求
    cout << "Please input the processNumber:";
    cin >> processNumber;
    cout << "Please input the every resources:";
    for(int i = 0; i < resourceSum; i++){
        cin >> Apply[i];
    }
    if(needLowThanApply(processNumber)){
        if(ApplyLowThanAvailable()){
            if (security()){
                for(int i = 0; i < resourceSum; i++){
                    Available[i] = Available[i] - Apply[i];
                    Allocation[processNumber][i] = Allocation[processNumber][i]-Apply[i];
                    Need[processNumber][i] = Need[processNumber][i] - Apply[i];
                }
            } else{
                cout << "error!";
            }
        } else {
            cout << "error!";
        }
    } else {
        cout << "error!";
    }
}

// 实现银行家算法
int main()
{
    while(!isAllTure()){
        resourceRequest();
    }
    return 0;
}
