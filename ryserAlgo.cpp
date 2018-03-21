
#include <bits/stdc++.h>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost;


inline int* dec2binarr(long n, int dim)
{
    // note: res[dim] will save the sum res[0]+...+res[dim-1]
    int* res = (int*)calloc(dim + 1, sizeof(int));   
    int pos = dim - 1;

    // note: this will crash if dim < log_2(n)...
    while (n > 0)
    {
        res[pos] = n % 2;
        res[dim] += res[pos];
        n = n / 2; // integer division        
        pos--;
    }

    return res;
}

long per(int* A, int n) // expects n by n matrix encoded as vector
{
    long sum = 0;
    long rowsumprod, rowsum;
    int* chi = new int[n + 1];    
    double C = (double)pow((double)2, n); 

    // loop all 2^n submatrices of A
    for (int k = 1; k < C; k++)
    {
        rowsumprod = 1;
        chi = dec2binarr(k, n); // characteristic vector        

        // loop columns of submatrix #k
        for (int m = 0; m < n; m++)
        {
            rowsum = 0;

            // loop rows and compute rowsum
            for (int p = 0; p < n; p++)
                rowsum += chi[p] * A[m * n + p];
        
            // update product of rowsums
            rowsumprod *= rowsum;    
        
            // (optional -- use for sparse matrices)
            // if (rowsumprod == 0) break;    
        }        
        
        sum += (long)pow((double)-1, n - chi[n]) * rowsumprod;        
    }    

    return sum;
}

int main()
{
    // int A[36] = { 0,1,1,1,1,0,
    //                1,0,0,1,0,0,
    //                0,0,1,0,0,0,
    //                0,0,1,1,0,0,
    //                1,1,1,1,1,1,
    //                1,1,1,1,1,1 };

    // int A[324] = { 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //                 }    



    ifstream fp;
    fp.open("partitions.txt");
    if (!fp) 
    {
        cerr << "Unable to open file partitions.txt";
        exit(1);   // call system to stop
    }

    string line;
    map<int,int> m1;
    map<int,int> m2;
    int flag=0;
    while (getline(fp, line))
    {
        cout<<"Splitting string \""<<line<<"\" into tokens:"<<endl;
        char_separator<char> sep(" ");
        tokenizer< char_separator<char> > tokens(line, sep);
        int count=0;
        int t2;
        BOOST_FOREACH ( const string &t, tokens)
        {

            if(flag==0)
            {
                m1[stoi(t)] = count;
                count++;
            }
            else
            {
                m2[stoi(t)] = count;
                count++;
            }
            cout << t << "." << endl;
        }
        flag=1;
        cout<<count<<endl;

    }

    fp.close();

    
    fp.open("temp3.txt");
    if (!fp) 
    {
        cerr << "Unable to open file temp3.txt";
        exit(1);   // call system to stop
    }

    //istringstream iss(myText);
    getline(fp, line);
    int N = stoi(line);
    int n = N/2; 
    int A[n][n]={};
    while (getline(fp, line))
    {
        cout<<"Splitting string \""<<line<<"\" into tokens:"<<endl;
        // typedef tokenizer<char_separator<char>> tokenizer;
     //    //string s = "Boost C++ Libraries";
     //    char_separator<char> sep{" ", ":", ","};
     //    tokenizer tok{line, sep};
     //    int t2;
     //    for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
     //    {
     //     cout << *it << '\n';
        //  string z=*it;
        //  t2= stoi(z);
     //    }


        char_separator<char> sep(": ,");
        tokenizer< char_separator<char> > tokens(line, sep);
        flag=0;
        int t2;
        BOOST_FOREACH ( const string &t, tokens)
        {
            if(flag==0)
            {
                t2= stoi(t);
                if ( m1.find(t2) == m1.end() ) 
                    break;
                flag=1;
            }
            else
            {
                A[m1[t2]][m2[stoi(t)]]=1;
            }
            cout << t << "." << endl;
            
        }

    }
    fp.close();


    int k=0;
    int B[n*n];
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<A[i][j]<<" ";
            B[k]=A[i][j];
            k++;
        }
        cout<<endl;
    }

    cout<<per(B, 18)<<endl;
}