#include "server/client.h"
#include "player/player.h"

int main() {
    // ---------------- Bitte hier eigenen Spieler eintragen (siehe Konstruktor client) -------------------- 
    Client client(player_type::alphabeta_v2, "localhost", 5555);
    client.run();
    return 0;
}