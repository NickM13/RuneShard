#include "engine\game\world\entity\actor\actors\Roger.h"

Roger::Roger()
	: Warrior({0.9f, 1.8f, 0.9f}) {
	setModel(MVoxelModel::getVoxelModel("Roger.nvm"));
	m_name = "Roger";
	LActor::addActor("Roger", this);
}
