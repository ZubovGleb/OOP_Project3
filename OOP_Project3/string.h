#ifndef STRING
#define STRING

#include <cstddef>
#include <iostream>

class String {
private:
	std::size_t size;
	std::size_t capacity;
	char* pointer;
	void swap(String& right) noexcept;
public:
	String();
	String(const char* str);
	String(const String& str);
	String(String&& str) noexcept;
	~String();
	String& operator= (const char* str);
	String& operator= (String&& str) noexcept;
	char& operator[] (std::size_t pos);
	String& insert(std::size_t pos, const char* str);
	int compare(const String& str);

	size_t find(const char* s, size_t pos, size_t n) const;
	String substr(size_t pos, size_t len) const;

	bool startsWith(const char* s, size_t n);
	bool operator< (String& str);
	friend std::ostream& operator<< (std::ostream& out, String const& str);
};

#endif