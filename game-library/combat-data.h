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
    void decrease(int damageAmount);
    void increase(int healedAmount);
};

class Mana {
private:
    int _current;
    int _max;

public:
    Mana ();
    Mana (int maxMana);
    int getCurrent();
    constexpr int getMax () {return _max;};
    void decrease (int consumedAmount);
    void increase (int regainedAmount);
};

class Spell {
private:
    std::string _name;
    int _cost;

public:
    Spell ();
    Spell (std::string name, int cost);
    std::string getName () const {return _name;};
    constexpr int getCost () {return _cost;};
    std::string getLabel () const;

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
    int getCurrentHealth () {return _health.getCurrent();};
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
    Mana _mana;
    int _manaRegainAmount;
    int _attack;

public:
    Player();    
    Player(int maxHealth, int maxMana, Type shieldingType);    
    constexpr Type getType() {return _shieldingType;};
    constexpr int getAttack () {return _attack;};
    constexpr int getCriticalHealth () {return _health.getMax() / 4;};
    constexpr int getMaxHealth () {return _health.getMax();};
    int getCurrentHealth () {return _health.getCurrent();};
    constexpr int getMaxMana () {return _mana.getMax();};
    int getCurrentMana () {return _mana.getCurrent();};
    TypeEffectivenessMultiplier checkTypeEffectiveness (Type opposingType);
    std::string getStringTemp ();
    bool isDefeated ();
    int takeDamage (int damage, Type opposingType);
    void heal (int healAmount);
    void recoverMana ();
    void recoverMana (int manaRegainedAmount);


};

struct Action {
    std::string _type;
    int _value;
    Player* _playerTarget;
    Enemy* _enemyTarget;

    Action();

};


#endif // COMBAT_DATA_H