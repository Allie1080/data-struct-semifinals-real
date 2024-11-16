#ifndef STACK_H
#define STACK_H

#include <string>

enum class Size {
    SMALL = 10,
    MEDIUM = 30,
    LARGE = 50
};

enum Type {
    NORMAL = -1,
    FIRE,
    WATER,
    GRASS
};

enum class TypeEffectivenessMultiplier {
    SAME_TYPE = 1,
    IMMUNE = 0,
    NORMAL = 1,
    VERY_EFFECTIVE = 2
};

class Health {
private:
    int _current;
    int _max;

public:
    Health();
    Health(int maxHealth);
    int getCurrent();
    constexpr int getMax() {return _max;};
    void decrease(int damage);
    void increase(int heal);
};

class Enemy {
private:
    std::string _name;
    Type _type;
    int _size;
    Health _health;
    int _attack;

public:
    Enemy();
    Enemy(Type type, Size size, int level, std::string name);
    constexpr Type getType() {return _type;};
    constexpr int getAttack () {return _attack;};
    constexpr int getCriticalHealth () {return _health.getMax() / 4;};
    constexpr int getMaxHealth () {return _health.getMax();};
    int getCurrentHealth ();
    std::string getName() const {return _name;};
    TypeEffectivenessMultiplier checkTypeEffectiveness(Type opposingType);
    std::string getStringTemp();
    bool isDefeated();
    int takeDamage(int damage, Type opposingType);
};

class Player {
private:
    std::string _name;
    Type _shieldingType;
    Health _health;
    int _attack;

public:
    Player();    
    Player(int maxHealth, Type shieldingType);    
    constexpr Type getType() {return _shieldingType;};
    constexpr int getAttack () {return _attack;};
    constexpr int getCriticalHealth () {return _health.getMax() / 4;};
    constexpr int getMaxHealth () {return _health.getMax();};
    int getCurrentHealth ();
    TypeEffectivenessMultiplier checkTypeEffectiveness (Type opposingType);
    std::string getStringTemp ();
    bool isDefeated ();
    int takeDamage (int damage, Type opposingType);
    void heal (int healAmount);


};

struct Action {
    std::string _type;
    int _value;
    Player* _playerTarget;
    Enemy* _enemyTarget;

    Action();

};


#endif // COMBAT_DATA_H
