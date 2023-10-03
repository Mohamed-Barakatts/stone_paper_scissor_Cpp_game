// بسم الله
#include <iostream>
#include <cstdlib>
#include <limits> // We must call this library to make the code run correctally during valedate nums.
using namespace std;

// 01:
enum enWinner
{
    Player = 1,
    Computer = 2,
    Draw = 3
};

enum enGameChoice
{
    Stone = 1,
    Paper = 2,
    Scissor = 3
};

string winner_name(enWinner winner) // to know who is the game winner
{
    string arr_winner_game_name[3] = {"Player", "Computer", "No Winner (Draw Case)"};
    return arr_winner_game_name[winner - 1];
}

string choice_name(enGameChoice choice) // to know the name of any choice has been chosen
{
    string arr_any_choice_name[3] = {"Stone", "Paper", "Scissor"};
    return arr_any_choice_name[choice - 1];
}

// 02:
struct stRoundInfo // Set each round info of the game.
{
    short round_num = 0;
    enGameChoice player_choice;
    enGameChoice computer_choice;
    enWinner round_winner; // to change the terminal background color according to it.
    string winner_name;    // to print ["Player", "Computer", "No Winner [Draw Case] in the print_round_info.
};

struct stGameResults // The results after finishing the game (all rounds).
{
    short game_rounds = 0;
    short player_win_times = 0;
    short computer_win_times = 0;
    short draw_times = 0;
    enWinner game_winner;
    string winner_name = "";
};

