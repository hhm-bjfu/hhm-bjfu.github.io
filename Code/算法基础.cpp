#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int getPriority (string str) {
    if (str == "+" || str == "-") return 1;
    if (str == "times") return 2;
    if (str == "*" || str == "/") return 2;
    return 10;
}

struct node {
    int index;
    int priority;
    string text;

    node* lchild;
    node* rchild;
};

node* newNode (string str) {
    node* Node = new node;
    Node->text = str;
    Node->priority = getPriority(str);
    Node->lchild = Node->rchild = NULL;
    return Node;
}

bool is_Latex(string str) {
    if (str[0] != '$' || str[str.size() - 1] != '$')
        return false;
    return true;
}

node* createTree(vector<string> data, int left, int right) {
    if (left >= right)  // 只有一个节点，直接建树
        return newNode(data[left]);

    // 合法式子中不会有两个节点建树的情况

    int minn = 100;
    for (int i = right; i >= left; i --)
        if (getPriority(data[i]) < minn)
            minn = getPriority(data[i]);

    cout << minn << endl;

    // 三个节点以上建树
    node* root = NULL;
    int index = 0;
    for (int i = right; i >= left; i --) // 得到优先级最低的节点
        if (getPriority(data[i]) == minn) {
            index = i;
            break;
        }

    root = newNode(data[index]); // 建立根节点
    root->rchild = createTree(data, index + 1, right);
    root->lchild = createTree(data, left, index - 1);
    return root;
}

void addIndex(node* &root) {
    queue<node*> q;
    q.push(root);
    int idx = 0;
    while (!q.empty()) {
        node* now = q.front();
        q.pop();
        now->index = ++idx;
        if (now->lchild != NULL) q.push(now->lchild);
        if (now->rchild != NULL) q.push(now->rchild);
    }
}

void printTree(node* root) {
    queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        node* now = q.front();
        q.pop();
        cout << "索引：" << now->index << "\t" << "值：" << now->text << endl;
        if (now->lchild != NULL) q.push(now->lchild);
        if (now->rchild != NULL) q.push(now->rchild);
    }
}

int main () {
    /* 输入部分 */
    start:
    cout << "Please input your Latex string:";
    string input_str; getline(cin, input_str);
//    cout << input_str << endl;

    /* 判断是否为合法Latex字符串 */
    if (!is_Latex(input_str)) {
        cout << "The input is invalid! Please enter again!" << endl;
        goto start;
    }

    /* 将每一个节点提取出来，放到vector中 */
    vector<string> input;
    for (int i = 1; i < input_str.size() - 1;) {
        if (input_str[i] == ' ') i ++;      // 空格则跳过
        else if (input_str[i] == '{') {     // 取 {} 包围的字符串
            int j = i;
            for (; j < input_str.size() - 1; j ++)
                if (input_str[j] == '}')
                    break;
            string dataTmp = input_str.substr(i + 1, j - i - 1);
            input.push_back(dataTmp);
            i += (j - i + 1);
        }else if (input_str[i] == '\\') {   // 取 \ 开头的字符串
            int j = i;
            for (; j < input_str.size() - 1; j ++)
                if (input_str[j] == ' ' || input_str[j] == '{')
                    break;
            string opTmp = input_str.substr(i + 1, j - i - 1);
            input.push_back(opTmp);
            i += (j - i);
        }else if (input_str[i] == '+'|| input_str[i] == '-') {  // 遇见 + 或者 -
            string opTmp = ""; opTmp.push_back(input_str[i]);
            input.push_back(opTmp);
            i ++;
        }else i ++;
    }

    /* 建树 输出树 */
    node * root = createTree(input, 0, input.size() - 1);
    addIndex(root);
    printTree(root);


    return 0;
}
