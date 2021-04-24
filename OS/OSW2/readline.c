#include "readline.h"

int read_line (char * str){
      fgets(str, 100, stdin);
      int size =  strlen(str)-1;
      return size > 0 ? size : -1;
}
