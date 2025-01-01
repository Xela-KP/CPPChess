
#include "state.hpp"
#include "encodings.hpp"
#include "mask.hpp"
namespace movement
{
    int get_num_attackers_on(int square, int color)
    {
        int num_attackers = 0;
        num_attackers +=
            (state::pawn_attack_mask[!color][square] &
             state::piece_occupancies[color ? chess::p : chess::P])
                ? 1
                : 0;
        num_attackers +=
            (state::knight_attack_mask[square] &
             state::piece_occupancies[color ? chess::n : chess::N])
                ? 1
                : 0;
        num_attackers +=
            (state::king_attack_mask[square] &
             state::piece_occupancies[color ? chess::k : chess::K])
                ? 1
                : 0;
        num_attackers +=
            (mask::get_bishop_attack_mask(square, state::side_occupancies[chess::BOTH]) &
             state::piece_occupancies[color ? chess::b : chess::B])
                ? 1
                : 0;
        num_attackers +=
            (mask::get_rook_attack_mask(square, state::side_occupancies[chess::BOTH]) &
             state::piece_occupancies[color ? chess::r : chess::R])
                ? 1
                : 0;
        num_attackers +=
            (mask::get_queen_attack_mask(square, state::side_occupancies[chess::BOTH]) &
             state::piece_occupancies[color ? chess::q : chess::Q])
                ? 1
                : 0;
        return num_attackers;
    }

    int get_moves()
    {
    }
}