#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <chrono>


using namespace std;


const int  N = 100'000;
const int  M = 1;	// число потоков
// = { 5, 3, 2, 4, 8, 9, 6, 1, 1, 7, 9, 3, 8, 2, 6, 3, 5, 5, 4, 7 };


/*int sum(int start, int& result) {
	for (auto i = start; i < start + N / M; i++) {
		cout << i << '\t' << arr[i] << '\t' << result << endl;
		result += arr[i];
	}
	return result;
}*/

int main() {
	srand(time(NULL));

	int arr[N];
	for (auto i = 0; i < N; i++)
		arr[i] = rand() % 10;

	auto size = N / M;
	int result = 0;

	vector <thread> th;

	auto begin_time = chrono::high_resolution_clock::now();

	for (auto i = 0; i < N; i += size) {
		th.push_back(thread(
			[i, size, arr, &result]
			()
			{
				for (auto j = i; j < i + size; j++) {
					//cout << j << '\t' << arr[j] << '\t' << result << endl;
					result += arr[j];
				}
			}
		));	// i, ref(result)));
	}

	for_each(th.begin(), th.end(), [](std::thread& it) { if (it.joinable())	it.join(); } );
	
	auto end_time = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = end_time - begin_time;

	cout << result << endl;
	cout << "Processing time (threads " << M << "): " << elapsed.count() << endl;

	return 0;
}