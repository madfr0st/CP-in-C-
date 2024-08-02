#include <bits/stdc++.h>

using namespace std;

int main() {
   
	int t;
	cin >> t;
	while(t-->0){
		int n,x,y;

		cin >> n >> x >> y;

		//cout << n<<x<<y;

		vector<int> ans;

		for(int i=0;i<n;i++){
			if(i==x){
				ans.push_back(-1);
			}
			else if(i==(y-2)){
				ans.push_back(-1);
			}
			else{
				ans.push_back(1);
			}
		}

		for(int i=0;i<n;i++){
			cout << ans[i] <<+" ";
		}

		cout << "\n";

	}


    return 0;
}
