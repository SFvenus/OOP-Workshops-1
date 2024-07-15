#include "Bakery.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <sstream>

namespace seneca {

Bakery::Bakery(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open file");
    }

    std::string line;
    while (std::getline(file, line)) {
        BakedGood good;
        std::string typeStr = line.substr(0, 8);
        std::string descStr = line.substr(8, 20);
        std::string shelfLifeStr = line.substr(28, 14);
        std::string stockStr = line.substr(42, 8);
        std::string priceStr = line.substr(50, 6);

        // Trim whitespace
        typeStr.erase(0, typeStr.find_first_not_of(" \t\n\r\f\v"));
        typeStr.erase(typeStr.find_last_not_of(" \t\n\r\f\v") + 1);
        descStr.erase(0, descStr.find_first_not_of(" \t\n\r\f\v"));
        descStr.erase(descStr.find_last_not_of(" \t\n\r\f\v") + 1);
        shelfLifeStr.erase(0, shelfLifeStr.find_first_not_of(" \t\n\r\f\v"));
        shelfLifeStr.erase(shelfLifeStr.find_last_not_of(" \t\n\r\f\v") + 1);
        stockStr.erase(0, stockStr.find_first_not_of(" \t\n\r\f\v"));
        stockStr.erase(stockStr.find_last_not_of(" \t\n\r\f\v") + 1);
        priceStr.erase(0, priceStr.find_first_not_of(" \t\n\r\f\v"));
        priceStr.erase(priceStr.find_last_not_of(" \t\n\r\f\v") + 1);

        good.type = (typeStr == "Bread") ? BakedType::BREAD : BakedType::PASTERY;
        good.description = descStr;
        good.shelfLife = std::stoi(shelfLifeStr);
        good.stock = std::stoi(stockStr);
        good.price = std::stod(priceStr);

        goods.push_back(good);
    }
}

void Bakery::showGoods(std::ostream& os) const {
    std::for_each(goods.begin(), goods.end(), [&os](const BakedGood& b) {
        os << b << std::endl;
    });

    int totalStock = std::accumulate(goods.begin(), goods.end(), 0, [](int sum, const BakedGood& b) {
        return sum + b.stock;
    });

    double totalPrice = std::accumulate(goods.begin(), goods.end(), 0.0, [](double sum, const BakedGood& b) {
        return sum + b.price;
    });

    os << "Total Stock: " << totalStock << std::endl;
    os << "Total Price: " << std::fixed << std::setprecision(2) << totalPrice << std::endl;
}

void Bakery::sortBakery(const std::string& field) {
    if (field == "Description") {
        std::sort(goods.begin(), goods.end(), [](const BakedGood& a, const BakedGood& b) {
            return a.description < b.description;
        });
    } else if (field == "Shelf") {
        std::sort(goods.begin(), goods.end(), [](const BakedGood& a, const BakedGood& b) {
            return a.shelfLife < b.shelfLife;
        });
    } else if (field == "Stock") {
        std::sort(goods.begin(), goods.end(), [](const BakedGood& a, const BakedGood& b) {
            return a.stock < b.stock;
        });
    } else if (field == "Price") {
        std::sort(goods.begin(), goods.end(), [](const BakedGood& a, const BakedGood& b) {
            return a.price < b.price;
        });
    }
}

std::vector<BakedGood> Bakery::combine(const Bakery& other) const {
    std::vector<BakedGood> combined(goods);
    combined.insert(combined.end(), other.goods.begin(), other.goods.end());

    std::sort(combined.begin(), combined.end(), [](const BakedGood& a, const BakedGood& b) {
        return a.price < b.price;
    });

    return combined;
}

bool Bakery::inStock(const std::string& description, BakedType type) const {
    auto it = std::find_if(goods.begin(), goods.end(), [&description, type](const BakedGood& b) {
        return b.description == description && b.type == type && b.stock > 0;
    });
    return it != goods.end();
}

std::list<BakedGood> Bakery::outOfStock(BakedType type) const {
    std::list<BakedGood> outOfStockItems;
    std::copy_if(goods.begin(), goods.end(), std::back_inserter(outOfStockItems), [type](const BakedGood& b) {
        return b.type == type && b.stock == 0;
    });
    return outOfStockItems;
}

std::ostream& operator<<(std::ostream& out, const BakedGood& b) {
    out << "* " << std::setw(10) << std::left << (b.type == BakedType::BREAD ? "Bread" : "Pastry")
        << " * " << std::setw(20) << b.description
        << " * " << std::setw(5) << b.shelfLife
        << " * " << std::setw(5) << b.stock
        << " * " << std::setw(8) << std::right << std::fixed << std::setprecision(2) << b.price
        << " * ";
    return out;
}

} // namespace seneca
