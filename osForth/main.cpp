#include <iostream>
#include <string>
#include <fstream>
#include <malloc.h>
#define N 10

using namespace std;

// 定义用户结构
struct USER {
    string username;
    string password;
    int usernameNumber;
};

// 定义用户文件目录UFD
//struct UFD {
//    string filename;
//    unsigned char protectedNumber;      // 定义文件的保护码
//    int fileLength;                     // 设置文件的大小，以字节为单位
//};

// 定义UFD的节点
struct UFDNode {
    string filename;
    unsigned char protectedNumber;      // 定义文件的保护码
    int fileLength;                     // 设置文件的大小，以字节为单位
    UFDNode* theNextUFD;
};

// 设置文件打开时运行时目录
//struct AFD {
//    string filename;                // 打开文件号码
//    unsigned  char protectedNumber; // 设置文件的保护码
//    int readWrite;                  // 设置读写指针等
//};

// 定义文件打开时的目录
struct AFDNode {
    string filename;                // 打开文件号码
    unsigned  char protectedNumber; // 设置文件的保护码
    int readWrite;                  // 设置读写指针等
    AFDNode* theNextAFD;
};

// 设置主文件目录节点
struct MFDNode {
    string theMFDContent;
    UFDNode* theHeadUFD;
};

USER allUser[N];
MFDNode MFDTable[N];      // 设置主文件链表
UFDNode UFDNode[N][N];    //
AFDNode* AFDTable;      // 设置打开文件目录

int userNumber = 0;     // 记录用户的数量
int currentUserNumber = -1; // 记录当前登录用户


// 所有工作进行初始化操作
void initAll();
// 创建一个用户
bool createUser();
// 进行登录
void doLogin();
// 出错信息提示
void outputMessage(int message);
// 显示某一个用户名下的所有目录文件
void displayAllFiles(string username);
// 初始化文件表AFD
void initAFDofUser(string username);
// 输入操作命令
string inputCommand();
// 创建文件
void createFile(string username);
// 删除文件
void deleteFile(string username);
// 打开文件
void openFile(string username, string filename);
// 关闭文件
void closeFile(string username, string filename);


int main() {
    initAll();
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

void initAll() {
    for (int i = 0; i < N; i++) {
        allUser[i].username = "";
        allUser[i].password = "";
        allUser[i].usernameNumber = 0;
        MFDTable[i].theMFDContent = "";
        MFDTable[i].theHeadUFD = NULL;
    }
    AFDTable = NULL;
}

bool createUser() {
    if (userNumber >= 10) {
        cout << "不支持10个以上的用户" << endl;
        return false;
    } else {
        cout << "请输入您要创建的用户名" << endl;
        string username;
        cin >> username;
        cout << "请输入密码" << endl;
        string password;
        cin >> password;
        cout << "创建用户名成功，您是第" << userNumber+1 << "个用户！" << endl;
        allUser[userNumber].username = username;
        allUser[userNumber].password = password;
        allUser[userNumber].usernameNumber = userNumber+1;
        // 用户创建成功，在MFD中插入相应的项目
        MFDTable[userNumber].theMFDContent = username;
        MFDTable[userNumber].theHeadUFD = NULL;
        userNumber += 1;
        return true;
    }
}

void doLogin() {
    cout << "请输入您的用户名" << endl;
    string username;
    cin >> username;
    cout << "请输入您的密码" << endl;
    string password;
    cin >> password;
    for (int i = 0; i < userNumber; i++) {
        if ((allUser[i].username.compare(username)) == 0 && (allUser[i].password.compare(password) == 0)) {
            currentUserNumber = i;
            cout << "登录成功！" << endl;
            break;
        }
    }
    // 登录之后，列出所有的文件，并且对AFD进行初始化操作
    // initAFDofUser(username);
    // displayAllFiles(username);
    cout << "请选择您要进行的操作" << endl;
    cout << "1、创建一个文件" << endl;
    cout << "2、删除一个文件" << endl;
    cout << "3、打开一个文件" << endl;
    cout << "4、关闭一个文件" << endl;
    int loginOperator;
    cin >> loginOperator;
    while (loginOperator != 0) {
        switch (loginOperator) {
            case 1:
                createFile(username);
                break;
            case 2:
                deleteFile(username);
                break;
            default:
                continue;
        }
    }
}

void createFile(string username) {
    cout << "请输入要创建的文件的名称，文件创建格式为txt" << endl;
    string filename;
    string tmpFilename;
    cin >> filename;
    tmpFilename = filename;
    ofstream mcfile;    // 创建一个对象
    mcfile.open("F://osFileoutput//"+filename+".txt");    // 创建文件
    if (!mcfile) {
        cout << "file open failed!" << endl;
        return;
    } else {
        cout << "file open success and now write something into it";
    }
    mcfile.close();
    cout << "currentUserNumber" << currentUserNumber << endl;
    UFDNode* pStr = MFDTable[currentUserNumber].theHeadUFD;
    UFDNode* theNewNode;
    theNewNode = (UFDNode *)malloc(sizeof(UFDNode));
    theNewNode->theNextUFD = NULL;
    theNewNode->fileLength = 0;
    cout << "filename" << filename << endl;
    theNewNode->filename = tmpFilename;
    cout << "protectedNumber" << endl;
    theNewNode->protectedNumber = 3;
    if (pStr == NULL) {
        MFDTable[currentUserNumber].theHeadUFD = theNewNode;
        cout << "I have made a dir" << endl;
    } else {
        while(pStr->theNextUFD != NULL) pStr = pStr->theNextUFD;
        // 进行文件的创建
        pStr->theNextUFD = theNewNode;
    }
}

void deleteFile(string username) {
    cout << "请输入要删除的文件的名称！" << endl;
    string filename;
    cin >> filename;
    string deleteFilename = "F://osFileoutput//"+filename+".txt";
    // 删除一个文件
    if (remove(deleteFilename.c_str()) == -1) {
        cout << "删除文件失败" << endl;
    } else {
        cout << "删除文件成功！" << endl;
    }
}
