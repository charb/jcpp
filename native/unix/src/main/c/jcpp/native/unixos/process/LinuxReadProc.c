#include "jcpp/native/unixos/process/LinuxReadProc.h"

#ifdef Linux

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <locale.h>
#include <sys/utsname.h>

#ifndef HZ
#include <netinet/in.h>  /* htons */
#endif

extern char **environ;

#define EINTR_RETRY(CODE) 						\
	int result = 0;								\
	while (1) { 								\
		result = CODE;		 					\
		if (result != -1 || errno != EINTR) { 	\
			break; 								\
		} 										\
	}


#define EINTR_RETRY_R(RESULT_NAME, CODE) 			\
	while (1) { 									\
		RESULT_NAME = CODE;		 					\
		if (RESULT_NAME != -1 || errno != EINTR) { 	\
			break; 									\
		} 											\
	}

#define EINTR_RETRY_RV(RESULT_NAME, FAIL_VALUE, CODE)		\
	while (1) { 											\
		RESULT_NAME = CODE;		 							\
		if (RESULT_NAME != FAIL_VALUE || errno != EINTR) { 	\
			break; 											\
		} 													\
	}

#define F(x) {#x, sizeof(#x)-1, (long)(&&case_##x-&&base)},
#define NUL  {"", 0, 0},
#define KLF "l"
//#define likely(x)       __builtin_expect(!!(x),1)
//#define unlikely(x)     __builtin_expect(!!(x),0)
//#define expected(x,y)   __builtin_expect((x),(y))

#define likely(x)       x
#define unlikely(x)     x

static int task_dir_missing;

typedef struct status_table_struct {
	unsigned char name[7];        // /proc/*/status field name
	unsigned char len;            // name length
	long offset;                  // jump address offset
} status_table_struct;

