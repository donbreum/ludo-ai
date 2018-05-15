#include "dialog.h"
#include <QApplication>
#include "game.h"
#include <vector>
#include "ludo_player.h"
#include "ludo_player_random.h"
#include "positions_and_dice.h"
#include <time.h>
#include "rl_player.h"


#define NUM_OF_GAMES_TO_PLAY 5
#define DELAY_GAME 0

Q_DECLARE_METATYPE( positions_and_dice )

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    qRegisterMetaType<positions_and_dice>();

    //instanciate the players here
//    ludo_player p1, p2;
//    ludo_player_random p3, p4;
    rl_player p1;
    //ludo_player p2,p3;//, p4;
    ludo_player p2,p3,p4;

    game g;
    g.setGameDelay(DELAY_GAME); //if you want to see the game, set a delay

    /* Add a GUI <-- remove the '/' to uncomment block
    Dialog w;
    QObject::connect(&g,SIGNAL(update_graphics(std::vector<int>)),&w,SLOT(update_graphics(std::vector<int>)));
    QObject::connect(&g,SIGNAL(set_color(int)),                   &w,SLOT(get_color(int)));
    QObject::connect(&g,SIGNAL(set_dice_result(int)),             &w,SLOT(get_dice_result(int)));
    QObject::connect(&g,SIGNAL(declare_winner(int)),              &w,SLOT(get_winner()));
    QObject::connect(&g,SIGNAL(close()),&a,SLOT(quit()));
    w.show();
    /*/ //Or don't add the GUI
    QObject::connect(&g,SIGNAL(close()),&a,SLOT(quit()));
    //*/

    //set up for each player
    QObject::connect(&g, SIGNAL(player1_start(positions_and_dice)),&p1,SLOT(start_turn(positions_and_dice)));
    QObject::connect(&p1,SIGNAL(select_piece(int)),                &g, SLOT(movePiece(int)));
    QObject::connect(&g, SIGNAL(player1_end(std::vector<int>)),    &p1,SLOT(post_game_analysis(std::vector<int>)));
    QObject::connect(&p1,SIGNAL(turn_complete(bool)),              &g, SLOT(turnComplete(bool)));

    QObject::connect(&g, SIGNAL(player2_start(positions_and_dice)),&p2,SLOT(start_turn(positions_and_dice)));
    QObject::connect(&p2,SIGNAL(select_piece(int)),                &g, SLOT(movePiece(int)));
    QObject::connect(&g, SIGNAL(player2_end(std::vector<int>)),    &p2,SLOT(post_game_analysis(std::vector<int>)));
    QObject::connect(&p2,SIGNAL(turn_complete(bool)),              &g, SLOT(turnComplete(bool)));

    QObject::connect(&g, SIGNAL(player3_start(positions_and_dice)),&p3,SLOT(start_turn(positions_and_dice)));
    QObject::connect(&p3,SIGNAL(select_piece(int)),                &g, SLOT(movePiece(int)));
    QObject::connect(&g, SIGNAL(player3_end(std::vector<int>)),    &p3,SLOT(post_game_analysis(std::vector<int>)));
    QObject::connect(&p3,SIGNAL(turn_complete(bool)),              &g, SLOT(turnComplete(bool)));

    QObject::connect(&g, SIGNAL(player4_start(positions_and_dice)),&p4,SLOT(start_turn(positions_and_dice)));
    QObject::connect(&p4,SIGNAL(select_piece(int)),                &g, SLOT(movePiece(int)));
    QObject::connect(&g, SIGNAL(player4_end(std::vector<int>)),    &p4,SLOT(post_game_analysis(std::vector<int>)));
    QObject::connect(&p4,SIGNAL(turn_complete(bool)),              &g, SLOT(turnComplete(bool)));

    //time_t start_time = time(NULL);
    for(int i = 0; i < NUM_OF_GAMES_TO_PLAY; ++i){
      cout << "GAME # " << i << endl;
        g.start();
        a.exec();
        g.reset();
        p1.reset(g.number_of_wins);
    }
    p1.print_q_table();
    p1.save_q_table();
    double num_played_games = g.number_of_wins[0] + g.number_of_wins[1] + g.number_of_wins[2] + g.number_of_wins[3];
    cout << "\------------------------"
         << "\nWin total of " << num_played_games << " played games"
         << "\nPlayer 1: " << g.number_of_wins[0] << " times - " << g.number_of_wins[0]/num_played_games*100 << " % winning rate"
         << "\nPlayer 2: " << g.number_of_wins[1] << " times - " << g.number_of_wins[1]/num_played_games*100 << " % winning rate"
         << "\nPlayer 3: " << g.number_of_wins[2] << " times - " << g.number_of_wins[2]/num_played_games*100 << " % winning rate"
         << "\nPlater 4: " << g.number_of_wins[3] << " times - " << g.number_of_wins[3]/num_played_games*100 << " % winning rate"
         << "\n------------------------" << endl;
    //time_t end_time = time(NULL);
    //cout << "Time used to play: "  << NUM_OF_GAMES_TO_PLAY << " games: " << double(end_time-start_time) << " Seconds" << endl;
    return 0;
}
