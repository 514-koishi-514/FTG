cmake_minimum_required(VERSION 3.28)
project(qt_programming_2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt_programming_2024 src/main.cpp
        src/MyGame.cpp
        src/MyGame.h
        src/Items/Item.cpp
        src/Items/Item.h
        src/Items/Characters/Character.cpp
        src/Items/Characters/Character.h


        src/Items/Armors/Armor.cpp
        src/Items/Armors/Armor.h
        src/Items/HeadEquipments/HeadEquipment.cpp
        src/Items/HeadEquipments/HeadEquipment.h
        src/Items/LegEquipments/LegEquipment.cpp
        src/Items/LegEquipments/LegEquipment.h
        src/Items/HeadEquipments/CapOfTheHero.cpp
        src/Items/HeadEquipments/CapOfTheHero.h
        src/Items/Armors/OldShirt.cpp
        src/Items/Armors/OldShirt.h
        src/Items/LegEquipments/WellWornTrousers.cpp
        src/Items/LegEquipments/WellWornTrousers.h
        src/Scenes/Scene.cpp
        src/Scenes/Scene.h
        src/Scenes/BattleScene.cpp
        src/Scenes/BattleScene.h
        assets/assets.qrc

        src/Items/Maps/Map.h


        src/Items/Mountable.cpp
        src/Items/Mountable.h
        src/Items/Armors/FlamebreakerArmor.cpp
        src/Items/Armors/FlamebreakerArmor.h


        src/Items/Maps/Map.cpp

        src/Items/Maps/MistyLake.h
        src/Items/Maps/MistyLake.cpp
        src/Items/Maps/HighGrass.h
        src/Items/Maps/HighGrass.cpp
        src/Items/Maps/Bridge.h
        src/Items/Maps/Bridge.cpp
        src/Items/Weapons/Melee.h
        src/Items/Weapons/Melee.cpp
        src/Items/Weapons/Weapon.h
        src/Items/Weapons/Weapon.cpp
        src/Items/Weapons/EnhancedMelee.h
        src/Items/Weapons/EnhancedMelee.cpp
        src/Items/Weapons/Throw.h
        src/Items/Weapons/Throw.cpp
        src/Items/Weapons/Ranged.h
        src/Items/Weapons/Ranged.cpp
        src/Items/Weapons/SpellCard.h
        src/Items/Weapons/SpellCard.cpp
        src/Items/BattleSystemWiget/Face.h
        src/Items/BattleSystemWiget/Face.cpp
        src/Items/BattleSystemWiget/HpBar.h
        src/Items/BattleSystemWiget/HpBar.cpp






        src/Items/AttackItems/Ball.h
        src/Items/AttackItems/Ball.cpp
        src/Items/AttackItems/Charm.h
        src/Items/AttackItems/EnhancedCharm.h
        src/Items/AttackItems/Charm.cpp
        src/Items/AttackItems/EnhancedCharm.cpp


        src/Items/AttackItems/RangedItem.h
        src/Items/AttackItems/RangedItem.cpp
        src/Items/AttackItems/Ball.h
        src/Items/AttackItems/Ball.cpp
        src/Items/AttackItems/Charm.h
        src/Items/AttackItems/Charm.cpp
        src/Items/AttackItems/EnhancedCharm.h
        src/Items/AttackItems/EnhancedCharm.cpp
        src/Items/SystemWidgets/HpBar.h
        src/Items/SystemWidgets/HpBar.cpp
        src/Items/Armors/DefaultArmor.h
        src/Items/Armors/DefaultArmor.cpp
        src/Items/Armors/LightArmor.h
        src/Items/Armors/LightArmor.cpp
        src/Items/Armors/HeavyArmor.h
        src/Items/Armors/HeavyArmor.cpp


)
target_link_libraries(qt_programming_2024
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

