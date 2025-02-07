

class Move
{
public:
    Move(int source_square, int target_square, int piece,
         int promotion_piece, int is_capture,
         int is_double_pawn_push, int is_enpassant, int is_castle);
    inline operator int() const;
    int Encode(int source_square, int target_square, int piece,
               int promotion_piece, int is_capture,
               int is_double_pawn_push, int is_enpassant, int is_castle);
    inline int DecodeTargetSquare(Move move) const { return (move & 0xfc0) >> 6; }
    inline int DecodeSourceSquare(Move move) const { return move & 0x3f; }
    inline int DecodePiece(Move move) const { return (move & 0xf000) >> 12; }
    inline int DecodePromotionPiece(Move move) const { return (move & 0xf0000) >> 16; }
    inline int DecodeCaptureFlag(Move move) const { return move & 0x100000; }
    inline int DecodeDoublePawnPushFlag(Move move) const { return move & 0x200000; }
    inline int DecodeEnpassantFlag(Move move) const { return move & 0x400000; }
    inline int DecodeCastleFlag(Move move) const { return move & 0x800000; }
private:
    int encoding;
};