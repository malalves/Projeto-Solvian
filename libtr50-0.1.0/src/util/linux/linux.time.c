/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 ILS Technology, LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <time.h>
#include <sys/time.h>
#include <string.h>

#include <stdio.h>

#include <tr50/util/time.h>

long long _time_now(void) {
	struct timeval ltime;
	long long ret;

	gettimeofday(&ltime, NULL);
	ret = ltime.tv_sec;
	ret *= 1000;
	ret += ltime.tv_usec / 1000;

	return ret;
}

int _time_now_in_sec(void) {
	struct timeval ltime;

	gettimeofday(&ltime, NULL);
	return (int)ltime.tv_sec;
}

void tr50_time_sprintf(char *buffer, const char *time_format, long long mstime) {
	tr50_time_sprintf2(buffer, time_format, mstime, 0);
}


void tr50_time_sprintf2(char *buffer, const char *time_format, long long mstime, int use_gmt) {
	time_t timestamp = mstime / 1000;
	struct tm tim;
	int len, ms = mstime % 1000;

	if (ms<0) {
		timestamp -= 1;
		ms += 1000;
	}

	if (use_gmt) {
		gmtime_r(&timestamp, &tim);
	}
	else {
		localtime_r(&timestamp, &tim);
	}
	if (time_format == NULL) {
#if defined (_HPUX)
		strftime((char *)buffer, 64, "%Y-%m-%d %H:%M:%S", &tim);
#else
		strftime((char *)buffer, 64, "%F %T", &tim);
#endif
		len = strlen(buffer);
		snprintf(buffer + len, 64 - len, ".%03d", ms);
	}
	else {
		strftime((char *)buffer, 64, time_format, &tim);
	}
}

void tr50_time_strptime(const char *timestamp_str, const char *time_format, long long *mstime) {
	struct tm tim;
	*mstime = 0LL;

	if (strptime(timestamp_str, time_format ? time_format : "%Y-%m-%dT%H:%M:%SZ", &tim) == 0) return;

	tim.tm_isdst = -1;
	*mstime = mktime(&tim);
	*mstime *= 1000;
	return;
}
