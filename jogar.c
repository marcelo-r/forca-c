#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.cli.h"

int main() {
	srand( time(NULL) );
	if (menu() == 0) return 0;
	else return 1;
}
