/**********************************************************************************************
title：中缀表达式转换后缀表达式
discription:含有+-* /（）的中缀表达式转换成后缀表达式后倒序输出，变量全部为字符型，整形需要做一些调整
author:KINMIN
date:2017.5.23
************************************************************************************************/


#define MAXLEN 50
#include<stdio.h>
#include<map>
#include<vector>
#include<string>
#include<iostream>
using namespace std;

struct DATA
{
    char sign;
} ;
//定义节点

struct StackType
{
    DATA data[MAXLEN + 1];
    //最大长度
    int top;
    //栈顶序号，top=0时，表示栈空
};
//定义栈

/**************初始化栈****************************/
StackType *StInit()
{
    StackType *p;
    //申请一个栈
    if(p = new StackType)
    {
        p->top = 0;
        //设置栈顶为0
        return p;
        //返回栈顶指针
    }
    return NULL;
    //申请失败返回NULL
}


/**************判断栈是否为空****************************/
int StIsEmpty(StackType *s)
{
    int t;
    t=(s->top == 0);
    //判断栈顶值是否为0
    return t;
}


/**************判断栈是否已满****************************/
int StIsNull(StackType *s)
{
    int t;
    t=(s->top == MAXLEN);
    //判断栈顶值是否为MAXLEN
    return t;
}


/**************释放空间***************************/
void StClear(StackType *s)
{
    s->top = 0;
}
//清空栈，只是逻辑上的清空栈，以后再存入新的数据时会覆盖已有数据

void StFree(StackType *s)
{
    delete s;
}



/**************入栈****************************/
int PushSt(StackType *s,DATA data)
{
    if((s->top + 1) > MAXLEN)
    {
        cout<<"overflow"<<endl;
        return 0;
    }
    //栈满则提示并返回
    s->data[++ s->top] = data;
    //数据入栈
    return 1;
}


/**************出栈操作****************************/
DATA  *PopSt(StackType *s)
{
    if(s->top == 0)
    {
        cout<<"no more data"<<endl;
        return 0;
    }
    //栈为空，则进行报错并返回
    return &(s->data[s->top--]);
}

/**************读取栈顶数据****************************/
DATA *ReadSt(StackType *s)
{
    if(s->top == 0)
    {
        cout<<"no more data"<<endl;
        return 0;
    }
    return &(s->data[s->top]);
}
/**************记录符号数组****************************/
    char symbol[7] = "+-*/()";
/**************查找函数****************************/
bool findSymbol(char s)
{
    for(int i = 0;i < 7;i ++)
    {
        if(symbol[i] == s)
        {
            return 1;
        }//在数组中则返回真
    }
    return 0;
    //不在数组中则返回假
}

int main()
{
   /*******************设置运算符优先级********************/
    map<const char,int> pri;
    pri['+'] = 1;
    pri['-'] = 1;
    pri['*'] = 2;
    pri['/'] = 2;
    pri['('] = 0;
     /*******************设置运算符优先级********************/
    StackType *StackSign;
    //符号栈
    StackType *StackNumber;
    //数字栈
    string exp;
    DATA data;
    StackSign = StInit();//符号栈初始化
    StackNumber = StInit();//变量栈初始化
    cout<<"==========================input with  infix expression ,end with'\'========================="<<endl;
        while(cin>>exp)//输入中缀表达式
        {
            for(int i = 0;i <= exp.length();i ++)
            {
                data.sign = exp[i];
                if(!findSymbol(data.sign))
                {
                    PushSt(StackNumber,data);
                    // cout<<PopSt(StackNumber)->sign;
                }//不是符号则放入变量栈里
                else
                {
                    if(data.sign == '(')
                    {
                        PushSt(StackSign,data);
                    }
                    //遇到'('时，直接放入符号栈，优先级为最低
                    else if(data.sign == ')')
                    {
                        while(ReadSt(StackSign)->sign != '(')
                        {
                            PushSt(StackNumber,*PopSt(StackSign));
                        }
                        *PopSt(StackSign);//将'('弹出栈，但是不输出
                    }
                    //遇到')'时，输出符号栈中元素，直到遇到'('
                    else if(StackSign->top == 0 || pri[data.sign] > pri[ReadSt(StackSign)->sign])
                    {
                        PushSt(StackSign,data);
                    }
                    //符号栈为空时或者优先级大于栈顶符号优先级时，直接将读取的符号输入字符串
                    else if(pri[data.sign] <= pri[ReadSt(StackSign)->sign])
                    {
                        while(StackSign->top != 0 && pri[ReadSt(StackSign)->sign] >= pri[data.sign] && ReadSt(StackSign)->sign != '(' && StackSign->top != 0)
                        {
                            PushSt(StackNumber,*PopSt(StackSign));
                        }
                        PushSt(StackSign,data);
                        //将当前符号存入符号栈
                    }
                    //符号优先级小于或等于栈顶符号优先级时，从栈中弹出元素直到遇到发现更低优先级的元素(或者栈为空)为止
               
                }
                 if(i == exp.length() - 1)
                {
                    while(StackSign->top > 0)
                        {
                            PushSt(StackNumber,*PopSt(StackSign));
                        }
                }
                //取到最后一个字符时，将符号栈中的内容全部输出
                
            }
            while(StackNumber->top > 0)
            {
                cout<<PopSt(StackNumber)->sign;
            }
            StClear(StackSign);
            StClear(StackNumber);
            //清空符号栈和变量栈
        }
            StFree(StackSign);
            StFree(StackNumber);
            //释放符号栈和变量栈内存
    return 0;
}


