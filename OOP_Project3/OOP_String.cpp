#include <iostream>
#include "string.h"

void insertionSort(String** list, int size);

int main()
{
	int listSize = 0;
	try {
		std::cout << "Input the number of strings: ";
		std::cin >> listSize;
		if (!std::cin.good() || std::cin.peek() != '\n' || listSize < 0) {
			throw std::exception("The size of the array must be set as a natural number");
		}
	}
	catch (std::exception const& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}

	std::cout << "Input your strings: \n";
	char* buff = new char[1024];
	String** list = new String * [listSize];
	for (int i = 0; i < listSize; i++) {
		std::cin >> buff;
		list[i] = new String(buff);
	}

	insertionSort(list, listSize);
	std::cout << "Strings after sorting: \n";
	for (int i = 0; i < listSize; i++) {
		std::cout << *(list[i]) << '\n';
	}

	char symbolToSearch{};
	int count = 0;
	try {
		std::cout << "Input the symbol to search: ";
		std::cin >> symbolToSearch;
		if (!std::cin || std::cin.peek() != '\n') {
			throw std::exception("Only one symbol should be entered");
		}
	}
	catch (std::exception const& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 2;
	}
	String symbol(&symbolToSearch);
	for (int i = 0; i < listSize; i++) {
		if (list[i]->find(&symbolToSearch, 0, 1) != -1)
		{
			std::cout << "Symbol '" << symbolToSearch << "' finded in string: " << *list[i] << '\n';
			count++;
		}
	}
	if (count == 0)
	{
		std::cout << "This symbol was not found\n";
	}

	char* substring = new char[256];
	count = 0;
	std::cout << "Input the substring to search at the beginning of the string: ";
	std::cin >> substring;

	for (int i = 0; i < listSize; i++) {
		if (list[i]->startsWith(substring, strlen(substring)))
		{
			std::cout << "String: '" << *list[i] << "' starts with: " << substring << '\n';
			count++;
		}
	}
	if (count == 0)
	{
		std::cout << "This substring was not found\n";
	}

	delete[] list;
	return 0;
}

void insertionSort(String** list, int size) {
	for (int i = 0; i < size; i++) {
		String* temp = list[i];
		int j = i - 1;
		while (j >= 0 && *temp < *list[j]) {
			list[j + 1] = list[j];
			j--;
		}
		list[j + 1] = temp;
	}
}