#ifndef REG_OPS_H
#define REG_OPS_H

#include "Arduino.h"

/* Set the value of register */
#define REGISTER_SET(addr, value)     \
  do {                                \
    (*((uint8_t *)(addr))) = value;   \
  } while(0);

/* Get the value of register */
#define REGISTER_GET(addr)  (*((uint8_t *)(addr)))

/* Set the bit of the given register */
#define REGISTER_BIT_SET(addr, value, bitnum)     \
  do {                                            \
    (*((uint8_t *)(addr))) &= ~(1 << bitnum);     \
    (*((uint8_t *)(addr))) |= (value << bitnum);  \
  } while(0);

/* Set the bit of the given register */
#define REGISTER_BIT_CLR(addr, bitnum)        \
  do {                                        \
    (*((uint8_t *)(addr))) &= ~(1 << bitnum); \
  } while(0);

#endif	/* REG_OPS_H */