static void status2proc(char *S, proc_t * P, int is_proc) {
	long Threads = 0;
	long Tgid = 0;
	long Pid = 0;

	static const unsigned char asso[] = { 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61,
			61, 61, 61, 61, 61, 15, 61, 61, 61, 61, 61, 61, 61, 30, 3, 5, 5, 61, 5, 61, 8, 61, 61, 3, 61, 10, 61, 6, 61, 13, 0, 30, 25, 0, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 3, 61, 13, 0, 0, 61, 30, 61, 25, 61, 61, 61, 0, 61, 61, 61, 61, 5, 61, 0, 61,
			61, 61, 0, 61, 61, 61, 61, 61, 61, 61 };

static const status_table_struct table[] = {
	F(VmStk)
	NUL NUL
	F(State)
	NUL
	F(VmExe)
	F(ShdPnd)
	NUL
	F(VmData)
	NUL
	F(Name)
	NUL NUL
	F(VmRSS)
	NUL NUL
	F(VmLck)
	NUL NUL NUL
	F(Gid)
	F(Pid)
	NUL NUL NUL
	F(VmSize)
	NUL NUL
	F(VmLib)
	NUL NUL
	F(PPid)
	NUL
	F(SigCgt)
	NUL
	F(Threads)
	F(SigPnd)
	NUL
	F(SigIgn)
	NUL
	F(Uid)
	NUL NUL NUL NUL NUL NUL NUL NUL NUL
	NUL NUL NUL NUL NUL
	F(Tgid)
	NUL NUL NUL NUL
	F(SigBlk)
	NUL NUL NUL
};

#undef F
#undef NUL

P->vm_size = 0;
P->vm_lock = 0;
P->vm_rss = 0;
P->vm_data = 0;
P->vm_stack= 0;
P->vm_exe = 0;
P->vm_lib = 0;
P->nlwp = 0;
P->signal[0] = '\0';  // so we can detect it as missing for very old kernels

goto base;

for(;;
){
        char *colon;
        status_table_struct entry;

        // advance to next line
        S = strchr(S, '\n');
        if(							unlikely(!S)) break;  // if no newline
        S++;

        // examine a field name (hash and compare)
    base:
        if(unlikely(!*S)) break;
        entry = table[63 & (asso[S[3]] + asso[S[2]] + asso[S[0]])];
        colon = strchr(S, ':');
        if(unlikely(!colon)) break;
        if(unlikely(colon[1]!='\t')) break;
        if(unlikely(colon-S != entry.len)) continue;
        if(unlikely(memcmp(entry.name,S,colon-S))) continue;

        S = colon+2; // past the '\t'

        goto *(&&base + entry.offset);

    case_Name:{
        unsigned u = 0;
        while(u < sizeof P->cmd - 1u){
            int c = *S++;
            if(unlikely(c=='\n')) break;
            if(unlikely(c=='\0')) break; // should never happen
            if(unlikely(c=='\\')
		) {
			c = *S++;
			if(c=='\n') break; // should never happen
			if(!c) break;// should never happen
			if(c=='n') c='\n';// else we assume it is '\\'
		}
		P->cmd[u++] = c;
	}
	P->cmd[u] = '\0';
	S--;   // put back the '\n' or '\0'
	continue;
}
case_ShdPnd:
memcpy(P->signal, S, 16);
P->signal[16] = '\0';
continue;
case_SigBlk:
memcpy(P->blocked, S, 16);
P->blocked[16] = '\0';
continue;
case_SigCgt:
memcpy(P->sigcatch, S, 16);
P->sigcatch[16] = '\0';
continue;
case_SigIgn:
memcpy(P->sigignore, S, 16);
P->sigignore[16] = '\0';
continue;
case_SigPnd:
memcpy(P->_sigpnd, S, 16);
P->_sigpnd[16] = '\0';
continue;
case_State:
P->state = *S;
continue;
case_Tgid:
Tgid = strtol(S,&S,10);
continue;
case_Pid:
Pid = strtol(S,&S,10);
continue;
case_PPid:
P->ppid = strtol(S,&S,10);
continue;
case_Threads:
Threads = strtol(S,&S,10);
continue;
case_Uid:
P->ruid = strtol(S,&S,10);
P->euid = strtol(S,&S,10);
P->suid = strtol(S,&S,10);
P->fuid = strtol(S,&S,10);
continue;
case_Gid:
P->rgid = strtol(S,&S,10);
P->egid = strtol(S,&S,10);
P->sgid = strtol(S,&S,10);
P->fgid = strtol(S,&S,10);
continue;
case_VmData:
P->vm_data = strtol(S,&S,10);
continue;
case_VmExe:
P->vm_exe = strtol(S,&S,10);
continue;
case_VmLck:
P->vm_lock = strtol(S,&S,10);
continue;
case_VmLib:
P->vm_lib = strtol(S,&S,10);
continue;
case_VmRSS:
P->vm_rss = strtol(S,&S,10);
continue;
case_VmSize:
P->vm_size = strtol(S,&S,10);
continue;
case_VmStk:
P->vm_stack = strtol(S,&S,10);
continue;
}

#if 0
   // recent kernels supply per-tgid pending signals
if(is_proc && *ShdPnd) {
memcpy(P->signal, ShdPnd, 16);
P->signal[16] = '\0';
}
#endif

   // recent kernels supply per-tgid pending signals

if(!is_proc || !P->signal[0]) {
memcpy(P->signal, P->_sigpnd, 16);
P->signal[16] = '\0';
}

   // Linux 2.4.13-pre1 to max 2.4.xx have a useless "Tgid"
   // that is not initialized for built-in kernel tasks.
   // Only 2.6.0 and above have "Threads" (nlwp) info.

if(Threads) {
P->nlwp = Threads;
P->tgid = Tgid;     // the POSIX PID value
P->tid = Pid;// the thread ID
} else {
P->nlwp = 1;
P->tgid = Pid;
P->tid = Pid;
}

}


