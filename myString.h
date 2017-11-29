#ifndef __MYSTRING_H__
#define __MYSTRING_H__

#include <iostream>
using namespace std;

class myString
{
public:
	myString();
	myString(const char* s);
	myString(const myString& s);
	~myString();

	myString operator+ (const myString& s);
	myString& operator= (const myString& s);
	myString& operator+= (const myString& s);
	bool operator== (const myString& s);
	bool operator!= (const myString& s);
	bool operator< (const myString& s);
	bool operator> (const myString& s);
	bool operator<= (const myString& s);
	bool operator>= (const myString& s);

	const char& operator[] (int index);
	const char& at(int index);
	int length_method();
	const char* c_str();
	myString substr(int position, int split_length);
	bool empty();
	void insert(int position, myString insert_str);
	void remove(int position, int delete_length);

	int find(myString s);
	int find(myString s, int position);
	int find_first_of(myString s, int position);
	int find_first_not_of(myString s, int position);

	friend ostream& operator<< (ostream& os, const myString& s);
	friend istream& operator>> (istream& is, myString& s);

private:
	int length;
	char* cStr;
};

#endif