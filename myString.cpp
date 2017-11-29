#include "myString.h"
#include <cstring>
#include <cstdlib>

myString::myString()
/*
*default constructor
*precondition : 아무 인자도 넣지 말아야 한다.
*postcondition : length는 0이고 cStr은 아무 것도 가리키지 않는다.
*/
{
	length = 0;
	cStr = NULL;
}

myString::myString(const char* s)
/*
*constructor
*precondition : 인자가 char형 포인터가 가리키는 값(문자열)으로 들어가야 한다.  
*postcondition : length는 널값을 포함한 길이, cStr는 인자로 받은 문자열을 가리킨다. 
*/
{
	length = strlen(s) + 1;
	cStr = new char[length];
	strcpy_s(cStr, length, s);
}

myString::myString(const myString& s)
/*
*copy constructor / deep copy
*precondition : 인자로 myString 클래스의 레퍼런스가 들어가야 한다.
*postcondition : 레퍼런스로 받은 myString 클래스의 length와 strcpy 
메소드를 이용하여 해당 문자열을 복사하고 cStr이 가리킨다.
*/
{
	length = s.length;
	cStr = new char[length];
	strcpy_s(cStr, length, s.cStr);
}

myString::~myString()
/*
*destructor
*precondition : 해당 객체가 소멸할 때 호출된다.
*postcondition : 힙 영역의 메모리를 반환하고 cStr이 아무 것도 가리키지 않는다.
*/
{
	if (cStr != NULL)
	{
		delete[] cStr;
		cStr = NULL;
	}
}

myString myString::operator+ (const myString& s)
/* 
*operator + //str1 + str2 
*precondition : + 연산자를 사용하였을 때 호출되며, const myString의 레퍼런스를 인자로 받는다.
//*postcondition : 두 문자열을 합한 새로운 객체를 반환한다.
*/
{
	int temp_length = length + s.length - 1;//기존의 length를 건드리면 안된다.
	char* temp = new char[temp_length];

	strcpy_s(temp, temp_length, cStr);
	strcat_s(temp, temp_length, s.cStr);
	myString obj(temp);//새로운 객체를 생성하여 반환

	delete[] temp;
	return obj;

}

myString& myString::operator= (const myString& s)
/*
*assignment operator = for deep copy / myString 뿐만 아니라 문자열도 가능 / chaining 기능이 있다.
*precondition : const myString의 레퍼런스를 인자로 받는다.
*postcondition : cStr이 어떠한 문자열을 가리킨다면 그 메모리를 반환해주고, 레퍼런스로 받은 
myString 클래스의 length와 strcpy 메소드를 이용하여 해당 문자열을 복사하고 cStr이 가리키고
현재 나 자신의 객체 레퍼런스를 반환한다.
*/
{												 
	if (cStr != NULL)
		delete[] cStr;

	length = s.length;
	cStr = new char[length];
	strcpy_s(cStr, length, s.cStr);

	return *this;//chaining 을 가능케 하기 위한 return
}

myString& myString::operator+= (const myString& s)
/*
*operator += / Append 기능  
*precondition : const myString의 레퍼런스를 인자로 받는다.
*postcondition : 레퍼런스로 받은 myString 클래스의 length를 자신 객체의 length에 더하고 
새로운 메모리에 현재 나 자신의 문자열과 인자로 받은 myString 클래스의 문자열을 append하여 
현재 나 자신의 객체 레퍼런스를 반환한다.
*/
{
	length += s.length - 1;
	char* temp = new char[length];

	strcpy_s(temp, length, cStr);
	strcat_s(temp, length, s.cStr);

	if (cStr != NULL)
		delete[] cStr;

	cStr = temp;

	return *this;
}

bool myString::operator== (const myString& s)
/*
*precondition : const myString의 레퍼런스를 인자로 받는다.
*postcondition : 0이 아닌 값이 나오면 false , 0이면 true를 리턴한다.
*/
{
	return strcmp(cStr, s.cStr) ? false : true;
}
bool myString::operator!= (const myString& s)
/*
*precondition : const myString의 레퍼런스를 인자로 받는다.
*postcondition : 0이 아닌 값이 나오면 true , 0이면 false를 리턴한다.
*/
{
	return strcmp(cStr, s.cStr) ? true : false;
}
bool myString::operator< (const myString& s)
/*
*precondition : const myString의 레퍼런스를 인자로 받는다.
*postcondition : -1이면 true , 아니면 false 리턴한다.
*/
{
	return strcmp(cStr, s.cStr) == -1 ? true : false;
}
bool myString::operator> (const myString& s)
/*
*precondition : const myString의 레퍼런스를 인자로 받는다.
*postcondition : 1이면 true , 아니면 false 리턴한다.
*/
{
	return strcmp(cStr, s.cStr) == 1 ? true : false;
}
bool myString::operator<= (const myString& s)
/*
*precondition : const myString의 레퍼런스를 인자로 받는다.
*postcondition : -1이거나 0이면 true 아니면 false 리턴한다.
*/
{
	return strcmp(cStr, s.cStr) == -1 || strcmp(cStr, s.cStr) == 0 ? true : false;
}
bool myString::operator>= (const myString& s)
/*
*precondition : const myString의 레퍼런스를 인자로 받는다.
*postcondition : 1이거나 0이면 true 아니면 false 리턴한다.
*/
{
	return strcmp(cStr, s.cStr) == 1 || strcmp(cStr, s.cStr) == 0 ? true : false;
}

