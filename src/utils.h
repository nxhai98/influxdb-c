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

#define influxdb_malloc(size) malloc(size)
#define influxdb_free(size) free(size)

typedef struct s_string_info
{
    char       *data; /* string data */
    size_t      len; /* string length */
    size_t      maxlen; /* string max length */
} s_string_info;

/**
 * Returns a pointer to a new string which is a duplicate of the string s
 */
char *influxdb_strdup(const char *s);

s_string_info *influxdb_make_string_info();
void influxdb_reset_string_info(s_string_info *str);
void influxdb_string_append_string(s_string_info *buf, char *s);

/* CSV parser */

/* parser to common type => performance may not good */
typedef struct s_csv_response
{
    char **res;
};

// parse to result set structure: point list
// v1: point has many fields
// v2: point has only one field (need check)
void influxdb_csv_parser(char *buffer, size_t len);

#endif /* !UTILS_H_ */
