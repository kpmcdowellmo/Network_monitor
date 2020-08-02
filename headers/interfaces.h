#include <dirent.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

const int8_t INITIAL_SIZE = 1;

struct network_interfaces {
  char **interface_names;
  int8_t num_interfaces;
};

void add_interface_name(struct network_interfaces *interface_storage,
                        const char *interface_name) {
  interface_storage->interface_names[interface_storage->num_interfaces] =
      (char *)malloc(sizeof(char) * (strlen(interface_name) + 1));
  strcpy(
      interface_storage->interface_names[interface_storage->num_interfaces++],
      interface_name);
}

void free_interface_names(struct network_interfaces *interfaces) {
  int8_t end = INITIAL_SIZE;
  if (interfaces->num_interfaces > INITIAL_SIZE) {
    end = interfaces->num_interfaces;
  }
  for (int8_t i = 0; i < end; ++i) {
    free(interfaces->interface_names[i]);
  }
  free(interfaces->interface_names);
}

void expand_interface_names(struct network_interfaces *interfaces) {
  interfaces->interface_names =
      (char **)realloc(interfaces->interface_names,
                       (interfaces->num_interfaces + 1) * sizeof(char *));
}

struct network_interfaces find_interfaces() {
  struct if_nameindex *interface_ptr;
  struct network_interfaces interface_storage;
  interface_storage.interface_names =
      (char **)malloc(INITIAL_SIZE * sizeof(char *));
  interface_storage.num_interfaces = 0;
  interface_ptr = if_nameindex();

  for (struct if_nameindex *cpy = interface_ptr;
       cpy != NULL && cpy->if_name != NULL; ++cpy) {
    if (interface_storage.num_interfaces >= INITIAL_SIZE) {
      expand_interface_names(&interface_storage);
    }
    add_interface_name(&interface_storage, cpy->if_name);
  }

  if_freenameindex(interface_ptr);

  return interface_storage;
}