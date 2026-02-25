#include "Player.hpp"

Item::Item() : _name(""), _damage(0)
{
    (void)_damage;
}

Item::Item(std::string name, int dmg) : _name(name), _damage(dmg)
{
}
Item::~Item()
{
}

Player::Player() : _room(CORRIDOR)
{
}

Player::~Player()
{
}

e_roomId    Player::getRoom() const
{
    return (_room);
}

void    Player::setRoom(e_roomId room)
{
    _room = room;
}

