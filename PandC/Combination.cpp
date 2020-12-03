#include <iostream>

using namespace std;

void combination(string& str, string& output, int start, int index)
{
    // start to select substring from str
    // index indicate which char is being working on in output

    // Base case
    if (index >= output.size())
    {
        cout << output << endl;
        return;
    }

    for (int i = start; i < str.length(); ++i)
    {
        // Check if needs continue
        if (str.length() - i < output.length() - index) 
            break;

        output[index] = str[i];
        combination(str, output, i + 1, index + 1);

    }
}

int main()
{
    string str = "12345";
    int r = 3;

    // start
    string out(r, 'a');

    combination(str, out, 0, 0);
}