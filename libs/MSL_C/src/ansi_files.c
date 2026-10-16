// Imported from SMGCommunity/Petari (CC0), src/MSL_C/ansi_files.c
#include "file_struct.h"
#include "ansi_files.h"
#include "console_io.h"
#include "cstdlib"

#pragma exceptions on

FILE __files[4] =
{
    {
        0,
        {
            must_exist,
            1,
            1,
            file_console,
            file_unoriented,
            0
        },

        {
            neutral,
            0,
            0,
            0
        },

        0,
        0,
        0,
        {0, 0},
        {0, 0},
        0,
        stdin_buff,
        0x100,
        stdin_buff,
        0,
        0,
        0,
        0,
        0,
        __read_console,
        __write_console,
        __close_console,
        0,
        &__files[1]
    },

    {
        1,
        {	
            must_exist,
            2,
            1,
            file_console,
            file_unoriented,
            0
        },
    
        {
            neutral,
            0,
            0,
            0
        },

        0,
        0,
        0,
        {0, 0},
        {0, 0},
        0,
        stdout_buff,
        0x100,
        stdout_buff,
        0,
        0,
        0,
        0,
        0,
        __read_console,
        __write_console,
        __close_console,
        0,
        &__files[2]
    },

    {
        2,
        {
            must_exist,
            2,	
            0,
            file_console,
            file_unoriented,
            0
        },

        {
            neutral,
            0,
            0,
            0
        },

        0,
        0,
        0,
        {0, 0},
        {0, 0},
        0,
        stderr_buff,
        0x100,
        stderr_buff,
        0,
        0,
        0,
        0,
        0,
        __read_console,
        __write_console,
        __close_console,
        0,
        &__files[3]
    },

    {
        0,
        {	
            0,
            0,
            0,
            0,
            0,
            0
        },
    
        {
            0,
            0,
            0,
            0
        },

        0,
        0,
        0,
        {0, 0},
        {0, 0},
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    }
};

void __close_all(void) {
    FILE* file = &__files[0];
    FILE* lastFile;

    while (file != 0) {
        if (file->mode.file != file_closed) {
            fclose(file);
        }

        lastFile = file;
        file = file->next_file;

        if (lastFile->is_dyn_alloc) {
            free(lastFile);
        }
        else {
            lastFile->mode.file = file_unavailable;

            if ((file != 0) && (file->is_dyn_alloc)) {
                lastFile->next_file = 0;
            }
        }
    }
}

// Not in the imported source: written from the original binary.
int __flush_line_buffered_output_files(void) {
    int res = 0;
    FILE* file = &__files[0];

    while (file != 0) {
        if (file->mode.file != file_closed && (file->mode.buffer & 1) && file->state.io_state == writing) {
            if (fflush(file)) {
                res = -1;
            }
        }

        file = file->next_file;
    }

    return res;
}

int __flush_all(void) {
    int res = 0;
    FILE* file = &__files[0];

    while (file != 0) {
        if (file->mode.file != file_closed) {
            if (fflush(file)) {
                res = -1;
            }
        }

        file = file->next_file;
    }

    return res;
}
