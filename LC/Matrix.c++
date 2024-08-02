#include <bits/stdc++.h>

using namespace std;

int main(){

	int a[3][3]= {{1,2,3},{4,5,6},{1,2,3}};
	int b[3][3]= {{1,2,3},{4,5,6},{1,2,3}};

	int r[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout << a[i][j] << ", ";
		}
		cout << "\n";
	}

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout << b[i][j] << ", ";
		}
		cout << "\n";
	}


	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			int sum = 0;
			for(int k=0;k<3;k++){
				sum+= a[i][k]*b[k][j];
			}
			r[i][j] = sum;

		}
	}

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout << r[i][j] << ", ";
		}
		cout << "\n";
	}



	return 0;
}