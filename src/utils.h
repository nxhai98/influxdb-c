/*
 * Copyright (c) 2013-2014 InfluxDB
 * Pierre-Olivier Mercier <pomercier@novaquark.com>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

#ifndef UTILS_H_
# define UTILS_H_

typedef struct string_info
{
    char       *data; /* string data */
    size_t      len; /* string length */
    size_t      max_len; /* string max length */
} string_info;

/**
 * Returns a pointer to a new string which is a duplicate of the string s
 */
char *influxdb_strdup(const char *s);

string_info *influxdb_make_string_info();
void influxdb_reset_string_info(string_info *str);
void influxdb_string_append_string(string_info *buf, char *s);

#endif /* !UTILS_H_ */
