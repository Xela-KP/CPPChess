#pragma once
namespace chess
{
    enum Piece
    {
        P,
        N,
        B,
        R,
        Q,
        K,
        p,
        n,
        b,
        r,
        q,
        k
    };
    enum Color
    {
        WHITE,
        BLACK,
        BOTH
    };
    enum SlidingPiece
    {
        ROOK,
        BISHOP
    };
    const char ASCII_PIECES[12] = {'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k'};
    const int ASCII_INT[256] = {
        ['P'] = P,
        ['N'] = N,
        ['B'] = B,
        ['R'] = R,
        ['Q'] = Q,
        ['K'] = K,
        ['p'] = p,
        ['n'] = n,
        ['b'] = b,
        ['r'] = r,
        ['q'] = q,
        ['k'] = k};
    const char PROMOTED_PIECE[] = {
        [Q] = 'q',
        [R] = 'r',
        [B] = 'b',
        [N] = 'n',
        [q] = 'q',
        [r] = 'r',
        [b] = 'b',
        [n] = 'n'};
    const std::string SQUARE_TO_ALGEBRAIC_NOTATION[64] = {
        "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
        "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
        "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
        "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
        "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
        "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
        "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
        "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"};
    enum Square
    {
        a8,
        b8,
        c8,
        d8,
        e8,
        f8,
        g8,
        h8,
        a7,
        b7,
        c7,
        d7,
        e7,
        f7,
        g7,
        h7,
        a6,
        b6,
        c6,
        d6,
        e6,
        f6,
        g6,
        h6,
        a5,
        b5,
        c5,
        d5,
        e5,
        f5,
        g5,
        h5,
        a4,
        b4,
        c4,
        d4,
        e4,
        f4,
        g4,
        h4,
        a3,
        b3,
        c3,
        d3,
        e3,
        f3,
        g3,
        h3,
        a2,
        b2,
        c2,
        d2,
        e2,
        f2,
        g2,
        h2,
        a1,
        b1,
        c1,
        d1,
        e1,
        f1,
        g1,
        h1,
        NO_SQUARE
    };
    enum CastlePrivelage
    {
        NO_CASTLE = 0,
        wk = 1,
        wq = 2,
        bk = 4,
        bq = 8
    };
}