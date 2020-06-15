#ifndef ENGINE_H
#define ENGINE_H

#include "renderer.h"
#include "spriteconfig.h"

#include <memory>

/**
 * @brief Klasa łączy elementy związane z działaniem programu.
 */
class Engine {
  public:
    Engine();

    /**
     * @return statyczną instancję obiektu @a Engine
     */
    static Engine &getEngine(); // silnik może być dostępny w każdym module korzystając jedynie z przestrzeni nazw a nie wskaźnika
    /**
     * Funkcja zamienia podaną wartość liczbową na tekst.
     * @param num - liczba całkowita
     * @return liczbę całkowitą jako tekst
     */
    static std::string intToString(int num);
    /**
     * Funkcja tworzy obiekty składowe silnika.
     */
    void initModules();

    /**
     * @return wskaźnik na obiekt Renderer pozwalający rysować na ekranie
     */
    Renderer *getRenderer() const;
    /**
     * @return wsaźnik na obiekt SpriteConfig przechowujący informacjie o teksturach
     */
    SpriteConfig *getSpriteConfig() const;

  private:
    std::unique_ptr<Renderer>     m_renderer{};
    std::unique_ptr<SpriteConfig> m_sprite_config{};
};

#endif // ENGINE_H
