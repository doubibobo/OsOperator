#include <iostream>
#define N 10
#define M 100

using namespace std;

// 定义用户结构
struct USER {
    string username;
    int usernameNumber;
};

// 定义用户文件目录UFD
struct UFD {
    string filename;
    unsigned char protectedNumber;      // 定义文件的保护码
    int fileLength;                     // 设置文件的大小，以字节为单位
};

// 定义UFD的节点
struct UFDNode {
    UFD theUFDContent;
    UFD* theNextUFD;
};

// 设置文件打开时运行时目录
struct AFD {
    string filename;                // 打开文件号码
    unsigned  char protectedNumber; // 设置文件的保护码
    int readWrite;                  // 设置读写指针等
};

// 定义文件打开时的目录
struct AFDNode {
    AFD theAFDContent;
    AFD* theNextAFD;
};

// 定义主文件目录MFD
struct MFD {
    string username;
    UFD* UFDPoint;
};

// 设置主文件目录节点
struct MFDNode {
    MFD theMFDContent;
    MFD* theNextMFD;
};

USER allUser[N];

// 创建一个用户
int createUser();
// 进行登录
void doLogin();
// 检查用户名
int checkUsername(string username);
// 出错信息提示
void outputMessage(int message);
// 显示某一个用户名下的所有目录文件
void displayAllFiles(string username);
// 初始化文件表AFD
void initAFDofUser(string username);
// 输入操作命令
string inputCommand();
// 创建文件
void createFile(string username, string filename);
// 删除文件
void deleteFile(string username, string filename);
// 打开文件
void openFile(string username, string filename);
// 关闭文件
void closeFile(string username, string filename);


int main() {
    cout << "doubibobo 的文件管理系统" << endl;
    cout << "请选择您要进行的操作" << endl;
    cout << "1、注册用户" << endl;
    cout << "2、进行登录" << endl;
    int choseOperator;
    while (cin >> choseOperator) {
        switch (choseOperator) {
            case 1:
                createUser();
                break;
            case 2:
                doLogin();
                break;
            default:
                continue;
        }
    }
    return 0;
}

int createUser() {
    
}

