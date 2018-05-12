#include "signal.h"
#include <windows.h>

void kill(int pid, int signal) {
   const HANDLE hProcess = OpenProcess(0x0400 | 0x0010, FALSE, pid);
   TerminateProcess(pid, 0);
   CloseHandle(hProcess);
}
