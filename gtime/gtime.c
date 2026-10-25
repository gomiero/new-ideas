// -*- coding: utf-8-unix -*-
/*
 * Copyright 2025-present Alexandre Gomiero de Oliveira
 * SPDX-License-Identifier: Apache-2.0
 * See LICENSE in the repository root.
 *
 * Returns UNIX timestamps, dates, and related calendar information.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define VERSION "1.4.0"

#define SYNODIC_MONTH_DAYS 29.530588853
#define KNOWN_NEW_MOON_UNIX 947182440LL /* 2000-01-06 18:14:00 UTC */

static void print_moon_phase(time_t value)
{
        static const char *phase_names[] = {
                "New Moon",
                "Waxing Crescent",
                "First Quarter",
                "Waxing Gibbous",
                "Full Moon",
                "Waning Gibbous",
                "Last Quarter",
                "Waning Crescent"
        };
        double cycles;
        double fraction;
        double age_days;
        long long whole_cycles;
        int phase_index;

        cycles = ((double)((long long)value - KNOWN_NEW_MOON_UNIX) / 86400.0) /
                 SYNODIC_MONTH_DAYS;
        whole_cycles = (long long)cycles;
        if(cycles < 0.0 && (double)whole_cycles != cycles)
                --whole_cycles;

        fraction = cycles - (double)whole_cycles;
        age_days = fraction * SYNODIC_MONTH_DAYS;
        phase_index = (int)(fraction * 8.0 + 0.5) % 8;

        printf("moon phase (approx): %s (age %.2f days)\n",
               phase_names[phase_index], age_days);
}


static long long days_from_civil(int year, int month, int day)
{
        int era;
        unsigned yoe;
        unsigned doy;
        unsigned doe;
        int adjusted_year;

        adjusted_year = year - (month <= 2);
        era = (adjusted_year >= 0 ? adjusted_year : adjusted_year - 399) / 400;
        yoe = (unsigned)(adjusted_year - era * 400);
        doy = (unsigned)((153 * (month + (month > 2 ? -3 : 9)) + 2) / 5 +
                         day - 1);
        doe = yoe * 365U + yoe / 4U - yoe / 100U + doy;

        return (long long)era * 146097LL + (long long)doe - 719468LL;
}

static int third_friday_day(int year, int month)
{
        long long first_day;
        int weekday;
        int offset;

        first_day = days_from_civil(year, month, 1);
        weekday = (int)((first_day + 4LL) % 7LL); /* 1970-01-01 was Thursday */
        if(weekday < 0)
                weekday += 7;

        offset = (5 - weekday + 7) % 7; /* Sunday=0, Friday=5 */
        return 1 + offset + 14;
}

static void next_month(int *year, int *month)
{
        ++(*month);
        if(*month > 12) {
                *month = 1;
                ++(*year);
        }
}

static void print_option_expirations(time_t value)
{
        static const char call_codes[] = "ABCDEFGHIJKL";
        static const char put_codes[] = "MNOPQRSTUVWX";
        struct tm *tm_value;
        int year;
        int month;
        int day;
        int first_year;
        int first_month;
        int first_day;
        int second_year;
        int second_month;
        int second_day;
        long long today;
        long long first_date;
        long long second_date;
        long long first_diff;
        long long second_diff;

        tm_value = localtime(&value);
        if(tm_value == NULL)
                return;

        year = tm_value->tm_year + 1900;
        month = tm_value->tm_mon + 1;
        day = tm_value->tm_mday;
        today = days_from_civil(year, month, day);

        first_year = year;
        first_month = month;
        first_day = third_friday_day(first_year, first_month);
        first_date = days_from_civil(first_year, first_month, first_day);

        if(first_date < today) {
                next_month(&first_year, &first_month);
                first_day = third_friday_day(first_year, first_month);
                first_date = days_from_civil(first_year, first_month, first_day);
        }

        second_year = first_year;
        second_month = first_month;
        next_month(&second_year, &second_month);
        second_day = third_friday_day(second_year, second_month);
        second_date = days_from_civil(second_year, second_month, second_day);

        first_diff = first_date - today;
        second_diff = second_date - today;

        printf("options expiration: %lld days (%04d-%02d-%02d, CALL=%c, PUT=%c)\n",
               first_diff, first_year, first_month, first_day,
               call_codes[first_month - 1], put_codes[first_month - 1]);
        printf("following options expiration: %lld days (%04d-%02d-%02d, CALL=%c, PUT=%c)\n",
               second_diff, second_year, second_month, second_day,
               call_codes[second_month - 1], put_codes[second_month - 1]);
}

static int format_datetime(char *buff, size_t buff_size, time_t value, int utc)
{
        struct tm *tm_value;

        tm_value = utc ? gmtime(&value) : localtime(&value);
        if(tm_value == NULL)
                return 1;

        if(strftime(buff, buff_size, "%a %b %d %H:%M:%S %Y", tm_value) == 0)
                return 1;

        return 0;
}

