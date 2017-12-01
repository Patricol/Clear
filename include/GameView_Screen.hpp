#ifndef CLEAR_GAMEVIEW_SCREEN_HPP
#define CLEAR_GAMEVIEW_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include "GameLogic.hpp"
#include "Screen_Abstract.hpp"

static char texture_filepaths[8][40] = {UP_TEXTURE,
                                        RIGHT_TEXTURE,
                                        DOWN_TEXTURE,
                                        LEFT_TEXTURE,
                                        ROTATING_0_TEXTURE,
                                        ROTATING_1_TEXTURE,
                                        ROTATING_2_TEXTURE,
                                        ROTATING_3_TEXTURE};

class GameView_Screen : public Screen_Abstract {
    private:
        sf::RenderWindow *App;
        sf::Texture texture[15];
        sf::RectangleShape * block_shapes;
        sf::RectangleShape shadow_shape;
        sf::RectangleShape restriction_shape;
        sf::RectangleShape * path_shapes;
        sf::RectangleShape * tab_shapes;
        sf::RectangleShape * double_tab_shapes;
        GameLogic * logic;
        float ** animation_ms;
        char ** animation_dir;
        int default_window_width = 600;
        int default_window_height = 600;
        int bottom_spacing = 75;
        int left_spacing = 75;
        char dir = DEFAULT_DIR;
        bool clicked = false;
        bool running = true;
        int mouse_x_start;
        int mouse_y_start;
        int deadzone = 10;
    public:
        int block_size = 50;
        sf::RenderWindow get_App();
        void set_GameLogic(GameLogic &logic);
        GameView_Screen();
        void init();
        bool isOpen();
        sf::RectangleShape make_block_shape(int block_id);
        sf::RectangleShape make_tab_shape(char dir);
        sf::RectangleShape make_double_tab_shape(char dir);
        sf::RectangleShape make_alpha_rectangle_shape(int, int, int, int, int, int);
        void load_texture(int);
        void load_textures();
        void draw(int);
        void draw_shadows();
        void draw_path_highlighting();
        void draw_blocks(int);
        void draw_tab(int, int, int);
        void draw_double_tab(int, int, int);
        void draw_tabs();
        void draw_selected_block();
        int BoardXToXPixel(int x);
        int BoardYToYPixel(int y);
        int XPixelToBoardX(int x);
        int YPixelToBoardY(int y);
        int run(sf::RenderWindow &window);
        void check_mouse_input();
        void check_keyboard_input();
};

#endif //CLEAR_GAMEVIEW_HPP