const char& myString::operator[] (int index)
/*
*operator [] /return a reference to the element at index position
*precondition : 0에서 length -1 사이의 index를 인자로 받아야 원하는 값을 리턴한다.
*postcondition : 해당 인덱스 번째의 배열을 리턴한다.
*/
{
	if (index > length - 1 || index < 0)
	{
		cout << "out of range!!" << endl;
		exit(1);
	}
	return cStr[index];
}

const char& myString::at(int index)
/*
*return a reference to the element at index position
*precondition : 0에서 length -1 사이의 index를 인자로 받아야 원하는 값을 리턴한다.
*postcondition : 해당 인덱스 번째의 배열을 리턴한다.
*/
{
	if (index > length - 1 || index < 0 )
	{
		cout << "out of range!!" << endl;
		exit(1);
	}
	return cStr[index];
}

int myString::length_method()
/*
*length()
*precondition : X
*postcondition : '\0'이 들어가는 자리를 제외한 길이를 반환한다.
*/
{
	if (length == 0)
		return 0;

	return length - 1; //null을 제외한 길이 반환
}

const char* myString::c_str()
/*
*c_str() return a pointer to an array that contains a null-terminated sequence of charactters
*precondition : 이 반환값을 저장하는 변수가 포인터 변수여야한다.
*postcondition : 포인터 변수 cStr을 반환한다.
*/
{
	return cStr;
}

myString myString::substr(int position, int length)
/*
*substr return substring object
*precondition : position과 length가 myString 객체의 범위 내의 값이어야 한다.
*postcondition : 원하는 myString class의 복사본을 반환한다.
*/
{
	int split_length = length;
	char* temp = new char[split_length];

	for (int i = 0; i < split_length; i++)
	{
		temp[i] = cStr[position + i];
	}
	temp[split_length] = '\0';

	myString tempstr(temp);
	return tempstr;
}

bool myString::empty()
/*
*precondition : X
*postcondition : cStr의 가리킴 유무를 반환한다.
*/
{
	return (cStr == NULL) ? true : false;
}

void myString::insert(int position, myString insert_str)
/*
*precondition : += operator가 구현되어 있어야 한다.
*postcondition : 현재 자신의 객체에 원하는 문자열을 원하는 위치에 삽입한다.
*/
{
	myString temp = substr(position, length - position);
	*this = substr(0, position);
	*this += insert_str += temp;
}

void myString::remove(int position, int delete_length)
/*
*precondition : += operator와 substr 함수가 구현되어 있어야 한다.
*postcondition : 현재 자신의 객체에 원하는 문자열을 원하는 위치에서 삭제한다.
*/
{
	myString temp = substr(position + delete_length, length - (position + delete_length));
	*this = substr(0, position);
	*this += temp;
}

int myString::find(myString s)
/*
*precondition : 문자열을 인자로 받아야 한다.
*postcondition : 원하는 문자열이 있는지 찾아서 해당 번째의 인덱스를 반환한다.
*/
{
	int sum = 0;

	for (int i = 0; i < length_method(); i++)
	{
		if (cStr[i] == s[0])
		{
			for (int j = 1; j < s.length_method(); j++)
			{
				if (cStr[i + j] == s[j])
					sum++;
				else
				{
					sum = 0;
					break;
				}
			}
			if (sum == s.length_method() - 1)
				return i;
		}
	}
	return -1;
}
int myString::find(myString s, int position)
/*
*precondition : 문자열과 범위를 벗어나지 않는 위치를 인자로 받아야 한다.
*postcondition : 원하는 문자열이 있는지 찾아서 해당 번째의 인덱스를 반환한다.
*/
{
	int sum = 0;

	for (int i = position; i < length_method(); i++)
	{
		if (cStr[i] == s[0])
		{
			for (int j = 1; j < s.length_method(); j++)
			{
				if (cStr[i + j] == s[j])
					sum++;
				else
				{
					sum = 0;
					break;
				}
			}
			if (sum == s.length_method() - 1)
				return i;
		}
	}
	return -1;
}

int myString::find_first_of(myString s, int position)
/*
*precondition : 문자열과 범위를 벗어나지 않는 위치를 인자로 받아야 한다.
*postcondition : 원하는 문자열이 있는지 찾아서 해당 번째의 인덱스를 반환한다.
*/
{
	for (int i = position; i < length_method(); i++)
	{
		for (int j = 0; j < s.length_method(); j++)
			if (cStr[i] == s[j])
				return i;
	}
	return -1;
}

int myString::find_first_not_of(myString s, int position)
/*
*precondition : 문자열과 범위를 벗어나지 않는 위치를 인자로 받아야 한다.
*postcondition : 원하는 문자열이 있는지 찾아서 해당 번째의 인덱스를 반환한다.
*/
{
	int sum = 0;
	for (int i = position; i < length_method(); i++)
	{
		for (int j = 0; j < s.length_method(); j++)
			if (cStr[i] == s[j])
				sum++;
		if (sum == 0)
			return i;
		else
			sum = 0;
	}
	return -1;
}

ostream& operator<< (ostream& os, const myString& s)
/*
*precondition : ostream 레퍼런스 객체와 const myString 레퍼런스 객체를 인자로 받는다.
*postcondition : ostream 레퍼런스 객체를 반환한다.
*/
{
	os << s.cStr;
	return os;
}

istream& operator>> (istream& is, myString& s)
/*
*precondition : istream 레퍼런스 객체와 const myString 레퍼런스 객체를 인자로 받는다.
*postcondition : istream 레퍼런스 객체를 반환한다.
*/
{
	char str[50];
	is >> str;
	s = myString(str);
	return is;
}