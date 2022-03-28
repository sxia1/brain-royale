// The ASIO_STANDALONE define is necessary to use the standalone version of Asio.
// Remove if you are using Boost Asio.
#define ASIO_STANDALONE

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include <string>
 
#include <functional>
#include <iostream>

#include "json.hpp"

typedef websocketpp::server<websocketpp::config::asio> server;
typedef websocketpp::config::asio::message_type::ptr message_ptr;
typedef nlohmann::json json;

void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    // s->get_alog().write(websocketpp::log::alevel::app, "Received Reply: "+msg->get_payload());
    json message = json::parse(msg->get_payload());
    std::cout << message << std::endl;
    std::string responseType = message["type"];
    if (responseType == "connected") {
        json response = R"({
            "type" : "connect",
            "data" : null
        })"_json;
        s->send(hdl, response.dump(), websocketpp::frame::opcode::text);
    }
    // s->close(hdl,websocketpp::close::status::normal,"");
}

void on_close(server* s, websocketpp::connection_hdl) {
    std::cout << "Some connection closed" << std::endl;
}

class utility_server {
public:
    utility_server() {
         // Set logging settings
        m_endpoint.set_error_channels(websocketpp::log::elevel::all);
        m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
        m_endpoint.set_close_handler(std::bind(&on_close, &m_endpoint, std::placeholders::_1));
        m_endpoint.set_message_handler(std::bind(&on_message, &m_endpoint, std::placeholders::_1, std::placeholders::_2));
 
        // Initialize Asio
        m_endpoint.init_asio();
    }
 
    void run() {
        // Listen on port 9002
        m_endpoint.listen(8000);
 
        // Queues a connection accept operation
        m_endpoint.start_accept();
 
        // Start the Asio io_service run loop
        m_endpoint.run();
    }
private:
    server m_endpoint;
};
 
int main() {
    utility_server s;
    s.run();
    return 0;
}