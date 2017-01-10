#ifndef BYTE_HEADER
#define BYTE_HEADER

typedef unsigned char uchar;

struct Byte{
    uchar b0: 1;
    uchar b1: 1;
    uchar b2: 1;
    uchar b3: 1;
    uchar b4: 1;
    uchar b5: 1;
    uchar b6: 1;
    uchar b7: 1;



    Byte(){}

    template<typename T>
    Byte(const T& x){
        *(uchar*)this = (const uchar)x;
    }



    operator char() const{
        return *(char*)this;
    }

    operator unsigned char() const{
        return *(uchar*)this;
    }

    operator int() const{
        return (int)(uchar)(*this);
    }
};

#endif
