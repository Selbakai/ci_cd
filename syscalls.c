// Minimal system calls implementation for ARM bare-metal
// This provides the missing functions for newlib linking

#include <errno.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

// Minimal implementations to satisfy linker

void _exit(int status) {
  (void)status;
  while (1)
    ; // Infinite loop for embedded systems
}

int _close(int file) {
  (void)file;
  return -1;
}

int _fstat(int file, struct stat *st) {
  (void)file;
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int file) {
  (void)file;
  return 1;
}

int _lseek(int file, int ptr, int dir) {
  (void)file;
  (void)ptr;
  (void)dir;
  return 0;
}

int _read(int file, char *ptr, int len) {
  (void)file;
  (void)ptr;
  (void)len;
  return 0;
}

char *_sbrk(int incr) {
  extern char end __asm("end");
  static char *heap_end;
  char *prev_heap_end;

  if (heap_end == 0)
    heap_end = &end;

  prev_heap_end = heap_end;
  heap_end += incr;

  return prev_heap_end;
}

int _write(int file, char *ptr, int len) {
  (void)file;
  (void)ptr;
  return len; // Pretend we wrote everything
}

int _kill(int pid, int sig) {
  (void)pid;
  (void)sig;
  errno = EINVAL;
  return -1;
}

int _getpid(void) { return 1; }

int _gettimeofday(struct timeval *tv, struct timezone *tz) {
  (void)tv;
  (void)tz;
  return 0;
}
