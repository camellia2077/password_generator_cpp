#include <iostream>
#include <string>
#include <random>
#include <fstream>

using namespace std;

// 函数：将密码存储到 TXT 文件
bool savePasswordToFile(const string& password, const string& filename) {
    ofstream outfile; // 创建一个输出文件流对象
    // 以追加模式打开文件，如果文件不存在则创建它
    outfile.open(filename, ios::app);
    outfile << password << endl; // 将密码写入文件，并换行
    outfile.close(); // 关闭文件
    cout << "Password saved to " << filename << endl;
    return true; // 表示保存成功
    

}

string generatePassword(int length) {
    // 定义密码中可能包含的字符集
    const string lowercase_chars = "abcdefghijklmnopqrstuvwxyz";
    const string uppercase_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digit_chars = "0123456789";
    const string symbol_chars = "!@#$%^&*()_+-=[]{}|;:',.<>/?";

    string all_available_chars = lowercase_chars + uppercase_chars + digit_chars + symbol_chars;

    std::random_device rd; //生成随机数
    string password = "";
    // 使用 mt19937 替代 random_device 以获得更好的随机性，并用 rd 初始化它
    // 利用随机数作为种子
    std::mt19937 generator(rd()); 
    std::uniform_int_distribution<int> distribution(0, static_cast<int>(all_available_chars.length()) - 1);

    for (int i = 0; i < length; ++i) {
        // 使用 generator 而不是 rd 来生成随机数
        password += all_available_chars[distribution(generator)];
        //  利用generator，并根据范围是 0 到 all_available_chars.length() - 1），
        //  生成一个在该范围内的、均匀分布的随机整数。这个整数将作为从 all_available_chars 字符串中选取字符的索引。
    }

    return password;
}

int main() {
    int password_length = 20; // 密码长度
    string new_password = generatePassword(password_length); // 调用函数

    cout << "Generated Password (" << password_length << " characters): " << new_password << endl;
    // 调用新的函数来保存密码
    string filename = "passwords.txt";
    // 把new_password保存得到txt中
    savePasswordToFile(new_password, filename);

    return 0;
}