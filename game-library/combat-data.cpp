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

// constexpr int Health::getMax () {
//         return _max;

// }

void Health::decrease (int damageAmount) {
    _current -= damageAmount;

    if (_current < 0) {
        _current = 0;

    }

}

void Health::increase (int healedAmount) {
    _current += healedAmount;

    if (_current > _max) {
        _current = _max;

    }

}

Mana::Mana () {
        _current = -1;
        _max = -1;
}

Mana::Mana (int maxMana) {
        _current = maxMana;
        _max = maxMana;

}

// constexpr int Health::getMax () {
//         return _max;

// }

void Mana::decrease (int consumedAmount) {
    _current -= consumedAmount;

    if (_current < 0) {
        _current = 0;

    }

}

void Mana::increase (int regainedAmount) {
    _current += regainedAmount;

    if (_current > _max) {
        _current = _max;

    }

}

Spell::Spell () {
    _name = "MagicMissile";
    _cost = 5;
    _attackBonus = 0.0;
    _type = NORMAL;

}

Spell::Spell (std::string name, int cost, float attackBonus, Type type) {
    _name = name;
    _cost = cost;
    _attackBonus = attackBonus;
    _type = type;

}

std::string Spell::getLabel () {
    std::stringstream label;
    // std::array<char, 4> typeNames = {'N', 'F', 'W', 'G'};
    // std::string type{typeNames[_type+1]};

    label << _name << " -- " << _cost << " MN";

    return label.str();

}

Enemy::Enemy () {
    _name = "ERROR";
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

// constexpr std::string Enemy::getName () {
//     return _name;

// }

// constexpr Type Enemy::getType () {
//     return _type;
//     // switch (_type) {
//     //     case Type::NORMAL:
//     //         return "NORMAL";

//     //     case Type::FIRE:
//     //         return "FIRE";

//     //     case Type::GRASS:
//     //         return "GRASS";

//     //     case Type::WATER:
//     //         return "WATER";

//     //     default:
//     //         return "UNKNOWN";
        
//     // }

// }

// constexpr int Enemy::getAttack () {
//     return _attack;

// }

// constexpr int Enemy::getMaxHealth() {
//     return _health.getMax();
    
// }

// constexpr int Enemy::getCriticalHealth() {
//     return _health.getMax() / 4;
    
// }

TypeEffectivenessMultiplier Enemy::checkTypeEffectiveness (Type opposingType) {
    if (_type == Type::NORMAL) {
        return TypeEffectivenessMultiplier::NORMAL;

    } else if (opposingType == _type) {
        return TypeEffectivenessMultiplier::SAME_TYPE;

    } else if (opposingType == ((_type != AMOUNT_OF_TYPES - 2) ? _type + 1 : 0 )) {
        return TypeEffectivenessMultiplier::VERY_EFFECTIVE;

    } else if (opposingType == Type::NORMAL) {
        return TypeEffectivenessMultiplier::NORMAL;

    } else if (opposingType == ((_type != 0) ? _type - 1 : AMOUNT_OF_TYPES - 2)) {
        return TypeEffectivenessMultiplier::IMMUNE;

    } else {
        return TypeEffectivenessMultiplier::IMMUNE;

    }

}

std::string Enemy::getStringTemp () {
    // for testing purposes only
    std::stringstream stringStream;

    stringStream << "TYPE: " << getType() << " SIZE: " << _size << " HEALTH: " << _health.getCurrent() << "/" << _health.getMax();

    return stringStream.str();
} 

int Enemy::takeDamage (int damage, Type opposingType) {
    damage *= static_cast<int>(checkTypeEffectiveness(opposingType));

    if (damage < 0) {
        _health.increase(std::abs(damage));

    } else {
        _health.decrease(damage);

    }

    return damage;

}

Player::Player () {
    _name = "Marisa";
    _shieldingType = Type::NORMAL;
    _health = Health(50);
    _mana = Mana(50);
    _manaRegainAmount = static_cast<int>(50 / 10);
    _attack = 5;

}

Player::Player (int maxHealth, int maxMana, Type shieldingType) {
    _name = "Marisa";
    _shieldingType = shieldingType;
    _health = Health(maxHealth);
    _mana = Mana(maxMana);
    _manaRegainAmount = static_cast<int>(maxMana / 10);
    _attack = 5;

}


// constexpr Type Player::getType () {
//     return _shieldingType;
    
//     // switch (_shieldingType) {
//     //     case Type::NORMAL:
//     //         return "NORMAL";

//     //     case Type::FIRE:
//     //         return "FIRE";

//     //     case Type::GRASS:
//     //         return "GRASS";

//     //     case Type::WATER:
//     //         return "WATER";

//     //     default:
//     //         return "UNKNOWN";
        
//     // }

// }

// constexpr int Player::getAttack () {
//     return _attack;

// }

// constexpr int Player::getMaxHealth() {
//     return _health.getMax();
    
// }

// constexpr int Player::getCriticalHealth() {
//     return _health.getMax() / 4;
    
// }

TypeEffectivenessMultiplier Player::checkTypeEffectiveness (Type opposingType) {
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

    stringStream << "TYPE: " << getType() << " HEALTH: " << _health.getCurrent() << "/" << _health.getMax();

    return stringStream.str();
} 



int Player::takeDamage (int damage, Type opposingType) {
    damage *= static_cast<int>(checkTypeEffectiveness(opposingType));

    if (damage < 0) {
        _health.increase(std::abs(damage));

    } else {
        _health.decrease(damage);

    }

    return damage;

}

void Player::consumeMana (int manaConsumed) {
    _mana.decrease(manaConsumed);

}

void Player::heal (int healAmount) {
    _health.increase(std::abs(healAmount));

}

void Player::recoverMana () {
    _mana.increase(std::abs(_manaRegainAmount));

}

void Player::recoverMana (int regainedManaAmount) {
    _mana.increase(std::abs(regainedManaAmount));

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


Action::Action () {
    _type = "None";
    _value = -1;

}