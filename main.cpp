#include <iostream>
#include <fstream>

#include "Byte.h"
#include "Blob.h"

int main(){
    auto blob = makeBlob(123);
    ((Byte*)&(blob[2]))->b5 = 1;

    blob.display();

    return 0;
}
