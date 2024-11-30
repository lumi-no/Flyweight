#include <iostream>
#include <unordered_map>
#include <string>

class Flyweight {
private:
    std::string sharedState_; 

public:
    Flyweight(const std::string& sharedState) : sharedState_(sharedState) {}

    void Operation(const std::string& uniqueState) const {
        std::cout << "Flyweight: ������� (" << sharedState_
            << ") �� ��������� (" << uniqueState
            << ") �����.\n";
    }

    std::string GetSharedState() const {
        return sharedState_;
    }
};

class FlyweightFactory {
private:
    std::unordered_map<std::string, Flyweight> flyweights_; 

    std::string GetKey(const std::string& sharedState) const {
        return sharedState;
    }

public:
    FlyweightFactory(std::initializer_list<std::string> sharedStates) {
        for (const auto& state : sharedStates) {
            flyweights_.emplace(state, Flyweight(state));
        }
    }

    Flyweight& GetFlyweight(const std::string& sharedState) {
        std::string key = GetKey(sharedState);
        if (flyweights_.find(key) == flyweights_.end()) {
            std::cout << "FlyweightFactory: ��������� ������ ������������� ��� ����� \""
                << sharedState << "\".\n";
            flyweights_.emplace(key, Flyweight(sharedState));
        }
        else {
            std::cout << "FlyweightFactory: ������������ ��������� ������������� ��� ����� \""
                << sharedState << "\".\n";
        }
        return flyweights_.at(key);
    }

    void ListFlyweights() const {
        std::cout << "FlyweightFactory: � ��� ����� " << flyweights_.size()
            << " �������������.\n";
        for (const auto& pair : flyweights_) {
            std::cout << "  - " << pair.first << "\n";
        }
    }
};

void AddCar(FlyweightFactory& factory, const std::string& sharedState, const std::string& uniqueState) {
    std::cout << "��������� ��������� � ��������� ������: \"" << uniqueState << "\".\n";
    Flyweight& flyweight = factory.GetFlyweight(sharedState);
    flyweight.Operation(uniqueState);
}

int main() {
    FlyweightFactory factory({ "Toyota", "BMW", "Audi" });

    factory.ListFlyweights();

    std::cout << "\n�볺��: ������ ��� ��������:\n";
    AddCar(factory, "Toyota", "��������, AB123CD");
    AddCar(factory, "BMW", "����, XY456EF");
    AddCar(factory, "Toyota", "������, GH789IJ");

    std::cout << "\n�볺��: ������ ������������� � �������:\n";
    factory.ListFlyweights();

    return 0;
}
