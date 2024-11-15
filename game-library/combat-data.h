#ifndef COMBAT_DATA_H
#define COMBAT_DATA_H

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
    SAME_TYPE = -1,
    IMMUNE,
    NORMAL,
    VERY_EFFECTIVE,

};

class Health  {
private:
    int _current;
    int _max;

public:
    Health ();
    Health (int maxHealth);
    int getCurrent ();
    int getMax ();
    void decrease (int damage);
    void increase (int heal);

};

class Enemy {
private:
    std::string _name;
    Type _type;
    int _size;
    Health _health;

public:
    Enemy ();
    Enemy (Type type, Size size, int level, std::string name);
    std::string type () const;
    TypeEffectivenessMultiplier checkTypeEffectiveness (Type opposingType) const;
    std::string getStringTemp ();
    bool isDefeated ();
    void takeDamage (int damage, Type opposingType);

};

Enemy getRandomEnemy (int level);


#endif
