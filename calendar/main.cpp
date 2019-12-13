#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;

int kDay = 1, kMonth = 1, kYear = 1980, kWeekDay = 2;

bool CheckIfYearIsLeap (int year) {
    bool year_is_leap;

    if (year % 400 == 0) {
        year_is_leap = true;
    } else if (year % 100 == 0) {
        year_is_leap = false;
    } else  {
        year_is_leap = year % 4 == 0;
    }

    return year_is_leap;
}

int GetCountOfDaysInYear (int year) {
    int count_of_days;

    if (CheckIfYearIsLeap(year)) {
        count_of_days = 366;
    } else {
        count_of_days = 365;
    }

    return count_of_days;
}

int GetCountOfDaysInMonth (int month, int year) {
    int count_of_days;

    if (month == 2) {
        if (CheckIfYearIsLeap(year)) {
            count_of_days = 29;
        } else {
            count_of_days = 28;
        }
    } else if (month <= 7 ) {
        count_of_days = 30 + month % 2;
    } else {
        count_of_days = 31 - month % 2;
    }

    return count_of_days;
}

int GetCountOfDaysSinceFirstJanuary (int day, int month, int year) {
    int count_of_days = 0;

    for (int number_of_month = 1; number_of_month < month; ++number_of_month) {
        count_of_days += GetCountOfDaysInMonth(number_of_month, year);
    }
    count_of_days += day - 1;

    return count_of_days;
}

int GetCountOfDaysSinceFirstJanuaryFirstYear (int day, int month, int year) {
    int count_of_days = 0;

    for (int number_of_year = 1; number_of_year < year; ++number_of_year) {
        count_of_days += GetCountOfDaysInYear(number_of_year);
    }
    count_of_days += GetCountOfDaysSinceFirstJanuary(day, month, year);

    return count_of_days;
}

int GetCountOfDaysBetweenTwoDates (int day_first, int month_first, int year_first,
                                   int day_second, int month_second, int year_second) {
    int count_of_days;

    count_of_days = abs(GetCountOfDaysSinceFirstJanuaryFirstYear(day_first, month_first, year_first)
                        - GetCountOfDaysSinceFirstJanuaryFirstYear(day_second, month_second, year_second));

    return count_of_days;
}

int GetDayOfWeek (int day_first, int month_first, int year_first, int number_of_day_first,
                  int day_second, int month_second, int year_second) {
    int number_of_day_second;
    number_of_day_second = (number_of_day_first + GetCountOfDaysBetweenTwoDates(day_first, month_first, year_first,
                                                                               day_second, month_second, year_second) - 1) % 7 + 1;

    return number_of_day_second;
}

string DrawStringOfMonths (int first_month, int last_month) {
    string line , kListOfMonths[12] = {
            "January ", "February", "March ", "April ", "May ", "June",
            "Jule", "August", "September ", "October ", "November", "December"
    };

    for (int month_number = first_month - 1; month_number < last_month - 1; ++month_number) {
        int length = kListOfMonths[month_number].size();
        string indent ((21 - length) / 2, ' ');
        line.append(indent).append(kListOfMonths[month_number]).append(indent).append(" | ");
    }
    string indent ((21 - kListOfMonths[last_month - 1].size()) / 2, ' ');
    line.append(indent).append(kListOfMonths[last_month - 1]).append(indent);
    line += "\n";
    return line;
}

string DrawDaysOfWeek (int count_of_rows) {
    string line;
    for (int i = 1; i < count_of_rows; ++i) {
        line.append("mo tu we th fr sa su").append(" | ");
    }
    line.append("mo tu we th fr sa su\n");
    return line;
}

void DrawSeparates () {
    string separate_line (66, '-');
    cout << separate_line << endl;
}

void DrawNumbers (int year, int first_month, int last_month) {
    int dates[3][42] = {};
    for (int number_of_month = first_month; number_of_month <= last_month; ++number_of_month) {
        int first_day_in_month = GetDayOfWeek(kDay, kMonth, kYear, kWeekDay, 1, number_of_month, year);
        int count_of_days_in_month = GetCountOfDaysInMonth(number_of_month, year);
        for (int i = first_day_in_month; i < count_of_days_in_month + first_day_in_month; ++i) {
            dates[(number_of_month - 1) % 3][i - 1] = i - first_day_in_month + 1;
        }
    }

    for (int number_of_string = 0; number_of_string < 6; ++number_of_string) {
        string line = "";
        for (int number_of_month = 0; number_of_month <= last_month - first_month; ++number_of_month) {
            for (int week_day = 0; week_day < 7; ++week_day) {
                int date = dates[number_of_month][week_day + number_of_string * 7];
                if (date == 0) {
                    line.append("   ");
                } else if (date <= 9) {
                    line.append(" ").append(to_string(date).append(" "));
                } else {
                    line.append(to_string(date).append(" "));
                }
            }
            if (number_of_month != last_month - first_month) {
                line.append("| ");
            }
        }
        cout << line << endl;
    }
}

void DisplayCalendar (int year) {
    string indent (31, ' ');
    cout << indent << year << indent << endl;
    DrawSeparates();
    for (int i = 0; i < 4; ++i) {
        cout << DrawStringOfMonths(i * 3 + 1, i * 3 +3);
        cout << DrawDaysOfWeek(3);
        DrawNumbers(year, i * 3 + 1, i * 3 +3);
        if (i != 3) {
            DrawSeparates();
        }
    }
}

int main(){
    DisplayCalendar(2019);
    return 0;
}