static void stat2proc(const char* S, proc_t * P) {
	unsigned num;
	char* tmp;

	P->processor = 0;
	P->rtprio = -1;
	P->sched = -1;
	P->nlwp = 0;

	S = strchr(S, '(') + 1;
	tmp = strrchr(S, ')');
	num = tmp - S;
	if (unlikely(num >= sizeof P->cmd)) {
		num = sizeof P->cmd - 1;
	}
	memcpy(P->cmd, S, num);
	P->cmd[num] = '\0';
	S = tmp + 2;

	num = sscanf(S, "%c "
			"%d %d %d %d %d "
			"%lu %lu %lu %lu %lu "
			"%Lu %Lu %Lu %Lu "
			"%ld %ld "
			"%d "
			"%ld "
			"%Lu "
			"%lu "
			"%ld "
			"%lu %"KLF"u %"KLF"u %"KLF"u %"KLF"u %"KLF"u "
			"%*s %*s %*s %*s "
			"%"KLF"u %*lu %*lu "
			"%d %d "
			"%lu %lu", &P->state, &P->ppid, &P->pgrp, &P->session, &P->tty, &P->tpgid, &P->flags, &P->min_flt, &P->cmin_flt, &P->maj_flt, &P->cmaj_flt, &P->utime, &P->stime, &P->cutime, &P->cstime, &P->priority, &P->nice, &P->nlwp, &P->alarm, &P->start_time,
			&P->vsize, &P->rss, &P->rss_rlim, &P->start_code, &P->end_code, &P->start_stack, &P->kstk_esp, &P->kstk_eip,
			&P->wchan,
			&P->exit_signal, &P->processor,
			&P->rtprio, &P->sched
	);

	if (!P->nlwp) {
		P->nlwp = 1;
	}
}

/////////////////////////////////////////////////////////////////////////

static void statm2proc(const char* s, proc_t * P) {
	int num;
	num = sscanf(s, "%ld %ld %ld %ld %ld %ld %ld", &P->size, &P->resident, &P->share, &P->trs, &P->lrs, &P->drs, &P->dt);
}

static int file2str(const char *directory, const char *what, char *ret, int cap) {
	static char filename[80];
	int fd, num_read;

	sprintf(filename, "%s/%s", directory, what);
	EINTR_RETRY_R(fd, open(filename, O_RDONLY, 0))
	if (unlikely(fd == -1))
		return -1;
	EINTR_RETRY_R(num_read, read(fd, ret, cap - 1))
	EINTR_RETRY(close(fd))
	if (unlikely(num_read <= 0))
		return -1;
	ret[num_read] = '\0';
	return num_read;
}

static char** file2strvec(const char* directory, const char* what) {
	char buf[2048]; /* read buf bytes at a time */
	char *p, *rbuf = 0, *endbuf, **q, **ret;
	int fd, tot = 0, n, c, end_of_file = 0;
	int align;

	sprintf(buf, "%s/%s", directory, what);
	EINTR_RETRY_R(fd, open(buf, O_RDONLY, 0))
	if (fd == -1)
		return NULL;

	while (1) {
		EINTR_RETRY_R(n, read(fd, buf, sizeof buf - 1))
		if(n <= 0) {
			break;
		}

		if (n < (int) (sizeof buf - 1))
			end_of_file = 1;
		if (n == 0 && rbuf == 0)
			return NULL; /* process died between our open and read */
		if (n < 0) {
			if (rbuf)
				free(rbuf);
			return NULL; /* read error */
		}
		if (end_of_file && buf[n - 1]) /* last read char not null */
			buf[n++] = '\0'; /* so append null-terminator */
		rbuf = (char *)xrealloc(rbuf, tot + n); /* allocate more memory */
		memcpy(rbuf + tot, buf, n); /* copy buffer into it */
		tot += n; /* increment total byte ctr */
		if (end_of_file)
			break;
	}
	EINTR_RETRY(close(fd))
	if (n <= 0 && !end_of_file) {
		if (rbuf)
			free(rbuf);
		return NULL; /* read error */
	}
	endbuf = rbuf + tot; /* count space for pointers */
	align = (sizeof(char*) - 1) - ((tot + sizeof(char*) - 1) & (sizeof(char*) - 1));
	for (c = 0, p = rbuf; p < endbuf; p++)
		if (!*p)
			c += sizeof(char*);
	c += sizeof(char*); /* one extra for NULL term */

	rbuf = (char *)xrealloc(rbuf, tot + c + align); /* make room for ptrs AT END */
	endbuf = rbuf + tot; /* addr just past data buf */
	q = ret = (char**) (endbuf + align); /* ==> free(*ret) to dealloc */
	*q++ = p = rbuf; /* point ptrs to the strings */
	endbuf--; /* do not traverse final NUL */
	while (++p < endbuf)
		if (!*p) /* NUL char implies that */
			*q++ = p + 1; /* next string -> next char */

	*q = 0; /* null ptr list terminator */
	return ret;
}

