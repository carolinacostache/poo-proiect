#include <iostream>
#include <string>
#include <vector>

class SkinCareProduct {
private:
    std::string productName;
    double productPrice = 0.0;

public:
    SkinCareProduct() = default;

    SkinCareProduct(const std::string& productName, double productPrice)
            : productName(productName), productPrice(productPrice) {}


    SkinCareProduct(const SkinCareProduct& other)
            : productName(other.productName), productPrice(other.productPrice) {}


    SkinCareProduct& operator=(const SkinCareProduct& other);


    ~SkinCareProduct();

    const std::string& getProductName() const {
        return productName;
    }

    double getProductPrice() const {
        return productPrice;
    }

    void displayProduct() const;

    friend std::ostream& operator<<(std::ostream& out, const SkinCareProduct& product);
};

class ShoppingCart {
private:
    static const int maxCapacity = 10;
    std::vector<SkinCareProduct> cartProducts;

public:
    ShoppingCart() = default;

    void addProduct(const SkinCareProduct& product);

    void displayCart() const;

    friend std::ostream& operator<<(std::ostream& out, const ShoppingCart& cart);
};

class SkinCareStore {
private:
    static const int maxStockCapacity = 400;
    std::string storeName;
    float storeReview = 0.0;
    std::vector<SkinCareProduct> storeStock;

public:
    SkinCareStore() = default;

    SkinCareStore(const std::string& storeName, float storeReview)
            : storeName(storeName), storeReview(storeReview) {}


    SkinCareStore(const SkinCareStore& other);


    SkinCareStore& operator=(const SkinCareStore& other);


    ~SkinCareStore();

    const std::string& getStoreName() const {
        return storeName;
    }

    float getStoreReview() const {
        return storeReview;
    }

    void addToStock(const SkinCareProduct& product);

    void displayAvailableProducts() const;

    friend std::ostream& operator<<(std::ostream& out, const SkinCareStore& store);
};


std::ostream& operator<<(std::ostream& out, const SkinCareProduct& product);


std::ostream& operator<<(std::ostream& out, const ShoppingCart& cart);


std::ostream& operator<<(std::ostream& out, const SkinCareStore& store);


void ShoppingCart::addProduct(const SkinCareProduct& product) {
    if (cartProducts.size() < maxCapacity) {
        cartProducts.push_back(product);
    } else {
        std::cout << "The shopping cart is full. Cannot add more products." << std::endl;
    }
}

void ShoppingCart::displayCart() const {
    if (cartProducts.empty()) {
        std::cout << "The shopping cart is empty." << std::endl;
    } else {
        std::cout << "Products in the cart:" << std::endl;
        for (const auto& product : cartProducts) {
            product.displayProduct();
        }
    }
}


SkinCareProduct& SkinCareProduct::operator=(const SkinCareProduct& other) {
    if (this != &other) {
        productName = other.productName;
        productPrice = other.productPrice;
    }
    return *this;
}

SkinCareProduct::~SkinCareProduct() {
    std::cout << "Destroyed SkinCareProduct: " << productName << std::endl;
}

void SkinCareProduct::displayProduct() const {
    std::cout << "Product Name: " << productName << ", Price: " << static_cast<float>(productPrice) << " lei;" << std::endl;
}


SkinCareStore::SkinCareStore(const SkinCareStore& other)
        : storeName(other.storeName), storeReview(other.storeReview), storeStock(other.storeStock) {}

SkinCareStore& SkinCareStore::operator=(const SkinCareStore& other) {
    if (this != &other) {
        storeName = other.storeName;
        storeReview = other.storeReview;
        storeStock = other.storeStock;
    }
    return *this;
}

SkinCareStore::~SkinCareStore() {
    std::cout << std::endl << storeName << " store called the destructor." << std::endl;
}

void SkinCareStore::addToStock(const SkinCareProduct& product) {
    if (storeStock.size() < maxStockCapacity) {
        storeStock.push_back(product);
    } else {
        std::cout << "No more space in the store!!!" << std::endl;
    }
}

void SkinCareStore::displayAvailableProducts() const {
    if (storeStock.empty()) {
        std::cout << "We will restock soon!" << std::endl;
    } else {
        std::cout << "Available products in the store " << storeName << " are:" << std::endl;
        for (const auto& product : storeStock) {
            product.displayProduct();
        }
    }
}


std::ostream& operator<<(std::ostream& out, const SkinCareProduct& product) {
    out << "Product Name: " << product.getProductName() << ", Price: " << product.getProductPrice() << " lei;";
    return out;
}


std::ostream& operator<<(std::ostream& out, const ShoppingCart& cart) {
    if (cart.cartProducts.empty()) {
        out << "The shopping cart is empty.";
    } else {
        out << "Products in the cart:" << std::endl;
        for (const auto& product : cart.cartProducts) {
            out << product << std::endl;
        }
    }
    return out;
}


std::ostream& operator<<(std::ostream& out, const SkinCareStore& store) {
    out << "Store Name: " << store.getStoreName() << std::endl;
    out << "Review Score: " << store.getStoreReview() << std::endl;
    out << "Number of products in stock: " << store.storeStock.size() << std::endl;
    for (const auto& product : store.storeStock) {
        out << product << std::endl;
    }
    return out;
}


int main() {
    SkinCareStore store("Fenty Skin", 4.8);
    SkinCareProduct product1("Facial Cleansing Gel", 76.99);
    SkinCareProduct product2("Moisturizing Cream", 82.99);
    SkinCareProduct product3("Eye Cream", 56.99);

    store.addToStock(product1);
    store.addToStock(product2);
    store.addToStock(product3);

    ShoppingCart cart;
    cart.addProduct(product2);
    cart.addProduct(product3);

    std::cout << "Welcome to " << store.getStoreName() << " with a rating of " << store.getStoreReview() << "!" << std::endl;
    std::cout << "Available products in the store are:" << std::endl;
    store.displayAvailableProducts();

    std::cout << "The initial shopping cart is empty." << std::endl;
    cart.displayCart();

    std::cout << store;

    return 0;
}
