#include <iostream>
#include <string>
#include <vector>

int to_int(char ch);
char to_char(int n);
std::string addition(std::string a, std::string b);
std::string subtraction(std::string a, std::string b);
std::string multiplication(std::string a, std::string b);

std::string karatsuba(std::string n1, std::string n2)
{
    if (n1 == "0" || n2 == "0")
        return "0";

    int N = static_cast<int>( std::max(n1.size(), n2.size()) );
    n1.insert(0, std::string(N - n1.size(), '0'));
    n2.insert(0, std::string(N - n2.size(), '0'));

    if (N == 1)
        return std::to_string(std::stoi(n1) * std::stoi(n2));

    /**
     * (a + b)(c + d) = ac + ad + bc + bd
     * ad + bc = (a + b)(c + d) - (ac + bd)
     * 
     * 12 + 34 
     * -> (10 + 2)(30 + 4)
     * -> (1*3)*100 + (1*4 + 2*3)*10 + (2*8)
     * -> 300 + 100 + 8
     * -> 408
    **/
    int mid = N / 2;
    std::string a = n1.substr(0, mid);
    std::string b = n1.substr(mid, N - mid);

    std::string c = n2.substr(0, mid);
    std::string d = n2.substr(mid, N - mid);

    std::string ac = karatsuba(a, c);
    std::string bd = karatsuba(b, d);
    std::string z = karatsuba(addition(a, b), addition(c, d));
    std::string temp = subtraction(z, addition(ac, bd));

    ac.append(std::string((N - mid) * 2, '0'));
    temp.append(std::string((N - mid), '0'));

    return addition(addition(ac, temp), bd);
}

int main(void)
{
    std::cout << multiplication("12", "34") << std::endl;
    std::cout << karatsuba("12", "34") << std::endl;

    return 0;
}

int to_int(char ch)
{
    return ch - '0';
}

char to_char(int n)
{
    return n + '0';
}

std::string addition(std::string a, std::string b)
{
    int N = static_cast<int>( std::max(a.size(), b.size()) );
    a.insert(0, std::string(N - a.size(), '0'));
    b.insert(0, std::string(N - b.size(), '0'));

    std::string result(N, '0');
    int carry = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        int n1 = to_int(a[i]);
        int n2 = to_int(b[i]);

        int sum = n1 + n2 + carry;
        carry = sum / 10;

        result[i] = to_char(sum % 10);
    }

    if (carry > 0)
        result.insert(0, std::string(1, to_char(carry)));

    return result;
}

std::string subtraction(std::string a, std::string b)
{
    if (a == b) 
        return "0";
    
    int N = static_cast<int>( std::max(a.size(), b.size()) );
    a.insert(0, std::string(N - a.size(), '0'));
    b.insert(0, std::string(N - b.size(), '0'));

    std::string result(N, '0');
    int carry = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        int n1 = to_int(a[i]);
        int n2 = to_int(b[i]);

        int sub = n1 - n2 + carry + 10;
        carry = (sub / 10) - 1;

        result[i] = to_char(sub % 10);
    }

    int i = 0;
    while (result[i] == '0')
        i++;

    result = result.substr(i, result.size() - i);

    return result;
}

std::string multiplication(std::string a, std::string b)
{
    if (a == "0" || b == "0")
        return "0";

    int N = static_cast<int>( std::max(a.size(), b.size()) );
    a.insert(0, std::string(N - a.size(), '0'));
    b.insert(0, std::string(N - b.size(), '0'));

    std::string result(2 * N, '0');
    for (int i = N - 1; i >= 0; i--)
    {
        int carry = 0;
        int n1 = to_int(a[i]);
        int k = i + 1;
        for (int j = N - 1; j >= 0; j--)
        {
            int n2 = to_int(b[j]);

            int sum = n1 * n2 + to_int(result[k + j]) + carry;
            
            carry = sum / 10;

            result[k + j] = to_char(sum % 10);
        }
        result[i] = to_char(carry);
    }

    int i = 0;
    while (result[i] == '0')
        i++;
    
    result = result.substr(i, result.size());

    return result;
}