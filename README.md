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
- `Creator` - абстрактный класс для создания NPC
- Конкретные создатели: `DruidCreator`, `OrcCreator`, `SquirrelCreator`
- Загрузка NPC из файла также использует Factory

#### 2. Visitor Pattern
- `BattleVisitor` - реализует боевой цикл
- `Visitor` - абстрактный интерфейс для посещения разных типов NPC
- Каждый NPC принимает Visitor через метод `accept()`

#### 3. Observer Pattern
- `Observer` - интерфейс для наблюдателей
- `Subject` - управляет списком наблюдателей
- Конкретные наблюдатели:
  - `ConsoleObserver` - выводит события в консоль
  - `FileObserver` - записывает события в файл `log.txt`

### Структура проекта

```
lab06/
├── src/
│   ├── main.cpp
│   ├── dungeon/
│   │   └── dungeon.cpp
│   ├── npc/
│   │   ├── npc.cpp
│   │   ├── types/
│   │   │   ├── druid.cpp
│   │   │   ├── orc.cpp
│   │   │   └── squirrel.cpp
│   │   └── factory/
│   │       ├── npc_factory.cpp
│   │       ├── druid_creator.cpp
│   │       ├── orc_creator.cpp
│   │       └── squirrel_creator.cpp
│   ├── combat/
│   │   ├── visitor/
│   │   │   └── battel_visitor.cpp
│   │   └── observer/
│   │       ├── console_observer.cpp
│   │       ├── file_observer.cpp
│   │       └── subject.cpp
│   └── geometry/
│       └── point.cpp
├── include/
│   ├── dungeon/
│   ├── npc/
│   ├── combat/
│   └── geometry/
├── test/
│   ├── test_npc.cpp
│   ├── test_npc_factory.cpp
│   ├── test_dungeon_basic.cpp
│   ├── test_dungeon_battle.cpp
│   ├── test_dungeon_file.cpp
│   ├── test_observers.cpp
│   └── test_point.cpp
└── CMakeLists.txt
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
