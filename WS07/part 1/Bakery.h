#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <string>
#include <vector>
#include <iostream>

namespace seneca {

enum class BakedType {
    BREAD, PASTRY
};

struct BakedGood {
    BakedType type;
    std::string description;
    int shelfLife;
    int stock;
    double price;
};

class Bakery {
    std::vector<BakedGood> goods;

public:
    Bakery(const std::string& filename);
    void showGoods(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& out, const BakedGood& b);

} // namespace seneca

#endif // SENECA_BAKERY_H
