#include "include/client.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>

using json = nlohmann::json;


Client::Client(const std::string& host, int port)
        : network(host, port)
{
    player_id = network.get_player_id();
    std::cout << "Connected as Player " << player_id << std::endl;

    // --------- Hier bitte eure eigenen Spieler erstellen, nach der Logik von euch --------------------
    bool is_blue = (player_id == "1"); 
    player = create_player(is_blue, 120000);
    // -------------------------------------------------------------------------------------------------
}

void Client::run()
{
    while (true) {
        try {
            // Kontinuerlich get-Anfragen senden
            std::string response = network.send("\"get\"");
            handleState(response);

            // Funktion wie bei pygame clock, um Server nicht zu überfluten
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        } catch (const std::exception& e) {
            std::cerr << "Client error: " << e.what() << std::endl;
            break;
        }
    }
}

void Client::handleState(const std::string& json_str)
{
    json state = json::parse(json_str);

    // Auf Verbindung warten Symbole
    if (!state["bothConnected"]) {
        static const std::string spinner[] = {
            "[|]", "[/]", "[-]", "[\\]"
        };
        std::cout << "\r" << spinner[std::rand() % 4] << std::flush;
        return;
    }

    // Verarbeitung von state-Zuständen
    if (state["end"]) {
        std::cout << "Game over." << std::endl;
        std::cout << "Final board:\n" << state["board"] << std::endl;
        return;
    }

    std::string turn = state["turn"];

    bool isMyTurn = (turn == "r" && player_id == "0") || (turn == "b" && player_id == "1");

    if (!isMyTurn) return;

    std::string fen = state["board"];

    // ----------- Bitte hier wieder eigene Logik einbauen, um von einem Fen-String einen Zug zu generieren ----------------
    Board board(fen);  
    Move move = player->get_move(board);
    json moveJson = move.to_fen();
    // ---------------------------------------------------------------------------------------------------------------------


    std::string reply = network.send(moveJson.dump());
}