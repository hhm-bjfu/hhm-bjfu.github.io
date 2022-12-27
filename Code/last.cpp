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
	struct  BiNode* lchild, * rchild; //���Һ���ָ��
}BiNode, * BiTree;
map<string, int> operatorMp;	//�����׺��ǰ׺ 
/*�ҵ����ȼ���͵��Ǹ��������λ�� ----���λ��Ӧ������������ʾ�����߷�����Ӧ����ʼλ�ú��ַ���
	Ѱ�����һ���������ֻ�е�p=0��ʱ��ſ��ǣ���p��¼���ţ�
	��Ϊ������������һ������������ģ�����������һ������������������
	flag��¼���ֵ�����һ������� ������Ҫ������ȷ��
	*/
string FindLowest(string s, int x, int y, int& c1, int& c2, int &c3, int& flag)	//�ȷֿ���׺ǰ׺ 
{
	int p = 0;//��¼��������û 
	int is_single = -1;//��¼��+- ^ �����Ƿ񷵻��ַ��������߷��ؿ��ַ�����ҪΪ��һ�����ڵ�ֽ�λ�ÿ��� 
	string opt;//��¼����� 
	for (int i = x; i < y; i++)	//---------��������ؼ���   ԭ��ֻ��Ҫ�ж�һ���ַ����ɣ�������Ҫ����ַ�һ���ж� 
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
			if (!p)		//p>0���������棬p=0���������� 
			{
				c1 = i;	//��¼���ų��ֵ�λ�ã���Ϊ�ҵľ��������������������ȼ���͵��Ǹ�����
				is_single = 1;//�����¼���ֵ��ǵ����ַ��������
				flag = 2;
			}
			break;
		case'^':
			if (!p)		//������ ���ȼ���
			{
				c3 = i;		//------- ��������ŵ�λ�ø�ֵ  
				is_single = 1;
				flag = 2;
			}
			break;
		case'\\':	//����������ַ�����������������������ǳ������� 
			if (!p && c1 < 0) //���������+ - �Ͳ���Ҫ�ж��������ȼ��ߵķ���
			{
				is_single = 0;
				opt = ""; 	//��¼����ַ�������� 
				int index = i + 1;//���� /
				while (1)
				{//�ж��ַ���Ƭ���Ƿ�ͷ�ı�־��{ } ���� + -  ����   ������ñ�־ ֻ��ÿ�ַ������ж��Ƿ��������
					if (s[index] == '{' || s[index] == '}'|| s[index] == '(' || s[index] == ')' || s[index]=='+'||s[index]=='-')
					break;
					else
					{
						string ch(1, s[index]);
						opt += ch;
						index++;
					}
				}
				map<string, int>::iterator it; //ȡ��opt֮���жϣ���ȡ���ȼ� 
				for (it = operatorMp.begin(); it != operatorMp.end(); it++)
				{
					if (it->first == opt)		//�ҵ����������� 
					{
						switch (it->second) //���⣺ǰ�� ���г�����׺��ǰ׺������ụ��ı����
						{
							case 2://˫Ŀ
							{
								c2 = i;//------- ��������ŵ�λ�ø�ֵ 
								flag = 2;
								opt = "\\" + opt;
								break;
							}
							case 12://˫Ŀǰ׺
							{
								c2 = i;
								flag = 12;
								opt = "\\" + opt;
								break;
							}
							case 1: //��Ŀ 
							{
								if (flag == 0) 
								{
									c2 = i;//------- ��������ŵ�λ�ø�ֵ
									flag = 1;
									opt = "\\" + opt;
									break;
								}
							}
							case 0: //��������
								break;
						}
						break;
					}
				}
				i = index - 1;//��i��ֵ�������Ž�����λ��
			}
			break;
		}
	}
	if (is_single == 1 || is_single == -1)	//������һ����������ȼ�������+ - ^
		return "";
	else if (is_single == 0)	//�����Ǳ�+-�ߵ����ȼ� ���� 
		return opt;
}
//��һ�����⣺����ֵis_singleû�б仯��-1������ֵӦ���ǡ���;index �� i��λ��Ҫȷ����
//����left right��ֱ�Ӻ��Ե�,�����ַ������ȣ���Ҫ����дһ���ж��Ƿ��������left right �ж���Ҫ�ڵڶ��� OK
//����ǰ׺�����
//ûд�жϺϷ���
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
int Is_prefix(string s,int x, string& opt)	//����ֵ�Ƕ�Ӧ������
{
	if (s[x] == '\\')//�ж���map���е�
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
			if (it->first == opt)		//�ҵ����������� ---- Ҳ�����ǳ������ţ����濼�ǣ�
			{
				opt = "\\" + opt;	
				return it->second;
			}
		}
		return 0;//û�ҵ���������
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
	if (s[x] == '\\') //�ж���map���е�
	{
		str = s.substr(x + 1,y - x - 1); //��x+1λ ��ʼ y-x -1λ
		map<string, int>::iterator it;
		for (it = operatorMp.begin(); it != operatorMp.end(); it++)
		{
			if (it->first == str && it->second == 0)	//�����ǳ�������
			{
				return 1;
			}
		}	
		return 0;
	}
	else
		return 0;
}
//���⣺ֻ�����˿�ͷ��ǰ׺����� ������������ʽ�Ӷ������������µ� ˵���׾���û�жԱ��������ȼ��Ĵ�С
BiTree build(BiTree& T, string s, int x, int y)//x��ʾ�ַ�������ʼ��ַ��y��ʾ������ַ��
{
	if (y - x == 1)		//��һ���ַ��������������
	{
		T = new BiNode;
		T->ch = s[x];
		T->lchild = NULL;
		T->rchild = NULL;
		return T;
	}
	else if (Is_cons(s, x, y) == 1) //�ǳ������� 
	{
		T = new BiNode;
		T->ch = s.substr(x, y - x);
		T->lchild = NULL;
		T->rchild = NULL;
		return T;
	}
	//�ж�left right  ����ж�Ҳ��ʵ�� ��������һ������left right����������ŷ���
	//if (Left_right(s, x, y) == 1)//����ǵĻ��޸�x,y��ֵ�����ı�s����
	//{
	//	x = x + 6;
	//	y = y - 7;
	//}
	//�ж�ǰ׺ �������  ����ȫ�����жϣ�ֻ��������ʽ�� ������Ǿʹ��� 
	//�ҵ�ʽ�������ȼ���͵ķ���
	int c1 = -1, c2 = -1,c3 = -1, flag = 0;
	//c1��¼�����ҡ����ֵļӼ��ţ�c2��¼�����ҡ����ֵĳ˳��ţ�p��¼����������
	string opt;
	opt = FindLowest(s, x, y, c1, c2, c3, flag);//��������ж�ȫ��
	if (c1 < 0)//�Ҳ����������������ȼ����š�+-��,��ô��͵����������Ŵ���ģ���������ȼ��ķ�����Ϊ�Ӹ�����
		c1 = c2;
	if (c1 < 0)//���c2û�䣬����ʽ�ӱ�һ�������Ÿ���������
		//����c3����û������ʽ����������ȼ�����^
	{
		if(c3 == -1)
		return build(T, s, x + 1, y - 1);  //�Ѵ�����ȥ��
	}
	//���Ƕ�����׺�����  ----����flag�ж� 
	if (flag == 2)	//---	������׺����� 
	{
		if (opt == "" && c3 < 0)	// �� + - 
		{
			T = new BiNode;
			T->ch = s[c1];            //���ɸ����
			build(T->lchild, s, x, c1);  //�ݹ鴴��������
			build(T->rchild, s, c1 + 1, y); //�ݹ鴴��������
		}
		else if(opt == "" && c3 > 0)	// ��^
		{
			T = new BiNode;
			T->ch = s[c3];            //���ɸ����
			build(T->lchild, s, x, c3);  //�ݹ鴴��������
			build(T->rchild, s, c3 + 1, y); //�ݹ鴴��������
		}
		else				  // ��map��������
		{
			T = new BiNode;
			T->ch = opt;            //���ɸ����
			build(T->lchild, s, x, c1);  //�ݹ鴴��������
			build(T->rchild, s, c1 + opt.length(), y); //�ݹ鴴��������
		}
		return T;
	}
	else if (flag == 12)	//ǰ׺˫Ŀ�����
	{
		int divide = FindDivide(s, x + opt.length(), y);//�ֽ��{��λ��
		T = new BiNode;
		T->ch = opt;            //���ɸ����
		build(T->lchild, s, x + opt.length(), divide + 1);  //�ݹ鴴��������
		build(T->rchild, s, divide + 1, y);		//�ݹ鴴��������
		return T;
	}
	else if (flag == 1)  
	{
		T = new BiNode;
		T->ch = opt;            //���ɸ����
		build(T->lchild, s, x + opt.length(), y);  //�ݹ鴴��������
		T->rchild = NULL;	//������Ϊ��
		return T;
	}
}
void OrderTraverse(BiTree T)
{
	BiTree temp[100];   //����ָ�����͵�ָ������
    int in = 0;
    int out = 0;

    temp[in++] = T;  //�ȱ�����������ڵ� 

    while (in > out)
    {
        if (temp[out])
        {
            //cout << temp[out]->ch << " �� ";
            cout << "��" << out+1 << "��ֵΪ��" << temp[out]->ch << endl;
            temp[in++] = temp[out]->lchild;
            temp[in++] = temp[out]->rchild;
        }
        out++;
    }
}
// �����ǣ�
// ${{a}\div{{c}+{b}}}$
// $\sin{{a}+{b}}$
// $\frac{a}{b}$
// $\sqrt{\frac{{a}+{b}}{{c}+{d}}}$
// $\frac{{a}-{1}}{{b}-{1}}$
// $\sqrt{a}+\sqrt{b}$     
// ${\alpha}+{\beta}$
// ����������{}������ ���߲����ж� ������� 
// ${a}^{2}+{b}^{2}$
// $({A}\land{B})\lor({A}\land{C})$
// û���ǲ��ǵ����ַ��ĳ�������� 2ab  
// �м��еȺŵĻ����ֳ����ηֱ���
// left right �������� �ڿ�ʼ��ʱ��ֱ���õ�  ȥ��ֻʣ����  
// û�����м��пո�
void node_exchange(BiTree T)//������ 
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

