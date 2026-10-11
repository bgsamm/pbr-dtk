// Imported from SMGCommunity/Petari (CC0), src/MSL_C/buffer_io.c
#include "file_struct.h"

#pragma exceptions on

void __prep_buffer(FILE *pFile) {
    pFile->buffer_ptr = pFile->buffer;
    pFile->buffer_len = pFile->buffer_size;
    pFile->buffer_len -= pFile->pos & pFile->buffer_alignment;
    pFile->buffer_pos = pFile->pos;
}

// Not in the imported source: written from the original binary.
int __load_buffer(FILE* file, size_t* bytes_loaded, int alignment) {
    int ioresult;

    file->buffer_ptr = file->buffer;
    file->buffer_len = file->buffer_size - (file->pos & file->buffer_alignment);
    file->buffer_pos = file->pos;

    if (alignment == 1) {
        file->buffer_len = file->buffer_size;
    }

    ioresult = (*file->read_proc)(file->handle, file->buffer, (size_t*)&file->buffer_len, file->ref);

    if (ioresult == 2) {
        file->buffer_len = 0;
    }

    if (bytes_loaded) {
        *bytes_loaded = file->buffer_len;
    }

    if (ioresult) {
        return ioresult;
    }

    file->pos += file->buffer_len;

    if (!file->mode.binary) {
        unsigned char* p = file->buffer;
        unsigned long i;

        for (i = file->buffer_len; i != 0; i--) {
            if (*p++ == '\n') {
                file->pos++;
            }
        }
    }

    return 0;
}

int __flush_buffer(FILE *pFile, size_t *pFlushed) {
    size_t len;
    int res;

    len = pFile->buffer_ptr - pFile->buffer;

    if (len != 0) {
        pFile->buffer_len = len;

        res = (*pFile->write_proc)(pFile->handle, pFile->buffer, (size_t*)&pFile->buffer_len, pFile->ref);
    
        if (pFlushed != 0) {
            *pFlushed = pFile->buffer_len;
        }

        if (res != 0) {
            return res;
        }

        pFile->pos += pFile->buffer_len;
    }

    __prep_buffer(pFile);
    return 0;
}
