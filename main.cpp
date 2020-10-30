#include <iostream>
#include "form.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define random(x) (rand()%x)
using namespace std;
int main()
{
	FILE *fp;
    int64_t data[100];
    Form form;
    int number=1000;
    for(int i=0;i<100;i++){
        data[i]=number--;
    }

//form.properties(fp);
//form.insert(fp,data);
//form.select(fp,101);
//form.add_index(0);
form.select(fp,0,50,100);
    return 0;
}
