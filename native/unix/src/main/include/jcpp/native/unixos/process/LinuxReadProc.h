#ifndef JCPP_NATIVE_UNIXOS_PROCESS_LINUXREADPROC
#define JCPP_NATIVE_UNIXOS_PROCESS_LINUXREADPROC

#ifdef Linux

#define PROC_FILLMEM         0x0001 // read statm
#define PROC_FILLCOM         0x0002 // alloc and fill in `cmdline'
#define PROC_FILLENV         0x0004 // alloc and fill in `environ'
#define PROC_FILLUSR         0x0008 // resolve user id number -> user name
#define PROC_FILLGRP         0x0010 // resolve group id number -> group name
#define PROC_FILLSTATUS      0x0020 // read status -- currently unconditional
#define PROC_FILLSTAT        0x0040 // read stat -- currently unconditional
#define PROC_FILLWCHAN       0x0080 // look up WCHAN name
#define PROC_FILLARG         0x0100 // alloc and fill in `cmdline'

#define PROC_LOOSE_TASKS     0x0200 // threat threads as if they were processes

// Obsolete, consider only processes with one of the passed:
#define PROC_PID             0x1000  // process id numbers ( 0   terminated)
#define PROC_UID             0x4000  // user id numbers    ( length needed )

// it helps to give app code a few spare bits
#define PROC_SPARE_1     0x01000000
#define PROC_SPARE_2     0x02000000
#define PROC_SPARE_3     0x04000000
#define PROC_SPARE_4     0x08000000

// used in pwcache and in readproc to set size of username or groupname
#define P_G_SZ 20

typedef struct proc_t {
	int tid,					// (special)       task id, the POSIX thread ID (see also: tgid)
			ppid;				// stat,status     pid of parent process
	unsigned pcpu;   			// stat (special)  %CPU usage (is not filled in by readproc!!!)
	char state,					// stat,status     single-char code for process state (S=sleeping)
			pad_1,				// n/a             padding
			pad_2,				// n/a             padding
			pad_3;				// n/a             padding
	unsigned long long utime,	// stat            user-mode CPU time accumulated by process
			stime,				// stat            kernel-mode CPU time accumulated by process
			cutime,				// stat            cumulative utime of process and reaped children
			cstime,				// stat            cumulative stime of process and reaped children
			start_time;			// stat            start time of process -- seconds since 1-1-70
	char signal[18],					// status          mask of pending signals, per-task for readtask() but per-proc for readproc()
			blocked[18],		// status          mask of blocked signals
			sigignore[18],		// status          mask of ignored signals
			sigcatch[18],		// status          mask of caught  signals
			_sigpnd[18];		// status          mask of PER TASK pending signals
	unsigned long start_code,	// stat            address of beginning of code segment
			end_code,			// stat            address of end of code segment
			start_stack,		// stat            address of the bottom of stack for the process
			kstk_esp,			// stat            kernel stack pointer
			kstk_eip,			// stat            kernel instruction pointer
			wchan;				// stat (special)  address of kernel wait channel proc is sleeping in
	long priority,				// stat            kernel scheduling priority
			nice,				// stat            standard unix nice level of process
			rss,				// stat            resident set size from /proc/#/stat (pages)
			alarm,				// stat            ?
			size,				// statm           total # of pages of memory
			resident,			// statm           number of resident set (non-swapped) pages (4k)
			share,				// statm           number of pages of shared (mmap'd) memory
			trs,				// statm           text resident set size
			lrs,				// statm           shared-lib resident set size
			drs,				// statm           data resident set size
			dt;					// statm           dirty pages
	unsigned long vm_size,		// status          same as vsize in kb
			vm_lock,        	// status          locked pages in kb
			vm_rss,         	// status          same as rss in kb
			vm_data,        	// status          data size
			vm_stack,       	// status          stack size
			vm_exe,         	// status          executable size
			vm_lib,         	// status          library size (all pages, not just used ones)
			rtprio,				// stat            real-time priority
			sched,				// stat            scheduling class
			vsize,				// stat            number of pages of virtual memory ...
			rss_rlim,			// stat            resident set size limit?
			flags,				// stat            kernel flags for the process
			min_flt,			// stat            number of minor page faults since process start
			maj_flt,			// stat            number of major page faults since process start
			cmin_flt,			// stat            cumulative min_flt of process and child processes
			cmaj_flt;			// stat            cumulative maj_flt of process and child processes
	char **environ,				// (special)       environment string vector (/proc/#/environ)
			**cmdline;			// (special)       command line string vector (/proc/#/cmdline)
	char euser[P_G_SZ],			// stat(),status   effective user name
			ruser[P_G_SZ],		// status          real user name
			suser[P_G_SZ],		// status          saved user name
			fuser[P_G_SZ],		// status          filesystem user name
			rgroup[P_G_SZ],		// status          real group name
			egroup[P_G_SZ],		// status          effective group name
			sgroup[P_G_SZ],		// status          saved group name
			fgroup[P_G_SZ],		// status          filesystem group name
			cmd[16];			// stat,status     basename of executable file in call to exec(2)
	struct proc_t *ring,		// n/a             thread group ring
			*next;				// n/a             various library uses
	int pgrp,					// stat            process group id
			session,			// stat            session id
			nlwp,				// stat,status     number of threads, or 0 if no clue
			tgid,				// (special)       task group ID, the POSIX PID (see also: tid)
			tty,				// stat            full device number of controlling terminal
			euid, egid, 	    // stat(),status   effective
			ruid, rgid, 	    // status          real
			suid, sgid, 	    // status          saved
			fuid, fgid, 	    // status          fs (used for file access only)
			tpgid,				// stat            terminal process group id
			exit_signal,		// stat            might not be SIGCHLD
			processor;      	// stat            current (or most recent?) CPU
} proc_t;

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#define PROCPATHLEN 64  // must hold /proc/2000222000/task/2000222000/cmdline

