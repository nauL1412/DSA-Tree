#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Hàm tạo bộ dữ liệu ngẫu nhiên với kích thước size và lưu vào tệp filename
void generateRandomData(int size, string filename) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        srand(time(nullptr));   // Khởi tạo seed cho hàm sinh số ngẫu nhiên
        for (int i = 0; i < size; i++) {
            int value = rand() % 1000000;   // Sinh số ngẫu nhiên trong khoảng từ 0 đến 999999
            outputFile << value<< endl;  // Ghi giá trị vào tệp văn bản
        }
        outputFile.close();
    }
    else {
        cout << "Không thể mở tệp!" << endl;
    }
}


int main() {
    // Tạo 10 bộ dữ liệu ngẫu nhiên với mỗi bộ có 10^6 giá trị
    for (int i = 1; i <= 10; i++) {
        string filename = "data" + to_string(i) + ".txt";
        
            generateRandomData(1000000, filename);
        
    }
    return 0;
}