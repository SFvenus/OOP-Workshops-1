#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <string>
#include <vector>
#include <iostream>
#include <list>

namespace seneca {

enum class BakedType {
    BREAD, PASTERY
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
    void sortBakery(const std::string& field);
    std::vector<BakedGood> combine(const Bakery& other) const;
    bool inStock(const std::string& description, BakedType type) const;
    std::list<BakedGood> outOfStock(BakedType type) const;
};

std::ostream& operator<<(std::ostream& out, const BakedGood& b);

} // namespace seneca

#endif // SENECA_BAKERY_H
