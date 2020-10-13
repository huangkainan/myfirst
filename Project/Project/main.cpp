#include <iostream>
#include <stack>

// �ж��Ƿ��ǲ�����
bool isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return true;
    return false; // ���򷵻�false
}

// ��ȡ���ȼ�
int getPriority(char ch) {
    int level = 0; // ���ȼ�

    switch (ch) {
    case '(':
        level = 1;
        break;
    case '+':
    case '-':
        level = 2;
        break;
    case '*':
    case '/':
        level = 3;
        break;
    default:
        break;
    }
    return level;
}

int main(int argc, const char* argv[]) {
    // insert code here...
    int num;
    char arr[250]; // һ��һ���Ķ�ȡ���ʽ��ֱ������'\0'
    std::stack<char> op; // ջop:�洢������

    while (1) {
        std::cin.getline(arr, 250);
        int len, i;
        char c; // c�洢��ջ��ȡ���Ĳ�����

        len = (int)strlen(arr); // strlen()������ǣ�unsigned long���ͣ�����Ҫǿ��ת��Ϊint����
        i = 0;
        while (i < len) {
            if (isdigit(arr[i])) { // ���������
                num = 0;
                do {
                    num = num * 10 + (arr[i] - '0'); // ch - 48����ASCAII�룬�ַ�������֮���ת����ϵ
                    i++; // ��һ���ַ�
                } while (isdigit(arr[i]));
                std::cout << num << " ";
            }
            else if (arr[i] == '(') { // (:������
                op.push(arr[i]);
                i++;
            }
            else if (isOperator(arr[i])) { // ������
                if (op.empty()) {// ���ջ�գ�ֱ��ѹ��ջ
                    op.push(arr[i]);
                    i++;
                }
                else {
                    // �Ƚ�ջop���Ĳ�������ch�����ȼ�
                    // ���ch�����ȼ��ߣ���ֱ��ѹ��ջ
                    // �����Ƴ�ջ�еĲ�������ֱ��������С��ch�����ȼ�������������������ջ�ѿ�
                    while (!op.empty()) {
                        c = op.top();
                        if (getPriority(arr[i]) <= getPriority(c)) {
                            // ���ȼ��ͻ����
                            std::cout << c << " ";
                            op.pop();
                        }
                        else // ch���ȼ�����ջ�в�����
                            break;
                    } // while����
                    op.push(arr[i]); // ��ֹ���ϵ��Ƴ�������������ջ��;����ch���ȼ�����
                    i++;
                } // else
            }
            else if (arr[i] == ')') { // ����������ţ�һֱ�Ƴ�ջ�в�������ֱ������������(
                while (op.top() != '(') {
                    std::cout << op.top() << " ";
                    op.pop();
                }
                op.pop(); // ��������(�Ƴ�ջ
                i++;
            }
            else // ����ǿհ׷����ͽ�����һ���ַ��Ĵ���
                i++;
        } // �ڶ���while����
        while (!op.empty()) { // ��ջ���գ��������������
            std::cout << op.top() << " ";
            op.pop();
        }
        std::cout << std::endl;
        flush(std::cout);
    } // ��һ��while����
    return 0;
}