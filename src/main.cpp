#include "server.hpp"


int main(int ac, char **av)
{
    if (ac != 3)
        exit(1);
    server sv(av[1], av[2]);
    sv.server_init();
}