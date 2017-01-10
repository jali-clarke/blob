#ifndef BLOB_HEADER
#define BLOB_HEADER

#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

typedef unsigned char uchar;

template<size_t N>
class Blob{
private:
    uchar _blob[N];

public:
    uchar& operator[](size_t n){
        if(n > N){
            throw std::out_of_range("Blob[] - index out of range");
        }

        return _blob[n];
    }

    void display(const size_t begin = 0, const size_t end = N, std::ostream& os = std::cout){
        if(end > N){
            throw std::out_of_range("Blob::display - out of range");
        }

        if(begin > end){
            throw std::logic_error("Blob::display - beginning must be before end");
        }

        os << end - begin << " bytes starting from " << (void*)(_blob + begin) << " (hex):\n";

        os << std::hex << std::setfill('0');

        for(size_t i = begin; i < end; ++ i){
            os << std::setw(2) << (int)(_blob[i]) << ' ';
        }

        os << std::setfill(' ') << '\n' << std::dec;
    }

    template<typename T>
    void read(T& var, const size_t offset = 0) const{
        if(sizeof(T) + offset > N){
            throw std::out_of_range("Blob::read - out of range");
        }

        for(size_t i = 0; i < sizeof(T); ++ i){
            ((uchar*)&var)[i] = _blob[i + offset];
        }
    }

    template<typename T>
    T& read(const size_t offset = 0){
        if(sizeof(T) + offset > N){
            throw std::out_of_range("Blob::read (1-arg) - out of range");
        }

        return *(T*)(_blob + offset);
    }

    template<typename T>
    void write(const T& var, const size_t offset = 0){
        if(sizeof(T) + offset > N){
            throw std::out_of_range("Blob::write - out of range");
        }

        for(size_t i = 0; i < sizeof(T); ++ i){
            _blob[i + offset] = ((uchar*)&var)[i];
        }
    }

    void writeToStream(std::ostream& os) const{
        os.write((const char*)_blob, N);
    }

    void readFromStream(std::istream& is){
        is.read((char*)_blob, N);
    }

    size_t getSize() const{
        return N;
    }
};

template<typename T>
Blob<sizeof(T)>&& makeBlob(const T& var){
    Blob<sizeof(T)> blob;
    blob.write(var);
    return std::move(blob);
}

template<size_t M, size_t N>
Blob<M + N>&& concatBlobs(const Blob<M>& blobm, const Blob<N>& blobn){
    Blob<M + N> blobmn;
    blobmn.write(blobm, 0);
    blobmn.write(blobn, M);

    return std::move(blobmn);
}

template<size_t M, size_t N>
Blob<M + N>&& concatBlobs(Blob<M>&& blobm, const Blob<N>& blobn){
    Blob<M + N> blobmn;
    blobmn.write(std::move(blobm), 0);
    blobmn.write(blobn, M);

    return std::move(blobmn);
}

template<size_t M, size_t N>
Blob<M + N>&& concatBlobs(const Blob<M>& blobm, Blob<N>&& blobn){
    Blob<M + N> blobmn;
    blobmn.write(blobm, 0);
    blobmn.write(std::move(blobn), M);

    return std::move(blobmn);
}

template<size_t M, size_t N>
Blob<M + N>&& concatBlobs(Blob<M>&& blobm, Blob<N>&& blobn){
    Blob<M + N> blobmn;
    blobmn.write(std::move(blobm), 0);
    blobmn.write(std::move(blobn), M);

    return std::move(blobmn);
}

#endif
