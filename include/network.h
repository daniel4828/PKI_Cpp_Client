#pragma once
/**
 * @file network.h
 * @brief Regelt die Netzwerk Verbindung für den Client mit Boost.Asio
 */

#include <string>
#include <boost/asio.hpp>

/**
 * @class Network
 * @brief Regelt die Netzwerk Verbindung via TCP
 */
class Network {
public:
    /**
     * @brief Konstruktor, der sich zum Server verbindet
     * @param host IP des Servers
     * @param port Port des Server
     */
    Network(const std::string& host, int port);

    /**
     * @brief Gibt die zugeteilte player_id zurück
     */
    std::string get_player_id() const;

    /**
     * @brief Schickt einen String (JSON)
     * @param data Raw String, der verschickt werden soll
     * @return Server Antwort
     * @throws std::runtime_error bei send/receive Fehler
     */
    std::string send(const std::string& data);

private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket;
    std::string player_id;
};