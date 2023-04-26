#include <iostream>
#include <string>
#include <cassert>

// Абстрактный класс блюда
class Dish {
public:
    virtual ~Dish() {}
    virtual std::string getName() const = 0;
    virtual double getPrice() const = 0;
};

// Конкретные классы блюд
class Breakfast : public Dish {
public:
    std::string getName() const override { return "Breakfast"; }
    double getPrice() const override { return 10.0; }
};

class Lunch : public Dish {
public:
    std::string getName() const override { return "Lunch"; }
    double getPrice() const override { return 15.0; }
};

// Абстрактная фабрика
class AbstractDishFactory {
public:
    virtual ~AbstractDishFactory() {}
    virtual Dish* createDish() = 0;
};

// Конкретные фабрики
class BreakfastFactory : public AbstractDishFactory {
public:
    Dish* createDish() override { return new Breakfast(); }
};

class LunchFactory : public AbstractDishFactory {
public:
    Dish* createDish() override { return new Lunch(); }
};

// Декораторы
class DishDecorator : public Dish {
public:
    DishDecorator(Dish* dish) : m_dish(dish) {}
    virtual ~DishDecorator() { delete m_dish; }
    std::string getName() const override { return m_dish->getName(); }
    double getPrice() const override { return m_dish->getPrice(); }
protected:
    Dish* m_dish;
};

class CheeseDecorator : public DishDecorator {
public:
    CheeseDecorator(Dish* dish) : DishDecorator(dish) {}
    std::string getName() const override { return m_dish->getName() + ", with cheese"; }
    double getPrice() const override { return m_dish->getPrice() + 2.5; }
};

class VegetableDecorator : public DishDecorator {
public:
    VegetableDecorator(Dish* dish) : DishDecorator(dish) {}
    std::string getName() const override { return m_dish->getName() + ", with vegetables"; }
    double getPrice() const override { return m_dish->getPrice() + 1.5; }
};

// Заказ в ресторане
class RestaurantOrder {
public:
    RestaurantOrder(AbstractDishFactory* breakfastFactory, AbstractDishFactory* lunchFactory) :
        m_breakfastFactory(breakfastFactory), m_lunchFactory(lunchFactory) {}
    ~RestaurantOrder() { delete m_breakfastFactory; delete m_lunchFactory; }

    // Заказ блюда со сыром
    Dish* orderDishWithCheese() {
        Dish* dish = m_breakfastFactory->createDish();
        dish = new CheeseDecorator(dish);
        return dish;
    }

    // Заказ блюда with vegetables
    Dish* orderDishWithVegetables() {
        Dish* dish = m_lunchFactory->createDish();
        dish = new VegetableDecorator(dish);
        dish = new VegetableDecorator(dish);
        return dish;
    }

private:
    AbstractDishFactory* m_breakfastFactory;
    AbstractDishFactory* m_lunchFactory;
};

int main() {
    // Создание фабрик для Breakfastа и Lunchа
    AbstractDishFactory* breakfastFactory = new BreakfastFactory();
    AbstractDishFactory* lunchFactory = new LunchFactory();

    // Создание заказа в ресторане
    RestaurantOrder order(breakfastFactory, lunchFactory);

    // Заказ блюда со сыром
    Dish* dish1 = order.orderDishWithCheese();
    std::cout << "Dish 1: " << dish1->getName() << ", Price: " << dish1->getPrice() << std::endl;
    delete dish1;

    // Заказ блюда with vegetables
    Dish* dish2 = order.orderDishWithVegetables();
    std::cout << "Dish 2: " << dish2->getName() << ", Price: " << dish2->getPrice() << std::endl;
    delete dish2;

    delete breakfastFactory;
    delete lunchFactory;

    return 0;
}

void testBreakfast() {
    Breakfast breakfast;
    assert(breakfast.getName() == "Breakfast");
    assert(breakfast.getPrice() == 10.0);
}
void testLunch() {
    Breakfast breakfast;
    assert(breakfast.getName() == "Lunch");
    assert(breakfast.getPrice() == 15.0);
}