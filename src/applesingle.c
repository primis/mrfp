#include <stdio.h>
#include <endian.h>

#include "internal.h"
#include "applesingle.h"

int32_t mrfp_find_resource_offset(mrfp_resource_t resource)
{
    mrfp_internal_t *state = get_state(resource);

    applesingle_header_t header;
    applesingle_entry_header_t entry;
    uint32_t file_type;

    fseek(state->fp, 0, SEEK_SET);
    fread(&file_type, sizeof(int32_t), 1, state->fp);

    // Convert to host from big endian, everything in mac land is big endian...
    // If the first 4 bytes match the magic number for appledouble or for
    // applesingle file formats, then we have an offset, otherwise it's a raw
    // resource file (very unlikely to exist outside of reading the fork direct)
    switch(be32toh(file_type))
    {
        case APPLESINGLE_SIGNATURE:
        case APPLEDOUBLE_SIGNATURE:
            break;
        default:
            return 0;
    }

    fseek(state->fp, 0, SEEK_SET); // Rewind file
    fread(&header, sizeof(header), 1, state->fp);
    
    // Next bytes out should be the first file header.
    // We step through the files until we hit the resource one.
    header.numEntries = be16toh(header.numEntries);
    while(header.numEntries-- > 0) {
        fread(&entry, sizeof(entry), 1, state->fp);
        if(be32toh(entry.entryID) == APPLESINGLE_RESOURCE_FORK) {
            return be32toh(entry.offset);
        }
    }

    // No resource file found! 
    return -1;
}
