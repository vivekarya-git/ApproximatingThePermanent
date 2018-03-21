#include <bits/stdc++.h>
using namespace std;


int main ()
{
	int n;
	cin>>n;
	vector< vector<int>> adj(n*n);
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(j==0)
			{
				if(i==0)
				{
					adj[6*i + j].push_back(6*i + j+1);
					adj[6*i + j].push_back(6*i + j+6);
				}
				else if(i==5)
				{
					adj[6*i + j].push_back(6*i + j-6);
					adj[6*i + j].push_back(6*i + j+1);
				}
				else
				{
					adj[6*i + j].push_back(6*i + j-6);
					adj[6*i + j].push_back(6*i + j+1);
					adj[6*i + j].push_back(6*i + j+6);
				}
			}
			else if(j==5)
			{
				if(i==0)
				{
					adj[6*i + j].push_back(6*i + j-1);
					adj[6*i + j].push_back(6*i + j+6);
				}
				else if(i==5)
				{
					adj[6*i + j].push_back(6*i + j-6);
					adj[6*i + j].push_back(6*i + j-1);
				}
				else
				{
					adj[6*i + j].push_back(6*i + j-6);
					adj[6*i + j].push_back(6*i + j-1);
					adj[6*i + j].push_back(6*i + j+6);
				}
			}
			else
			{
				if(i==0)
				{
					adj[6*i + j].push_back(6*i + j-1);
					adj[6*i + j].push_back(6*i + j+1);
					adj[6*i + j].push_back(6*i + j+6);
				}
				else if(i==5)
				{
					adj[6*i + j].push_back(6*i + j-1);
					adj[6*i + j].push_back(6*i + j-6);
					adj[6*i + j].push_back(6*i + j+1);
				}
				else
				{
					adj[6*i + j].push_back(6*i + j-6);
					adj[6*i + j].push_back(6*i + j-1);
					adj[6*i + j].push_back(6*i + j+1);
					adj[6*i + j].push_back(6*i + j+6);
				}	
			}
		}
	}

	vector<int>  :: iterator it;
	for(int i=0; i<adj.size(); i++)
	{
		cout<<i<<" :";
		for(it= adj[i].begin(); it!= adj[i].end(); it++ )
		{
			cout<< *it<<" ";
		}	
		cout<<endl;
	}

	if (remove("temp3.txt") == 0)
      printf("temp3.txt deleted successfully");
   	else
      printf("Unable to delete the file");

  	ofstream fp;
    fp.open("temp3.txt", ios::out);
    if (!fp) 
    {
        cerr << "Unable to open file temp2.txt";
        exit(1);   // call system to stop
    }

    fp << n*n;
    fp << "\n";
    for(int i=0; i<adj.size(); i++)
	{
		fp << i;
		fp << " :";
 		for(it= adj[i].begin(); it!= adj[i].end(); it++ )
		{
			fp << *it;
			fp << " ";
		}	
		fp<<"\n";
	}
    
    fp.close();

    // int N = (n*n)/2;  // N : no. of vertices in one set of bipartite graph
    // int A[N][N]={};

    // for(int )
	
	return 0;
}