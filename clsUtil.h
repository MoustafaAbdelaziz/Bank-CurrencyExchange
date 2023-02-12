#pragma once
#include <string>
#include <iostream>
#include "clsDate.h"
class clsUtil
{
public:
    enum enCharType { SamallLetter = 1, CapitalLetter = 2, Digit = 3, SpecialCharacter = 4, MixChars = 5};
        
    static void  Srand()
    {
        //Seeds the random number generator in C++, called only once
        srand((unsigned)time(NULL));
    }

    template <typename T>
    static T RandomNumber(T From, T To)
    {
        T randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    static char GetRandomCharacter(enCharType CharType)
    {
        //updated this method to accept mixchars
        if (CharType == MixChars)
        {
            CharType = (enCharType)RandomNumber<short>(1, 4);
        }

        switch (CharType)
        {
            case enCharType::SamallLetter:
            {
                return char(RandomNumber<short>(97, 122));
                break;
            }
            case enCharType::CapitalLetter:
            {
                return char(RandomNumber<short>(65, 90));
                break;
            }
            case enCharType::SpecialCharacter:
            {
                return char(RandomNumber<short>(33, 43));
                break;
            }
            case enCharType::Digit:
            {
                return char(RandomNumber<short>(48, 57));
                break;
            }
        default:
            {
                return char(RandomNumber<short>(65, 90));
                break;
            }
        }
    }

    static string GenerateWord(short Length, enCharType CharType = MixChars)
    {
        string Word;

        for (int i = 1; i <= Length; i++)
            Word = Word + GetRandomCharacter(CharType);
        return Word;
    }

    static string  GenerateKey(enCharType CharType = MixChars)
    {
        string Key = "";

        Key = GenerateWord(4, CharType) + "-";
        Key = Key + GenerateWord(4, CharType) + "-";
        Key = Key + GenerateWord(4, CharType) + "-";
        Key = Key + GenerateWord(4, CharType);

        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharType = MixChars)
    {
        for (int i = 1; i <= NumberOfKeys; i++)

        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }
    }

    static void FillArrayWithRandomNumbersInRange(vector <int> &Vector, int From, int To, int Number)
    {
        for (int i = 0; i < Number; i++)
            Vector.push_back(RandomNumber(From, To));
    }

    static void FillArrayWithRandomWords(vector <string> &Vector, short NumberOfWords, short Wordlength, enCharType CharType = MixChars)
    {
        for (int i = 0; i < NumberOfWords; i++)
            Vector.push_back( GenerateWord(Wordlength, CharType));
    }

    static void FillArrayWithRandomKeys(vector <string>& Vector, int NumberOfKeys, enCharType CharType = MixChars)
    {
        for (int i = 0; i < NumberOfKeys; i++)
            Vector.push_back( GenerateKey(CharType));
    }

    template <typename T>
    static  void Swap(T& A, T& B)
    {
        T Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    template <typename T>
    static void ShuffleArray(T arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
    }

    static string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }

    static string EncryptText(string Text, short EncryptionKey = 3)
    {
        for (int i = 0; i <= Text.length(); i++)
            Text[i] = char((int)Text[i] + EncryptionKey);
        return Text;
    }
    static string DecryptText(string Text, short EncryptionKey = 3)
    {
        for (int i = 0; i <= Text.length(); i++)
            Text[i] = char((int)Text[i] - EncryptionKey);
        return Text;
    }

    template <typename T>
    static void PrintArrElements(vector <T> V)
    {
        for (T Element : V)
        {
            cout << Element << " " << endl;
        }
        cout << endl;
    }

    static string NumberToText(long Number)
    {
        if (Number >= 0 && Number <= 19)
        {
            string Arr[] = { "", "One", "Two", "Three" , "Four", "Five", "Six", "Seven",
                            "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                             "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Ninteen" };
            return Arr[Number] + " ";
        }
        if (Number >= 20 && Number <= 99)
        {
            string Arr[] = { "", "", "Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
            return Arr[Number / 10] + " " + NumberToText(Number % 10);
        }
        if (Number >= 100 && Number <= 999)
            return NumberToText(Number / 100) + "Hundred " + NumberToText(Number % 100);
        if (Number >= 1000 && Number <= 999999)
            return NumberToText(Number / 1000) + "Thousand " + NumberToText(Number % 1000);
        if (Number >= 1000000 && Number <= 999999999)
            return NumberToText(Number / 1000000) + "Million " + NumberToText(Number % 1000000);
        if (Number >= 1000000000 && Number <= 9999999999)
            return NumberToText(Number / 1000000000) + "Billion " + NumberToText(Number % 1000000000);
        else {
            cout << "this number is very long";
        }
        return "";
    }
};