static int parse_ll(const char *text, long long *value)
{
        char *endptr;

        errno = 0;
        endptr = NULL;
        *value = strtoll(text, &endptr, 10);

        if(errno != 0 || endptr == text || *endptr != '\0')
                return 1;

        return 0;
}

// banner & help
void print_help(char banner) {
        printf("\n\x1b[1;34mCopyright 2025-present Alexandre Gomiero de Oliveira\x1b[0m\n\n");
        printf("\x1b[1;32mLicensed under Apache 2.0\x1b[0m\n");
        printf("version: %s\n\n", VERSION);

        if(banner)
                return;

        printf("use:\n\n");

        printf("\t\x1b[1;33m* gtime [-utc] - for current UNIX time.\x1b[0m\n\n");
        printf("\x1b[1;90m> gtime\x1b[0m\n");
        printf("\x1b[1;90m> gtime -utc\x1b[0m\n\n");

        printf("\t\x1b[1;33m* gtime [UNIX time in milliseconds] [-utc] - for diff in days.\x1b[0m\n\n");
        printf("\x1b[1;90m> gtime 1738396543210\x1b[0m\n\n");

        printf("\t\x1b[1;33m* gtime -u [UNIX time in seconds] [-utc] - convert UNIX time to datetime.\x1b[0m\n\n");
        printf("\x1b[1;90m> gtime -u 1738392514\x1b[0m\n");
        printf("\x1b[1;90m> gtime -u 1738392514 -utc\x1b[0m\n\n");

        printf("-utc changes only the displayed datetime to UTC; UNIX input values are unchanged.\n");
        printf("moon phase is an approximate 8-phase result based on the mean synodic month.\n");
        printf("options expiration uses the local calendar, third Friday and B3 month codes (CALL A-L, PUT M-X).\n\n");
}

int main(int argc, char *argv[])
{
        struct timespec ts;
        time_t tt;
        long long tmsec;
        long long targ;
        char buff[250];
        int utc = 0;
        int unix_to_datetime = 0;
        const char *value_arg = NULL;
        int i;

        if(argc == 2 &&
           (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
                print_help(0);
                return 0;
        }

        for(i = 1; i < argc; ++i) {
                if(strcmp(argv[i], "-utc") == 0) {
                        if(utc) {
                                print_help(0);
                                return 1;
                        }
                        utc = 1;
                }
                else if(strcmp(argv[i], "-u") == 0) {
                        if(unix_to_datetime) {
                                print_help(0);
                                return 1;
                        }
                        unix_to_datetime = 1;
                }
                else if(value_arg == NULL) {
                        value_arg = argv[i];
                }
                else {
                        print_help(0);
                        return 1;
                }
        }

        if(unix_to_datetime && value_arg == NULL) {
                print_help(0);
                return 1;
        }

        print_help(1);

        if(unix_to_datetime) {
                if(parse_ll(value_arg, &targ) != 0) {
                        fprintf(stderr, "invalid UNIX time: %s\n", value_arg);
                        return 1;
                }

                tt = (time_t)targ;
                if((long long)tt != targ) {
                        fprintf(stderr, "UNIX time out of range: %s\n", value_arg);
                        return 1;
                }

                if(format_datetime(buff, sizeof buff, tt, utc) != 0) {
                        fprintf(stderr, "could not convert UNIX time: %s\n", value_arg);
                        return 1;
                }

                printf("UNIX epoch (seconds): %lld\n", targ);
                printf("%s time: %s\n", utc ? "UTC" : "local", buff);
                print_moon_phase(tt);
                print_option_expirations(tt);
                return 0;
        }

        if(timespec_get(&ts, TIME_UTC) != TIME_UTC) {
                fprintf(stderr, "could not get current time\n");
                return 1;
        }

        tmsec = (long long)ts.tv_sec * 1000LL + (long long)ts.tv_nsec / 1000000LL;

        if(format_datetime(buff, sizeof buff, ts.tv_sec, utc) != 0) {
                fprintf(stderr, "could not convert current time\n");
                return 1;
        }

        printf("current %s time: %s\n", utc ? "UTC" : "local", buff);
        printf("UNIX epoch (seconds): %lld\n", (long long)ts.tv_sec);
        printf("UNIX epoch (milisec): %lld\n", tmsec);
        print_moon_phase(ts.tv_sec);
        print_option_expirations(ts.tv_sec);

        if(value_arg != NULL) {
                if(parse_ll(value_arg, &targ) != 0) {
                        fprintf(stderr, "invalid UNIX time: %s\n", value_arg);
                        return 1;
                }

                printf("diff: %lld days\n",
                       (targ - tmsec) / (24LL * 60LL * 60LL * 1000LL));
        }

        return 0;
}