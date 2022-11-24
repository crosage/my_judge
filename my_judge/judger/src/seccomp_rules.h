#ifndef JUDGER_SECCOMP_RULES_H
#define JUDGER_SECCOMP_RULES_H
#include <stdbool.h>

int _c_cpp_seccomp_rules(struct limits *limit, bool allow_write_file);
int c_cpp_seccomp_rules(struct limits *limit);
int c_cpp_file_io_seccomp_rules(struct limits *limit);

#endif //JUDGER_SECCOMP_RULES_H
