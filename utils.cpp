#include "utils.h"
#include <cstring>
#include <random>
#include <QDebug>
#include <QTime>
#include <QtGlobal>

utils::utils()
{

}
char* utils::genRandomString(int length)
{
    const char *c = "0123456789abcdefghijklmnopqrstuvwxyz";    //可填充的字符
    char* MsgBuffer = new char[length+1];       //定义一个length长度的字符数组
    memset(MsgBuffer, 0, length+1);      //初始化数组，都置零
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (int i = 0; i < length;i++)
    {
        int index = qrand() % strlen(c);
        MsgBuffer[i] = c[index];
    }
    MsgBuffer[length] = '\0';
    qDebug()<<"utils:"<<MsgBuffer;
    return MsgBuffer;
}

//char* utils::genRandomString(int length)
//{
//    int flag, i;
//    char* string;
//    srand((unsigned) time(NULL ));
//    if ((string = (char*) myMalloc(length)) == NULL )
//    {
//        myLog("Malloc failed!flag:14\n");
//        return NULL ;
//    }

//    for (i = 0; i < length - 1; i++)
//    {
//        flag = rand() % 3;
//        switch (flag)
//        {
//            case 0:
//                string[i] = 'A' + rand() % 26;
//                break;
//            case 1:
//                string[i] = 'a' + rand() % 26;
//                break;
//            case 2:
//                string[i] = '0' + rand() % 10;
//                break;
//            default:
//                string[i] = 'x';
//                break;
//        }
//    }
//    string[length - 1] = '\0';
//    return string;
//}
