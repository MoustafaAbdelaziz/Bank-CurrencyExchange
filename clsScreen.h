#pragma once
#include <iostream>
#include <iomanip>
#include "clsDate.h"
#include "Global.h"
using namespace std;
class clsScreen
{
protected:
	static void _DrawScreenHeader(string Title, string SubTitle = "") {
        cout << setw(37) << "" << "__________________________________";
        cout << "\n\n\t\t\t\t\t   " << Title;
        if (SubTitle != "" || CurrentUser.UserName != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
            cout << "\n\t\t\t\t     " << "User: " << CurrentUser.UserName;
            cout << "\t" << "Date: " << clsDate::DateToString(clsDate());
        }
        cout << "\n" << setw(37) << "" << "__________________________________";

    }
};

