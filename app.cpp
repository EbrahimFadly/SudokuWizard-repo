#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <memory>

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf()
    }
    int opt;
    char *input_fname;
    while((opt = getopt(argc, argv, "f:")) != -1){
        if (opt == f)
        {
            input_fname = optarg;
        }else
        {
            print("error in the parameters format {-f input_file}");
            exit(1);
        }
    }

    return 0;
}