/* These are some nice GNU C expression subscope "inline" functions.
 * The can be used with arbitrary types and evaluate their arguments
 * exactly once.
 */

/* Test if item X of type T is present in the 0 terminated list L */
#   define XinL(T, X, L) ( {			\
	    T  x = (X), *l = (L);		\
	    while (*l && *l != x) l++;		\
	    *l == x;				\
	} )

/* Test if item X of type T is present in the list L of length N */
#   define XinLN(T, X, L, N) ( {		\
	    T x = (X), *l = (L);		\
	    int i = 0, n = (N);			\
	    while (i < n && l[i] != x) i++;	\
	    i < n && l[i] == x;			\
	} )

//////////////////////////////////////////////////////////////////////////////////
// This reads process info from /proc in the traditional way, for one process.
// The pid (tgid? tid?) is already in p, and a path to it in path, with some
// room to spare.
static proc_t* simple_readproc(PROCTAB * const PT, proc_t * const p) {
static struct stat sb;		// stat() buffer
static char sbuf[1024];	// buffer for stat,statm
char * const path = PT->path;
unsigned flags = PT->flags;

if (unlikely(stat(path, &sb) == -1)) /* no such dirent (anymore) */
goto next_proc;

if ((flags & PROC_UID) && !XinLN(uid_t, sb.st_uid, PT->uids, PT->nuid))
goto next_proc;
/* not one of the requested uids */

p->euid = sb.st_uid; /* need a way to get real uid */
p->egid = sb.st_gid; /* need a way to get real gid */

if (flags & PROC_FILLSTAT) { /* read, parse /proc/#/stat */
if (unlikely(file2str(path, "stat", sbuf, sizeof sbuf) == -1))
	goto next_proc;
/* error reading /proc/#/stat */
stat2proc(sbuf, p); /* parse /proc/#/stat */
}

if (unlikely(flags & PROC_FILLMEM)) { /* read, parse /proc/#/statm */
if (likely(file2str(path, "statm", sbuf, sizeof sbuf) != -1))
	statm2proc(sbuf, p); /* ignore statm errors here */
} /* statm fields just zero */

if (flags & PROC_FILLSTATUS) { /* read, parse /proc/#/status */
if (likely(file2str(path, "status", sbuf, sizeof sbuf) != -1)) {
	status2proc(sbuf, p, 1);
}
}

	// if multithreaded, some values are crap
if (p->nlwp > 1) {
p->wchan = (long) ~0ull;
}

/* some number->text resolving which is time consuming and kind of insane */
if (flags & PROC_FILLUSR) {
memcpy(p->euser, user_from_uid(p->euid), sizeof p->euser);
if (flags & PROC_FILLSTATUS) {
	memcpy(p->ruser, user_from_uid(p->ruid), sizeof p->ruser);
	memcpy(p->suser, user_from_uid(p->suid), sizeof p->suser);
	memcpy(p->fuser, user_from_uid(p->fuid), sizeof p->fuser);
}
}

/* some number->text resolving which is time consuming and kind of insane */
if (flags & PROC_FILLGRP) {
memcpy(p->egroup, group_from_gid(p->egid), sizeof p->egroup);
if (flags & PROC_FILLSTATUS) {
	memcpy(p->rgroup, group_from_gid(p->rgid), sizeof p->rgroup);
	memcpy(p->sgroup, group_from_gid(p->sgid), sizeof p->sgroup);
	memcpy(p->fgroup, group_from_gid(p->fgid), sizeof p->fgroup);
}
}

if ((flags & PROC_FILLCOM) || (flags & PROC_FILLARG)) /* read+parse /proc/#/cmdline */
p->cmdline = file2strvec(path, "cmdline");
else
p->cmdline = NULL;

if (unlikely(flags & PROC_FILLENV)) /* read+parse /proc/#/environ */
p->environ = file2strvec(path, "environ");
else
p->environ = NULL;

return p;
next_proc: return NULL;
}

