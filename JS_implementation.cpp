/*  Approximation Algo for counting perfect matching  */


#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <time.h>
#include <utility>


using namespace std;
using namespace boost;


// Ford-Fulkerson algorithm to find maximum Bipartite matching.
// A DFS based recursive function that returns true if a
// matching for vertex u is possible
bool bpm(vector<vector<int>>& adjList, int u, bool seen[], int matchR[], int n)
{
	// Try every job one by one
// 	for (int v = 0; v < n; v++)
// 	{
	vector<int>  :: iterator it;
	for(it= adjList[u].begin(); it!= adjList[u].end(); it++ )
	{
		// If applicant u is interested in job v and v is
		// not visited
		if ( !seen[*it-n])
		{
			seen[*it-n] = true; // Mark v as visited

			// If job 'v' is not assigned to an applicant OR
			// previously assigned applicant for job v (which is matchR[v]) 
			// has an alternate job available. 
			// Since v is marked as visited in the above line, matchR[v] 
			// in the following recursive call will not get job 'v' again
			if (matchR[*it-n] < 0 || bpm(adjList, matchR[*it-n], seen, matchR, n))
			{
				matchR[*it-n] = u;
				return true;
			}
		}
	}
	return false;
}

// Returns maximum number of matching from M to N
int maxBPM(vector<vector<int>>& adjList, int n)
{
	// An array to keep track of the applicants assigned to
	// jobs. The value of matchR[i] is the applicant number
	// assigned to job i, the value -1 indicates nobody is
	// assigned.
	int matchR[n];

	// Initially all jobs are available
	memset(matchR, -1, sizeof(matchR));

	int result = 0; // Count of jobs assigned to applicants
	for (int u = 0; u < n; u++)
	{
		// Mark all jobs as not seen for next applicant.
		bool seen[n];
		memset(seen, 0, sizeof(seen));

		// Find if the applicant 'u' can get a job
		if (bpm(adjList, u, seen, matchR, n))
			result++;
	}
	return result;
}

// checking existence of perfect matching or not in the given graph 
bool checkPerfectMatching( vector< vector<int> >& adjList, int n)
{
	bool res = false;
	int maxMatchingSize = maxBPM(adjList, n);
	if(maxMatchingSize == n)
		res = true;
	return res;
}
 
int noOfEdges(vector< vector<int> >& adjList)
{
	vector<int>  :: iterator it;
	int sum=0;
	for(int i=0; i<adjList.size(); i++)
	{
		sum += adjList[i].size();	
	}
	return sum/2;
}

void checkCases(vector <pair<int, int>> currentState, pair<int, int> edge, bool *p1, bool *p2, bool *p3, int *p4, int *p5)
{
	if(currentState.empty())
	{
		*p2 = true;
		return;
	}

	int ucount=0, ucountIndex = -1;
	int vcount=0, vcountIndex = -1;
	int u = edge.first;
	int v = edge.second;
	for(int i=0; i<currentState.size(); i++)
	{
		if(currentState[i].first == u || currentState[i].second == u)
		{
			ucount++;
			ucountIndex = i;
		}
		if(currentState[i].first == v || currentState[i].second == v)
		{
			vcount++;
			vcountIndex = i;
		}
		if( (currentState[i].first == u && currentState[i].second == v) || (currentState[i].first == v && currentState[i].second == u) )
		{
			*p1 = true;
			*p4 = i;
			break;
		}
		// if((currentState[i].first != u && currentState[i].second != v) && (currentState[i].first != v && currentState[i].second != u) )
		// {
		// 	*p2 = true;
		// 	break;
		// }

	}

	if( (ucount == 1 && vcount == 0) || (ucount == 0 && vcount == 1) )
		*p3 = true;
	if(ucount == 0 && vcount == 0)
		*p2 = true;
	if(ucount == 1 && vcount == 0)
		*p5 = ucountIndex;
	if(ucount == 0 && vcount == 1)
		*p5 = vcountIndex;

	return;
}


void MarkovChain(vector< vector<int> >& adjList, float c, int T, int *a, int *b, int E, int k, vector< pair<int, int> > edgeSet, int n)
{
	//vector< pair<int, int> > matching;
	//vector< vector <pair<int, int> > > sampleSet;
	
	for(int j=0; j<T; j++)
	{
		vector <pair<int, int>> currentState, nextState;
		bool case1 = false;
		bool case2 = false;
		bool case3 = false;
		int t=0;
		while(t <= n*n*n)//-------------------------------------???
		{
			int r = rand()%(edgeSet.size());//----------------------edgeSet
			pair<int, int> edge = edgeSet[r];
			int EdgeIndexDelete1 = -1, EdgeIndexDelete2 = -1;
			checkCases(currentState, edge, &case1, &case2, &case3, &EdgeIndexDelete1, &EdgeIndexDelete2);//-------------------checkCases
			//cout<<"case1 "<<case1<<" case2 "<<case2<<" case3 "<<case3<<" "<<(case1 + case2 + case3) <<endl;
			if(case1 == true)
			{
				double val = (double)rand()/(double)RAND_MAX; // for generating random values between 0 and 1 
				if(0 <= val && val <= 1/(2*(float)E*(1+c)) )
				{
					currentState.erase(currentState.begin() + EdgeIndexDelete1);//--------------------------------
					nextState = currentState;
				}
			}

			if(case2 == true)
			{
				double val = (double)rand()/(double)RAND_MAX;
				double term =  c/(2*(float)E*(1+c));
				//cout<<"val "<<val<<" term "<<term<<endl;
				if(0 <= val && val <= term)
				{
					currentState.push_back(edge); //----------------------------------------
					nextState = currentState;
				}
			}

			if(case3 == true)
			{
				double val = (double)rand()/(double)RAND_MAX;
				double term = c/(2*(float)E*(c+c));
				if(0 <= val && val <= term )
				{
					currentState.erase(currentState.begin() + EdgeIndexDelete2);
					currentState.push_back(edge);//------------------------------------------
					nextState = currentState;
				}
			}

			case1 = false;
			case2 = false;
			case3 = false;
			currentState = nextState;
			t++;
		}

		

		cout<<"sample "<<j<<endl;
		for(int i=0; i<currentState.size(); i++)
		{
			cout<<currentState[i].first<<" "<<currentState[i].second;
		}
		cout<<endl;

		if(currentState.size() == k)
		{
			*a = *a + 1;
		}
		if(currentState.size() == (k+1))
		{
			*b = *b + 1;
		}

	}
	return ;
}

