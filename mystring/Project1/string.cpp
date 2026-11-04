#define _CRT_SECURE_NO_WARNINGS
#include"string.h"
namespace mystring {
	string::string()
		:_size(0)
		,_str(new char[4])
		,_capacity(3)
	{
		_str[0] = '\0';
	}
	string::string(const char* str)
		:_size(strlen(str))
	{
		_str = new char[_size+1];
		strcpy(_str, str);
		_capacity = _size;
	}
	//拷贝构造(深拷贝)
	string::string(const string& s){
		string tmp(s.c_str());
		swap(tmp);
	}
	//string& string::operator=(const string& s) {
	//	if (_str != s.c_str()) {
	//		delete[] _str;
	//		_str = new char[s._capacity + 1];
	//		strcpy(_str, s._str);
	//		_capacity = s._capacity;
	//		_size = s._size;
	//	}
	//	return *this;
	//}
	string& string::operator=(string tmp) {
		swap(tmp);
		return *this;
	}


	void string::push_back(char ch) {
		//扩容
		if (_size == _capacity) {
			reserve(_capacity > 0 ? _capacity * 2 : 2);
		}
		_str[_size] = ch;//aaaaaa\0
		_size++;
		_str[_size] = '\0';
	}

	void string::append(const char* str) {
		size_t len = strlen(str);
		if (len + _size > _capacity) {
			reserve(len + _size);
		}
		strcpy(_str + _size, str);
		_size += len;
		
	}

	void string::reserve(size_t n) {
		if (n > _capacity) {
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
			_capacity = n;
		}
	}
	void string::insert(size_t pos, char ch) {
		//扩容
		if (_size == _capacity) {
			reserve(_capacity > 0 ? _capacity * 2 : 2);
		}
		//在尾部插入
		if (pos == npos || pos > _size) {
			_str[_size] = ch;
			_size++;
		}
		//在中间插入
		for (size_t i = _size; i > pos; i--)
		{
			_str[i] = _str[i - 1];
		}
		_str[pos] = ch;
		_size++;
		_str[_size] = '\0';
	}
	void string::insert(size_t pos, const char* str) {
		size_t len = strlen(str);
		//扩容
		if (strlen(str) > (_capacity - _size)) {
			reserve(_size + len + 1);
		}
		//尾插
		if (pos == npos || pos > _size) {
			for (size_t i = _size-1; i < len; i++) {
				_str[pos + len + i] = str[pos+i];
			}
			_size += len;
			_str[_size] = '\0';
		}
		//从中间插or头插
		//挪数据
		for (size_t i = _size; i > pos; --i) {
			_str[i - 1 + len] = _str[i - 1];
		}

		for (size_t i = 0; i < len; i++) {
			_str[pos + i] = str[i];    // 不写 '\0'
		}
		_size += len;
		_str[_size] = '\0';

	}
	string& string::operator+=(char ch) {
		push_back(ch);
		return *this;
	}

	string& string::operator+=(const char* str) {
		append(str);
		return *this;
	}

	string operator+ (const string& lhs, const string& rhs) {
		string str(lhs);
		str += rhs.c_str();
		return str;
	}
	string operator+ (const string& lhs, const char* rhs) {
		string str(lhs);
		str += rhs;
		return str;
	}
	string operator+ (const char* lhs, const string& rhs) {
		string str(rhs);
		str += lhs;
		return str;
	}

	bool operator== (const string& lhs, const string& rhs)
	{
		return strcmp(lhs.c_str(), rhs.c_str()) == 0;
	}
	bool operator!= (const string& lhs, const string& rhs)
	{
		return !(lhs == rhs);
	}
	bool operator>(const string& lhs, const string& rhs) {
		return strcmp(lhs.c_str(), rhs.c_str()) > 0;
	}
	bool operator<(const string& lhs, const string& rhs) {
		return strcmp(lhs.c_str(), rhs.c_str()) < 0;
	}
	bool operator>= (const string& lhs, const string& rhs) {
		return !(lhs < rhs);
	}
	bool operator<= (const string& lhs, const string& rhs) {
		return !(lhs > rhs);
	}

	ostream& operator<<(ostream& out, const string& s) {
		out << s.c_str();
		return out;
	}
	istream& operator>>(istream& in, string& s) {
		s.erase();
		char ch;
		//in >> ch;
		char buff[128];
		int i = 0;
		ch = in.get();
		while (ch != ' ' && ch != '\n') {
			buff[i++] = ch;
			if (i == 127) {
				s += buff;
				i = 0;
			}
			ch = in.get();
		}
		if (i > 0) {
			s += buff;
		}
		return in;
	}
	istream& getline(istream& in, string& s) {
		char ch;
		//in >> ch;
		ch = in.get();
		while (ch != '\n') {
			s += ch;
			ch = in.get();
		}
		return in;
	}
	
	void string::erase(size_t pos, size_t len) {
		assert(pos <= _size);
		if (len >= _size - pos || pos == npos) {
			len = _size - pos;
		}
		for (size_t i = pos; i < _size-len; i++) 
		{
			_str[i] = _str[len + i];
		}
		_size -= len;
		_str[_size] = '\0';
	}
	size_t string::find(char ch, size_t pos) const {
		for (size_t i = pos; i < _size; i++)
		{
			if (_str[i] == ch)
				return i;
		}
		return -1;
	}
	size_t string::find(const char* str, size_t pos) const {
		char* ret = strstr(_str + pos, str);
		return ret - str;
	}
	string string::substr(size_t pos, size_t len) const {
		if (len > _size - pos) {
			len = _size - pos;
		}
		string sub;
		sub.reserve(len);
		for (size_t i = pos; i < len; i++)
		{
			sub += _str[pos];
		}
		return sub;

	}
	void string::swap(string& s) {
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);
	}
	string::~string() {
		_size = _capacity = 0;
		delete[] _str;
	}
}
void swap(mystring::string& s1, mystring::string& s2) {
	s1.swap(s2);
}