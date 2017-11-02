#pragma once
#include "engine\utils\Utilities.h"

class Item {
protected:
	enum ItemType {
		WEAPON,
		ARMOR,
		CONSUMABLE,
		MISC
	} m_itemType;
	enum Rarity {
		COMMON = 0,
		UNCOMMON = 1,
		RARE = 2,
		EPIC = 3,
		LEGENDARY = 4
	} m_rarity;
	std::string m_name;
	Sint32 m_price;
public:
	Item() {

	}

};
