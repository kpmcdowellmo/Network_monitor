#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

struct interfaces {
    char** interface_names;
    int num_interfaces;
};

struct interfaces* find_interfaces() {
  DIR *dir_ptr = opendir("/sys/class/net");
  struct interfaces* network_interfaces;
  if (dir_ptr != NULL) {
      int counter = 0;
      while(dir_ptr){
          dirent* child_dir;
          if((child_dir = readdir(dir_ptr)) != NULL){
              network_interfaces->interface_names[counter++] = child_dir->d_name;
          }
      }
      network_interfaces->num_interfaces = counter;
      return network_interfaces;
  } else {
    printf("Could not open net interfaces directory");
    exit(1);
  }
}