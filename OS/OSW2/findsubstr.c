#include "findsubstr.h"
int find_sub_string(const char *str, const char* sub){
if(strstr(str, sub) != NULL) {
    return 1;
}
return 0;
}