typedef struct PROCTAB {
	DIR* procfs;
	DIR* taskdir;  				// for threads
	pid_t taskdir_user;  		// for threads
	int did_fake; 				// used when taskdir is missing
	int (*finder)(struct PROCTAB * const, proc_t * const);
	proc_t* (*reader)(struct PROCTAB * const, proc_t * const);
	int (*taskfinder)(struct PROCTAB * const, const proc_t * const, proc_t * const, char * const);
	proc_t*(*taskreader)(struct PROCTAB * const, const proc_t * const, proc_t * const, char * const);
	pid_t* pids;				// pids of the procs
	uid_t* uids;				// uids of procs
	int nuid;					// cannot really sentinel-terminate unsigned short[]
	int i;  					// generic
	unsigned flags;
	unsigned u;  				// generic
	void * vp; 					// generic
	char path[PROCPATHLEN];  	// must hold /proc/2000222000/task/2000222000/cmdline
	unsigned pathlen;        	// length of string in the above (w/o '\0')
} PROCTAB;

typedef struct proc_data_t {
	proc_t **tab;
	proc_t **proc;
	proc_t **task;
	int n;
	int nproc;
	int ntask;
} proc_data_t;


PROCTAB* openproc(int flags, ... /* pid_t*|uid_t*|dev_t*|char* [, int n] */);

void closeproc(PROCTAB* PT);

proc_t* readproc(PROCTAB * const PT, proc_t * p);

void freeproc(proc_t* p);

void *xrealloc(void *oldp, unsigned int size) __attribute__ ((__malloc__));
void *xmalloc(unsigned int size) __attribute__ ((__malloc__));
void *xcalloc(void *pointer, int size) __attribute__ ((__malloc__));

char *user_from_uid(uid_t uid);
char *group_from_gid(gid_t gid);

unsigned long long getHertz(void);

#endif // Linux

#endif
