#include "shell.h"

void *safe_realloc(void *ptr, size_t old_size, size_t new_size) {
  void *new_ptr;
  size_t copy_size;
  
    if (new_size == 0) {
        /* If new size is 0, treat it as a free operation */
        free(ptr);
        return NULL;
    }

    new_ptr = malloc(new_size);
    if (new_ptr == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    /* Copy data from the old block to the new one */
    copy_size = (old_size < new_size) ? old_size : new_size;
    _memcpy(new_ptr, ptr, copy_size);

    /* Free the old block */
    free(ptr);

    return new_ptr;
}
