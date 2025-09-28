#ifndef SIMPLEGUI
#define SIMPLEGUI

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>

namespace simpleGUI {
    namespace sgui = simpleGUI;

    struct Mouse {
        private:
            bool mb1;
            bool mb2;
            bool mb3;
            
            sf::Vector2i mousePosition;

        public:
            Mouse() {
                mb1 = false;
                mb2 = false;
                mb3 =  false;

                mousePosition = {0, 0};
            }

            void update(bool pMB1, bool pMB2, bool pMB3, sf::Vector2i pMousePos) {
                mb1 = pMB1;
                mb2 = pMB2;
                mb3 = pMB3;

                mousePosition = pMousePos;
            }

            /*
            * Key = Mouse Key To Check:
            * 0   = Left
            * 1   = Right
            * 2   = Middle (Wheel)
            */
            bool isPressed(int key) {
                switch (key) {
                    case 0:
                        return mb1;
                        break;
                    case 1:
                        return mb2;
                        break;
                    case 2:
                        return mb3;
                        break;
                }
            }

            sf::Vector2i getMousePosition() {
                return mousePosition;
            }
    };

    Mouse mouse = Mouse();

    /*
    * MB = Mouse Button: true = isPressed!
    * 1   = Left
    * 2   = Right
    * 3   = Middle (Wheel)
    * 
    * MousePosition = MousePosition in window!
    */
    inline void updateMouse(bool pMB1, bool pMB2, bool pMB3, sf::Vector2i pMousePos) {
        mouse.update(pMB1, pMB2, pMB3, pMousePos);
    }

    inline void emptyFunction() {
        std::cout << "\nThis Function Is Empty!\n";
    };

    enum class STATE {
        Normal   = 0,
        Active   = 1,
        Hovered  = 2,
        Disabled = 3
    };

