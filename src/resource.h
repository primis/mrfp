#ifndef __RESOURCE_H
#define __RESOURCE_H

#include <stdint.h>

typedef struct __attribute__((__packed__))
{
    int32_t dataOffset;
    int32_t mapOffset;
    int32_t dataSize;
    int32_t mapSize;
} resource_header_t;

typedef struct __attribute__((__packed__))
{
    resource_header_t header;
    int32_t nextResourceMap;
    int16_t fileRef;
    int16_t attributes;
    int16_t nameListOffset;
} resource_map_t;

typedef struct __attribute__((__packed__))
{
    int32_t type;
    int16_t count;
    int16_t resourceListOffset;
} resource_type_t;

typedef struct __attribute__((__packed__))
{
    int16_t id;
    int16_t nameOffset;
    uint32_t dataOffsetAttribute;    // Combined attributes and data offset
    int32_t resourcePtr;
} resource_t;

#define RESOURCE_ATTR_SYSTEM    0x40
#define RESOURCE_ATTR_PURGEABLE 0x20
#define RESOURCE_ATTR_LOCKED    0x10
#define RESOURCE_ATTR_PROTECTED 0x08
#define RESOURCE_ATTR_PRELOAD   0x04
#define RESOURCE_ATTR_CHANGED   0x02
#define RESOURCE_ATTR_COMPRESS  0x01

#endif