//////////////////////////////////////////////////////////////////////////////////
// This reads /proc/*/task/* data, for one task.
// p is the POSIX process (task group summary) (not needed by THIS implementation)
// t is the POSIX thread (task group member, generally not the leader)
// path is a path to the task, with some room to spare.
static proc_t* simple_readtask(PROCTAB * const PT, const proc_t * const p, proc_t * const t, char * const path) {
static struct stat sb;		// stat() buffer
static char sbuf[1024];	// buffer for stat,statm
unsigned flags = PT->flags;

//printf("hhh\n");
if (unlikely(stat(path, &sb) == -1)) /* no such dirent (anymore) */
goto next_task;

//    if ((flags & PROC_UID) && !XinLN(uid_t, sb.st_uid, PT->uids, PT->nuid))
//	goto next_task;			/* not one of the requested uids */

t->euid = sb.st_uid; /* need a way to get real uid */
t->egid = sb.st_gid; /* need a way to get real gid */

//printf("iii\n");
if (flags & PROC_FILLSTAT) { /* read, parse /proc/#/stat */
if (unlikely(file2str(path, "stat", sbuf, sizeof sbuf) == -1))
	goto next_task;
/* error reading /proc/#/stat */
stat2proc(sbuf, t); /* parse /proc/#/stat */
}

if (unlikely(flags & PROC_FILLMEM)) { /* read, parse /proc/#/statm */
#if 0
if (likely( file2str(path, "statm", sbuf, sizeof sbuf) != -1 ))
statm2proc(sbuf, t); /* ignore statm errors here */
#else
t->size = p->size;
t->resident = p->resident;
t->share = p->share;
t->trs = p->trs;
t->lrs = p->lrs;
t->drs = p->drs;
t->dt = p->dt;
#endif
} /* statm fields just zero */

if (flags & PROC_FILLSTATUS) { /* read, parse /proc/#/status */
if (likely(file2str(path, "status", sbuf, sizeof sbuf) != -1)) {
	status2proc(sbuf, t, 0);
}
}

/* some number->text resolving which is time consuming */
if (flags & PROC_FILLUSR) {
memcpy(t->euser, user_from_uid(t->euid), sizeof t->euser);
if (flags & PROC_FILLSTATUS) {
	memcpy(t->ruser, user_from_uid(t->ruid), sizeof t->ruser);
	memcpy(t->suser, user_from_uid(t->suid), sizeof t->suser);
	memcpy(t->fuser, user_from_uid(t->fuid), sizeof t->fuser);
}
}

/* some number->text resolving which is time consuming */
if (flags & PROC_FILLGRP) {
memcpy(t->egroup, group_from_gid(t->egid), sizeof t->egroup);
if (flags & PROC_FILLSTATUS) {
	memcpy(t->rgroup, group_from_gid(t->rgid), sizeof t->rgroup);
	memcpy(t->sgroup, group_from_gid(t->sgid), sizeof t->sgroup);
	memcpy(t->fgroup, group_from_gid(t->fgid), sizeof t->fgroup);
}
}

#if 0
if ((flags & PROC_FILLCOM) || (flags & PROC_FILLARG)) /* read+parse /proc/#/cmdline */
t->cmdline = file2strvec(path, "cmdline");
else
t->cmdline = NULL;

if (unlikely(flags & PROC_FILLENV)) /* read+parse /proc/#/environ */
t->environ = file2strvec(path, "environ");
else
t->environ = NULL;
#else
t->cmdline = p->cmdline;  // better not free these until done with all threads!
t->environ = p->environ;
#endif

t->ppid = p->ppid;  // ought to put the per-task ppid somewhere

return t;
next_task: return NULL;
}

static int simple_nextpid(PROCTAB * const PT, proc_t * const p) {
	static struct direct *ent;
	char * const path = PT->path;
	for (;;) {
		ent = readdir(PT->procfs);
		if (unlikely(unlikely(!ent) || unlikely(!ent->d_name))) {
			return 0;
		}
		if (likely(likely(*ent->d_name > '0') && likely(*ent->d_name <= '9'))) {
			break;
		}
	}
	p->tgid = strtoul(ent->d_name, NULL, 10);
	p->tid = p->tgid;
	memcpy(path, "/proc/", 6);
	strcpy(path + 6, ent->d_name);
	return 1;
}

