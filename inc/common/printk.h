/* This file is part of the blessOS OS (GPL v2 or later), see LICENSE.html */

#ifndef PRINTK_H
#define PRINTK_H

#include <common/types.h>

#define KERN_SOH        "\001"
#define KERN_SOH_ASCII  '\001'

#define KERN_EMERG      KERN_SOH "0"
#define KERN_ALERT      KERN_SOH "1"
#define KERN_CRIT       KERN_SOH "2"
#define KERN_ERR        KERN_SOH "3"
#define KERN_WARNING    KERN_SOH "4"
#define KERN_NOTICE     KERN_SOH "5"
#define KERN_INFO       KERN_SOH "6"
#define KERN_DEBUG      KERN_SOH "7"

#define KERN_DEFAULT    KERN_SOH "d"

int printk_get_level(const char *buffer);

int vsprintf(char *buf, const char *fmt, va_list args);
int printk(const char *fmt, ...);

#endif // PRINTK_H
