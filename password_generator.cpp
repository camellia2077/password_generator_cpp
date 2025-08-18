#include <iostream>
#include <string>
#include <random>
#include <fstream>
using namespace std;

// 函数：将密码写入 TXT 文件（写入前会自动清空内容）
bool savePasswordToFile(const string& password, const string& filename) {
    // ofstream 默认模式是 ios::out | ios::trunc，打开时就会把文件内容清空
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "无法打开文件：" << filename << endl;
        return false;
    }
    outfile << password << endl; // 写入密码并换行
    outfile.close();
    return true;
}

string generatePassword(int length) {
    const string all_chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()_+-=[]{}|;:',.<>/?-";
    random_device rd;
    uniform_int_distribution<int> dist(0, static_cast<int>(all_chars.size()) - 1);

    string pwd;
    pwd.reserve(length);
    for (int i = 0; i < length; i++) {
        pwd += all_chars[dist(rd)];
    }
    return pwd;
}

int main() {
    int password_length = 20;
    string new_password = generatePassword(password_length);
    cout << new_password << endl;
    string filename = "passwords.txt";
    bool tofile = savePasswordToFile(new_password, filename);
    system("pause");
    return 0;
}
