#include <iostream>
#include <memory>

// abstract furniture class
class Furniture {
    public:
    virtual std::string getName() const = 0;
};

// sittable interface
class Sittable {};
// sittable at interface
class SittableAt {};

// sittable furniture interface 
class SittableFurniture : public Sittable, public Furniture {};
// sittable at furniture interface
class SittableAtFurniture : public SittableAt, public Furniture {};

// abstract furniture classes
class AbstractSofa : public SittableFurniture {};
class AbstractChair : public SittableFurniture {};
class AbstractTable : public SittableAtFurniture {};

class ModernSofa : public AbstractSofa {
    public:
    std::string getName() const override { return "modern sofa"; }
};

class VictorianSofa : public AbstractSofa {
    public:
    std::string getName() const override { return "victorian sofa"; }
};

class ModernTable : public AbstractTable {
    public:
    std::string getName() const override { return "modern table"; }
};

class VictorianTable : public AbstractTable {
    public:
    std::string getName() const override { return "victorian table"; }
};

class ModernChair : public AbstractChair {
    public:
    std::string getName() const override { return "modern chair"; }
};

class VictorianChair : public AbstractChair {
    public:
    std::string getName() const override { return "victorian chair"; }
};

// abstract factory class
class AbstractFactory {
    public:
    virtual std::unique_ptr<AbstractSofa> produceSofa() const = 0;
    virtual std::unique_ptr<AbstractTable> produceTable() const = 0;
    virtual std::unique_ptr<AbstractChair> produceChair() const = 0;
};

class ModernFactory : public AbstractFactory {
    public:
    std::unique_ptr<AbstractSofa> produceSofa() const override {
        return std::make_unique<ModernSofa>();
    }
    std::unique_ptr<AbstractTable> produceTable() const override {
        return std::make_unique<ModernTable>();
    }
    std::unique_ptr<AbstractChair> produceChair() const override {
        return std::make_unique<ModernChair>();
    }
};

class VictorianFactory : public AbstractFactory {
    public:
    std::unique_ptr<AbstractSofa> produceSofa() const override {
        return std::make_unique<VictorianSofa>();
    }
    std::unique_ptr<AbstractTable> produceTable() const override {
        return std::make_unique<VictorianTable>();
    }
    std::unique_ptr<AbstractChair> produceChair() const override {
        return std::make_unique<VictorianChair>();
    }
};

// person class that interacts with furniture
class Person {
    std::string name;

    public:
    Person(std::string name) : name(name) {}
    
    void SitOn(SittableFurniture& seat) {
        std::cout << name << " sat down on the " << seat.getName() << '\n';
    }

    void SitAt(SittableAtFurniture& surface) {
        std::cout << name << " sat at the " << surface.getName() << '\n';
    }
};

void ClientCode(const AbstractFactory& factory) {
    std::cout << "------Testing code------" << '\n';
    auto person = std::make_unique<Person>("Mike");
    person->SitOn(*factory.produceSofa());
    person->SitOn(*factory.produceChair());
    person->SitAt(*factory.produceTable());
    std::cout << std::endl;
}

int main() {
    std::unique_ptr<AbstractFactory> factory = std::make_unique<ModernFactory>();
    ClientCode(*factory);
    factory = std::make_unique<VictorianFactory>();
    ClientCode(*factory);
}