static int simple_nexttid(PROCTAB * const PT, const proc_t * const p, proc_t * const t, char * const path) {
	static struct direct *ent; /* dirent handle */
	if (PT->taskdir_user != p->tgid) {
		if (PT->taskdir) {
			closedir(PT->taskdir);
		}
		snprintf(path, PROCPATHLEN, "/proc/%d/task", p->tgid);
		PT->taskdir = opendir(path);
		if (!PT->taskdir)
			return 0;
		PT->taskdir_user = p->tgid;
	}
	for (;;) {
		ent = readdir(PT->taskdir);
		if (unlikely(unlikely(!ent) || unlikely(!ent->d_name))) {
			return 0;
		}
		if (likely(likely(*ent->d_name > '0') && likely(*ent->d_name <= '9'))) {
			break;
		}
	}
	t->tid = strtoul(ent->d_name, NULL, 10);
	t->tgid = p->tgid;
	t->ppid = p->ppid;  // cover for kernel behavior? we want both actually...?
	snprintf(path, PROCPATHLEN, "/proc/%d/task/%s", p->tgid, ent->d_name);
	return 1;
}


static int listed_nextpid(PROCTAB * const PT, proc_t * const p) {
	char * const path = PT->path;
	pid_t tgid = *(PT->pids)++;
	if (likely(tgid)) {
		snprintf(path, PROCPATHLEN, "/proc/%d", tgid);
		p->tgid = tgid;
		p->tid = tgid;  // they match for leaders
	}
	return tgid;
}


proc_t* readproc(PROCTAB * const PT, proc_t * p) {
	proc_t *ret;
	proc_t *saved_p;

	PT->did_fake = 0;

	saved_p = p;
	if (!p) {
		p = (proc_t *)xcalloc(p, sizeof *p); /* passed buf or alloced mem */
	}

	for (;;) {
		if (unlikely(!PT->finder(PT, p))) {
			goto out;
		}

		ret = PT->reader(PT, p);
		if (ret) {
			return ret;
		}
	}

	out: if (!saved_p) {
		free(p);
	}

	return NULL;
}

PROCTAB* openproc(int flags, ...) {
	va_list ap;
	struct stat sbuf;
	static int did_stat;
	PROCTAB* PT = xmalloc(sizeof(PROCTAB));

	if (!did_stat) {
		task_dir_missing = stat("/proc/self/task", &sbuf);
		did_stat = 1;
	}

	PT->taskdir = NULL;
	PT->taskdir_user = -1;
	PT->taskfinder = simple_nexttid;
	PT->taskreader = simple_readtask;

	PT->reader = simple_readproc;
	if (flags & PROC_PID) {
		PT->procfs = NULL;
		PT->finder = listed_nextpid;
	} else {
		PT->procfs = opendir("/proc");
		if (!PT->procfs)
			return NULL;
		PT->finder = simple_nextpid;
	}
	PT->flags = flags;

	va_start(ap, flags);

	if (flags & PROC_PID) {
		PT->pids = va_arg(ap, pid_t*);
	} else if (flags & PROC_UID) {
		PT->uids = va_arg(ap, uid_t*);
		PT->nuid = va_arg(ap, int);
	}

	va_end(ap);

	return PT;
}


void closeproc(PROCTAB* PT) {
	if (PT) {
		if (PT->procfs) {
			closedir(PT->procfs);
		}
		if (PT->taskdir) {
			closedir(PT->taskdir);
		}
		memset(PT, '#', sizeof(PROCTAB));
		free(PT);
	}
}

void freeproc(proc_t* p) {
	if (!p) {
		return;
	}
	if (p->cmdline) {
		free((void*) *p->cmdline);
	}
	if (p->environ) {
		free((void*) *p->environ);
	}
	free(p);
}

void *xcalloc(void *pointer, int size) {
    void * ret;
    if (pointer)
        free(pointer);
    if (!(ret = calloc(1, size))) {
        fprintf(stderr, "xcalloc: allocation error, size = %d\n", size);
        exit(1);
    }
    return ret;
}

void *xmalloc(unsigned int size) {
    void *p;

    if (size == 0)
        ++size;
    p = malloc(size);
    if (!p) {
	fprintf(stderr, "xmalloc: malloc(%d) failed", size);
	perror(NULL);
	exit(1);
    }
    return(p);
}

