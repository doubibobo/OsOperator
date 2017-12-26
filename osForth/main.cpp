#include <iostream>
#include <string>
#include <fstream>
#include <malloc.h>
#define N 10

using namespace std;

// �����û��ṹ
struct USER {
    string username;
    string password;
    int usernameNumber;
};

// �����û��ļ�Ŀ¼UFD
//struct UFD {
//    string filename;
//    unsigned char protectedNumber;      // �����ļ��ı�����
//    int fileLength;                     // �����ļ��Ĵ�С�����ֽ�Ϊ��λ
//};

// ����UFD�Ľڵ�
struct UFDNode {
    string filename;
    unsigned char protectedNumber;      // �����ļ��ı�����
    int fileLength;                     // �����ļ��Ĵ�С�����ֽ�Ϊ��λ
    UFDNode* theNextUFD;
};

// �����ļ���ʱ����ʱĿ¼
//struct AFD {
//    string filename;                // ���ļ�����
//    unsigned  char protectedNumber; // �����ļ��ı�����
//    int readWrite;                  // ���ö�дָ���
//};

// �����ļ���ʱ��Ŀ¼
struct AFDNode {
    string filename;                // ���ļ�����
    unsigned  char protectedNumber; // �����ļ��ı�����
    int readWrite;                  // ���ö�дָ���
    AFDNode* theNextAFD;
};

// �������ļ�Ŀ¼�ڵ�
struct MFDNode {
    string theMFDContent;
    UFDNode* theHeadUFD;
};

USER allUser[N];
MFDNode MFDTable[N];      // �������ļ�����
UFDNode UFDNode[N][N];    //
AFDNode* AFDTable;      // ���ô��ļ�Ŀ¼

int userNumber = 0;     // ��¼�û�������
int currentUserNumber = -1; // ��¼��ǰ��¼�û�


// ���й������г�ʼ������
void initAll();
// ����һ���û�
bool createUser();
// ���е�¼
void doLogin();
// ������Ϣ��ʾ
void outputMessage(int message);
// ��ʾĳһ���û����µ�����Ŀ¼�ļ�
void displayAllFiles(string username);
// ��ʼ���ļ���AFD
void initAFDofUser(string username);
// �����������
string inputCommand();
// �����ļ�
void createFile(string username);
// ɾ���ļ�
void deleteFile(string username);
// ���ļ�
void openFile(string username, string filename);
// �ر��ļ�
void closeFile(string username, string filename);


int main() {
    initAll();
    cout << "doubibobo ���ļ�����ϵͳ" << endl;
    cout << "��ѡ����Ҫ���еĲ���" << endl;
    cout << "1��ע���û�" << endl;
    cout << "2�����е�¼" << endl;
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
        cout << "��֧��10�����ϵ��û�" << endl;
        return false;
    } else {
        cout << "��������Ҫ�������û���" << endl;
        string username;
        cin >> username;
        cout << "����������" << endl;
        string password;
        cin >> password;
        cout << "�����û����ɹ������ǵ�" << userNumber+1 << "���û���" << endl;
        allUser[userNumber].username = username;
        allUser[userNumber].password = password;
        allUser[userNumber].usernameNumber = userNumber+1;
        // �û������ɹ�����MFD�в�����Ӧ����Ŀ
        MFDTable[userNumber].theMFDContent = username;
        MFDTable[userNumber].theHeadUFD = NULL;
        userNumber += 1;
        return true;
    }
}

void doLogin() {
    cout << "�����������û���" << endl;
    string username;
    cin >> username;
    cout << "��������������" << endl;
    string password;
    cin >> password;
    for (int i = 0; i < userNumber; i++) {
        if ((allUser[i].username.compare(username)) == 0 && (allUser[i].password.compare(password) == 0)) {
            currentUserNumber = i;
            cout << "��¼�ɹ���" << endl;
            break;
        }
    }
    // ��¼֮���г����е��ļ������Ҷ�AFD���г�ʼ������
    // initAFDofUser(username);
    // displayAllFiles(username);
    cout << "��ѡ����Ҫ���еĲ���" << endl;
    cout << "1������һ���ļ�" << endl;
    cout << "2��ɾ��һ���ļ�" << endl;
    cout << "3����һ���ļ�" << endl;
    cout << "4���ر�һ���ļ�" << endl;
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
    cout << "������Ҫ�������ļ������ƣ��ļ�������ʽΪtxt" << endl;
    string filename;
    string tmpFilename;
    cin >> filename;
    tmpFilename = filename;
    ofstream mcfile;    // ����һ������
    mcfile.open("F://osFileoutput//"+filename+".txt");    // �����ļ�
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
        // �����ļ��Ĵ���
        pStr->theNextUFD = theNewNode;
    }
}

void deleteFile(string username) {
    cout << "������Ҫɾ�����ļ������ƣ�" << endl;
    string filename;
    cin >> filename;
    string deleteFilename = "F://osFileoutput//"+filename+".txt";
    // ɾ��һ���ļ�
    if (remove(deleteFilename.c_str()) == -1) {
        cout << "ɾ���ļ�ʧ��" << endl;
    } else {
        cout << "ɾ���ļ��ɹ���" << endl;
    }
}
