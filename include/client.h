#pragma once

#include <memory>
#include <string>
#include "network.h"
#include "player/player.h"
#include "board.h"
#include "move.h"


/**
 * @file client.h
 * @brief Client-Klasse, welche sich um die Verbindung zum Server kümmert.
 *  - verbindet sich zum Server
 *  - schickt get-Anfragen
 *  - wartet auf Antwort
 *  - verarbeitet Antwort und generiert Zug
 *  - schickt Zug als Fen-String zurück
 */

class Client {
public:
    /**
     * @brief Baut einen Client, basierend auf dem Player-Type (bitte Logik ggf. anpassen) und Host und Port
     * @param host IP Adresse vom Server
     * @param port Port vom Server
     */
    // ------------- Muss auf eure Logik angepasst werden (Konstruktor eures Spielers) -------------------
    Client(const std::string& host, int port);
    // ---------------------------------------------------------------------------------------------------

    /**
     * @brief Startet die Client-Loop und schickt kontinuierlich get-Anfragen
     */
    void run();

private:
    std::unique_ptr<Player> player; 
    Network network;
    std::string player_id;          

    /**
     * @brief Verarbeitet ein vom Server geschicktes Board
     * @param json_str JSON String vom Server
     */
    void handleState(const std::string& json_str);
};