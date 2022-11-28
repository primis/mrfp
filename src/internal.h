#ifndef __INTERNAL_H
#define __INTERNAL_H

#include <stdint.h>
#include <stdio.h>
#include "mrfp.h"
#include "resource.h"

typedef struct
{
    FILE *fp;
    int32_t base_offset;
    resource_header_t header;
} mrfp_internal_t;

void mrfp_seek(mrfp_resource_t resource, int32_t offset);
mrfp_internal_t *get_state(mrfp_resource_t resource);

#endif
