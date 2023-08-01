#include <iostream>

enum class ProductType {A = 0, B, C};

class Product {
public:
    virtual void Show() = 0;
    virtual ~Product() = 0;
};

class ProductA : public Product {
public:
    void Show() override {
        std::cout << "ProductA" << std::endl;
    }
    ~ProductA() {
        std::cout << "~ProductA" << std::endl;
    }
};

class ProductB : public Product {
public:
    void Show() override {
        std::cout << "ProductB" << std::endl;
    }
    ~ProductB() {
        std::cout << "~ProductB" << std::endl;
    }
};

class ProductC : public Product {
public:
    void Show() override {
        std::cout << "ProductC" << std::endl;
    }
    ~ProductC() {
        std::cout << "~ProductC" << std::endl;
    }
};

class Factoy {
    Product* createProduct(ProductType type) {
        switch (type)
        {
        case ProductType::A:
            return new ProductA();
            break;
        case ProductType::B:
            return new ProductB();
            break;
        case ProductType::C:
            return new ProductC();
            break;
        default:
            return nullptr;
            break;
        }
    }
};