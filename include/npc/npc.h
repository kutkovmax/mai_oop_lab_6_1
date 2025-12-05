#pragma once

#include <optional>
#include <string>
#include "../geometry/point.h"

// Forward declaration для уменьшения связности
class Visitor;

// Базовый класс NPC (Open/Closed Principle)
class NPC {
protected:
    std::string name;
    Point position;
    bool alive;

public:
    virtual ~NPC() = default;

    NPC(const std::string& name, const Point& position);

    // Query methods (Command Query Separation)
    [[nodiscard]] virtual std::string get_type() const = 0;
    [[nodiscard]] virtual std::string get_name() const;
    [[nodiscard]] virtual Point get_position() const;
    [[nodiscard]] virtual bool is_alive() const;
    
    // Query: проверка возможности убийства (не изменяет состояние)
    [[nodiscard]] virtual std::optional<std::string> vs(const NPC& target) const = 0;

    // Command: принятие посетителя (Visitor pattern)
    virtual void accept(Visitor& visitor) = 0;
    
    // Command: убить NPC (изменяет состояние)
    void kill();
};
