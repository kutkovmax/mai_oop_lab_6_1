# Проверка структуры проекта

## Текущая структура файлов

### ✅ Новая структура (используется):

```
include/
├── battle/              ✅
│   ├── battle_event.h
│   ├── battle_visitor.h
│   ├── console_observer.h
│   ├── event_manager.h
│   ├── file_observer.h
│   ├── observer.h
│   └── visitor.h
├── npc/                 ✅ (в корне)
│   ├── druid.h
│   ├── npc.h
│   ├── npc_factory.h
│   ├── orc.h
│   └── squirrel.h
├── dungeon/
├── geometry/
└── utils/

src/
├── battle/              ✅
│   ├── battle_visitor.cpp
│   ├── console_observer.cpp
│   ├── event_manager.cpp
│   └── file_observer.cpp
├── npc/                 ✅ (в корне)
│   ├── druid.cpp
│   ├── npc.cpp
│   ├── npc_factory.cpp
│   ├── orc.cpp
│   └── squirrel.cpp
├── dungeon/
└── geometry/

test/
├── test_dungeon.cpp     ✅ (объединен)
├── test_npc.cpp         ✅
├── test_factory.cpp     ✅
├── test_battle.cpp      ✅
├── test_observer.cpp    ✅
└── test_point.cpp       ✅
```

### ❌ Старые папки (нужно удалить):

- `include/combat/` - не используется, заменено на `battle/`
- `src/combat/` - не используется
- `include/npc/types/` - не используется, файлы в корне `npc/`
- `include/npc/factory/` - не используется, файлы в корне `npc/`
- `src/npc/types/` - не используется
- `src/npc/factory/` - не используется

## Соответствие требованиям

Структура соответствует предложенной:
- ✅ `battle/` вместо `combat/`
- ✅ NPC файлы в корне `npc/`
- ✅ `event_manager.h` вместо `subject.h`
- ✅ `utils/distance.h` добавлен
- ✅ Тесты переименованы

