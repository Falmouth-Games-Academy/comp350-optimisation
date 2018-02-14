#pragma once
#include "Items.h"

class Inventory
{
public:
	Inventory();
	~Inventory();


	// Add item to inventory
	bool add(const Item& item)
	{
		if (capacity > items.size())
		{
			items.push_back(item);
			//item.onInsertionFailed() /* A trick I've done in the past to give custom behavior */
			return true;
		}
		return false;
	}

	void removeItemType(const Item::ItemType type)
	{
		for (unsigned int i = 0; i < getCurrentSize(); i++)
		{

				if (items[i].type.Resource == type.Resource)
				{
					items[i].type.Resource = Item::ItemType::noResource;
					return;
				}
				if (items[i].type.Food == type.Food)
				{
					items[i].type.Food = Item::ItemType::noFood;
					return;
				}
					
				if (items[i].type.Tool == type.Tool)
				{
					items[i].type.Tool = Item::ItemType::noTool;
					return;
				}
			
		}
	}
	// returns the size of inventory
	unsigned int getCapacity(void) const
	{
		return capacity;
	}
	//Get size of the current inventory
	unsigned int getCurrentSize(void) const
	{
		return items.size();
	}

	// May throw
	const Item& get(unsigned int index) const
	{
		return items.at(index);
	}

	// Returns true if the index was removed, false if the index was out of bounds
	bool remove(unsigned int index)
	{
		if (index < items.size())
		{
			items.erase(items.begin() + index);
			return true;
		}
		return false;
	}
	unsigned int setCapacity(unsigned int newCapacity)
	{ 
		return capacity = newCapacity; 
	}
private:
	unsigned int capacity = 20;
	std::vector<Item> items;
};

