

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
    inline int DecodeTargetSquare() const;
    inline int DecodeSourceSquare() const;
    inline int DecodePiece() const;
    inline int DecodePromotionPiece() const ;
    inline int DecodeCaptureFlag() const;
    inline int DecodeDoublePawnPushFlag() const;
    inline int DecodeEnpassantFlag() const;
    inline int DecodeCastleFlag() const;
private:
    int encoding;
};