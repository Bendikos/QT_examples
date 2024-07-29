#ifndef _BUZZ_H_
#define _BUZZ_H_

#include "public.h"
#include <REGX52.H>

sbit buzz=P2^5;

void Buzz_Times(unsigned char times);

#endif