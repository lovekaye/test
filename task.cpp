/*
9 9
4 1 1 2 2 3 2 7 5 6 7 6 1 5 8 5 8 9
5 4
2 4 3 5 2 3 1 2
20 19
9 2 10 16 10 13 16 7 11 20 20 4 13 3 11 1 10 19 2 6 18 11 10 14 13 15 5 8 13 9 9 18 16 12 20 17 9 5
100 99
21 91 27 77 30 38 48 76 13 23 21 28 87 95 60 10 89 99 67 34 60 85 37 61 16 24 97 7 60 40 19 59 70 63 38 100 37 86 46 27 50 2 49 25 91 6 60 42 20 31 19 68 30 20 30 58 97 15 67 19 49 48 74 46 67 53 59 75 11 57 21 67 60 90 59 51 89 49 15 66 30 88 88 93 49 5 21 50 38 9 37 71 62 41 59 29 11 18 44 98 66 32 19 13 62 12 91 72 46 97 78 89 68 36 45 87 62 92 73 62 85 64 3 69 67 74 74 30 60 54 93 22 45 1 14 47 7 73 7 94 72 81 67 70 49 33 71 35 73 8 21 55 66 43 39 52 36 79 5 44 46 82 49 17 21 78 96 84 78 56 51 4 3 83 7 60 53 14 10 65 53 16 15 80 37 45 3 96 32 39 40 26 3 11 97 37 66 3

3 2
2 1 1 3
9 9
4 1 1 2 2 3 2 7 5 6 7 6 1 5 8 5 8 9
5 4
1 2 2 3 4 1 1 5

#1 2 1 3
#2 1 2 3 4
#3 1 2 3 4 5


8, 9, 4, 1, 5, 2, 3, 7, 6
4, 1, 2, 3, 8, 5, 7, 6, 9
*/


#include<iostream>

using namespace std;

int V, E;
int task[1001][1001];
int visited[1001] = { 0, };
int vCnt;

void dump(){
	for (int i = 0; i <= V; i++){
		for (int j = 0; j <= V; j++){
			cout << task[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool valid(int u, int v){		
	if (task[0][v] == 1) return true;    // 진입차수 1개 true	
	else {    // 진입차수 2개 이상일 때, 진입 정점들이 visited가 아니면 false
		for (int i = 1; i <= V; i++){   // 진출차수 0, 방문한 적 없는 정점
			if (u != v && task[i][v] == 1 && visited[i] == 0) {
				return false;
			}		
		}
		return true;
	}
}

void visit(int i){  // 출력, visited 표시, vCnt 카운트 증가
	cout << i << " ";
	visited[i] = 1;
	task[0][i]--;
	vCnt++;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("Day10_1sample_input.txt", "r", stdin);
	//T = 10;
	T = 2;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> V >> E;

		for (int i = 0; i <= V; i++){   // 0 은 진입, 진출 차수 count
			for (int j = 0; j <= V; j++){
				task[i][j] = 0;
			}
			visited[i] = 0;
		}

		for (int i = 1; i <= E; i++){
			int s, t;
			cin >> s >> t;
			task[s][t] = 1;
			task[s][t] = 1;
			task[0][t]++; // 진출차수 count 증가
			task[s][0]++;
		}
		dump();

		cout << "#" << test_case << " ";
		vCnt = 0;

		while (vCnt < V){  // V개 출력할 때까지

			for (int i = 1; i <= V; i++){   // 진출차수 0, 방문한 적 없는 정점
				if (vCnt == V) break;

				if (task[0][i] == 0 && visited[i] == 0) {
					visit(i);  // 출력, visited 표시, vCnt 카운트 증가

					// i로부터 따라감  진입차수 검색
					// 연결된 task가 없을 때, 다른 task와 종속관계일 때
					int u = i;
					bool going = true;
					while (going){
						if (vCnt == V) break;
						if (task[u][0] == 0) break; // 연결된 task가 없을 때

						//	while (going){
						for (int j = 1; j <= V; j++){ // 다음 task 검색 - 진출행
							if (u != j && task[u][j] == 1 && visited[j] != 1){
								if (valid(u, j)){ // 다른 task와 종속관계 여부와 가도 되는지 체크									
									visit(j);
									u = j; // j에서 따라 들어감
									break;
								}
							}
							if (j == V) going = false;
						}
					}
					//task[0][i]--;
				}
				//else if (visited[i] == 0) visit(i);
				
			}
		}

		cout << endl;
	}
		return 0;//정상종료시 반드시 0을 리턴해야합니다.
	
}
