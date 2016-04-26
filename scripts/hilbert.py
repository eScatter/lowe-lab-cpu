from display.lines import (Turtle, Canvas, LSystem)
from display.pretty_term import (OutStream)

import sys

import numpy as np

def hilbert_permutation(n):
    if n == 0:
        return np.array([[0]])

    p = hilbert_permutation(n - 1)
    N = p.shape[0]
    M = p.size

    q = np.zeros(dtype=int, shape=(N*2, N*2)) 
    q[0:N, 0:N] += p.T

    p += M
    q[0:N, N:2*N] += p

    p += M
    q[N:2*N, N:2*N] += p

    p += M
    q[N:2*N, 0:N] += p[::-1, ::-1].T

    return q


if __name__ == '__main__':
    out = OutStream(sys.stdout)

    cx = Canvas(64, 64)
    cx.turtle.jump(0, 0, 0)
    cx.put(LSystem(
        '1', 
        {'1': '-2F+1F1+F2-',
         '2': '+1F-2F2-F1+'}).compute(6))
    ls = cx.render()

    for l in ls:
        out << l << '\n'

    for l in hilbert_permutation(4):
        print(''.join('{:4}'.format(i) for i in l))

