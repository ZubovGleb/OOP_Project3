#include "string.h"
#include <cstring>
#include <iostream>

void String::swap(String& right) noexcept
{
	std::swap(size, right.size);
	std::swap(capacity, right.capacity);
	std::swap(pointer, right.pointer);
}

String::String()
{
	size = 0;
	capacity = 0;
	pointer = nullptr;
}

String::String(const char* str)
{
	size = strlen(str);
	capacity = strlen(str);
	pointer = new char[capacity];
	for (int i = 0; i < capacity; i++)
	{
		pointer[i] = str[i];
	}
}

String::String(const String& str)
{
	size = str.size;
	capacity = str.capacity;
	pointer = new char[capacity];
	for (int i = 0; i < capacity; i++)
	{
		pointer[i] = str.pointer[i];
	}
}

String::String(String&& str) noexcept
{
	size = str.size;
	capacity = str.capacity;
	pointer = str.pointer;
	str.size = 0;
	str.capacity = 0;
	str.pointer = nullptr;
}

String::~String()
{
	if (pointer != nullptr)
	{
		delete[] pointer;
	}
}

String& String::operator=(const char* str)
{
	size = strlen(str);
	capacity = strlen(str);
	if (pointer != nullptr)
	{
		delete[] pointer;
	}
	pointer = new char[capacity];
	for (int i = 0; i < capacity; i++)
	{
		pointer[i] = str[i];
	}
	return *this;
}

String& String::operator=(String&& str) noexcept
{
	if (this != &str)
	{
		swap(str);
	}
	return *this;
}

char& String::operator[](std::size_t pos)
{
	if (pos >= 0 && pos <= size - 1)
	{
		return pointer[pos];
	}
	throw std::exception();
}

String& String::insert(std::size_t pos, const char* str)
{
	if (strlen(str) == 0)
	{
		return *this;
	}
	if (pointer == nullptr)
	{
		return *this;
	}
	if (pos > size - 1 || pos < 0)
	{
		return *this;
	}
	char* temp = new char[strlen(str) + size];
	if (capacity <= strlen(str) + size)
	{
		capacity = strlen(str) + size;
		size = capacity;
	}
	int k = 0;
	for (int i = 0; i < pos; i++)
	{
		temp[i] = pointer[k];
		k++;
	}
	for (int i = pos, j = 0; i < strlen(str) + pos; i++, j++)
	{
		temp[i] = str[j];
	}
	for (int i = pos + strlen(str); i < size; i++)
	{
		temp[i] = pointer[k];
		k++;
	}
	delete[] pointer;
	pointer = temp;
	return *this;
}

int String::compare(const String& str)
{
	size_t length = size < str.size ? size : str.size;
	for (int i = 0; i < length; i++)
	{
		if (pointer[i] == str.pointer[i])
		{
			continue;
		}
		if (pointer[i] < str.pointer[i])
		{
			return -1;
		}
		if (pointer[i] > str.pointer[i])
		{
			return 1;
		}
	}
	return 0;
}

size_t String::find(const char* s, size_t pos, size_t n) const
{
	for (int i = pos; i < strlen(this->pointer); i++) {
		for (int j = 0; j < n; j++) {
			if (this->pointer[i + j] != s[j]) 
			{
				break;
			}
			if (j + 1 == n) 
			{
				return i;
			}
		}
	}
	return -1;
}

String String::substr(size_t pos, size_t len) const
{
	if (pos >= this->size)
	{
		return nullptr;
	}
	len = len + pos <= this->size ? len : this->size - pos;
	String out((char*)malloc(len));

	for (int i = 0; i < len; i++) {
		out.pointer[i] = this->pointer[pos + i];
	}

	return out;
}

bool String::startsWith(const char* s, size_t n)
{
	for (int i = 0; i < n; i++) {
		if (this->pointer[i] != s[i]) 
		{
			return false;
		}
	}
	return true;
}

bool String::operator< (String& str)
{
	for (int i = 0; i < std::min(this->size, str.size); i++) {
		char cleft = this->pointer[i];
		char cright = str.pointer[i];
		if (cleft == cright)
		{
			continue;
		}
		return cleft < cright;
	}
	return this->size < str.size;
}

std::ostream& operator<< (std::ostream& out, String const& str)
{
	for (int i = 0; i < str.size; i++) {
		out << str.pointer[i];
	}
	return out;
}