void node_associate(BiTree T)//����� 
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
 	if(str[0] != '$' || str[len - 1] != '$'){//��ͷ��β������$
	 	cout<<"$����!"<<endl;
		return false;
	} 
    else if(num != 0){//�����Ų�ƥ�� 
		cout<<"�����Ÿ�����ƥ��!"<<endl;
		return false;
	}
	else if(flag_sum != 1){//latex�������ƥ��
		cout<<"LaTex���ű�ʾ����!"<<endl;
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
	//��׺����� -----˫Ŀ 
	operatorMp.insert(pair<string, int>{"times", 2});
	operatorMp.insert(pair<string, int>{"div", 2});
	operatorMp.insert(pair<string, int>{"land", 2});	//��
	operatorMp.insert(pair<string, int>{"lor", 2});		//��	
	operatorMp.insert(pair<string, int>{"oplus", 2});	//���
	operatorMp.insert(pair<string, int>{"to", 2});		//
	//ǰ׺�����------˫Ŀ 
	operatorMp.insert(pair<string, int>{"frac", 12});
	//ǰ׺�����------��Ŀ 
	operatorMp.insert(pair<string, int>{"sin", 1});
	operatorMp.insert(pair<string, int>{"cos", 1});
	operatorMp.insert(pair<string, int>{"tan", 1});
	operatorMp.insert(pair<string, int>{"sec", 1});
	operatorMp.insert(pair<string, int>{"neg", 1});
	operatorMp.insert(pair<string, int>{"sqrt", 1});
	//��������&ϣ����ĸ
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
	cin >> s;	//����Ĺ�ʽ��$ $��ʽ
	if(Is_legal(s)) 
	{
		int len = s.length();
		int eq = Equal_sign(s);
		if (eq) //�м��� = �ֳ����ηֱ���
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
	cout<<"���벻�Ϸ���"<<endl;
	return 0;
}
