#ifndef RUNNER_H
#define RUNNER_H
#include "guard.h"
#define ERROR_EXIT(error_code)\
    {\
        LOG_ERROR(error_code);  \
        _result->error = error_code; \
        log_close(log_fp);  \
        return; \
    }

void setLimit(struct limits *limit);
void run(struct limits *limit);
#endif