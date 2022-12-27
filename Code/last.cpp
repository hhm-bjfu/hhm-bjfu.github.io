#include<iostream>
#include <string.h>
#include <map>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
#define option_LEN 21
using namespace std;
typedef struct BiNode
{
	string ch;
	struct  BiNode* lchild, * rchild; //左右孩子指针
}BiNode, * BiTree;
map<string, int> operatorMp;	//存放中缀、前缀 
/*找到优先级最低的那个运算符的位置 ----这个位置应该两个参数表示，或者返回相应的起始位置和字符串
	寻找最后一个运算符，只有当p=0的时候才考虑，（p记录括号）
	因为括号里的运算符一定不是最后计算的，括号外的最后一个运算符才是最后计算的
	flag记录出现的是哪一类运算符 还是需要在这里确定
	*/
string FindLowest(string s, int x, int y, int& c1, int& c2, int &c3, int& flag)	//先分开中缀前缀 
{
	int p = 0;//记录括号满了没 
	int is_single = -1;//记录是+- ^ 决定是否返回字符串，或者返回空字符串，要为下一步建节点分界位置考虑 
	string opt;//记录运算符 
	for (int i = x; i < y; i++)	//---------这里是最关键的   原来只需要判断一个字符即可，现在需要多个字符一起判断 
	{
		switch (s[i])
		{
		case'(':
		case'{':
			p++;
			break;
		case')':
		case'}':
			p--;
			break;
		case'+':
		case'-':
			if (!p)		//p>0在括号里面，p=0在括号外面 
			{
				c1 = i;	//记录符号出现的位置，因为找的就是在最外层括号外的优先级最低的那个符号
				is_single = 1;//这里记录出现的是单个字符的运算符
				flag = 2;
			}
			break;
		case'^':
			if (!p)		//最晚建树 最先计算
			{
				c3 = i;		//------- 这里给符号的位置赋值  
				is_single = 1;
				flag = 2;
			}
			break;
		case'\\':	//代表出现了字符串，可能是运算符，可能是常量符号 
			if (!p && c1 < 0) //如果出现了+ - 就不需要判断其他优先级高的符号
			{
				is_single = 0;
				opt = ""; 	//记录这个字符串运算符 
				int index = i + 1;//不计 /
				while (1)
				{//判断字符串片段是否到头的标志：{ } （） + -  ……   如果不用标志 只能每字符遍历判断是否是运算符
					if (s[index] == '{' || s[index] == '}'|| s[index] == '(' || s[index] == ')' || s[index]=='+'||s[index]=='-')
					break;
					else
					{
						string ch(1, s[index]);
						opt += ch;
						index++;
					}
				}
				map<string, int>::iterator it; //取出opt之后判断：获取优先级 
				for (it = operatorMp.begin(); it != operatorMp.end(); it++)
				{
					if (it->first == opt)		//找到了这个运算符 
					{
						switch (it->second) //问题：前后 并列出现中缀和前缀运算符会互相改变符号
						{
							case 2://双目
							{
								c2 = i;//------- 这里给符号的位置赋值 
								flag = 2;
								opt = "\\" + opt;
								break;
							}
							case 12://双目前缀
							{
								c2 = i;
								flag = 12;
								opt = "\\" + opt;
								break;
							}
							case 1: //单目 
							{
								if (flag == 0) 
								{
									c2 = i;//------- 这里给符号的位置赋值
									flag = 1;
									opt = "\\" + opt;
									break;
								}
							}
							case 0: //其他符号
								break;
						}
						break;
					}
				}
				i = index - 1;//给i赋值，到符号结束的位置
			}
			break;
		}
	}
	if (is_single == 1 || is_single == -1)	//代表这一部分最低优先级符号是+ - ^
		return "";
	else if (is_single == 0)	//代表是比+-高的优先级 符号 
		return opt;
}
//第一个问题：返回值is_single没有变化，-1，返回值应该是“”;index 和 i的位置要确定好
//处理left right：直接忽略掉,但是字符串长度？需要单独写一个判断是否符合左右left right 判断需要在第二步 OK
//处理前缀运算符
//没写判断合法性
int Left_right(string s, int x, int y)
{
	if (y < x + 5)
		return 0;
	string opt = s.substr(x + 1, 4);
	if(opt=="left")
	return 1;
	else
	return 0;
}
int Is_prefix(string s,int x, string& opt)	//返回值是对应的数字
{
	if (s[x] == '\\')//判断是map当中的
	{
		int index = x + 1;
		while(1)
		{
			if (s[index] == '{')
				break;
			string ch(1, s[index]);
			opt += ch;
			index++;
		}
		map<string, int>::iterator it;
		for (it = operatorMp.begin(); it != operatorMp.end(); it++)
		{
			if (it->first == opt)		//找到了这个运算符 ---- 也可能是常量符号（后面考虑）
			{
				opt = "\\" + opt;	
				return it->second;
			}
		}
		return 0;//没找到这个运算符
	}
	else
	return 0;
}
int FindDivide(string s,int x,int y)
{
	int p = 1;
	for (int i = x + 1; i < y; i++)	
	{
		if (s[i] == '{')
			p++;
		else if (s[i] == '}')
		{
			p--;
			if (p == 0)
			{
				return i;
			}
		}		
	}
}
int Is_cons(string s, int x, int y) 
{
	if (y - x > 9)
		return 0;
	string str;
	if (s[x] == '\\') //判断是map当中的
	{
		str = s.substr(x + 1,y - x - 1); //从x+1位 开始 y-x -1位
		map<string, int>::iterator it;
		for (it = operatorMp.begin(); it != operatorMp.end(); it++)
		{
			if (it->first == str && it->second == 0)	//代表是常量符号
			{
				return 1;
			}
		}	
		return 0;
	}
	else
		return 0;
}
//问题：只考虑了开头是前缀运算符 但不代表整个式子都是这个运算符下的 说到底就是没有对比所有优先级的大小
BiTree build(BiTree& T, string s, int x, int y)//x表示字符串的起始地址，y表示结束地址；
{
	if (y - x == 1)		//仅一个字符，建立单独结点
	{
		T = new BiNode;
		T->ch = s[x];
		T->lchild = NULL;
		T->rchild = NULL;
		return T;
	}
	else if (Is_cons(s, x, y) == 1) //是常量符号 
	{
		T = new BiNode;
		T->ch = s.substr(x, y - x);
		T->lchild = NULL;
		T->rchild = NULL;
		return T;
	}
	//判断left right  这个判断也不实际 得首先是一整个被left right包括的情况才符合
	//if (Left_right(s, x, y) == 1)//如果是的话修改x,y的值，不改变s本身
	//{
	//	x = x + 6;
	//	y = y - 7;
	//}
	//判断前缀 两种情况  得在全局下判断，只考虑整个式子 如果不是就错误 
	//找到式子中优先级最低的符号
	int c1 = -1, c2 = -1,c3 = -1, flag = 0;
	//c1记录“最右”出现的加减号，c2记录“最右”出现的乘除号，p记录完整的括号
	string opt;
	opt = FindLowest(s, x, y, c1, c2, c3, flag);//必须得先判断全局
	if (c1 < 0)//找不到括号外的最低优先级符号【+-】,那么最低的是其他符号代表的，将最低优先级的符号作为子根建；
		c1 = c2;
	if (c1 < 0)//如果c2没变，整个式子被一个大括号给括起来了
		//看看c3变了没，可能式子里最高优先级的是^
	{
		if(c3 == -1)
		return build(T, s, x + 1, y - 1);  //把大括号去掉
	}
	//这是对于中缀的情况  ----根据flag判断 
	if (flag == 2)	//---	代表中缀运算符 
	{
		if (opt == "" && c3 < 0)	// 是 + - 
		{
			T = new BiNode;
			T->ch = s[c1];            //生成根结点
			build(T->lchild, s, x, c1);  //递归创建左子树
			build(T->rchild, s, c1 + 1, y); //递归创建右子树
		}
		else if(opt == "" && c3 > 0)	// 是^
		{
			T = new BiNode;
			T->ch = s[c3];            //生成根结点
			build(T->lchild, s, x, c3);  //递归创建左子树
			build(T->rchild, s, c3 + 1, y); //递归创建右子树
		}
		else				  // 是map里的运算符
		{
			T = new BiNode;
			T->ch = opt;            //生成根结点
			build(T->lchild, s, x, c1);  //递归创建左子树
			build(T->rchild, s, c1 + opt.length(), y); //递归创建右子树
		}
		return T;
	}
	else if (flag == 12)	//前缀双目运算符
	{
		int divide = FindDivide(s, x + opt.length(), y);//分界的{的位置
		T = new BiNode;
		T->ch = opt;            //生成根结点
		build(T->lchild, s, x + opt.length(), divide + 1);  //递归创建左子树
		build(T->rchild, s, divide + 1, y);		//递归创建右子树
		return T;
	}
	else if (flag == 1)  
	{
		T = new BiNode;
		T->ch = opt;            //生成根结点
		build(T->lchild, s, x + opt.length(), y);  //递归创建左子树
		T->rchild = NULL;	//右子树为空
		return T;
	}
}
void OrderTraverse(BiTree T)
{
	BiTree temp[100];   //创建指针类型的指针数组
    int in = 0;
    int out = 0;

    temp[in++] = T;  //先保存二叉树根节点 

    while (in > out)
    {
        if (temp[out])
        {
            //cout << temp[out]->ch << " → ";
            cout << "第" << out+1 << "个值为：" << temp[out]->ch << endl;
            temp[in++] = temp[out]->lchild;
            temp[in++] = temp[out]->rchild;
        }
        out++;
    }
}
// 例子们：
// ${{a}\div{{c}+{b}}}$
// $\sin{{a}+{b}}$
// $\frac{a}{b}$
// $\sqrt{\frac{{a}+{b}}{{c}+{d}}}$
// $\frac{{a}-{1}}{{b}-{1}}$
// $\sqrt{a}+\sqrt{b}$     
// ${\alpha}+{\beta}$
// 常量符号用{}括起来 或者补充判断 这种情况 
// ${a}^{2}+{b}^{2}$
// $({A}\land{B})\lor({A}\land{C})$
// 没考虑不是单个字符的常量的情况 2ab  
// 中间有等号的话，分成两段分别建树
// left right 单独处理 在开始的时候直接拿掉  去掉只剩括号  
// 没考虑中间有空格
void node_exchange(BiTree T)//交换律 
{
	BiTree temp;
	temp = T;
	if(!temp)
	{
		return;
	}
	if(temp->ch=="+" || temp->ch=="\\times")
	{
		if(temp->lchild->lchild || temp->rchild->rchild)
		{
			return;
		}
		if(temp->lchild->ch[0] > temp->rchild->ch[0])
		{
			string exg;
			exg = temp->lchild->ch;
			temp->lchild->ch = temp->rchild->ch;
			temp->rchild->ch = exg;
		}
	}
	node_exchange(temp->lchild);
	node_exchange(temp->rchild);
}

