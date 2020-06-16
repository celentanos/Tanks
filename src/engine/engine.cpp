#include "engine.h"

Engine::Engine() {}

Engine &Engine::getEngine()
{
    static Engine engine;
    return engine;
}

std::string Engine::intToString(int num)
{
    if (num == 0)
        return "0";

    std::string buf;
    bool        negative = false;
    if (num < 0) {
        negative = true;
        num      = -num;
    }
    for (; num; num /= 10)
        buf = "0123456789abcdef"[num % 10] + buf;
    if (negative)
        buf = "-" + buf;
    return buf;
}

void Engine::initModules()
{
    m_renderer      = std::make_unique<Renderer>();
    m_sprite_config = std::make_unique<SpriteConfig>();
}

void Engine::destroyModules()
{
    m_renderer.reset(nullptr);
    m_sprite_config.reset(nullptr);
}

Renderer *Engine::getRenderer() const { return m_renderer.get(); }

SpriteConfig *Engine::getSpriteConfig() const { return m_sprite_config.get(); }
