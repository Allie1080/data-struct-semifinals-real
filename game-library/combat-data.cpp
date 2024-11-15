#include "combat-data.h"

#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <chrono>
#include <random>

constexpr int AMOUNT_OF_TYPES = 4;
constexpr int AMOUNT_OF_SIZES = 3;
constexpr int AMOUNT_OF_POSSIBLE_ENEMIES = AMOUNT_OF_SIZES * AMOUNT_OF_TYPES;

Health::Health () {
        _current = -1;
        _max = -1;
    }

Health::Health (int maxHealth) {
        _current = maxHealth;
        _max = maxHealth;

    }

int Health::getCurrent () {
        return _current;

    }

int Health::getMax () {
        return _max;

    }

void Health::decrease (int damage) {
    _current -= damage;

    if (_current < 0) {
        _current = 0;

    }

}

void Health::increase (int heal) {
    _current += heal;

    if (_current > _max) {
        _current = _max;

    }

}

Enemy::Enemy () {
    _name = "Blob";
    _type = Type::NORMAL;
    _size = static_cast<int>(Size::SMALL);
    _health = Health(_size);
    _attack = (_size / 10) + 2;

}

Enemy::Enemy (Type type, Size size, int level, std::string name="Blob") {
    _name = name;
    _type = type;
    _size = static_cast<int>(size);
    _health = Health(_size + (_size * (level / 3)));
    _attack = ((_size / 10) + 2) + ((_size / 10) * (level / 3));

}


std::string Enemy::type () const {
    switch (_type) {
        case Type::NORMAL:
            return "NORMAL";

        case Type::FIRE:
            return "FIRE";

        case Type::GRASS:
            return "GRASS";

        case Type::WATER:
            return "WATER";

        default:
            return "UNKNOWN";
        
    }

}

int Enemy::getCurrentHealth() {
    return _health.getCurrent();
    
}

int Enemy::getMaxHealth() {
    return _health.getMax();
    
}

TypeEffectivenessMultiplier Enemy::checkTypeEffectiveness (Type opposingType) const {
    if (_type == Type::NORMAL) {
        return TypeEffectivenessMultiplier::NORMAL;

    } else if (opposingType == _type) {
        return TypeEffectivenessMultiplier::SAME_TYPE;

    } else if (opposingType == _type + 1) {
        return TypeEffectivenessMultiplier::IMMUNE;

    } else if (opposingType == Type::NORMAL) {
        return TypeEffectivenessMultiplier::NORMAL;

    } else if (opposingType == (_type != 0) ? _type - 1 : AMOUNT_OF_TYPES - 1) {
        return TypeEffectivenessMultiplier::VERY_EFFECTIVE;

    } else {
        return TypeEffectivenessMultiplier::IMMUNE;

    }

}

std::string Enemy::getStringTemp () {
    // for testing purposes only
    std::stringstream stringStream;

    stringStream << "TYPE: " << type() << " SIZE: " << _size << " HEALTH: " << _health.getCurrent() << "/" << _health.getMax();

    return stringStream.str();
} 

bool Enemy::isDefeated () {
    if (_health.getCurrent() == 0) {
        return true;

    }

    return false;

}

void Enemy::takeDamage (int damage, Type opposingType) {
    damage *= static_cast<int>(checkTypeEffectiveness(opposingType));

    if (damage < 0) {
        _health.increase(std::abs(damage));

    } else {
        _health.decrease(damage);

    }

}

Player::Player () {
    _name = "Marisa";
    _shieldingType = Type::NORMAL;
    _health = Health(50);
    _attack = 5;

}

Player::Player (int maxHealth, Type shieldingType) {
    _name = "Marisa";
    _shieldingType = shieldingType;
    _health = Health(maxHealth);
    _attack = 5;

}


std::string Player::type () const {
    switch (_shieldingType) {
        case Type::NORMAL:
            return "NORMAL";

        case Type::FIRE:
            return "FIRE";

        case Type::GRASS:
            return "GRASS";

        case Type::WATER:
            return "WATER";

        default:
            return "UNKNOWN";
        
    }

}

int Player::getCurrentHealth() {
    return _health.getCurrent();
    
}

int Player::getMaxHealth() {
    return _health.getMax();
    
}

TypeEffectivenessMultiplier Player::checkTypeEffectiveness (Type opposingType) const {
    if (_shieldingType == Type::NORMAL) {
        return TypeEffectivenessMultiplier::NORMAL;

    } else if (opposingType == _shieldingType) {
        return TypeEffectivenessMultiplier::SAME_TYPE;

    } else if (opposingType == _shieldingType + 1) {
        return TypeEffectivenessMultiplier::IMMUNE;

    } else if (opposingType == Type::NORMAL) {
        return TypeEffectivenessMultiplier::NORMAL;

    } else if (opposingType == (_shieldingType != 0) ? _shieldingType - 1 : AMOUNT_OF_TYPES - 1) {
        return TypeEffectivenessMultiplier::VERY_EFFECTIVE;

    } else {
        return TypeEffectivenessMultiplier::IMMUNE;

    }

}

std::string Player::getStringTemp () {
    // for testing purposes only
    std::stringstream stringStream;

    stringStream << "TYPE: " << type() << " HEALTH: " << _health.getCurrent() << "/" << _health.getMax();

    return stringStream.str();
} 

bool Player::isDefeated () {
    if (_health.getCurrent() == 0) {
        return true;

    }

    return false;

}

void Player::takeDamage (int damage, Type opposingType) {
    damage *= static_cast<int>(checkTypeEffectiveness(opposingType));

    if (damage < 0) {
        _health.increase(std::abs(damage));

    } else {
        _health.decrease(damage);

    }

}

int getRandomNumber (int minimum, int maximum) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(minimum, maximum);
    
    return distr(gen);
}

Type getRandomType () {
    Type randomType;



    return randomType;

}

Size getRandomSize () {
    Size randomSize;

    return randomSize;

}

Enemy getRandomEnemy (int level) {
    Type type;
    Size size;


    //return Enemy(type, size, level);
    return Enemy();

}


