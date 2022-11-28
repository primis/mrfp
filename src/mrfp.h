#ifndef __MRFP_H
#define __MRFP_H

#include <stdint.h>

typedef void* mrfp_resource_t;

extern int32_t mrfp_data_offset(mrfp_resource_t resource);
extern int32_t mrfp_data_size(mrfp_resource_t resource);

extern int32_t mrfp_map_offset(mrfp_resource_t resource);
extern int32_t mrfp_map_size(mrfp_resource_t resource);

extern mrfp_resource_t mrfp_resource_file_close(mrfp_resource_t resource);
extern mrfp_resource_t mrfp_resource_file_open(char* filename);

#endif
