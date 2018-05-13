#pragma once

#ifndef _SIGNAL_H
#define _SIGNAL_H

#define SIGTERM         15
#define SIGQUIT         14

void kill(int pid, int signal);

#endif _SIGNAL_H
