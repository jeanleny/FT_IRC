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

std::string	Item::getName()
{
	return (_name);
}

int	Item::getDmg()
{
	return (_damage);
}

Player::Player() : _room(CORRIDOR)
{
	_item = Item();
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

void    Player::setAlive(bool state)
{
    _alive = state;
}

void	Player::setItem(Item item)
{
	_item = item;
}


std::string	Player::getItemName()
{
	return (_item.getName());
}
int	Player::getItemDmg()
{
	return (_item.getDmg());
}
