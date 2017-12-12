#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// 定义进程控制快结构体
struct PCB
{
    char    processName;    // 进程标识符（进程名称）
    struct PCB     *theNext;        // 进程控制块的连接指针
    int     timeViewed;     // 进程控制块的优先数或者轮转时间片
    int     timeUsed;       // 已经占用的CPU时间片数
    int     timeNeeded;     // 进程所需要的时间片数
    int     status;         // 进程的状态，0表示就绪状态，1表示正在运行，2表示结束运行
};

// 定义就、完成状态的链表
struct readyFinished
{
    struct PCB *theprocess;
};

int main()
{
    // 创建就绪队列
    struct PCB *theReady = (struct PCB *)malloc(sizeof(struct PCB));
    theReady->theNext = NULL;
    // 创建完成队列
    // struct readyFinished *theFinish = (struct readyFinished *)malloc(sizeof(struct readyFinished));
    struct PCB *theFinish = (struct PCB *)malloc(sizeof(struct PCB));
    theFinish->theNext = NULL;
    // 创建正在运行的队列
    // struct readyFinished *therunning = (struct readyFinished *)malloc(sizeof(struct readyFinished));
    struct PCB *therunning = (struct PCB *)malloc(sizeof(struct PCB));
    therunning->theNext = NULL;
    int i, count = 5, timeView, timeNeeded;
    char name;
    struct PCB *theCreate[5] = {NULL};
    struct PCB *ptr = (struct PCB *)malloc(sizeof(struct PCB));
    struct PCB *doubi = (struct PCB *)malloc(sizeof(struct PCB));
    struct PCB *pstr = (struct PCB *)malloc(sizeof(struct PCB));
    // 创建五个进程，即进程控制块，并且加入就绪队列
    for (i = 0; i < count; i++)
    {
        getchar();
        theCreate[i] = (struct PCB *)malloc(sizeof(struct PCB));
        printf("Please input the process name, timeView and timeNeeded, use ',' to divide\n");
        scanf("%c,%d,%d", &name, &timeView, &timeNeeded);
        theCreate[i]->processName = name;
        theCreate[i]->timeViewed = timeView;
        theCreate[i]->timeNeeded = timeNeeded;
        theCreate[i]->status = 0;
        theCreate[i]->timeUsed = 0;
        theCreate[i]->theNext = NULL;
        ptr = theReady->theNext;
        pstr = theReady;

        printf("%c, %d, %d\n", theCreate[i]->processName, theCreate[i]->timeViewed, theCreate[i]->timeNeeded);

        // 将创建好的进程加入到就绪队列，按照优先级的先后顺序
        if (theReady->theNext == NULL) {
            theReady->theNext = theCreate[i];

        } else {
            while(ptr != NULL && theCreate[i]->timeViewed < ptr->timeViewed) {
                pstr = ptr;
                ptr = ptr->theNext;
            }
            // 找到合适的插入位置
            theCreate[i]->theNext = ptr;
            pstr->theNext = theCreate[i];
        }
    }

        // 就绪状态插入完毕
    pstr = theReady->theNext;
    // 选择就绪状态的第一个进程
    while (pstr != NULL) {
        printf("%c %d %d\n", pstr->processName, pstr->timeNeeded, pstr->timeUsed);
        pstr = pstr->theNext;
    }

    // 就绪状态插入完毕
    pstr = theReady->theNext;
    // 选择就绪状态的第一个进程
    while (pstr != NULL) {
        // 输出当前状态下的进程就绪队列
        therunning = pstr;
        doubi = theReady->theNext;
        while (doubi != NULL) {
            //printf("    %c", doubi->processName);
            printf("%c %d %d||", doubi->processName, doubi->timeNeeded, doubi->timeUsed);
            doubi = doubi->theNext;
        }

        theReady->theNext = pstr->theNext;

        // 分配到时间片，减1,优先级减3
        therunning->timeNeeded = therunning->timeNeeded-1;
        therunning->timeViewed = therunning->timeViewed-3;
        therunning->timeUsed = therunning->timeUsed+1;
        printf("||%c    \n", therunning->processName);
        if (therunning->timeNeeded == 0) {
            // 加入完成状态
            therunning->theNext = theFinish->theNext;
            theFinish->theNext = therunning;
        } else {
            ptr = theReady->theNext;
            // 此进程未结束，优先级降低，找到合适的插入位置
            if (theReady->theNext == NULL) {
                theReady->theNext = therunning;

            } else {
                while(ptr != NULL && therunning->timeViewed < ptr->timeViewed) {
                    pstr = ptr;
                    ptr = ptr->theNext;
                }
                // 找到合适的插入位置
                therunning->theNext = ptr;
                pstr->theNext = therunning;
            }
        }
        pstr = theReady->theNext;
    }
    //  将所有的进程加入完成状态
    therunning->theNext = theFinish->theNext;
    theFinish->theNext = therunning;

    printf("\nAll process finished!\n");

    return 0;
}