void *xrealloc(void *oldp, unsigned int size) {
    void *p;

    if (size == 0)
        ++size;
    p = realloc(oldp, size);
    if (!p) {
	fprintf(stderr, "xrealloc: realloc(%d) failed", size);
	perror(NULL);
	exit(1);
    }
    return(p);
}

#define	HASHSIZE	64		/* power of 2 */
#define	HASH(x)		((x) & (HASHSIZE - 1))

static struct pwbuf {
    struct pwbuf *next;
    uid_t uid;
    char name[P_G_SZ];
} *pwhash[HASHSIZE];

char *user_from_uid(uid_t uid) {
    struct pwbuf **p;
    struct passwd *pw;

    p = &pwhash[HASH(uid)];

    while (*p) {
    	if ((*p)->uid == uid) {
    		return((*p)->name);
    	}
    	p = &(*p)->next;
    }

    *p = (struct pwbuf *) xmalloc(sizeof(struct pwbuf));
    (*p)->uid = uid;
    pw = getpwuid(uid);

    if(!pw || strlen(pw->pw_name) >= P_G_SZ) {
    	sprintf((*p)->name, "%u", uid);
    } else {
        strcpy((*p)->name, pw->pw_name);
    }

    (*p)->next = NULL;
    return((*p)->name);
}

static struct grpbuf {
    struct grpbuf *next;
    gid_t gid;
    char name[P_G_SZ];
} *grphash[HASHSIZE];

char *group_from_gid(gid_t gid) {
    struct grpbuf **g;
    struct group *gr;

    g = &grphash[HASH(gid)];
    while (*g) {
        if ((*g)->gid == gid) {
            return((*g)->name);
        }
        g = &(*g)->next;
    }
    *g = (struct grpbuf *) malloc(sizeof(struct grpbuf));
    (*g)->gid = gid;
    gr = getgrgid(gid);
    if (!gr || strlen(gr->gr_name) >= P_G_SZ) {
        sprintf((*g)->name, "%u", gid);
    } else {
        strcpy((*g)->name, gr->gr_name);
    }
    (*g)->next = NULL;
    return((*g)->name);
}

#ifndef AT_CLKTCK
#define AT_CLKTCK       17    // frequency of times()
#endif

#define NOTE_NOT_FOUND 42


/* for ELF executables, notes are pushed before environment and args */
static unsigned long find_elf_note(unsigned long findme){
  unsigned long *ep = (unsigned long *)environ;
  while(*ep++);
  while(*ep){
    if(ep[0]==findme) return ep[1];
    ep+=2;
  }
  return NOTE_NOT_FOUND;
}

#define LINUX_VERSION(x,y,z)   (0x10000*(x) + 0x100*(y) + z)
#define STAT_FILE    "/proc/stat"
static int stat_fd = -1;
#define UPTIME_FILE  "/proc/uptime"
static int uptime_fd = -1;
#define LOADAVG_FILE "/proc/loadavg"
#define MEMINFO_FILE "/proc/meminfo"
#define VMINFO_FILE "/proc/vmstat"

#define BAD_OPEN_MESSAGE					\
"Error: /proc must be mounted\n"				\
"  To mount /proc at boot you need an /etc/fstab line like:\n"	\
"      /proc   /proc   proc    defaults\n"			\
"  In the meantime, run \"mount /proc /proc -t proc\"\n"

static char buf[2048];

#define FILE_TO_BUF(filename, fd) do{				\
    static int local_n;						\
    if (fd == -1 && (fd = open(filename, O_RDONLY)) == -1) {	\
	fputs(BAD_OPEN_MESSAGE, stderr);			\
	fflush(NULL);						\
	_exit(102);						\
    }								\
    lseek(fd, 0L, SEEK_SET);					\
    if ((local_n = read(fd, buf, sizeof buf - 1)) < 0) {	\
	perror(filename);					\
	fflush(NULL);						\
	_exit(103);						\
    }								\
    buf[local_n] = '\0';					\
}while(0)

