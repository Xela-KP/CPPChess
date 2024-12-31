#include <iostream>
#include "../include/mask.cpp"
#include "../include/util.cpp"
#include "../include/fen.cpp"
int main()
{
    mask::map_slide_attacks();
    mask::map_leap_attacks();
    return 0;
}