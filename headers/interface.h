#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <dirent.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

struct network_interfaces {
  char **interface_names;
  int8_t num_interfaces;
};

// Function prototypes
void add_interface_name(struct network_interfaces *, const char *);
void free_interface_names(struct network_interfaces *);
void expand_interface_names(struct network_interfaces *);
struct network_interfaces find_interfaces();

#endif