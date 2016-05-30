#include <iostream>
using namespace std;

#define ABS(a) (((a) < 0)? -(a) : (a))

int N;  // map 사이즈
int map[11][11] = { 0, };
int Dist[10][2];
int E1[2], E2[2];  // 비상구1, 2 좌표 r, c
int mCnt;
int temp[100] = { 0, };
int Min = 100000000;

void dump(){
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void dump_dist(){
	for (int i = 1; i <= mCnt; i++){
		cout << Dist[i][0] << ", " << Dist[i][1] << endl;
	}
	cout << endl;
}

void setDist(){
	int cnt = 0;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			if (map[i][j] == 1){
				cnt++;
				Dist[cnt][0] = ABS(E1[0] - i) + ABS(E1[1] - j);
				Dist[cnt][1] = ABS(E2[0] - i) + ABS(E2[1] - j);
			}
		}
	}
	dump_dist();
}

int calDist(int n){
	int time1 = 0, time2 = 0;
	int temp_cal1[100] = { 0, };
	int temp_cal2[100] = { 0, };

	for (int i = 0; i < n; i++){
		if (temp[i] == 0){    // E1인 경우
			int index0 = Dist[i + 1][0];
			while (true){
				if (temp_cal1[index0] == 0){
					temp_cal1[index0] = 1;
					if (time1 < index0) time1 = index0;
					break;
				}
				else index0++;
			}
		}
		else if (temp[i] == 1){    // E2인 경우
			int index1 = Dist[i + 1][1];
			while (true){
				if (temp_cal2[index1] == 0){
					temp_cal2[index1] = 1;
					if (time2 < index1) time2 = index1;
					break;
				}
				else index1++;
			}
		}
	}

	cout << time1 << " " << time2 << endl;

	if (time1 > time2) return time1;
	else return time2;
}

void comb(int n, int r){

	if (n == r){
		for (int i = 0; i < n; i++){
			cout << temp[i] << " ";
		}
		cout << endl;

		int tempDist = calDist(n);
		cout << tempDist << endl;
		if (tempDist < Min) Min = tempDist;		
	}
	else{
		for (int i = 0; i < 2; i++)	{ // M3
			temp[r] = i;
			comb(n, r + 1);
		}
	}
}

int main(){

	freopen("sample_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	int T;
	cin >> T;
	int test_case = T;

	while (T--){
		cin >> N;

		mCnt = 0;
		E1[0] = 0, E1[1] = 0, E2[0] = 0, E2[1] = 0;  // 비상구 좌표 초기화

		for (int i = 1; i <= N; i++){
			for (int j = 1; j <= N; j++){
				cin >> map[i][j];
				if (map[i][j] == 1){  // 사람 수 증가
					mCnt++;
				}
				else if (map[i][j] == 2){ // 비상구
					if (E1[0] == 0) {
						E1[0] = i;  // 비상구1의 r
						E1[1] = j;  // 비상구1의 c
					}
					else{
						E2[0] = i;  // 비상구1의 r
						E2[1] = j;  // 비상구1의 c
					}
				}
			}
		}
		dump();

		setDist(); // 비상구와 사람간 거리 table 셋팅

		Min = 100000000;
		comb(mCnt, 0);

		cout << endl;
		cout << "# " << test_case - T << " " << Min << endl;
	}
	return 0;
}
