# Применение принципов проектирования

## Структура проекта

```
.
├── CMakeLists.txt
├── README.md
├── DESIGN_PRINCIPLES.md
│
├── include/
│   ├── dungeon/
│   │   └── dungeon.h
│   │
│   ├── npc/
│   │   ├── npc.h
│   │   ├── orc.h
│   │   ├── druid.h
│   │   ├── squirrel.h
│   │   └── npc_factory.h
│   │
│   ├── battle/
│   │   ├── visitor.h
│   │   ├── battle_visitor.h
│   │   ├── observer.h
│   │   ├── event_manager.h      // Subject (observer pattern) с PIMPL
│   │   ├── console_observer.h
│   │   └── file_observer.h
│   │
│   └── geometry/
│       └── point.h
│
├── src/
│   ├── dungeon/
│   │   └── dungeon.cpp
│   │
│   ├── npc/
│   │   ├── npc.cpp
│   │   ├── orc.cpp
│   │   ├── druid.cpp
│   │   ├── squirrel.cpp
│   │   └── npc_factory.cpp
│   │
│   ├── battle/
│   │   ├── battle_visitor.cpp
│   │   ├── event_manager.cpp
│   │   ├── console_observer.cpp
│   │   └── file_observer.cpp
│   │
│   └── geometry/
│       └── point.cpp
│
├── main.cpp
│
└── test/
    ├── test_dungeon.cpp
    ├── test_npc.cpp
    ├── test_factory.cpp
    ├── test_battle.cpp
    ├── test_observer.cpp
    └── test_point.cpp
```

## Примененные принципы проектирования

### 1. SOLID принципы

#### Single Responsibility Principle (SRP)
- **DungeonEditor**: отвечает только за управление подземельем и NPC
- **NPCFactory**: отвечает только за создание и загрузку NPC
- **BattleVisitor**: отвечает только за логику боя
- **EventManager**: отвечает только за управление наблюдателями
- **Observer классы**: каждый отвечает за свой способ логирования

#### Open/Closed Principle (OCP)
- **NPC классы**: легко добавлять новые типы NPC без изменения существующего кода
- **Factory**: регистрирует создателей через функцию, легко расширяется
- **Observer**: легко добавлять новые типы наблюдателей

#### Liskov Substitution Principle (LSP)
- Все NPC типы корректно заменяют базовый класс NPC
- Все Observer классы корректно заменяют базовый Observer

#### Interface Segregation Principle (ISP)
- Разделены интерфейсы Visitor и Observer
- Каждый класс реализует только необходимые методы

#### Dependency Inversion Principle (DIP)
- Высокоуровневые модули зависят от абстракций (Visitor, Observer, NPC)
- Конкретные реализации зависят от интерфейсов

### 2. PIMPL (Pointer to Implementation)

**EventManager** использует PIMPL паттерн:
```cpp
class EventManager {
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
    // ...
};
```

**Преимущества**:
- Уменьшение связности (coupling)
- Сокрытие деталей реализации
- Уменьшение времени компиляции
- Возможность изменять реализацию без перекомпиляции клиентского кода

### 3. Tell Don't Ask

**Примеры**:
- `npc.kill()` вместо `if (npc.is_alive()) npc.set_alive(false)`
- `battle_visitor.perform_battle(target)` вместо проверки всех условий снаружи
- `event_manager.publish(event)` вместо прямого вызова наблюдателей

### 4. Command Query Separation (CQS)

**Command методы** (изменяют состояние):
- `add_npc()`, `save_to_file()`, `load_from_file()`
- `start_battle()`, `kill()`, `subscribe()`, `publish()`
- Возвращают `void`

**Query методы** (не изменяют состояние):
- `get_type()`, `get_name()`, `get_position()`, `is_alive()`
- `get_alive_count()`, `is_name_exists()`, `get_radius()`
- Помечены `[[nodiscard]]` и `const`

### 5. Low Coupling (Слабая связность)

**Достигнуто через**:
- Forward declarations вместо полных включений где возможно
- Интерфейсы и абстракции
- PIMPL паттерн для EventManager
- Разделение ответственности между классами

### 6. High Cohesion (Высокая сцепленность)

**Достигнуто через**:
- Группировку связанной функциональности
- Четкое разделение модулей (battle, npc, dungeon)
- Логическую организацию классов

### 7. Принцип надежности

**Обработка ошибок**:
- Проверка входных данных
- Использование исключений для критических ошибок
- Проверка валидности указателей
- Безопасная работа с файлами

**Rule of Five**:
- Запрет копирования где необходимо (EventManager, BattleVisitor)
- Правильное управление ресурсами через умные указатели

### 8. DRY (Don't Repeat Yourself)

- Переиспользование кода через наследование
- Общие паттерны вынесены в базовые классы
- Использование методов класса Point напрямую без лишних обёрток

## Структурные улучшения

### Реорганизация директорий

1. **combat → battle**: более понятное название
2. **npc/types и npc/factory → npc/**: упрощение структуры
3. **subject → event_manager**: более описательное название

### Инкапсуляция

- Приватные методы для внутренней логики
- Использование умных указателей для управления памятью
- Сокрытие деталей реализации через PIMPL

## Соответствие требованиям лабораторной работы

### ✅ Требования выполнены:

1. **Factory Pattern** для создания NPC
   - Реализован через NPCFactory с регистрацией создателей
   - Используется для загрузки NPC из файла

2. **Visitor Pattern** для боевого цикла
   - BattleVisitor реализует Visitor интерфейс
   - Каждый NPC принимает Visitor через accept()

3. **Observer Pattern** для логирования
   - EventManager (Subject) управляет наблюдателями
   - ConsoleObserver для консоли
   - FileObserver для файла log.txt

4. **Функциональность**:
   - ✅ Добавление NPC (типы: Орк, Белка, Друид)
   - ✅ Сохранение/загрузка из файла
   - ✅ Печать списка NPC
   - ✅ Боевой режим с радиусом
   - ✅ Удаление погибших NPC

5. **Боевые правила (Вариант 1)**:
   - ✅ Орки убивают Друидов
   - ✅ Друиды убивают Белок
   - ✅ Белки за мир (никого не убивают)

## Тестирование

Все тесты обновлены под новую структуру и проходят успешно:
- Тесты NPC
- Тесты Factory
- Тесты Dungeon
- Тесты Battle
- Тесты Observer

## Заключение

Проект полностью соответствует требованиям лабораторной работы и применяет современные принципы проектирования для создания расширяемого, поддерживаемого и надежного кода.

