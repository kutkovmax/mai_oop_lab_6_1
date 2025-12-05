#include "../../../include/combat/visitor/battle_visitor.h"
#include "../../../include/npc/types/druid.h"
#include "../../../include/npc/types/orc.h"
#include "../../../include/npc/types/squirrel.h"

BattleVisitor::BattleVisitor(double radius) : current_attacker(nullptr), battle_radius(radius) {}

void BattleVisitor::set_attacker(NPC* attacker) { current_attacker = attacker; }

double BattleVisitor::get_radius() const { return battle_radius; }

void BattleVisitor::add_observer(Observer* observer) {
    subject.add_observer(observer);
}

void BattleVisitor::battle(NPC& target) {
    if (!current_attacker || !current_attacker->is_alive() || !target.is_alive())
        return;

    double distance = current_attacker->get_position().distance_to(target.get_position());
    if (distance > battle_radius) {
        return; 
    }

    auto action1 = current_attacker->vs(target);
    auto action2 = target.vs(*current_attacker);

    // Проверяем, может ли атакующий убить цель
    if (action1) {
        target.kill();
        BattleEvent event;
        event.action = *action1 + " (" + current_attacker->get_name() + " убивает " + target.get_name() + ")";
        subject.notify(event);
    }

    // Проверяем, может ли цель убить атакующего (взаимное убийство)
    if (action2) {
        current_attacker->kill();
        BattleEvent event;
        event.action = *action2 + " (" + target.get_name() + " убивает " + current_attacker->get_name() + ")";
        subject.notify(event);
    }
}

void BattleVisitor::visit(Druid& druid) { battle(druid); }
void BattleVisitor::visit(Orc& orc) { battle(orc); }
void BattleVisitor::visit(Squirrel& squirrel) { battle(squirrel); }