# Лабораторная работа № 06
## Редактор подземелья для RPG игры Balagur Fate 3

### Вариант 1
- **NPC типы**: Орк, Белка, Друид
- **Боевые правила**:
  - Орки убивают Друидов
  - Друиды убивают Белок
  - Белки за мир (никого не убивают)

### Реализованные паттерны проектирования

#### 1. Factory Pattern
- `NPCFactory` - создает NPC по типу
- Регистрация создателей через функции (расширяемо)
- Загрузка NPC из файла также использует Factory

#### 2. Visitor Pattern
- `BattleVisitor` - реализует боевой цикл
- `Visitor` - абстрактный интерфейс для посещения разных типов NPC
- Каждый NPC принимает Visitor через метод `accept()`

#### 3. Observer Pattern
- `Observer` - интерфейс для наблюдателей
- `EventManager` (Subject) - управляет списком наблюдателей с использованием PIMPL
- Конкретные наблюдатели:
  - `ConsoleObserver` - выводит события в консоль
  - `FileObserver` - записывает события в файл `log.txt`

### Структура проекта

```
.
├── CMakeLists.txt
├── README.md
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

### Функциональность

1. **Добавление NPC**
   - Поддержка типов: Орк, Белка, Друид
   - Уникальные имена
   - Координаты в диапазоне 0-500

2. **Сохранение и загрузка**
   - Сохранение всех живых NPC в файл
   - Загрузка NPC из файла с использованием Factory

3. **Печать списка NPC**
   - Вывод всех живых NPC с типом, именем и координатами

4. **Боевой режим**
   - NPC сражаются каждый с каждым в указанном радиусе
   - Поддержка взаимных убийств
   - Удаление погибших NPC после битвы
   - Логирование событий в консоль и файл

### Сборка и запуск

```bash
mkdir -p build
cd build
cmake ..
make
```

Запуск программы:
```bash
./lab6
```

Запуск тестов:
```bash
./tests
```

### Тестирование

Всего реализовано **103 теста**, которые проверяют:
- Создание и поведение NPC всех типов
- Боевые правила и взаимодействия
- Factory для создания и загрузки NPC
- Visitor для боевого цикла
- Observer для логирования
- Сохранение и загрузку из файлов
- Граничные случаи

### Особенности реализации

- Все NPC наследуются от базового класса `NPC`
- Используются умные указатели (`std::unique_ptr`) для управления памятью
- Боевая система проверяет обе стороны на возможность убийства (взаимные убийства)
- Observer pattern позволяет легко добавлять новые типы логирования
- Factory pattern обеспечивает расширяемость для новых типов NPC

### Принципы проектирования

- **SOLID**: Single Responsibility, Open/Closed, Liskov Substitution, Interface Segregation, Dependency Inversion
- **PIMPL**: EventManager использует Pointer to Implementation для инкапсуляции
- **Tell Don't Ask**: методы говорят объектам что делать
- **Command Query Separation**: команды изменяют состояние, запросы только читают
- **Low Coupling / High Cohesion**: минимальные зависимости, четкое разделение модулей
