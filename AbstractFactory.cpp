#include <iostream>
#include <memory>

class Furniture {
    public:
    virtual std::string getName() const = 0;
};

class Sittable {};
class SittableAt {};

class SittableFurniture : public Sittable, public Furniture {};
class SittableAtFurniture : public SittableAt, public Furniture {};

class AbstractSofa : public SittableFurniture {};
class AbstractTable : public SittableAtFurniture {};
class AbstractChair : public SittableFurniture {};

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

class AbstractFactory {
    public:
    virtual std::unique_ptr<AbstractSofa> produceSofa() = 0;
    virtual std::unique_ptr<AbstractTable> produceTable() = 0;
    virtual std::unique_ptr<AbstractChair> produceChair() = 0;
};

class ModernFactory : public AbstractFactory {
    public:
    std::unique_ptr<AbstractSofa> produceSofa() override {
        return std::make_unique<ModernSofa>();
    }
    std::unique_ptr<AbstractTable> produceTable() override {
        return std::make_unique<ModernTable>();
    }
    std::unique_ptr<AbstractChair> produceChair() override {
        return std::make_unique<ModernChair>();
    }
};

class VictorianFactory : public AbstractFactory {
    public:
    std::unique_ptr<AbstractSofa> produceSofa() override {
        return std::make_unique<VictorianSofa>();
    }
    std::unique_ptr<AbstractTable> produceTable() override {
        return std::make_unique<VictorianTable>();
    }
    std::unique_ptr<AbstractChair> produceChair() override {
        return std::make_unique<VictorianChair>();
    }
};


class Person {
    std::string name;

    public:
    Person(std::string name) : name(name) {}
    
    void SitOn(SittableFurniture& seat) {
        std::cout << name << " sat down on the " << seat.getName() << '\n';
    }

    void SitAt(SittableAtFurniture& table) {
        std::cout << name << " sat at the " << table.getName() << '\n';
    }
};

void ClientCode(AbstractFactory& factory) {
    std::cout << "------Testing code------" << '\n';
    auto person = std::make_unique<Person>("Mike");
    person->SitOn(*factory.produceSofa());
    person->SitOn(*factory.produceChair());
    person->SitAt(*factory.produceTable());
}

int main() {
    std::unique_ptr<AbstractFactory> factory = std::make_unique<ModernFactory>();
    ClientCode(*factory);
    factory = std::make_unique<VictorianFactory>();
    ClientCode(*factory);
}