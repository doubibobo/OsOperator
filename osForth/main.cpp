#include <iostream>
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
struct UFD {
    string filename;
    unsigned char protectedNumber;      // �����ļ��ı�����
    int fileLength;                     // �����ļ��Ĵ�С�����ֽ�Ϊ��λ
};

// ����UFD�Ľڵ�
struct UFDNode {
    UFD theUFDContent;
    UFDNode* theNextUFD;
};

// �����ļ���ʱ����ʱĿ¼
struct AFD {
    string filename;                // ���ļ�����
    unsigned  char protectedNumber; // �����ļ��ı�����
    int readWrite;                  // ���ö�дָ���
};

// �����ļ���ʱ��Ŀ¼
struct AFDNode {
    AFD theAFDContent;
    AFD* theNextAFD;
};

// �������ļ�Ŀ¼�ڵ�
struct MFDNode {
    string theMFDContent;
    UFDNode* theHeadUFD;
};

USER allUser[N];
MFDNode MFDTable[N];      // �������ļ�����
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
    cin >> filename;
    ofstream mcfile;    // ����һ������
    mcfile.open("F://osFileoutput//"+filename+".txt");    // �����ļ�
    mcfile.close();
    UFDNode* pStr = MFDTable[currentUserNumber].theHeadUFD;
    UFDNode* thePtr = MFDTable[currentUserNumber].theHeadUFD;
    UFDNode* theNewNode;
    theNewNode = (UFDNode *)malloc(sizeof(UFDNode));
    if (pStr == NULL) {
        cout << "doubibobolalala" << endl;
        pStr = theNewNode;
        pStr->theNextUFD = NULL;
        pStr->theUFDContent.fileLength = 0;
        pStr->theUFDContent.filename = filename;
        pStr->theUFDContent.protectedNumber = 0x0003;
    } else {
        while(thePtr->theNextUFD != NULL) thePtr = thePtr->theNextUFD;
        // �����ļ��Ĵ���
        thePtr->theNextUFD = theNewNode;
        thePtr->theNextUFD->theNextUFD = NULL;
        thePtr->theNextUFD->theUFDContent.fileLength = 0;
        thePtr->theNextUFD->theUFDContent.filename = filename;
        thePtr->theNextUFD->theUFDContent.protectedNumber = 0x0003;
    }
}

void deleteFile(string username) {
    cout << "������Ҫɾ�����ļ������ƣ�" << endl;
    string filename;
    cin >> filename;
    string deleteFilename = "F://osFileoutput//"+filename+".txt";
    remove(deleteFilename.c_str());    // �����ļ�
    cout << "ɾ���ļ��ɹ���" << endl;
}
