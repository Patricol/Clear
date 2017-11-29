//
// Created by Yiyang Zhao on 18/10/2017
// Additional work by Ivan & Yosef
//

#ifndef CLEAR_GAMEVIEW_H
#define CLEAR_GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Normal_Block.h"
#include "GameLogic.h"


static char texture_filepaths[4][40] = {"../resources/up.png",
                                        "../resources/right.png",
                                        "../resources/down.png",
                                        "../resources/left.png"};

class GameView {
    private:
        sf::Texture texture[15];
        sf::RectangleShape * block_shapes;
        sf::RectangleShape * shadow_shapes;
        sf::RectangleShape * path_shapes;
        sf::Shader selected_shader;
        sf::CircleShape selected_shadow;
        GameLogic * logic;
        sf::Sprite tab;
        int default_window_width = 600;
        int default_window_height = 600;
        int bottom_spacing = 50;
        int left_spacing = 50;
        char dir = 'n';
        bool clicked = false;
        int mouse_x_start;
        int mouse_y_start;
        int deadzone = 10;
    public:
        int block_size = 50;
        sf::RenderWindow App;
        sf::RenderWindow get_App();
        void set_GameLogic(GameLogic &logic);
        GameView();
        void init();
        bool isOpen();
        sf::RectangleShape make_block_shape(int block_id);
        sf::RectangleShape make_shadow_shape();
        sf::RectangleShape make_path_shape(int w, int h);
        void make_selected_shadow();
        void load_texture(int);
        void load_textures();
        void draw();
        void draw_shadows();
        void draw_path_highlighting();
        void draw_blocks();
        void draw_selected_block();
        int BoardXToXPixel(int x);
        int BoardYToYPixel(int y);
        int XPixelToBoardX(int x);
        int YPixelToBoardY(int y);
        void poll_event();
        void check_mouse_position();
        void check_keyboard_in();
        void update();
};


#endif //CLEAR_GAMEVIEW_H
