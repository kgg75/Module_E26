#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

using namespace std;

const int  N = 20;
const int  M = 4;
const int arr[N] = {5, 3, 2, 4, 8, 9, 6, 1, 1, 7, 9, 3, 8, 2, 6, 3, 5, 5, 4, 7};


int sum(int start, int& result) {
	for (auto i = start; i < start + N / M; i++) {
		cout << i << '\t' << arr[i] << '\t' << result << endl;
		result += arr[i];
	}
	return result;
}

int main() {
	vector <thread> th;

	auto size = N / M;
	int result = 0;

	for (auto i = 0; i < N; i += size) {
		th.push_back(thread(
			[i, size, &result]
			()
			{
				for (auto j = i; j < i + size; j++) {
					cout << i << '\t' << arr[j] << '\t' << result << endl;
					result += arr[j];
				}
			}
		));	// i, ref(result)));
	}

	for_each(th.begin(), th.end(), [](std::thread& it) { if (it.joinable())	it.join(); } );

	cout << result << endl;

	return 0;
}