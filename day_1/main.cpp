#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class key_count_t
{
    public:
    key_count_t(int a, unsigned int b) : 
        value(a), count(b)
    {}
    int value;
    unsigned int count;

    void print()
    {
        cout << value << " -- " << count << endl;
    }
};

bool comp(int a, int b) {
    return a <= b;
}

void load_data(const char* filepath, vector<int> &left, vector<int> &right)
{
    fstream file(filepath);
    string line;
    int num1, num2;
    while (file >> num1 >> num2)
    {
        left.push_back(num1);
        right.push_back(num2);
    }
    sort(left.begin(), left.end(), comp);
    sort(right.begin(), right.end(), comp);
    file.close();
}


void right_count(vector<int> right, vector<key_count_t> &right_counter)
{
    key_count_t prev(0,0);
    for (int i : right)
    {
        if (i == prev.value)
        {
            prev.count++;
        }
        else
        {
            if (prev.value)
            {
                right_counter.push_back(prev);
            }
            prev.value = i;
            prev.count = 1;
        }
        
    }
    // for (int i = 0; i < right_counter.size(); i++)
    // {
    //     right_counter[i].print();
    // }
}

void count_similarity(vector<int> &left, vector<key_count_t> &right_counter)
{
    long long sum = 0;
    for (int i : left)
    {
        for (key_count_t x : right_counter)
        {
            if (i == x.value) sum += i*x.count;
            else if (i < x.value)
            {
                break;
            }
            
        }
    }
    cout << "SUM = " << sum << endl;
}

int main(int argc, char **argv)
{
    vector<int> left; 
    vector<int> right;
    vector<key_count_t> right_counter;
    load_data("test.txt", left, right);
    right_count(right, right_counter);
    count_similarity(left, right_counter);

    return 0;
}