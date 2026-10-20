#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

static bool bufferEnabled() { return Mod::get()->getSettingValue<bool>("enabled"); }
static int extraFrames() { return static_cast<int>(Mod::get()->getSettingValue<int64_t>("extra-frames")); }

struct PlayerBuf { bool held = false; bool releaseQueued = false; int framesSincePress = 0; int button = 1; };

class $modify(BufferedGL, GJBaseGameLayer) {
    struct Fields { PlayerBuf p[2]; bool injecting = false; };

    void sendRaw(bool down, int button, bool isP1) {
        m_fields->injecting = true;
        GJBaseGameLayer::handleButton(down, button, isP1);
        m_fields->injecting = false;
    }

    void handleButton(bool down, int button, bool isP1) {
        if (m_fields->injecting || !bufferEnabled() || extraFrames() <= 0) {
            GJBaseGameLayer::handleButton(down, button, isP1);
            return;
        }
        auto& s = m_fields->p[isP1 ? 0 : 1];
        if (down) {
            if (s.releaseQueued) { s.releaseQueued = false; sendRaw(false, s.button, isP1); }
            s.held = true; s.framesSincePress = 0; s.button = button;
            GJBaseGameLayer::handleButton(true, button, isP1);
            return;
        }
        if (s.held && s.framesSincePress < extraFrames()) { s.releaseQueued = true; return; }
        s.held = false;
        GJBaseGameLayer::handleButton(false, button, isP1);
    }

    void processCommands(float dt, bool isHalfTick, bool isLastTick) {
        GJBaseGameLayer::processCommands(dt, isHalfTick, isLastTick);
        for (int i = 0; i < 2; i++) {
            auto& s = m_fields->p[i];
            if (!s.held) continue;
            s.framesSincePress++;
            if (s.releaseQueued && s.framesSincePress >= extraFrames()) {
                s.releaseQueued = false; s.held = false;
                sendRaw(false, s.button, i == 0);
            }
        }
    }
};

class $modify(BufferPause, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();
        auto winSize = CCDirector::get()->getWinSize();
        auto spr = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
        spr->setScale(0.6f);
        auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(BufferPause::onBufferSettings));
        auto menu = CCMenu::create();
        menu->addChild(btn);
        menu->setPosition({ winSize.width - 30.f, 30.f });
        menu->setID("input-buffer-menu"_spr);
        this->addChild(menu);
    }
    void onBufferSettings(CCObject*) { geode::openSettingsPopup(Mod::get()); }
};
