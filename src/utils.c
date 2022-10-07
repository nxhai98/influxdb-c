/*
 * Copyright (c) 2013-2014 InfluxDB
 * Pierre-Olivier Mercier <pomercier@novaquark.com>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

#include <stdlib.h>
#include <string.h>

#include "utils.h"

char *
influxdb_strdup(const char *s)
{
    char *d;

    if (s == NULL)
        return NULL;

    d = malloc(sizeof (char) * (strlen(s) + 1));
    if (d == NULL)
        return NULL;

    strcpy(d, s);
    return d;
}

void
influxdb_reset_string_info(string_info *str)
{
    str->data[0] = '\0';
	str->len = 0;
}

/*
 * initStringInfo
 *
 * Initialize a StringInfoData struct (with previously undefined contents)
 * to describe an empty string.
 */
static void
influxdb_init_string_info(string_info *str)
{
    int            size = 1024;    /* initial default buffer size */

    str->data = (char *) malloc(sizeof(char) * size);
    str->len = 0;
    str->max_len = size;
    influxdb_reset_string_info(str);
}

/**
 * @brief init empty string info and return pointer to it
 *
 * @return string_info*
 */
string_info *
influxdb_make_string_info()
{
    string_info    *res;

    res = (string_info *) malloc(sizeof(string_info));

    influxdb_init_string_info(res);

    return res;
}

/**
 * @brief extend 'needed' size for string_info
 *
 * @param buf
 * @param needed
 */
static void
influxdb_enlarge_string_info(string_info *buf, int needed)
{
    int     newlen;

    if (needed < 0)
        return;

    needed += buf->len + 1;		/* total space required now */

    if (needed <= buf->maxlen)
		return;					/* got enough space already */

    /*
	 * We don't want to allocate just a little more space with each append;
	 * for efficiency, double the buffer size each time it overflows.
	 * Actually, we might need to more than double it if 'needed' is big...
	 */
	newlen = 2 * buf->maxlen;
	while (needed > newlen)
		newlen = 2 * newlen;

    buf->data = (char *) realloc(buf->data, newlen);

	buf->maxlen = newlen;
}

/**
 * @brief append string s to stringInfo buf
 *
 * @param buf
 * @param s
 */
void
influxdb_string_append_string(string_info *buf, char *s)
{
    int datalen = strlen(s);

    /* Make more room if needed */
	influxdb_enlarge_string_info(buf, datalen);

	/* OK, append the data */
	memcpy(buf->data + buf->len, s, datalen);
	buf->len += datalen;

	/*
	 * Keep a trailing null in place, even though it's probably useless for
	 * binary data.  (Some callers are dealing with text but call this because
	 * their input isn't null-terminated.)
	 */
	buf->data[buf->len] = '\0';
}
