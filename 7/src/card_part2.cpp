#include "card_part2.h"

bool operator<(card_part2 c1, card_part2 c2)
{ return static_cast<char>(c1) < static_cast<char>(c2); }

bool operator>(card_part2 c1, card_part2 c2)
{ return static_cast<char>(c1) > static_cast<char>(c2); }

card_part2 to_card_part2(char c)
{
    if (std::isdigit(c))
        return static_cast<card_part2>(c);
    switch (c) {
        case 'T': return card_part2::T;
        case 'J': return card_part2::J;
        case 'Q': return card_part2::Q;
        case 'K': return card_part2::K;
        case 'A': return card_part2::A;
        default:
                  throw std::invalid_argument("unknown card number");
    }
}
