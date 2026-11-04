#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

namespace mystring {
	class string {
	public:
		// 迭代器
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin() { return _str; }
		iterator end() { return _str + _size; }
		const_iterator begin() const { return _str; }
		const_iterator end() const { return _str + _size; }

		string();
		string(const char* str);
		string(const string& s);
		//string& operator=(const string& s);
		string& operator=(string tmp);
		~string();

		void reserve(size_t n);
		void push_back(char ch);
		void append(const char* str);
		string& operator+=(char ch);
		string& operator+=(const char* str);
		void insert(size_t pos, char ch);
		void insert(size_t pos, const char* str);
		void erase(size_t pos = 0, size_t len = string::npos);
		size_t find(char ch, size_t pos = 0) const;
		size_t find(const char* str, size_t pos = 0) const;
		string substr(size_t pos = 0, size_t len = npos) const;
		void swap(string& s);

		const char* c_str() const { return _str; }

		// 下标访问
		size_t size() const { return _size; }
		char& operator[](size_t pos) {
			assert(pos < _size);
			return _str[pos];
		}

		const char& operator[](size_t pos) const {
			assert(pos < _size);
			return _str[pos];
		}

	
		static const size_t npos = -1;

		// 其他类型不支持
		//static const double x = 1.1;

		//static const size_t N = 16;
	private:
		//char buffer[N];
		char* _str;
		size_t _size;
		size_t _capacity; // 存储有效字符的空间大小，不包含最后\0，也就是说实际空间比capacity要大1
	};
	///////////////////////////////////////////////////////////////////////////////////////////
	string operator+ (const string& lhs, const string& rhs);
	string operator+ (const string& lhs, const char* rhs);
	string operator+ (const char* lhs, const string& rhs);

	bool operator== (const string& lhs, const string& rhs);
	bool operator!= (const string& lhs, const string& rhs);
	bool operator>(const string& lhs, const string& rhs);
	bool operator<(const string& lhs, const string& rhs);
	bool operator>= (const string& lhs, const string& rhs);
	bool operator<= (const string& lhs, const string& rhs);
	ostream& operator<<(ostream& out, const string& s);
	istream& operator>>(istream& in, string& s);
	istream& getline(istream& in, string& s);
}
void swap(mystring::string& s1, mystring::string& s2);
