#include <bits/stdc++.h>
using namespace std;
int main ()
{
    string str = "g++ -std=c++11 -o JSobject JS_implementation.cpp";
    //str = str + " -o a.out JS_implementation.cpp";
 
    // Convert string to const char * as system requires
    // parameter of type const char *
    const char *command = str.c_str();
    cout << "Compiling file using " << command << endl;
    system(command);

    if (remove("temp2.txt") == 0)
      printf("temp2.txt deleted successfully");
    else
      printf("Unable to delete the file");
 
 
    // for(int example=0; example<5; example++)
    // {
        for(int i=0; i<10; i++)
        {
            cout << "\nRunning program for example 1 "<<i<<"th time"<<endl;
            string str2 = "./JSobject";
            system(str2.c_str());

        }

        ifstream fp;
        fp.open("temp2.txt");
        if (!fp) 
        {
            cerr << "Unable to open file temp2.txt"<<endl;
            exit(1);   // call system to stop
        }

        
        
        string line;
        float sum=0,approxValue;
        //istringstream iss(myText);
        while (fp >> approxValue)
        {
            sum = sum + abs(approxValue-2)/2;

        }
        fp.close();

        float avgRelError = sum/10;

        cout<<"Avg relative error is "<<avgRelError<<endl;
        // ifstream fp;
        // fp.open("logs.txt");
        // if (!fp) 
        // {
        //     cerr << "Unable to open file logs.txt";
        //     exit(1);   // call system to stop
        // }

    //}
 
    return 0;
}
