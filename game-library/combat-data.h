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
    int getCurrent() {return _current;};
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
    int getCurrent() {return _current;};
    constexpr int getMax () {return _max;};
    void decrease (int consumedAmount);
    void increase (int regainedAmount);
};

class Spell {
private:
    std::string _name;
    int _cost;
    float _attackBonus;
    Type _type;

public:
    Spell ();
    Spell (std::string name, int cost, float attackBonus, Type type);
    std::string getName () {return _name;};
    constexpr int getCost () {return _cost;};
    constexpr int getAttackBonus () {return _attackBonus;};
    constexpr Type getType () {return _type;};
    std::string getLabel ();

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
    bool isDefeated () {return _health.getCurrent() == 0;};
    bool isCriticalHealth () {return _health.getCurrent() <= getCriticalHealth();};
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
    bool isDefeated () {return _health.getCurrent() == 0;};
    int takeDamage (int damage, Type opposingType);
    void consumeMana (int manaConsumed);
    void heal (int healAmount);
    void recoverMana ();
    void recoverMana (int manaRegainedAmount);


};

class Action {
private:
    std::string _targetName;
    std::string _actionType;
    std::string _spellName;
    int _value;
    
public:
    Action();
    Action(std::string targetName, std::string spellName, std::string actionType, int value);
    constexpr int getValue() const {return _value;};
    std::string getActionType() const {return _actionType;};
    std::string getSpellName() const {return _spellName;};
    std::string getTargetName() const {return _targetName;};
    std::string getActionMessage() const;

};

int getRandomNumber(int minimum, int maximum);


#endif // COMBAT_DATA_H