void node_associate(BiTree T)//结合律 
{
	BiTree temp;
	temp = T;
	if(temp->ch=="+" || temp->ch=="-")
	{
		//cout<< 1;
		string cheng,chu;
		cheng = "\\times";
		chu = "\\div";
		if((temp->lchild->ch==cheng || temp->lchild->ch==chu) && temp->lchild->ch == temp->rchild->ch)
		{
			//cout<< 2;
			BiTree l,r;
			l = temp->lchild;
			r = temp->rchild;
			if(l->ch==cheng)
			{
				if(l->lchild->ch == r->lchild->ch || l->rchild->ch == r->lchild->ch || l->lchild->ch == r->rchild->ch || l->rchild->ch == r->rchild->ch)
				{
					string ass = temp->ch;
					temp->ch = l->ch;
					string a,b,c,d,mas,div1,div2;
					a = l->lchild->ch;
					b = l->rchild->ch;
					c = r->lchild->ch;
					d = r->rchild->ch;
					if(a==c)
					{
						mas = a;
						div1 = b;
						div2 = d;
					}
					if(a==d)
					{
						mas = a;
						div1 = b;
						div2 = c;
					}
					if(b==c)
					{
						mas = b;
						div1 = a;
						div2 = d;
					}
					if(b==d)
					{
						mas = b;
						div1 = a;
						div2 = c;
					}
					l->ch = mas;
					l->lchild = NULL;
					l->rchild = NULL;
					r->ch = ass;
					r->lchild->ch = div1;
					r->rchild->ch = div2;
				}
			}
			if(l->ch==chu)
			{
				if(l->lchild->ch == r->lchild->ch || l->rchild->ch == r->rchild->ch)
				{
					string ass,a,b,c,d,mas,div1,div2;
					ass = temp->ch;
					temp->ch = l->ch;
					a = l->lchild->ch;
					b = l->rchild->ch;
					c = r->lchild->ch;
					d = r->rchild->ch;
					if(a==c)
					{
						mas = a;
						div1 = b;
						div2 = d;
						l->ch = mas;
						l->lchild = NULL;
						l->rchild = NULL;
						r->ch = ass;
						r->lchild->ch = div1;
						r->rchild->ch = div2;
					}
					if(b==d)
					{
						mas = b;
						div1 = a;
						div2 = c;
						r->ch = mas;
						r->lchild = NULL;
						r->rchild = NULL;
						l->ch = ass;
						l->lchild->ch = div1;
						l->rchild->ch = div2;
					}
				}
			}
		}
	}
	return;
}

