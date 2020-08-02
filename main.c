#include "headers/interfaces.h"
#include "headers/init.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  printf("Attempting to find interfaces...\n");
  struct network_interfaces network_interfaces = find_interfaces();
  for (int i = 0; i < network_interfaces.num_interfaces; ++i) {
    printf("Interface Name: %s\n", network_interfaces.interface_names[i]);
  }
  free_interface_names(&network_interfaces);
  return 0;
}