// 未完成，先睡觉
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
    if (str[0] != '$' || str[str.size() - 1] != '$') {  // 开头结尾并非 '$'
        cout << "输入Latex公式开头或结尾缺少'$'" << endl;
        return false;
    }

    // 判断 { } 是否配对
    int num = 0;
    for (auto ch : str) {
        if (ch == '{') num ++;
        if (ch == '}') num --;
    }
    if (num) return false;

    return true;
}

bool has_equal_sign(string str) { // 判断有无等号
    for (auto ch : str)
        if (ch == '=')
            return true;
    return false;
}

vector<string> getNode(string input_str) {  // 将结点提取出来，放到vector中
    vector<string> input;
    for (int i = 1; i < input_str.size() - 1;) {
        if (input_str[i] == ' ') i ++;      // 空格则跳过
        else if (input_str[i] == '{') {     // 取 {} 包围的字符串
            int j = i;
            for (; j < input_str.size() - 1; j ++)
                if (input_str[j] == '}')
                    break;
            int start = i + 1;
            if (input_str[i + 1] == '\\') start ++;
            string dataTmp = input_str.substr(start, j - start);
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

    return input;
}

node* createTree(vector<string> data, int left, int right) {
    if (left >= right)  // 只有一个节点，直接建树
        return newNode(data[left]);

    // 合法式子中不会有两个节点建树的情况

    int minn = 100;
    for (int i = right; i >= left; i --)
        if (getPriority(data[i]) < minn)
            minn = getPriority(data[i]);

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

    if (has_equal_sign(input_str)) { // 有等号，需要分成两棵树
        int index = -1;
        for (int i = 0; i < input_str.size(); i ++)
            if (input_str[i] == '=')
                index = i;
        string input_str1 = input_str.substr(1, index - 1);
        string input_str2 = input_str.substr(index + 1, input_str.size() - index - 2);

        vector<string> data1 = getNode(input_str1);
        vector<string> data2 = getNode(input_str2);
        /* 建树 输出树 */
        node* root1 = createTree(data1, 0, data1.size() - 1);
        addIndex(root1);
        cout << "等式左边树结构如下：\n";
        printTree(root1);
        cout << endl;

        node* root2 = createTree(data2, 0, data2.size() - 1);
        addIndex(root2);
        cout << "等式右边树结构如下：\n";
        printTree(root2);
    }else {
        vector<string> data = getNode(input_str);

        /* 建树 输出树 */
        node* root = createTree(data, 0, data.size() - 1);
        addIndex(root);
        printTree(root);
    }

    return 0;
}

// 测试样例：${\alpha } + {\beta} \times {\gamma} = {\lambda} + {\pi} \times {\tau}$
//Please input your Latex string:${\alpha } + {\beta} \times {\gamma} = {\lambda} + {\pi} \times {\tau}$
//        等式左边树结构如下：
//        索引：1	值：+
//        索引：2	值：alpha
//        索引：3	值：times
//        索引：4	值：beta
//        索引：5	值：gamma
//
//        等式右边树结构如下：
//        索引：1	值：+
//        索引：2	值：lambda
//        索引：3	值：times
//        索引：4	值：pi
//        索引：5	值：tau


// 测试样例：${a} - {b} + {c} \times {d} + {c} - {a} \times {b} + {c} \times {d}$
//Please input your Latex string:${a} - {b} + {c} \times {d} + {c} - {a} \times {b} + {c} \times {d}$
//        索引：1	值：+
//        索引：2	值：-
//        索引：3	值：times
//        索引：4	值：+
//        索引：5	值：times
//        索引：6	值：c
//        索引：7	值：d
//        索引：8	值：+
//        索引：9	值：c
//        索引：10	值：a
//        索引：11	值：b
//        索引：12	值：-
//        索引：13	值：times
//        索引：14	值：a
//        索引：15	值：b
//        索引：16	值：c
//        索引：17	值：d

// 测试样例：${a} - {b} + {c} \times {d} + {c} = {a} \times {b} + {c} \times {d}$
//Please input your Latex string:${a} - {b} + {c} \times {d} + {c} = {a} \times {b} + {c} \times {d}$
//        等式左边树结构如下：
//        索引：1	值：+
//        索引：2	值：+
//        索引：3	值：c
//        索引：4	值：-
//        索引：5	值：times
//        索引：6	值：-
//        索引：7	值：b
//        索引：8	值：c
//        索引：9	值：d
//
//        等式右边树结构如下：
//        索引：1	值：+
//        索引：2	值：times
//        索引：3	值：times
//        索引：4	值：a
//        索引：5	值：b
//        索引：6	值：c
//        索引：7	值：d
