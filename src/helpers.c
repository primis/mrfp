#include <stdint.h>
#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "resource.h"
#include "internal.h"
#include "applesingle.h"
#include "mrfp.h"

mrfp_internal_t *get_state(mrfp_resource_t resource)
{
    return (mrfp_internal_t *)resource;
}

int32_t mrfp_data_offset(mrfp_resource_t resource)
{
    return get_state(resource)->header.dataOffset;
}

int32_t mrfp_data_size(mrfp_resource_t resource)
{
    return get_state(resource)->header.dataSize;
}

int32_t mrfp_map_offset(mrfp_resource_t resource)
{
    return get_state(resource)->header.mapOffset;
}

int32_t mrfp_map_size(mrfp_resource_t resource)
{
    return get_state(resource)->header.mapSize;
}

void mrfp_seek(mrfp_resource_t resource, int32_t offset)
{
    mrfp_internal_t *state = get_state(resource);
    fseek(state->fp, state->base_offset + offset, SEEK_SET);
}

mrfp_resource_t mrfp_resource_file_close(mrfp_resource_t resource)
{
    mrfp_internal_t *state = get_state(resource);
    fclose(state->fp);
    free(state);
    return NULL;
}

mrfp_resource_t mrfp_resource_file_open(char* filename)
{
    mrfp_internal_t *state = malloc(sizeof(mrfp_internal_t));
    resource_header_t temp_header;

    state->fp = fopen(filename, "r");
    if(state->fp == NULL) {
        return mrfp_resource_file_close(state);
    }

    state->base_offset = mrfp_find_resource_offset(state);
    if(state->base_offset == -1) {
        return mrfp_resource_file_close(state);
    }

    mrfp_seek(state, 0);
    fread(&temp_header, sizeof(temp_header), 1, state->fp);
    
    state->header.dataOffset = be32toh(temp_header.dataOffset);
    state->header.dataSize = be32toh(temp_header.dataSize);
    state->header.mapOffset = be32toh(temp_header.mapOffset);
    state->header.mapSize = be32toh(temp_header.mapSize);

    mrfp_seek(state, state->header.mapOffset);
    fread(&temp_header, sizeof(temp_header), 1, state->fp);

    temp_header.dataOffset = be32toh(temp_header.dataOffset);
    temp_header.dataSize = be32toh(temp_header.dataSize);
    temp_header.mapOffset = be32toh(temp_header.mapOffset);
    temp_header.mapSize = be32toh(temp_header.mapSize);

    // Check the secondary header at the mapOffset location
    if(memcmp(&temp_header, &state->header, sizeof(temp_header))){
        return mrfp_resource_file_close(state);
    }

    return state;
}
