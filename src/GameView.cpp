//
// Created by Yiyang Zhao on 18/10/2017.
// Additional work by Ivan & Yosef
//


#include "GameView.h"

#include <iostream>

/**Create the game window*/
GameView::GameView(float length, float width):
    App(sf::VideoMode(length, width, 32), "Clear",  sf::Style::Default){}


/**
  Check if window is open
  @return bool
*/
bool GameView::isOpen() {return App.isOpen();}


/**Updates the view and logic at each frame*/
void GameView::update() {
    check_mouse_position();
    check_keyboard_in();
    draw();
}


/**
  Assigns a GameLogic to this view
  @param logic is the GameLogic associated with this view
*/
void GameView::set_GameLogic(GameLogic &logic) {this->logic = &logic;}


/**
  Make block shapes based on their properties
  @param Normal_Block to draw
  @return sf::RectangleShape
*/
sf::RectangleShape GameView::make_block_shape(int block) {
    sf::RectangleShape block_shape(sf::Vector2f(block_size, block_size));
    block_shape.setFillColor(sf::Color::White);
    if (block>=20) {block_shape.setTexture(&texture[block%20]);}//TODO probably a bug here; didn't seem intended to do anything with block>23
    return block_shape;
}

void GameView::load_texture(int texture_index) {
    if (!texture[texture_index].loadFromFile(texture_filepaths[texture_index])) {
        texture[texture_index].loadFromFile(texture_filepaths[texture_index]+1);
        //Converts ../* to ./*
    }
}

void GameView::load_textures() {
    for (int i=0; i<4; i++) {load_texture(i);}
}


/**
  Make shadow shapes
  @return sf::RectangleShape shadow_shape
*/
sf::RectangleShape GameView::make_shadow_shape() {
    sf::RectangleShape shadow_shape(sf::Vector2f(block_size, block_size));
    shadow_shape.setFillColor(sf::Color(0, 0, 0, 60));
    return shadow_shape;
}


/**Create all of the shapes*/
void GameView::init() {
    int board_width = logic->get_board_width();
    int board_height = logic->get_board_height();
    
    load_textures();

    sf::RectangleShape * shapes;
    sf::RectangleShape * shadows;

    shapes = new sf::RectangleShape[board_width*board_height];
    shadows = new sf::RectangleShape[board_width*board_height];

    for (int x=0; x<board_width; x++) {
        for (int y=0; y<board_height; y++) {
            if (logic->get_block(x, y) != 0) {
                shapes[(y*board_width)+x] = make_block_shape(logic->get_block(x, y));
                shadows[(y*board_width)+x] = make_shadow_shape();
            }
        }
    }
    this->block_shapes = shapes;
    this->shadow_shapes = shadows;
}


//TODO FIX THIS
/**Checks if mouse has clicked on a block*/
void GameView::check_mouse_position() {
    int current_y = App.getSize().y;
    int current_x = App.getSize().x;
    int mouse_x = sf::Mouse::getPosition(App).x;
    int mouse_y = sf::Mouse::getPosition(App).y;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        logic->set_selected_position(((mouse_y - top_spacing) * 600 / block_size) / current_y,
                                     ((mouse_x - left_spacing) * 800 / block_size) / current_x);
    }

}


/**Draws an outline around a block if it is selected*/
void GameView::draw_selected_block() {
    if (logic->get_selected_block()!=0) {
        int index = (logic->get_selected_y() * logic->get_board_width()) + logic->get_selected_x();
        block_shapes[index].setOutlineThickness(3.5);
        block_shapes[index].setOutlineColor(sf::Color::Red);
        App.draw(block_shapes[index]);
    }
}


/**Draw all blocks, shadows, movements, and selections*/
void GameView::draw() {//TODO split this into functions for drawing each thing.
    poll_event();
    App.clear(sf::Color(120, 180, 255));
    int width = logic->get_board_width();
    int height = logic->get_board_height();
    // shadow drawing pass
    for (int i=0; i<height*width; i++) {
        if (logic->get_block(i/height, i%width) != 0) {
            shadow_shapes[i].setPosition((i%width)*block_size + left_spacing + (block_size/5),
                                         (i/height)*block_size + top_spacing + (block_size/5));
            App.draw(shadow_shapes[i]);
        }
    }
    // block drawing pass
    for (int i=0; i < logic->get_board_width()*logic->get_board_height(); i++) {
        if (logic->get_block(i/height, i%width) != 0) {
            block_shapes[i].setOutlineThickness(0);
            block_shapes[i].setPosition((i%width)*block_size + left_spacing,
                                        (i/height)*block_size + top_spacing);
            App.draw(block_shapes[i]);
        }
    }
    draw_selected_block();
    App.display();
}


/**Checks keyboard input, sends input to logic for handling*/
void GameView::check_keyboard_in() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {logic->try_move("up");}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {logic->try_move("down");}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {logic->try_move("left");}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {logic->try_move("right");}
}


/**Check events*/
void GameView::poll_event(){
    sf::Event Event;
    while(App.pollEvent(Event)){
        switch (Event.type) {
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){App.close();}
                break;
            case sf::Event::Closed:
                App.close();
                break;
            default: break;
        }
    }
}
