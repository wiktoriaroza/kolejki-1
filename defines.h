#ifndef _DEFINES_
#define _DEFINES_

#define SERVER_QUEUE_KEY 123456
#define REPORT_QUEUE_KEY 234567

#define RESULTS_TYPE 1
typedef struct
{
    int dane;
}
Results;

#define QUERY_TYPE 2
typedef struct
{
    char what;
}
Query;

typedef union
{
    Results results;
    Query   query;
}
Data;

typedef struct
{
    long type;
    Data data;
}
Message;

#endif
