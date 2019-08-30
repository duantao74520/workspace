#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s("abcdefg");
    cout<<"s.size = "<<s.size()<<endl;
    cout<<"s.capacity = "<<s.capacity()<<endl;
    s[s.size()] = 'h';
    cout<<"s[s.size()] = " << s[s.size()]<<endl;
    return 0;

}