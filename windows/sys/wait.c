#include "wait.h"
#include <windows.h>

int waitpid(int pid, int *status, int options) {
   const HANDLE hProcess = OpenProcess(0x0400 | 0x0010, FALSE, pid);
   WaitForSingleObject(hProcess, INFINITE);
   CloseHandle(hProcess);
   return pid;
}
