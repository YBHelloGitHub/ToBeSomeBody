#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include <iostream>

class server {
    typedef server                              this_type;
    typedef boost::asio::ip::tcp::socket        socket_type;
    typedef boost::asio::io_service             io_service_type;
    typedef boost::asio::ip::tcp::endpoint      endpoint_type;
    typedef boost::asio::ip::tcp::acceptor      acceptor_type;
    typedef boost::shared_ptr<socket_type>      socket_ptr;


private:
    io_service_type     m_io;
    acceptor_type       m_acceptor;
    std::vector<char>   m_buf;

public:
    server() : m_acceptor(m_io, endpoint_type(boost::asio::ip::tcp::v4(), 6688)), m_buf(100, 0)
    {
        accept();
    }

    void run()
    {
        m_io.run();
    }

    void accept()
    {
        socket_ptr sock(new socket_type(m_io));
        m_acceptor.async_accept(*sock,
            bind(&this_type::accept_handler, this,
                boost::asio::placeholders::error, sock));
    }

    void accept_handler(const boost::system::error_code &ec, socket_ptr sock)
    {
        if (ec) {
            std::cout << "accept error: " << ec << std::endl;
            return;
        }

        std::cout << "accept from: ";
        std::cout << sock->remote_endpoint().address() << std::endl;

        sock->async_write_some(boost::asio::buffer("hello asio\n"),
            bind(&this_type::write_handler, this,
                boost::asio::placeholders::error, sock));
        accept();
    }

    void write_handler(const boost::system::error_code &ec, socket_ptr sock)
    {
        if (ec) {
            std::cout << "write error: " << ec << std::endl;
            return;
        }
        std::cout << "write finished" << std::endl;

        // sock->async_read_some(boost::asio::buffer(m_buf),
        //     bind(&this_type::read_handler, this,
        //         boost::asio::placeholders::error, sock));

    }

    void read_handler(const boost::system::error_code &ec, socket_ptr sock)
    {
        if (ec) {
            std::cout << "read err: " << ec << std::endl;
            return;
        }
        std::cout << &m_buf[0] << std::endl;
    }

};

int main()
{
    server s;
    s.run();
}