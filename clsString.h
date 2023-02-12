#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;
class clsString
{
	string _Value;

public:
	clsString()
	{
		_Value = "";
	}
	clsString(string Value)
	{
		_Value = Value;
	}

	clsString operator = (string Value)
	{
		this->Value = Value;
		return *this;

	}
	/*clsString operator >> (string Value)
	{
		this->Value = Value;
		return *this;
	}*/

	void SetValue(string Value)
	{
		_Value = Value;
	}
	string GetValue()
	{
		return _Value;
	}
	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static size_t Length(string S1)
	{
		return S1.length();
	};
	size_t Length()
	{
		return _Value.length();
	};
	
	static size_t CountWords(string str)
	{
		size_t pos = 0, Counter = 0;
		string word = "", delim = " ";
		while ((pos = str.find(delim)) != std::string::npos)
		{
			word = str.substr(0, pos);
			if (word != "")
			{
				Counter++;
			}
			str.erase(0, pos + delim.length());
		}
		if (str != "")
		{
			Counter++;
		}
		return Counter;
	}
	size_t CountWords()
	{
		return CountWords(_Value);
	}

	static void PrintFirstLetterFromWord(string MyString)
	{
		bool IsFirstLetter = true;
		for (short x = 0; x <= MyString.length(); x++)
		{
			if (MyString[x] != ' ' && IsFirstLetter)
			{
				cout << MyString[x] << endl;
			}
			IsFirstLetter = (MyString[x] == ' ' ? true : false);
		}
	}
	void PrintFirstLetterFromWord()
	{
		PrintFirstLetterFromWord(_Value);
	}

	string UpperFirstLetterFromEachWord(string MyString)
	{
		bool IsFirstLetter = true;
		for (short x = 0; x <= MyString.length(); x++)
		{
			if (MyString[x] != ' ' && IsFirstLetter)
			{
				MyString[x] = toupper(MyString[x]);
			}
			IsFirstLetter = (MyString[x] == ' ' ? true : false);
		}
		return MyString;
	}
	void UpperFirstLetterFromEachWord()
	{
		_Value = UpperFirstLetterFromEachWord(_Value);
	}

	static string LowerFirstLetterFromWord(string MyString)
	{
		bool IsFirstLetter = true;
		for (short x = 0; x <= MyString.length(); x++)
		{
			if (MyString[x] != ' ' && IsFirstLetter)
			{
				MyString[x] = tolower(MyString[x]);
			}
			IsFirstLetter = (MyString[x] == ' ' ? true : false);
		}
		return MyString;
	}
	void LowerFirstLetterFromWord()
	{
		_Value = LowerFirstLetterFromWord(_Value);
	}

	static string UpperString(string MyString)
	{
		for (short x = 0; x <= MyString.length(); x++)
		{
			MyString[x] = toupper(MyString[x]);
		}
		return MyString;
	}
	void UpperString()
	{
		_Value = UpperString(_Value);
	}

	static string LowerString(string MyString)
	{
		for (short x = 0; x <= MyString.length(); x++)
		{
			MyString[x] = tolower(MyString[x]);
		}
		return MyString;
	}
	void LowerString()
	{
		_Value = LowerString(_Value);
	}

	static char InvertLetterCase(char Letter)
	{
		return isupper(Letter) ? tolower(Letter) : toupper(Letter);
	}

	static string InvertAllLettersCase(string str)
	{
		for (int i = 0; i <= str.length(); i++)
			str[i] = InvertLetterCase(str[i]);
		return str;
	}
	void InvertAllLettersCase()
	{
		_Value = InvertAllLettersCase(_Value);
	}

	enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 2 };
	static size_t CountLetters(string str, enWhatToCount WhatToCount = enWhatToCount::All)
	{
		if (WhatToCount == enWhatToCount::All)
			return str.length();

		short CountLetter = 0;
		for (size_t i = 0; i <= str.length(); i++)
		{
			if (WhatToCount == enWhatToCount::CapitalLetters && isupper(str[i]))
				CountLetter++;

			if (WhatToCount == enWhatToCount::SmallLetters && islower(str[i]))
				CountLetter++;
		}
		return CountLetter;
	}
	size_t CountLetters(enWhatToCount cWhatToCount = enWhatToCount::All)
	{
		return CountLetters(_Value, cWhatToCount);
	}

	static int CountSpecificLetter(string str, char Letter, bool MatchCase = true)
	{
		short CountLetter = 0;
		for (short i = 0; i <= str.length(); i++)
		{
			if (MatchCase) {
				if (str[i] == Letter)
					CountLetter++;
			}
			else
			{
				if (tolower(str[i]) == tolower(Letter))
					CountLetter++;
			}
		}
		return CountLetter;
	}
	int CountSpecificLetter(char Letter, bool MatchCase = true)
	{
		return CountSpecificLetter(_Value, Letter, MatchCase);
	}

	static bool IsVowel(char L)
	{
		L = tolower(L);
		return (L == 'a' || L == 'e' || L == 'i' || L == 'o' || L == 'u');
	}

	static int CountVowels(string str)
	{
		int Counter = 0;
		for (short i = 0; i < str.length(); i++)
		{
			if (IsVowel(str[i]))
				Counter++;
		}
		return Counter;
	}
	int CountVowels()
	{
		return CountVowels(_Value);
	}

	static void PrintVowels(string str)
	{
		for (short i = 0; i < str.length(); i++)
		{
			if (IsVowel(str[i]))
				cout << str[i] << "\t";
		}
	}
	void PrintVowels()
	{
		PrintVowels(_Value);
	}

	static vector <string> Split(string str, string delim = " ")
	{
		vector <string> vString;
		size_t pos = 0;
		string word = "";
		while ((pos = str.find(delim)) != str.npos) {
			word = str.substr(0, pos);
			//if (word != "") {
			vString.push_back(word);
			//}
			str.erase(0, pos + delim.length());
		}
		if (str != "") {
			vString.push_back(str);
		}
		return vString;
	}
	vector <string> Split(string delim = " ")
	{
		return Split(_Value, delim);
	}

	static void PrintEachWordInString(string str)
	{
		size_t pos = 0;
		string word = "", delim = " ";
		while ((pos = str.find(delim)) != std::string::npos)
		{
			word = str.substr(0, pos);
			if (word != "")
			{
				cout << word << endl;
			}

			str.erase(0, pos + delim.length());
		}
		if (str != "")
			cout << str << endl;
	}
	void PrintEachWordInString()
	{
		PrintEachWordInString(_Value);
	}

	static string LeftTrim(string str)
	{
		for (size_t i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ')
				return str.substr(i, str.length() - i);
		}
		return "";
	}
	void LeftTrim()
	{
		_Value = LeftTrim(_Value);
	}

	static string RightTrim(string str)
	{
		for (short i = (str.length() - 1); i >= 0; i--)
		{
			if (str[i] != ' ')
				return str.substr(0, i + 1);
		}
		return "";
	}
	void RightTrim() {
		_Value = RightTrim(_Value);
	}

	static string Trim(string str) {
		return LeftTrim(RightTrim(str));
	}
	void Trim() {
		_Value = Trim(_Value);
	}

	static string JoinString(vector<string> vString, string Delim)
	{

		string S1 = "";

		for (string& s : vString)
		{
			S1 = S1 + s + Delim;
		}

		return S1.substr(0, S1.length() - Delim.length());


	}

	static string JoinString(string arrString[], short Length, string Delim)
	{

		string S1 = "";

		for (short i = 0; i < Length; i++)
		{
			S1 = S1 + arrString[i] + Delim;
		}

		return S1.substr(0, S1.length() - Delim.length());

	}

	static string ReverseWordInString(string S, string Delim = " ")
	{
		string st = "";
		vector <string> str = Split(S, Delim);

		vector <string>::iterator iter = str.end();
		while (iter != str.begin())
		{
			--iter;
			st += *iter + " ";
		}
		return st;
	}
	string ReverseWordInString(string Delim = " ")
	{
		return ReverseWordInString(_Value, Delim);
	}

	static string ReplaceWord(string S, string stringToReplace, string ReplaceTo)
	{
		size_t pos = S.find(stringToReplace);
		while (pos != S.npos)
		{
			S = S.replace(pos, stringToReplace.length(), ReplaceTo);
			pos = S.find(stringToReplace);
		}
		return S;
	}
	string ReplaceWord(string stringToReplace, string ReplaceTo) {
		return ReplaceWord(_Value, stringToReplace, ReplaceTo);
	}

	static string RemoveeAllPunct(string str)
	{
		string s = "";
		for (short i = 0; i < str.length(); i++)
		{
			if (!ispunct(str[i]))
			{
				s += str[i];
			}
		}
		return s;
	}
	void RemoveeAllPunct() {
		_Value = RemoveeAllPunct(_Value);
	}
};

