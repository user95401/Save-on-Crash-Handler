# Game Objects Factory

Abuse original GD logic to "add" your custom objects like triggers, deco, rings and whatever tf you want into the editor/gameplay...

Hooks into scary RobTop's object system and lets you add custom game objects with your own IDs and callbacks.

## Features

- **Custom Triggers**: Hook into `triggerObject()`, `triggerActivated()`, setup custom edit popups
- **Custom Rings/Orbs**: Override `activatedByPlayer()` for custom player interactions  
- **Custom Decorations**: Add deco objects with custom sprite or even detail sprite (color2 support)
- **Save/Load**: Add your custom logic in `saveString()` and `objectFromVector()` callbacks
- **Other Runtime Callbacks**: `customSetup()`, `resetObject()`, `spawnObject()` hooks
- **Editor Integration**: Add your objects to create tab

## Object Types Supported

- **Triggers**: Based on existing trigger object (1613 ref), custom logic + edit UI
- **Decoration**: Static deco objects with second color support (detail sprite)
- **Rings (Orbs)**: Player-activated ring objects (1594 ref)
- **Rotated Objects**: Objects with rotation (396 ref)
- **Pulse Objects**: Objects with pulse animation (52 ref)

## How it works

1. Registers custom object IDs in `ObjectToolbox::m_allKeys`
2. Hooks `GameObject::createWithKey()` to intercept custom IDs
3. Creates base object from reference ID, applies custom setups
4. Stores config in object's `userData` for callback access
5. Temporarily swaps IDs during vanilla function calls

## Usage

```cpp
// Register a custom trigger
GameObjectsFactory::registerGameObject(
    GameObjectsFactory::createTriggerConfig(
        UNIQ_ID("my-trigger"), "my_sprite.png"_spr,
        [](EffectGameObject* trigger, GJBaseGameLayer* game, int p1, gd::vector<int> const* p2) {
            // Custom trigger logic
        }
    )
);

// Register a custom orb
GameObjectsFactory::registerGameObject(
    GameObjectsFactory::createRingConfig(
        UNIQ_ID("my-orb"), "orb_sprite.png"_spr,
        [](EnhancedGameObject* obj, PlayerObject* player) {
            player->spiderTestJump(true); // Works as spider orb as example
        }
    )
);

// Register decoration
GameObjectsFactory::registerGameObject(
    GameObjectsFactory::createDecorationObjectConfig(
        UNIQ_ID("my-deco"), "deco_sprite.png"_spr
    )
);

// Register decoration with detail and registerMe()
GameObjectsFactory::createDecorationObjectConfig(
	UNIQ_ID("my-deco"), "deco_sprite.png"_spr, "deco_sprite_color.png"_spr
)->registerMe();
```

Use `UNIQ_ID("string")` macro to generate unique IDs from strings. Keeps your objects from conflicting with vanilla or other mods. Theorically you can modify original object if you set its id.

## Sprite Frames Unity?

This mod is one of ways to use your own sprite frames for objects without editing original `GJ_GameSheet` or `GJ_GameSheet02`.

https://github.com/user95401/geode-sprite-frames-unity

## Full example
https://github.com/user95401/geode-game-objects-factory/blob/master/src/main.cpp#L247
#### mod.json:
```json
"dependencies": {
	"user95401.sprite-frames-unity": ">=v1.0.0",
	"user95401.game-objects-factory": ">=v1.0.0"
}
```
#### main.cpp:
```cpp
#include <user95401.game-objects-factory/include/main.hpp>

#include <Geode/Geode.hpp>
using namespace geode::prelude;

void registerCustomObjects();
$execute{ registerCustomObjects(); }
inline void registerCustomObjects() {

    // Single line deco objects register
    GameObjectsFactory::createDecorationObjectConfig(UNIQ_ID("a1"), "d_sign_img_01_001.png")->registerMe();
    GameObjectsFactory::createDecorationObjectConfig(UNIQ_ID("a2"), "d_sign_img_02_001.png")->registerMe();
    GameObjectsFactory::createDecorationObjectConfig(UNIQ_ID("a3"), "d_sign_img_03_001.png")->registerMe();

    // Trigger object register
    GameObjectsFactory::registerGameObject(GameObjectsFactory::createTriggerConfig(
        UNIQ_ID("test-trigger"),
        "framename.png"_spr,

        [](EffectGameObject* trigger, GJBaseGameLayer* game, int p1, gd::vector<int> const* p2)
        {
            log::info("trigger callback!");
        },

        [](EditTriggersPopup* popup, EffectGameObject* trigger, CCArray* objects)
        {
            popup->m_buttonMenu->addChild(SimpleTextArea::create(
                "edit triggers popup init callback to setup!"
            ));
        }
    ));

    //  Trigger object with additional callbacks
    GameObjectsFactory::registerGameObject(
        GameObjectsFactory::createTriggerConfig(
            UNIQ_ID("test-trigger2"),
            "frame_name.png"_spr
        )->triggerObject(
            [](EffectGameObject* trigger, GJBaseGameLayer* game, int p1, gd::vector<int> const* p2) {
                log::info("trigger2 callback!");
            }
        )->customSetup(
            [](GameObject* object) {}
        )->saveString(
            [](std::string str, GameObject* object, GJBaseGameLayer* level) {
                // do something with str
                return str;
            }
        )->objectFromVector(
            [](GameObject* object, gd::vector<gd::string>& p0, gd::vector<void*>&, void*, bool) {
                // do something with object by p0
                return object;
            }
        )
    );

    // Add simple deco object
    GameObjectsFactory::registerGameObject(GameObjectsFactory::createDecorationObjectConfig(
        UNIQ_ID("pxa1"), "pxa1.png"_spr
    ));
    // Add deco object with detail sprite (color 2)
    GameObjectsFactory::registerGameObject(GameObjectsFactory::createDecorationObjectConfig(
        UNIQ_ID("pxb1"), "pxb1.png"_spr, "pxb1_2.png"_spr
    ));
    // Add deco object with pulse animation
    GameObjectsFactory::registerGameObject(GameObjectsFactory::createPulseConfig(
        UNIQ_ID("d_sign_img_03__shine"), "d_sign_img_03_001.png"
    ));
    // Add deco object with rotate animation (and vanilla rotate setup ability)
    GameObjectsFactory::registerGameObject(GameObjectsFactory::createRotatedConfig(
        UNIQ_ID("shine_d_sign_i"), "d_sign_img_01_001.png",
        [](void*) { log::info("setup"); }
    ));
    // Add ring (orb)
    GameObjectsFactory::registerGameObject(
        GameObjectsFactory::createRingConfig(
            UNIQ_ID("test-ring"),
            "d_ball_06_001.png",
            [](EnhancedGameObject* object, PlayerObject* plr) {
                plr->spiderTestJump(true); log::info("activated by player, {}, {}", object, plr);
            }
        )->onEditObjectSpecial(
            [](EditorUI* ui, GameObject* game) {
                queueInMainThread([]() // run this code after FLAlertLayer is shown to get it
                    {
                        auto alert = CCScene::get()->getChildByType<FLAlertLayer>(-1);
                        if (!alert) return;
                        auto title = alert->m_mainLayer->getChildByType<CCLabelBMFont>(0);
                        if (!title) return;
                        title->setString("My Custom Orb...");
                    }
                );
                return false; // call default onEditObjectSpecial, if you set true it will be skipped
            }
        )
    );
}
```
