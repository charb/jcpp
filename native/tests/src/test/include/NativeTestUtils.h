#ifndef NATIVE_TEST
#define NATIVE_TEST

#include <stdarg.h>
#include <stdio.h>

#define PASS_TEST(m) logEnd(m, true); return 0;
#define FAIL_TEST(m) logEnd(m, false); return 1;

void logTitle(const char *message, ...);

void logInfo(const char * message, ...);

void logError(const char * message, ...);

void logEnd(const char * message, bool passed);

void logSection(const char * message, ...);

//TODO go through define and split them on several lines
#define ASSERT(R,E,TN) \
			if(R == E) { \
			} else { \
				FAIL_TEST(TN); \
			}

#define ASSERT_M(R,E,PM,EM,TN) if(R == E) { logInfo(PM); } else { logError(EM), FAIL_TEST(TN); }
#define ASSERT_EM(R,E,EM,TN) if(R == E) { } else { logError(EM), FAIL_TEST(TN); }
#define ASSERT_PM(R,E,PM,TN) if(R == E) { logInfo(PM) } else { FAIL_TEST(TN); }

#define ASSERT_NE(R,E,TN) if(R != E) { } else { FAIL_TEST(TN); }
#define ASSERT_NE_M(R,E,PM,EM,TN) if(R != E) { logInfo(PM); } else { logError(EM), FAIL_TEST(TN); }
#define ASSERT_NE_EM(R,E,EM,TN) if(R != E) { } else { logError(EM), FAIL_TEST(TN); }
#define ASSERT_NE_PM(R,E,PM,TN) if(R != E) { logInfo(PM) } else { FAIL_TEST(TN); }

#define ASSERT_TRUE(R,TN) if(R) { } else { FAIL_TEST(TN); }
#define ASSERT_TRUE_M(R,PM,EM,TN) if(R) { logInfo(PM); } else { logError(EM), FAIL_TEST(TN); }
#define ASSERT_TRUE_EM(R,EM,TN) if(R) { } else { logError(EM), FAIL_TEST(TN); }
#define ASSERT_TRUE_PM(R,PM,TN) if(R) { logInfo(PM) } else { FAIL_TEST(TN); }

#endif
