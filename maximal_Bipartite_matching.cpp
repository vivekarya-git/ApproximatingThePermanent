// A C++ program to find maximal Bipartite matching.
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

// M is number of applicants and N is number of jobs
#define M 6
#define N 6

// A DFS based recursive function that returns true if a
// matching for vertex u is possible
bool bpm(vector<vector<int>> bpGraph2, int u, bool seen[], int matchR[])
{
	// Try every job one by one
// 	for (int v = 0; v < N; v++)
// 	{
	vector<int>  :: iterator it;
	for(it= bpGraph2[u].begin(); it!= bpGraph2[u].end(); it++ )
	{
		// If applicant u is interested in job v and v is
		// not visited
		if ( !seen[*it-N])
		{
			seen[*it-N] = true; // Mark v as visited

			// If job 'v' is not assigned to an applicant OR
			// previously assigned applicant for job v (which is matchR[v]) 
			// has an alternate job available. 
			// Since v is marked as visited in the above line, matchR[v] 
			// in the following recursive call will not get job 'v' again
			if (matchR[*it-N] < 0 || bpm(bpGraph2, matchR[*it-N], seen, matchR))
			{
				matchR[*it-N] = u;
				return true;
			}
		}
	}
	return false;
}

// Returns maximum number of matching from M to N
int maxBPM(vector<vector<int>> bpGraph2)
{
	// An array to keep track of the applicants assigned to
	// jobs. The value of matchR[i] is the applicant number
	// assigned to job i, the value -1 indicates nobody is
	// assigned.
	int matchR[N];

	// Initially all jobs are available
	memset(matchR, -1, sizeof(matchR));

	int result = 0; // Count of jobs assigned to applicants
	for (int u = 0; u < M; u++)
	{
		// Mark all jobs as not seen for next applicant.
		bool seen[N];
		memset(seen, 0, sizeof(seen));

		// Find if the applicant 'u' can get a job
		if (bpm(bpGraph2, u, seen, matchR))
			result++;
	}
	return result;
}

// Driver program to test above functions
int main()
{
	// Let us create a bpGraph shown in the above example
// 	bool bpGraph[M][N] = { {0, 1, 1, 0, 0, 0},
// 						{1, 0, 0, 1, 0, 0},
// 						{0, 0, 1, 0, 0, 0},
// 						{0, 0, 1, 1, 0, 0},
// 						{0, 0, 0, 0, 0, 0},
// 						{0, 0, 0, 0, 0, 1}
// 					};
					
	vector<vector<int>> bpGraph2(M+N);
	
	int u,v,i,m;
	cin>>m;
	for( i=0; i<m; i++)
	{
	    cin>>u>>v;
	    bpGraph2[u].push_back(v);
	    bpGraph2[v].push_back(u);
	    
	    
	}
	
	vector<int>  :: iterator it;
	for(i=0; i<bpGraph2.size(); i++)
	{
		cout<<i<<" :";
		for(it= bpGraph2[i].begin(); it!= bpGraph2[i].end(); it++ )
		{
			cout<< *it<<" ";
		}	
		cout<<endl;
	}
	

	cout << "Maximum number of applicants that can get job is "
		//<< maxBPM(bpGraph)<<endl;
		<< maxBPM(bpGraph2)<<endl;
		
		//cout<<sizeof(bpGraph2);

	return 0;
}
