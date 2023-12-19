#include "card.h"

bool operator<(card c1, card c2)
{ return static_cast<int>(c1) < static_cast<int>(c2); }

bool operator>(card c1, card c2)
{ return static_cast<int>(c1) > static_cast<int>(c2); }

card to_card(char c)
{
    if (std::isdigit(c))
        return static_cast<card>(c);
    switch (c) {
        case 'T': return card::T;
        case 'J': return card::J;
        case 'Q': return card::Q;
        case 'K': return card::K;
        case 'A': return card::A;
        default:
                  throw std::invalid_argument("unknown card number");
    }
}
