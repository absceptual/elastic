#include "aimbot.hpp"

#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
aimbot::mouse_t::mouse_t( ) 
: m_ready{ false }, m_conn{ 0 }, m_address{ "127.0.0.1" }, m_port{ 9900 } {

    m_conn = socket( AF_INET, SOCK_STREAM, 0 );
    if ( m_conn == -1 ) {
        perror( "[aimbot::mouse( )] failed to initalize a socket");
    }
    std::cout << "socket intialized!\n";

    struct sockaddr_in socket_address{};
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons( this->m_port ); 
    socket_address.sin_addr.s_addr = inet_addr( this->m_address.data( ) ); 

    // Connect to the socket.
    auto result = connect(
        m_conn,
        reinterpret_cast< const sockaddr * >( &socket_address ),
        sizeof( socket_address ) 
    );
      
    if ( result == -1 ) {
        close( m_conn );
        perror( "[aimbot::mouse( )] failed to connect to the socket (is the spice server running?)");
    }
     std::cout << "connected\n";

    m_ready = true;
    std::string_view message{R"({ "execute": "qmp_capabilities" })"};

    auto status = this->send( message );
    if ( !status ) 
        perror( "[aimbot::mouse( )] failed to enable qmp capabilities");

}
 
aimbot::mouse_t::~mouse_t( ) {
    close( m_conn );
}
 
bool aimbot::mouse_t::move( const std::int32_t x, const std::int32_t y ) const {
    std::string message{
        "{\n"
        "  \"execute\": \"input-send-event\",\n"
        "  \"arguments\": {\n"
        "    \"events\": [\n"
        "      {\n"
        "        \"type\": \"rel\",\n"
        "        \"data\": {\n"
        "          \"axis\": \"x\",\n"
        "          \"value\": " +
        std::to_string( x ) + "\n"
                                  "        }\n"
                                  "      },\n"
                                  "      {\n"
                                  "        \"type\": \"rel\",\n"
                                  "        \"data\": {\n"
                                  "          \"axis\": \"y\",\n"
                                  "          \"value\": " +
        std::to_string( y ) + "\n"
                                  "        }\n"
                                  "      }\n"
                                  "    ]\n"
                                  "  }\n"
                                  "}"};
    
    return this->send( message );
}


 
bool aimbot::mouse_t::send( std::string_view message ) const {
    ssize_t sent = ::send( m_conn, message.data( ), message.size( ), 0 );

    char buf[1024];
    if ( read( m_conn, buf, 1024) == -1 )
        perror("[aimbot::send] receiving datagram packet");

    return static_cast<size_t>(sent) == message.size();
}

bool aimbot::mouse_t::is_ready( ) const {
    return m_ready;
}

bool aimbot::init( ) {
    mouse = new mouse_t{ };
    return mouse->is_ready( );
}