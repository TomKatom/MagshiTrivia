/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    vector<unsigned char> buffer;
    buffer.push_back(1);
    buffer.push_back(0);
    buffer.push_back(1);
    buffer.push_back(0);
    
    int length = (((buffer[0] << 8 | buffer[1]) << 8 | buffer[2]) << 8 | buffer[3]) ;

    
    cout<<"length = " << length;

    return 0;
}