int main()
{

	bool pmExist;
	int i,n,N;
	srand (time(NULL));
	// Read Graph file
	ifstream fp;
	fp.open("adj.txt");
	if (!fp) 
	{
	    cerr << "Unable to open file adj.txt";
	    exit(1);   // call system to stop
	}

	
	
	string line;
	//istringstream iss(myText);
	getline(fp, line);
	N = stoi(line);
	if(N%2 != 0)
	{
		cout<<"Graph contains odd no. of vertices";
		return 0;
	}
	n = N/2;
	vector< vector<int> > adjList(N);

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
	 //    	cout << *it << '\n';
		// 	string z=*it;
		// 	t2= stoi(z);
	 //    }


		char_separator<char> sep(": ,");
	    tokenizer< char_separator<char> > tokens(line, sep);
	    int flag=0;
	    int t2;
	    BOOST_FOREACH ( const string &t, tokens)
	    {
	    	if(flag==0)
	    	{
	    		t2= stoi(t);
	    		flag=1;
	    	}
	    	else
	    	{
	    		adjList[t2].push_back(stoi(t));
	    	}
	        cout << t << "." << endl;
	        
	    }

	}

	fp.close();

	cout<<"Adjacent List:"<<endl;
	vector< pair<int, int>> edgeSet;
	vector<int>  :: iterator it;
	for(i=0; i<adjList.size(); i++)
	{
		cout<<i<<" :";
		for(it= adjList[i].begin(); it!= adjList[i].end(); it++ )
		{
			cout<< *it<<" ";
			if(i<n)
			{
				pair<int, int> temp1;
				temp1.first = i;
				temp1.second = *it;
				edgeSet.push_back(temp1);
			}
			
		}	
		cout<<endl;
	}

	cout<<"edgeSet is:"<<endl;
	for(i=0; i<edgeSet.size(); i++)
	{
		cout<<edgeSet[i].first<<" "<< edgeSet[i].second<<endl;
	}
	
	
	//cout<<"No. of edges"<<noOfEdges(adjList)<<endl;
	
	//pmExist = checkPerfectMatching(adjList, n);
	//cout<< "pmExist:"<<pmExist<<endl;
	pmExist = true;
	if(pmExist == false)
	{
		cout<<"Graph doesn't contain perfect matching"<<endl;
	}
	else
	{
		int E;
		E = noOfEdges(adjList);
		cout<<"E value: "<< E <<endl;
		float c = 1/(float)E;
		cout<<"c value: "<< c <<endl;
		float product = (float)E;
		int qn = pow(n,3);

		for(int k=1; k<n; k++)
		{
			cout<<"c value: "<< c <<endl;
			if(c > (2*(float)qn) || c < 1/(2*(float)E) )
			{
				cout<<"halting1"<<endl;
				return 0;
			}
			else
			{
				vector <pair <int, int>> matching;
				int T = n*n*n*n;
				int K_SizeMatching_Count = 0;
				int Kplus1_SizeMatching_Count = 0;
				// for(int j=0; j<T; j++)
				// {
				// 	matching = MarkovChain(adjList, c, T);
				// 	if(matching.size() == k)
				// 	{
				// 		K_SizeMatching_Count++;
				// 	}
				// 	if(matching.size() == k+1)
				// 	{
				// 		Kplus1_SizeMatching_Count++;
				// 	}

				// }

				MarkovChain(adjList, c, T, &K_SizeMatching_Count, &Kplus1_SizeMatching_Count, E, k, edgeSet, n);
				
				float p_K = (float)K_SizeMatching_Count/ (float)T;
				float p_Kplus1 = (float)Kplus1_SizeMatching_Count/ (float)T;
				cout<<(float)K_SizeMatching_Count<<" "<<(float)Kplus1_SizeMatching_Count;
				if(p_K == 0 || p_Kplus1 == 0)
				{
					cout<<"halting2";
					cout<<"stage no."<<k;
					return 0;
				}
				else
				{
					c = (c*p_K)/p_Kplus1;
					product = product/c;
				}
			}
		}

		cout<<"approximated count of PM in given graph is "<< product<<endl;

		ofstream fp;
        fp.open("temp2.txt", ios::out | ios::ate | ios::app );
        if (!fp) 
        {
            cerr << "Unable to open file temp2.txt";
            exit(1);   // call system to stop
        }
        fp << product;
        fp<<"\n";
        fp.close();
	}

	cout<<"edgeSet is:"<<endl;
	for(i=0; i<edgeSet.size(); i++)
	{
		cout<<edgeSet[i].first<<" "<< edgeSet[i].second<<endl;
	}
	return 0;
}
