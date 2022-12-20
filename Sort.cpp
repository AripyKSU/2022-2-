#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

#define SIZE 20000		//*******여기서 입력 값의 개수를 조정하세요.*******
enum SORT{INSERTION_SORT, SELECTION_SORT, BUBBLE_SORT, QUICK_SORT, HEAP_SORT, MERGE_SORT, RADIX_SORT};

void insertionSort(vector<string>& list, int len);
void selectionSort(vector<string>& list, int len);
void bubbleSort(vector<string>& list, int len);
void quickSort(vector<string>& list, int left, int right);
void heapSort(vector<string>& list, int len);
void changeParent(vector<string>& list, int len, int parentIndex);
void makeHeap(vector<string>& list, int len);
//void mergeSort(vector<string>& list, int len);
void radixSort();
void read(vector<string>& list);
void compare(vector<string> list1, vector<string> list2);

int main() {
	//시간 계산을 위한 clock() 호출
	clock_t startTime, endTime;
	startTime = clock();

	//데이터를 담을 list와 file stream
	vector<string> list;
	fstream fs;

	fs.open("Sorting algorithm sample.csv", ios::in);

	string tmp;
	
	//vector<string> compareList;						compare 전용

	getline(fs, tmp, '\n');
	for(int i = 0; i<SIZE; i++) {
		getline(fs, tmp, ',');
		getline(fs, tmp, '\n');
		list.push_back(tmp);
		//compareList.push_back(tmp);					compare 전용
	}
	//cout << "push 완료\n";							compare 전용
	//insertionSort(compareList, SIZE);					compare 전용
	//cout << "insertion 완료\n";						compare 전용
	switch (HEAP_SORT) {	//*******여기에 정렬 이름을 INSERTION_SORT와 같은 방식으로 입력하세요.*******
		case INSERTION_SORT: insertionSort(list, SIZE);
			break;
		case SELECTION_SORT: selectionSort(list, SIZE);
			break;
		case BUBBLE_SORT: bubbleSort(list, SIZE);
			break;
		case QUICK_SORT: quickSort(list, 0, SIZE);
			break;
		case HEAP_SORT: heapSort(list, SIZE);
			break;
		//case MERGE_SORT: mergeSort();
			break;
		case RADIX_SORT: radixSort();
			break;
	}
	//cout << "sort 완료\n";							compare 전용
	//compare(compareList, list);						compare 전용
	//read(list);

	fs.close();
	endTime = clock();
	cout << "소요된 시간 : " << endTime - startTime;
	return 0;
}

// 삽입 정렬
void insertionSort(vector<string>& list, int len) {
	int i, j;
	string tmp;

	for (i = 1; i < len; i++) {
		tmp = list[i];
		//뒤에서 부터 정렬된 배열과 비교
		for (j = i - 1; j >= 0 && list[j] > tmp; j--) {
			list[j + 1] = list[j];
		}

		list[j + 1] = tmp;
	}
	return;
}

//선택 정렬
void selectionSort(vector<string>& list, int len) {
	int i, j;
	string tmp;
	int minIndex;

	for (i = 0; i < len; i++) {
		minIndex = i;
		for (j = i + 1; j < len; j++) {
			if (list[j] < list[minIndex]) {
				minIndex = j;
			}
		}
		tmp = list[i];
		list[i] = list[minIndex];
		list[minIndex] = tmp;
	}
	return;
}

void bubbleSort(vector<string>& list, int len) {
	int i, j;
	string tmp;

	for (i = len - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (list[j] > list[j + 1]) {
				tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
		}
	}
	return;
}

void quickSort(vector<string>& list, int left, int right) {
	int pivot, sp, unknown;
	string tmp;

	if (left >= right) return; //재귀 함수 종결 조건
	sp = left;
	pivot = left;
	for (unknown = pivot + 1; unknown < right; unknown++) {
		if (list[unknown] < list[pivot]) {
			sp++;
			tmp = list[sp];
			list[sp] = list[unknown];
			list[unknown] = tmp;
		}
	}

	//최종 sp위치 값과 pivot값 교체
	tmp = list[pivot];
	list[pivot] = list[sp];
	list[sp] = tmp;

	//분할하여 재귀 실행
	quickSort(list, left, sp);
	quickSort(list, sp + 1, right);
	return;
}

void changeParent(vector<string>& list, int len, int parentIndex) {
	//양쪽 다 자식이 있을 경우
	string tmp;
	if (len > (parentIndex + 1) * 2) {
		int maxChildIndex = list[(parentIndex + 1) * 2 - 1] > list[(parentIndex + 1) * 2] ? (parentIndex + 1) * 2 - 1 : (parentIndex + 1) * 2;
		if (list[parentIndex] < list[maxChildIndex]) {
			tmp = list[maxChildIndex];
			list[maxChildIndex] = list[parentIndex];
			list[parentIndex] = tmp;
			//교환 후 재귀 호출
			changeParent(list, len, maxChildIndex);
		}
	}
	//한쪽만 자식이 있을 경우
	else if (len == (parentIndex + 1) * 2) {
		int childIndex = (parentIndex + 1) * 2 - 1;
		if (list[parentIndex] < list[childIndex]) {
			tmp = list[childIndex];
			list[childIndex] = list[parentIndex];
			list[parentIndex] = tmp;
		}
		return;
	}
	//재귀함수 종결 조건
	else return;
}

void makeHeap(vector<string>& list, int len) {
	int index;
	for (index = (len - 1) / 2; index >= 0; index--) {
		changeParent(list, len, index);
	}
	return;
}

void heapSort(vector<string>& list, int len) {
	makeHeap(list, len);
	for (int i = len - 1; i > 0; i--) {
		//root와 배열의 끝 교체
		string tmp;
		tmp = list[i];
		list[i] = list[0];
		list[0] = tmp;
		changeParent(list, i, 0);
	}
	return;
}

/*vector<vector<string>> divide() {

}

vector<string> merge(vector<string> &leftList, vector<string> &rightList) {
	int leftIndex = 0;
	int rightIndex = 0;
	vector<string> mergeList;
	string tmp;
	while (leftIndex < leftList.size() && rightIndex <= rightList.size()) {
		if (leftList[leftIndex] <= rightList[rightIndex]) {
			mergeList.push_back(leftList[leftIndex]);
			leftIndex++;
		}
		else {
			mergeList.push_back(rightList[rightIndex]);
			rightIndex++;
		}
	}

	//left가 먼저 다 채워질 경우(right가 남은 경우)
	if (leftIndex == leftList.size()) {
		while (rightIndex <= rightList.size()) {
			mergeList.push_back(rightList[rightIndex]);
			rightIndex++;
		}
	}
	//right가 먼저 다 채워질 경우(left가 남은 경우)
	else if (rightIndex == rightList.size()) {
		while (leftIndex <= leftList.size()) {
			mergeList.push_back(leftList[leftIndex]);
			leftIndex++;
		}
	}

	//메모리 해제
	leftList.clear();
	rightList.clear();
	return mergeList;
}

void mergeSort(vector<string>& list, int len) {
	//분할 과정

	//병합 과정
	merge(leftList, rightList);
}
*/
void radixSort() {

}

// 데이터 출력
void read(vector<string>& list) {
	for (int i = 0; i < list.size(); i++) {
		cout << list[i] << endl;
	}
}

void compare(vector<string> list1, vector<string> list2) {
	for (int i = 0; i < SIZE; i++) {
		if (list1[i] != list2[i]) {
			cout << "ERROR" << endl;
			return;
		}
	}
	cout << "OK" << endl;
}