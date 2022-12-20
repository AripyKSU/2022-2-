#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

#define SIZE 20000		//*******���⼭ �Է� ���� ������ �����ϼ���.*******
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
	//�ð� ����� ���� clock() ȣ��
	clock_t startTime, endTime;
	startTime = clock();

	//�����͸� ���� list�� file stream
	vector<string> list;
	fstream fs;

	fs.open("Sorting algorithm sample.csv", ios::in);

	string tmp;
	
	//vector<string> compareList;						compare ����

	getline(fs, tmp, '\n');
	for(int i = 0; i<SIZE; i++) {
		getline(fs, tmp, ',');
		getline(fs, tmp, '\n');
		list.push_back(tmp);
		//compareList.push_back(tmp);					compare ����
	}
	//cout << "push �Ϸ�\n";							compare ����
	//insertionSort(compareList, SIZE);					compare ����
	//cout << "insertion �Ϸ�\n";						compare ����
	switch (HEAP_SORT) {	//*******���⿡ ���� �̸��� INSERTION_SORT�� ���� ������� �Է��ϼ���.*******
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
	//cout << "sort �Ϸ�\n";							compare ����
	//compare(compareList, list);						compare ����
	//read(list);

	fs.close();
	endTime = clock();
	cout << "�ҿ�� �ð� : " << endTime - startTime;
	return 0;
}

// ���� ����
void insertionSort(vector<string>& list, int len) {
	int i, j;
	string tmp;

	for (i = 1; i < len; i++) {
		tmp = list[i];
		//�ڿ��� ���� ���ĵ� �迭�� ��
		for (j = i - 1; j >= 0 && list[j] > tmp; j--) {
			list[j + 1] = list[j];
		}

		list[j + 1] = tmp;
	}
	return;
}

//���� ����
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

	if (left >= right) return; //��� �Լ� ���� ����
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

	//���� sp��ġ ���� pivot�� ��ü
	tmp = list[pivot];
	list[pivot] = list[sp];
	list[sp] = tmp;

	//�����Ͽ� ��� ����
	quickSort(list, left, sp);
	quickSort(list, sp + 1, right);
	return;
}

void changeParent(vector<string>& list, int len, int parentIndex) {
	//���� �� �ڽ��� ���� ���
	string tmp;
	if (len > (parentIndex + 1) * 2) {
		int maxChildIndex = list[(parentIndex + 1) * 2 - 1] > list[(parentIndex + 1) * 2] ? (parentIndex + 1) * 2 - 1 : (parentIndex + 1) * 2;
		if (list[parentIndex] < list[maxChildIndex]) {
			tmp = list[maxChildIndex];
			list[maxChildIndex] = list[parentIndex];
			list[parentIndex] = tmp;
			//��ȯ �� ��� ȣ��
			changeParent(list, len, maxChildIndex);
		}
	}
	//���ʸ� �ڽ��� ���� ���
	else if (len == (parentIndex + 1) * 2) {
		int childIndex = (parentIndex + 1) * 2 - 1;
		if (list[parentIndex] < list[childIndex]) {
			tmp = list[childIndex];
			list[childIndex] = list[parentIndex];
			list[parentIndex] = tmp;
		}
		return;
	}
	//����Լ� ���� ����
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
		//root�� �迭�� �� ��ü
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

	//left�� ���� �� ä���� ���(right�� ���� ���)
	if (leftIndex == leftList.size()) {
		while (rightIndex <= rightList.size()) {
			mergeList.push_back(rightList[rightIndex]);
			rightIndex++;
		}
	}
	//right�� ���� �� ä���� ���(left�� ���� ���)
	else if (rightIndex == rightList.size()) {
		while (leftIndex <= leftList.size()) {
			mergeList.push_back(leftList[leftIndex]);
			leftIndex++;
		}
	}

	//�޸� ����
	leftList.clear();
	rightList.clear();
	return mergeList;
}

void mergeSort(vector<string>& list, int len) {
	//���� ����

	//���� ����
	merge(leftList, rightList);
}
*/
void radixSort() {

}

// ������ ���
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