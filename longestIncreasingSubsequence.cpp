class Solution
{
    public:
    int solve(int n, int a[], int curr, int prev, vector<vector<int> > &dp) {
        //base case
        if(curr == n )
            return 0;
            
        if(dp[curr][prev+1] != -1)
            return dp[curr][prev+1];
            
        //include wala case
        int incl = 0;
        if(prev == -1 || a[curr] > a[prev])
            incl = 1 + solve(n, a, curr + 1, curr, dp);
        
        //exclude wala case
        int excl = solve(n, a, curr + 1, prev, dp);
        
        dp[curr][prev+1] = max(incl, excl);
        return dp[curr][prev+1];
    }
    
    int solveTab(int a[], int n) {
        vector<vector<int> > dp(n+1, vector<int> (n+1, 0));
        
        for(int curr = n-1; curr >= 0; curr--) {
            
            for(int prev = curr-1; prev >= -1; prev--) {
                
                int incl = 0;
                
                if(prev == -1 || a[curr] > a[prev])
                    incl = 1 + dp[curr+1][curr+1];
                
                //exclude wala case
                int excl = dp[curr+1][prev+1];
                
                dp[curr][prev+1] = max(incl, excl);
            }
        }
        return dp[0][0];
    }
    
    int solveFast(int a[], int n) {
        
        vector<int> abhi(n+1, 0);
        vector<int> next(n+1, 0);
        
        for(int curr = n-1; curr >= 0; curr--) {
            
            for(int prev = curr-1; prev >= -1; prev--) {
                
                int incl = 0;
                
                if(prev == -1 || a[curr] > a[prev])
                    incl = 1 + next[curr+1];
                
                //exclude wala case
                int excl = next[prev+1];
                
                abhi[prev+1] = max(incl, excl);
            }
            next = abhi;
        }
        
        return next[0];
    }
    
    int solveOptimal(int a[], int n) {
        
        if(n == 0)
            return 0;
        
        vector<int> ans;
        ans.push_back(a[0]);
        
        for(int i = 1; i < n; i++) {
            if(a[i] > ans.back())
                ans.push_back(a[i]);
            else {
                int index = lower_bound(ans.begin(), ans.end(), a[i]) - ans.begin();
                ans[index] = a[i];
            }
        }
        return ans.size();
    }
    //Function to find length of longest increasing subsequence.
    int longestSubsequence(int n, int a[])
    {
        // vector<vector<int> > dp(n, vector<int> (n+1, -1));
        // return solve(n, a, 0, -1, dp);
        
        return solveOptimal(a, n);
    }
};