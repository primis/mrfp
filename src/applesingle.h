// Parses AppleSingle / AppleDouble Files to find the resource fork location

#ifndef __APPLESINGLE_H
#define __APPLESINGLE_H

#include "mrfp.h"
#include <stdint.h>

#define APPLESINGLE_SIGNATURE   0x00051600
#define APPLEDOUBLE_SIGNATURE   0x00051607

int32_t mrfp_find_resource_offset(mrfp_resource_t resource);

typedef struct __attribute__((__packed__))
{
    uint32_t magicNumber;
    uint32_t versionNumber;
    uint8_t  homeFS[16];
    uint16_t numEntries;
} applesingle_header_t;

typedef struct __attribute__((__packed__))
{
    uint32_t entryID;
    uint32_t offset;
    uint32_t length;
} applesingle_entry_header_t;

#define APPLESINGLE_DATA_FORK       1
#define APPLESINGLE_RESOURCE_FORK   2
#define APPLESINGLE_REAL_NAME       3
#define APPLESINGLE_COMMENT         4
#define APPLESINGLE_ICON_BW         5
#define APPLESINGLE_ICON_COLOR      6
#define APPLESINGLE_FILE_INFO       7
#define APPLESINGLE_FINDER_INFO     9

#endif
