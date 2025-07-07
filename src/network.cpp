#include "include/network.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using boost::asio::ip::tcp;

// Verbindung zum Netzwerk aufbauen mit Boost
Network::Network(const std::string& host, int port)
        : socket(io_context)
{
    try {
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host, std::to_string(port));
        boost::asio::connect(socket, endpoints);

        char raw[16];
        boost::system::error_code ec;
        std::size_t len = socket.read_some(boost::asio::buffer(raw), ec);

        if (ec) {
            throw std::runtime_error("Lesen fehlgeschlagen: " + ec.message());
        }

        player_id = std::string(raw, len);
        
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Verbindung fehlgeschlagen: ") + e.what());
    }
}

std::string Network::get_player_id() const {
    return player_id;
}

std::string Network::send(const std::string& data)
{
    try {
        // Nachricht senden
        boost::asio::write(socket, boost::asio::buffer(data + "\n"));

        // Antwort empfangen
        char raw[4096];
        boost::system::error_code ec;
        std::size_t len = socket.read_some(boost::asio::buffer(raw), ec);

        if (ec) {
            throw std::runtime_error("Lesen fehlgeschlagen " + ec.message());
        }

        return std::string(raw, len);
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Netzwerk Kommunikation fehlgeschlagen ") + e.what());
    }
}