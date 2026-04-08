// Copyright (c) 2025. All rights reserved.
#include "yesterdate.h"

#include <stdexcept>
#include <tuple>

namespace yesterdate {

    namespace {

        bool IsLeapYear(int year) {
            return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        }

        int DaysInMonth(int year, int month) {
            switch (month) {
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    return 31;
                case 4: case 6: case 9: case 11:
                    return 30;
                case 2:
                    return IsLeapYear(year) ? 29 : 28;
                default:
                    return 0;
            }
        }

        void ValidateDate(int year, int month, int day) {
            if (year < 1900 || year > 2050) {
                throw std::invalid_argument("Year out of range [1900, 2050]");
            }
            if (month < 1 || month > 12) {
                throw std::invalid_argument("Month out of range [1, 12]");
            }
            int max_day = DaysInMonth(year, month);
            if (day < 1 || day > max_day) {
                throw std::invalid_argument("Day out of range for given month/year");
            }
        }

    }  // namespace

    std::tuple<int, int, int> YesterDate(int year, int month, int day) {
        ValidateDate(year, month, day);

        if (day > 1) {
            return std::make_tuple(year, month, day - 1);
        }

        if (month > 1) {
            int prev_month = month - 1;
            int days_in_prev_month = DaysInMonth(year, prev_month);
            return std::make_tuple(year, prev_month, days_in_prev_month);
        }

        return std::make_tuple(year - 1, 12, 31);
    }

}  // namespace yesterdate
