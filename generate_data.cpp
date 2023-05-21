#include <iostream>
#include <fstream>
#include <random>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    const int num_datasets = 10;
    const int dataset_size = 1000000;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000000);

    for (int i = 0; i < num_datasets; ++i) {
        vector<int> dataset;

        for (int j = 0; j < dataset_size; ++j) {
            dataset.push_back(dist(gen));
        }

        shuffle(dataset.begin(), dataset.end(), gen);

        string filename = "data" + to_string(i+1) + ".txt";
        ofstream outfile(filename);

        if (outfile.is_open()) {
            for (int x : dataset) {
                outfile << x << endl;
            }
            outfile.close();
        }
        else {
            cout << "Unable to open file " << filename << endl;
            return 1;
        }
    }

    return 0;
}
