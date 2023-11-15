#include "shell.h"


char *_getenv(const char *name) {

	char **env = environ;
        char *env_var = *env;
        const char *name_ptr = name;
        char *equal_sign;
        char *value;
        int value_length;
	
	while (*env){

        while (*name_ptr && *env_var == *name_ptr) {
            env_var++;
            name_ptr++;
        }

        if (*name_ptr == '\0' && *env_var == '=') {
            
            equal_sign = env_var;
            while (*equal_sign != '\0') {
                if (*equal_sign == '=') {
                    
                    equal_sign++;

                    value_length = _strlen(equal_sign);
                    value = (char *)malloc(value_length + 1);
                    if (value == NULL) {
                        return NULL;
                    }
                    _strncpy(value, equal_sign, value_length);
                    value[value_length] = '\0';
                    return value;
                }
                equal_sign++;
            }
        }
        env++;
    }
    return NULL;
}
