#include "../main/command.hh"
#include "hilbert.hh"

#include <iostream>
#include <iomanip>

using namespace eScatter::numeric;

NdArray<size_t, 2> eScatter::numeric::hilbert_array(unsigned n)
{
    if (n == 0)
        return NdArray<size_t, 2>({1, 1}, 0);

    auto p = hilbert_array(n - 1);
    uint32_t N = p.shape()[0],
             M = p.size();

    NdArray<size_t, 2> q({2*N, 2*N}, 0);

    q.sub<0>(0,   N).sub<1>(0,   N) = p.transpose();

    p += M;
    q.sub<0>(0,   N).sub<1>(N, 2*N) = p;

    p += M;
    q.sub<0>(N, 2*N).sub<1>(N, 2*N) = p;

    p += M;
    q.sub<0>(N, 2*N).sub<1>(0,   N) = p.reverse<0>().reverse<1>().transpose();

    return q;
}


std::vector<size_t> eScatter::numeric::hilbert_walk(unsigned n)
{
    auto a = hilbert_array(n);
    std::vector<size_t> result(a.size());
    for (size_t i = 0; i < a.size(); ++i)
        result[a[i]] = i;
    return result;
}


template <typename T>
void write(NdArrayBase<T, 2> const &image)
{
    auto shape = image.shape();
    auto flat = image.cbegin();
    for (unsigned j = 0; j < shape[1]; ++j)
    {
        for (unsigned i = 0; i < shape[0]; ++i, ++flat)
        {
            std::cout << std::setw(4) << *flat << " ";
        }
        std::cout << "\n";
    }
}

Command cmd_hilbert("hilbert",
    "Computes an array of integers giving the walk of "
    "a Hilbert curve over a 16x16 grid.",
    [] (std::vector<std::string> const &args)
{
    NdArray<int, 2> b({10, 10});
    int cnt = 0;
    for (auto i = b.begin(); i != b.end(); ++i, ++cnt)
        *i = cnt;
    write(b.transpose());

    NdArray<int, 2> a({10, 10});
    a.sub<1>(0, 1) += 100;
    a.sub<0>(3, 7) += 10;
    a.sub<1>(0, 10, 2) += 1;
    write(a.reverse<1>().transpose()); //a.transpose().reverse<0>());

    auto hilbert = hilbert_array(4);
    std::cout << "shape : " << hilbert.shape()[0] << ", " << hilbert.shape()[1] << "\n";
    write(hilbert);
    return 0;
});

