#pragma inline
#include <stdio.h>
#include <signal.h>
#include <limits.h>
#ifdef __cplusplus
   typedef void (*fptr)(int);
#else
   typedef void (*fptr)();
#endif
void Catcher(int *reglist)
{
//   signal(SIGFPE, (fptr)Catcher);  //  ******reinstall signal handler
   printf("Caught it!\n"); *(reglist + 8) = 3; /* make return AX = 3 */
}
int main(void)
{
	int a = 0;
   signal(SIGABRT, (fptr)Catcher);  /* cast Catcher to appropriate type */
//   asm     mov     ax,07FFFH       /* AX = 32767 */
//   asm     inc     ax              /* cause overflow */
//   asm     into                    /* activate handler */
   /* The handler set AX to 3 on return. If that had not happened,
      there would have been another exception when the next 'into'
      executed after the 'dec' instruction. */
//   asm     dec     ax              /* no overflow now */
//   asm     into                    /* doesn't activate */
	a = INT_MAX + INT_MAX;
	printf ( "over %d", a);
   return 0;
}
