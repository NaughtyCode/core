#ifndef __COMMON_H
#define __COMMON_H

struct ip_addr;

#include "lib.h"
#include "hash.h"
#include "master-settings.h"

#include "../auth/auth-master-interface.h"

enum {
	PROCESS_TYPE_UNKNOWN,
	PROCESS_TYPE_AUTH,
	PROCESS_TYPE_LOGIN,
	PROCESS_TYPE_IMAP,
	PROCESS_TYPE_POP3,
	PROCESS_TYPE_SSL_PARAM,

	PROCESS_TYPE_MAX
};

extern struct ioloop *ioloop;
extern struct hash_table *pids;
extern int null_fd, inetd_login_fd;
extern uid_t master_uid;

#define IS_INETD() \
	(inetd_login_fd != -1)

/* processes */
#define PID_GET_PROCESS_TYPE(pid) \
	POINTER_CAST_TO(hash_lookup(pids, POINTER_CAST(pid)), pid_t)

#define PID_ADD_PROCESS_TYPE(pid, type) \
	hash_insert(pids, POINTER_CAST(pid), POINTER_CAST(type))

#define PID_REMOVE_PROCESS_TYPE(pid) \
	hash_remove(pids, POINTER_CAST(pid))

void child_process_init_env(struct settings *set);

/* misc */
#define VALIDATE_STR(str) \
	validate_str(str, sizeof(str))
int validate_str(const char *str, size_t max_len);

#endif