unsigned long long getHertz(void){
	unsigned long long Hertz = 100;

	long smp_num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	 if(smp_num_cpus<1) smp_num_cpus=1; /* SPARC glibc is buggy */

	 int linux_version_code;
	 static struct utsname uts;
	 int x = 0, y = 0, z = 0;	/* cleared in case sscanf() < 3 */

	 if (uname(&uts) == -1)	/* failure implies impending death */
	 	exit(1);

	 if (sscanf(uts.release, "%d.%d.%d", &x, &y, &z) < 3)
	 	fprintf(stderr,		/* *very* unlikely to happen by accident */
	 		"Non-standard uts for running kernel:\n"
	 		"release %s=%d.%d.%d gives version code %d\n",
	 		uts.release, x, y, z, LINUX_VERSION(x,y,z));
	  linux_version_code = LINUX_VERSION(x, y, z);


	  if(linux_version_code > LINUX_VERSION(2, 4, 0)){
	    Hertz = find_elf_note(AT_CLKTCK);
	    if(Hertz!=NOTE_NOT_FOUND)
	    	return Hertz;
	    fputs("2.4+ kernel w/o ELF notes? -- report this\n", stderr);
	  }

  unsigned long long user_j, nice_j, sys_j, other_j;  /* jiffies (clock ticks) */
  double up_1, up_2, seconds;
  unsigned long long jiffies;
  unsigned h;
  char * savelocale;

  savelocale = setlocale(LC_NUMERIC, NULL);
  setlocale(LC_NUMERIC, "C");
  do{
    FILE_TO_BUF(UPTIME_FILE,uptime_fd);  sscanf(buf, "%lf", &up_1);
    /* uptime(&up_1, NULL); */
    FILE_TO_BUF(STAT_FILE,stat_fd);
    sscanf(buf, "cpu %Lu %Lu %Lu %Lu", &user_j, &nice_j, &sys_j, &other_j);
    FILE_TO_BUF(UPTIME_FILE,uptime_fd);  sscanf(buf, "%lf", &up_2);
    /* uptime(&up_2, NULL); */
  } while((long long)( (up_2-up_1)*1000.0/up_1 )); /* want under 0.1% error */
  setlocale(LC_NUMERIC, savelocale);
  jiffies = user_j + nice_j + sys_j + other_j;
  seconds = (up_1 + up_2) / 2;
  h = (unsigned)( (double)jiffies/seconds/smp_num_cpus );
  /* actual values used by 2.4 kernels: 32 64 100 128 1000 1024 1200 */
  switch(h){
  case    9 ...   11 :  Hertz =   10; break; /* S/390 (sometimes) */
  case   18 ...   22 :  Hertz =   20; break; /* user-mode Linux */
  case   30 ...   34 :  Hertz =   32; break; /* ia64 emulator */
  case   48 ...   52 :  Hertz =   50; break;
  case   58 ...   61 :  Hertz =   60; break;
  case   62 ...   65 :  Hertz =   64; break; /* StrongARM /Shark */
  case   95 ...  105 :  Hertz =  100; break; /* normal Linux */
  case  124 ...  132 :  Hertz =  128; break; /* MIPS, ARM */
  case  195 ...  204 :  Hertz =  200; break; /* normal << 1 */
  case  247 ...  252 :  Hertz =  250; break;
  case  253 ...  260 :  Hertz =  256; break;
  case  393 ...  408 :  Hertz =  400; break; /* normal << 2 */
  case  790 ...  808 :  Hertz =  800; break; /* normal << 3 */
  case  990 ... 1010 :  Hertz = 1000; break; /* ARM */
  case 1015 ... 1035 :  Hertz = 1024; break; /* Alpha, ia64 */
  case 1180 ... 1220 :  Hertz = 1200; break; /* Alpha */
  default:
#ifdef HZ
    Hertz = (unsigned long long)HZ;    /* <asm/param.h> */
#else
    /* If 32-bit or big-endian (not Alpha or ia64), assume HZ is 100. */
    Hertz = (sizeof(long)==sizeof(int) || htons(999)==999) ? 100UL : 1024UL;
#endif
    fprintf(stderr, "Unknown HZ value! (%d) Assume %Ld.\n", h, Hertz);
  }
  return Hertz;
}

#endif // Linux

