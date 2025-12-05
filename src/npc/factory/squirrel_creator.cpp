#include "../../../include/npc/factory/squirrel_creator.h"
#include "../../../include/npc/types/squirrel.h"

std::unique_ptr<NPC> SquirrelCreator::create_npc(const std::string& name, Point position) const {
    return std::make_unique<Squirrel>(name, position);
}

