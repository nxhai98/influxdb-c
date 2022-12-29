/*
 * Copyright (c) 2013-2014 InfluxDB
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

#ifndef POINT_H_
# define POINT_H_

/* TODO need define some rules for error code an it desctiption */
#define INF_OK 0
#define INF_ERROR 1
#define INF_WARNING 2
#define INF_TYPE_ 1


typedef enum FieldType
{
    INF_BOOL,
    INF_UINT,
    INF_INT64,  /* may be unused */
    INF_FLOAT,
    INF_STRING,
    INF_TIME    /* may be unused, treat as string */
};

typedef struct s_influxdb_point
{
    /* unix time */
    unsigned long long   _unix_time;
    char                *_time;

    /* Tags info */
    char          **_tag_name;
    char          **_tags;          /* tag always not null */
    int             _tag_num;

    /* Field info */
    char          **_val_names;
    char          **_vals;          /* CSV return char* => any conversion will making bad performance */
    size_t         *_val_sizes;
    bool           *isnulls;
    FieldType      *_val_types;
    int             _field_num;     /* with flux query len may be 1 */
} s_influxdb_point;

void inf_point_free(s_influxdb_point *point);
void inf_point_set_time(s_influxdb_point *point, unsigned long long time);
void inf_point_add_tag(s_influxdb_point *point, char *name, char *tag_val);
void inf_point_add_field(s_influxdb_point *point, char *name, INF_POINTER val, FieldType type);

/*
 * get data from point
 * TODO: need using status/ERROR code instead of bool
 */
bool inf_point_get_time(s_influxdb_point *point, unsigned long long *time);
bool inf_point_get_tag(s_influxdb_point *point, const char *name, char **out);
bool inf_point_get_field(s_influxdb_point *point, const char *name, FieldType target_type, void *target_value_ptr);
bool inf_point_to_line_protocol(s_influxdb_point *point);

#endif POINT_H_