string option[option_LEN] ={"\\times", "\\div", "\\frac", "\\left(", "\\right)", "\\sqrt", 
							"\\sin", "\\cos", "\\tan", "\\pi", "\\neg", "\\land", "\\lor", 
							"\\oplus", "\\lambda", "\\lnot", "\\alpha", "\\beta", "\\gamma",
							"\\tau"};
bool Is_legal(string str)  		 
{
	int len = str.length();
    int num; 
    int flag = 0;
    int flag_sum = 1;
    string op;
    for(int i = 0; i < len; i++){
	    if(str[i] == '{'){
	    	//cout<<str[i]<<endl;
	       	num++;
		}
	    if(str[i] == '}'){
	    	//cout<<str[i]<<endl;
	        num--;
		}
	    if(str[i] == (char)92){
	    	str[i] = '\\';
	    	op += str[i];
	    	i++;
       		while(str[i] != '{' && str[i] != '=' && str[i] != '/' 
			   && str[i] != '*' && str[i] != '+' && str[i] != '-'
			   && str[i] != '^' && str[i] != '[' && str[i] != '}'
			   && str[i] != '$'){
       			if(str[i] == (char)92){
       				str[i] = '\\';
       				break;
				   }
				else{
					op += str[i];
       				//cout<<"op:"<<op<<endl;
					i++;
				}	
			}
			i--;
			for(int j = 0; j < option_LEN; j++){
				if(op == option[j]){
					flag = 1;
					break;
				}
				else{
					flag = 0;
				}
			}
			//cout<<"--"<<flag<<endl;
			op.clear();
			if(flag == 0){
			flag_sum = 0;
			}
		}	
 	}
// 	for(int i=0;i<len;i++){
// 		cout<<str[i];
//	 } 
 	if(str[0] != '$' || str[len - 1] != '$'){//开头结尾不存在$
	 	cout<<"$出错!"<<endl;
		return false;
	} 
    else if(num != 0){//花括号不匹配 
		cout<<"花括号个数不匹配!"<<endl;
		return false;
	}
	else if(flag_sum != 1){//latex运算符不匹配
		cout<<"LaTex符号表示出错!"<<endl;
		return false;
	} 
	else{return true;}
}
int Equal_sign(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '=')
		{
			return i;
		}
	}
	return 0;
}
int main()
{
	//中缀运算符 -----双目 
	operatorMp.insert(pair<string, int>{"times", 2});
	operatorMp.insert(pair<string, int>{"div", 2});
	operatorMp.insert(pair<string, int>{"land", 2});	//与
	operatorMp.insert(pair<string, int>{"lor", 2});		//或	
	operatorMp.insert(pair<string, int>{"oplus", 2});	//异或
	operatorMp.insert(pair<string, int>{"to", 2});		//
	//前缀运算符------双目 
	operatorMp.insert(pair<string, int>{"frac", 12});
	//前缀运算符------单目 
	operatorMp.insert(pair<string, int>{"sin", 1});
	operatorMp.insert(pair<string, int>{"cos", 1});
	operatorMp.insert(pair<string, int>{"tan", 1});
	operatorMp.insert(pair<string, int>{"sec", 1});
	operatorMp.insert(pair<string, int>{"neg", 1});
	operatorMp.insert(pair<string, int>{"sqrt", 1});
	//常量符号&希腊字母
	operatorMp.insert(pair<string, int>{"pi", 0});
	operatorMp.insert(pair<string, int>{"alpha", 0});
	operatorMp.insert(pair<string, int>{"beta", 0});
	operatorMp.insert(pair<string, int>{"gamma", 0});
	operatorMp.insert(pair<string, int>{"delta", 0});
	operatorMp.insert(pair<string, int>{"lambda", 0});
	operatorMp.insert(pair<string, int>{"tau", 0});
	operatorMp.insert(pair<string, int>{"epsilon", 0});
	operatorMp.insert(pair<string, int>{"sigma", 0});
	BiTree T = NULL;
	string s;
	cin >> s;	//输入的公式以$ $形式
	if(Is_legal(s)) 
	{
		int len = s.length();
		int eq = Equal_sign(s);
		if (eq) //中间有 = 分成两段分别建树
		{
			string left = s.substr(1,eq - 1);
			string right = s.substr(eq + 1, len-eq - 2);
			BiTree T1,T2;
			build(T1, left, 0, left.length());
			node_exchange(T1);
			node_associate(T1);
			OrderTraverse(T1);
			build(T2, right, 0, right.length());
			node_exchange(T2);
			node_associate(T2);
			OrderTraverse(T2);
		}
		else
		build(T, s, 1, len - 1);
		node_exchange(T);
		node_associate(T);
		OrderTraverse(T);
		cout << endl;
	}
	else
	cout<<"输入不合法！"<<endl;
	return 0;
}
