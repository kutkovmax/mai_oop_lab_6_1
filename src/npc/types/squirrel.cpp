#include "../../../include/npc/types/squirrel.h"
#include "../../../include/combat/visitor/visitor.h"

Squirrel::Squirrel(const std::string& name, const Point& position) : NPC(name, position) {}

std::string Squirrel::get_type() const { return "Белка"; }

void Squirrel::accept(Visitor& visitor) { visitor.visit(*this); }

// Белки за мир - они никого не убивают
std::optional<std::string> Squirrel::vs(const NPC& target) const {
    return std::nullopt;
}