enWinner round_winner(stRoundInfo round_info)
// A func from enWinner enum to know the winner of each round of the game. So it took a var from stRoundInfo struct as a pram to compare.
{
    if (round_info.computer_choice == round_info.player_choice)
    {
        return enWinner::Draw;
    }
    switch (round_info.player_choice)
    {
    case enGameChoice::Stone:
        if (round_info.computer_choice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (round_info.computer_choice == enGameChoice::Scissor)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissor:
        if (round_info.computer_choice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player;
}

enWinner game_winner(short player_win_times, short computer_win_times)
{
    if (computer_win_times > player_win_times)
    {
        return enWinner::Computer; // It's allow to use the return with a function that has the same type return.
    }
    else if (player_win_times > computer_win_times)
    {
        return enWinner::Player;
    }
    return enWinner::Draw;
}

// 03: Some VI funcs and procs
int random_num(int from, int to)
{
    int rand_num = rand() % (to - from + 1) + from;
    return rand_num;
}

void reset_terminal_screen()
{
    system("cls");
    system("color 0F");
}

string tabs(int num_of_tabs)
{
    string t = "";
    for (int i = 0; i < num_of_tabs; i++)
    {
        t += "\t";
    }
    return t;
}

void set_winner_screen_color(enWinner winner) // To change the terminal background color. winner ==> [1,2,3]
{
    switch (winner)
    {
    // winner = 1
    case enWinner::Player:
        system("color 2F"); // green ==> the winner is the player.
        break;
    // winner = 2
    case enWinner::Computer:
        system("color 4F"); // Red ==> the winner is the computer.
        cout << "\a";
        break;

    default:
        system("color 6F"); // Yellow ==> A Draw case.
        // winner = 3
        break;
    }
}

short rounds_count()
{
    short rounds = 0;
    // Do-While Loop ==> To check that the num is between 1 and 10.
    // While Loop ==> To check that the input is just nums.
    do
    {
        cout << "\nHow many rounds will you play 1 to 10? : ";
        cin >> rounds;
        while (cin.fail()) // true => NOT num.
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input! Please enter only numbers: ";
            cin >> rounds;
        }
    } while (rounds < 1 || rounds > 10);

    return rounds;
}

// 04:
enGameChoice read_player_choice()
{
    short choice = 1;
    do
    {
        cout << "Your choice:  [1]:Stone, [2]:Paper, [3]:Scissors? : ";
        cin >> choice;
        while (cin.fail()) // true => NOT num.
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input! Please enter only numbers: ";
            cin >> choice;
        }
    } while (choice < 1 || choice > 3);

    return (enGameChoice)choice;
    /*that line ((enGameChoice)choice) means:
    1 ==> enGameChoice::Stone;
    2 ==> enGameChoice::Paper;
    3 ==> enGameChoice::Scissors; like :
    return (int)choice; */
}

enGameChoice get_computer_choice()
{
    return (enGameChoice)random_num(1, 3);
}

void print_round_info(stRoundInfo round_info)
{
    cout << "\n____________Round [" << round_info.round_num << "] ____________\n\n";
    cout << "Player1  Choice: " << choice_name(round_info.player_choice) << endl;
    cout << "Computer Choice: " << choice_name(round_info.computer_choice) << endl;
    cout << "Round Winner   : [" << round_info.winner_name << "]\n";
    cout << "__________________________________\n\n";
    set_winner_screen_color(round_info.round_winner);
}

stGameResults fill_game_results(short game_rounds, short player_win_times, short computer_win_times, short draw_times)
// A VVI func to fill the structure with the needed values.
{
    stGameResults game_results; // <== A var from stGameResults data structure type
    game_results.game_rounds = game_rounds;
    game_results.player_win_times = player_win_times;
    game_results.computer_win_times = computer_win_times;
    game_results.draw_times = draw_times;
    game_results.game_winner = game_winner(player_win_times, computer_win_times);
    game_results.winner_name = winner_name(game_results.game_winner);

    return game_results; // <== we must do this
}

// 05:
// So I func (the main func of the game)
stGameResults play_game(short rounds_count)
// the same type (stGameResults) of what it will return ==> (fill_game_results), we can't write --> 'stRoundInfo' play_game(short rounds_count)
{
    stRoundInfo round_info;
    short player_win_times = 0, computer_win_times = 0, Draw_times = 0;

    for (short game_round = 1; game_round <= rounds_count; game_round++)
    {
        cout << "\nRound [" << game_round << "] begins.\n";
        round_info.round_num = game_round;
        round_info.player_choice = read_player_choice(); // After this line it will print print_round_info(round_info) in the terminal.
        round_info.computer_choice = get_computer_choice();
        round_info.round_winner = round_winner(round_info);
        round_info.winner_name = winner_name(round_info.round_winner);

        if (round_info.round_winner == enWinner::Player)
        {
            player_win_times++;
        }
        else if (round_info.round_winner == enWinner::Computer)
        {
            computer_win_times++;
        }
        else
        {
            Draw_times++;
        }
        print_round_info(round_info);
    }
    return fill_game_results(rounds_count, player_win_times, computer_win_times, Draw_times); // Pass the prams to be filled in fill_game_results()
}

// 06:
void game_over(stGameResults game_results)
{
    string final_winner = "No Winner [Draw Case]";
    cout << "\n\n";
    cout << tabs(3) << "__________________________________________________________________\n\n";
    cout << tabs(3) << "                +++++ G a m e   O v e r +++++ \n";
    cout << tabs(3) << "__________________________________________________________________\n\n";
    cout << tabs(3) << "________________________ [ Game Results ] ________________________\n";
    cout << tabs(3) << "Game Rounds        : " << game_results.game_rounds << endl;
    cout << tabs(3) << "Player won times   : " << game_results.player_win_times << endl;
    cout << tabs(3) << "Computer won times : " << game_results.computer_win_times << endl;
    cout << tabs(3) << "Draw times         : " << game_results.draw_times << endl;
    cout << tabs(3) << "Final Winner       : [" << game_results.winner_name << "]\n";
    set_winner_screen_color(game_results.game_winner);
}

void start_the_game()
{
    char play_again = 'Y';
    do
    {
        reset_terminal_screen();
        stGameResults game_results = play_game(rounds_count()); // An structure to get the needed info to be printed in game_over(game_results); func.
        game_over(game_results);
        cout << endl;
        cout << tabs(3) << "Do you want to play again? Y/N? ";
        cin >> play_again;
        if (play_again != 'Y' || play_again != 'y')
            system("color 0F"); // to return the terminal to its default color.
    } while (play_again == 'Y' || play_again == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    start_the_game();
    return 0;
}