    /*
     * Standart AABB Collision Check
    */
    inline bool aabbCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2 = 1, float h2 = 1) {
        if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2) {
            return true;
        } return false;
    }

    struct Widget {
        protected:
            std::unique_ptr<sf::RenderWindow> master = nullptr; //! Kepp In Mind!

            sf::Color textColorNormal;
            sf::Color textColorHovered;
            sf::Color textColorActive;
            sf::Color textColorDisabled;

            sf::Color backgroundColorNormal;
            sf::Color backgroundColorHovered;
            sf::Color backgroundColorActive;
            sf::Color backgroundColorDisabled;

            float outlineThickness = 0;
            sf::Color outlineColorNormal;
            sf::Color outlineColorHovered;
            sf::Color outlineColorActive;
            sf::Color outlineColorDisabled;

            int positionX = 0;
            int positionY = 0;

            int height = 0;
            int width = 0;

            int padX = 0;
            int padY = 0;

        public:
            Widget() {};
            virtual void update(Mouse* pMouse) {};
            virtual void render() {};
    };

    struct Button : Widget {
        private:
            sf::Font font;
            sf::Text text= sf::Text(font, "", 0);

            void (*command)() = sgui::emptyFunction;

            bool hasTexture = true;
            sf::Texture texture;


            STATE state;

        public:
            inline Button(std::unique_ptr<sf::RenderWindow> pMaster, std::string pText = "", int x = 0, int y = 0, void (&pCommand)() = sgui::emptyFunction) {
                master = std::move(pMaster);
                text = sf::Text(font, pText, 16);
                text.setPosition({x, y});
                command = pCommand;
            }

            inline void setText(std::string pText, int size, std::string fontPath, int r = 255, int g = 255, int b = 255, int a = 255) {
                font.openFromFile(fontPath);
                text.setString(pText);
                text.setFont(font);
                text.setCharacterSize(size);
                text.setFillColor(sf::Color(r, g, b, a));
            }

            inline void setTextColors(int r = 255, int g = 255, int b = 255, int a = 255) {
                
                textColorNormal   = sf::Color(r, g, b, a);
                textColorHovered  = sf::Color(
                    std::min(r+5, 255), 
                    std::min(g+5, 255), 
                    std::min(b+5, 255), 
                    std::min(a+5, 255));
                textColorActive   = sf::Color(
                    std::min(r+15, 255), 
                    std::min(g+15, 255), 
                    std::min(b+15, 255), 
                    std::min(a+15, 255));
                textColorDisabled = sf::Color(
                    std::max(r-20, 0), 
                    std::max(g-20, 0), 
                    std::max(b-20, 0), 
                    std::max(a-20, 0));
            }

            inline void setBackgroundColors(int r = 255, int g = 255, int b = 255, int a = 255) {
                
                backgroundColorNormal   = sf::Color(r, g, b, a);
                backgroundColorHovered  = sf::Color(
                    std::min(r+5, 255), 
                    std::min(g+5, 255), 
                    std::min(b+5, 255), 
                    std::min(a+5, 255));
                backgroundColorActive   = sf::Color(
                    std::min(r+15, 255), 
                    std::min(g+15, 255), 
                    std::min(b+15, 255), 
                    std::min(a+15, 255));
                backgroundColorDisabled = sf::Color(
                    std::max(r-20, 0), 
                    std::max(g-20, 0), 
                    std::max(b-20, 0), 
                    std::max(a-20, 0));
            }

            inline void setoutlineColors(int r = 255, int g = 255, int b = 255, int a = 255) {
                
                outlineColorNormal   = sf::Color(r, g, b, a);
                outlineColorHovered  = sf::Color(
                    std::min(r+5, 255), 
                    std::min(g+5, 255), 
                    std::min(b+5, 255), 
                    std::min(a+5, 255));
                outlineColorActive   = sf::Color(
                    std::min(r+15, 255), 
                    std::min(g+15, 255), 
                    std::min(b+15, 255), 
                    std::min(a+15, 255));
                outlineColorDisabled = sf::Color(
                    std::max(r-20, 0), 
                    std::max(g-20, 0), 
                    std::max(b-20, 0), 
                    std::max(a-20, 0));
            }


            inline void setCommand(void (&pCommand)()) {
                command = pCommand;
            }

            inline void update(Mouse* pMouse) override {
                sf::Vector2i mousePos = pMouse->getMousePosition();
                //* AABB calculation
                if (aabbCollision(positionX, positionY, width, height, mousePos.x, mousePos.y)) {
                    if (pMouse->isPressed(0)) {
                        if (state != STATE::Active) {
                            state = STATE::Active;
                            command();
                        }
                    } else {
                        state = STATE::Hovered;
                    }
                }
            }

            inline void render() override {
                sf::Color textCol;
                sf::Color outlineCol;
                sf::Color backgroundCol;

                switch (state) {
                    case STATE::Active:
                        textCol        = textColorActive;
                        outlineCol     = outlineColorActive;
                        backgroundCol  = backgroundColorActive;
                        break;
                    case STATE::Hovered:
                        textCol        = textColorHovered;
                        outlineCol     = outlineColorHovered;
                        backgroundCol  = backgroundColorHovered;
                        break;
                    case STATE::Normal:
                        textCol        = textColorNormal;
                        outlineCol     = outlineColorNormal;
                        backgroundCol  = backgroundColorNormal;
                        break;
                    case STATE::Disabled:
                        textCol        = textColorDisabled;
                        outlineCol     = outlineColorDisabled;
                        backgroundCol  = backgroundColorDisabled;
                        break;
                }

                sf::RectangleShape outerRect(sf::Vector2f(width, height));
                outerRect.setPosition(sf::Vector2f(positionX, positionY));
                outerRect.setFillColor(backgroundCol);
                outerRect.setOutlineColor(outlineCol);
                outerRect.setOutlineThickness(outlineThickness);

                master->draw(outerRect);
            }



            inline void disableButton(bool disable = true) {
                if (!disable) {
                    state = STATE::Normal;
                } else {
                    state = STATE::Disabled;
                }
            }

            inline std::string getText() {
                return text.getString();
            }
    };

    struct Label : Widget{
        private:
                sf::Font font;
                sf::Text text= sf::Text(font, "", 0);

                bool hasTexture = true;
                sf::Texture texture;

        public:
            inline Label(std::unique_ptr<sf::RenderWindow> pMaster, std::string pText = "", float x = 0, float y = 0) {
                master = std::move(pMaster);
                text = sf::Text(font, pText, 16);
                text.setPosition({x, y});
            }
    

                
            inline void update(Mouse* pMouse) {

            }

            inline void render() {

            }
            std::string getText() {
                return text.getString();
            }
    };



    



    std::vector<std::variant<Button, Label>> objectVector;

    inline void updateObjects(bool* runUpdateThread, bool* pauseUpdateThread, std::vector<std::variant<Button, Label>>* objectVectorPtr, Mouse* pMouse) {
        while (runUpdateThread) {
            if (!*pauseUpdateThread) {
                for (auto& obj : objectVector) {
                    std::visit([&](auto& o) {
                        o.update(pMouse);
                        o.render();
                    }, obj);
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }

    bool updateThreadRunning = true;
    bool pauseUpdateThread   = false;

    inline void startUpdateThread() {
        std::thread updateThread(updateObjects, &updateThreadRunning, &pauseUpdateThread, &objectVector, &mouse);
    }
}

#endif