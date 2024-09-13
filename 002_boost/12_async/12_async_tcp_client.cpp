#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include <iostream>

class client {
    typedef client                                  this_type;
    typedef boost::asio::ip::tcp::endpoint          endpoint_type;
    typedef boost::asio::ip::address                address_type;
    typedef boost::asio::ip::tcp::socket            socket_type;
    typedef boost::shared_ptr<socket_type>          socket_ptr;
    typedef boost::asio::io_service                 server_type;
    typedef std::vector<char>                       buffer_type;

private:
    server_type         m_io;
    buffer_type         m_buf;
    endpoint_type       m_ep;

public:
    client(): m_buf(100, 0),
        m_ep(address_type::from_string("127.0.0.1"), 6688)
    {
        start();
    }

    void run()
    {
        m_io.run();
    }

    void start()
    {
        socket_ptr sock(new socket_type(m_io));
        sock->async_connect(m_ep,
            bind(&this_type::conn_handler, this,
                boost::asio::placeholders::error, sock));
    }

    void conn_handler(const boost::system::error_code &ec, socket_ptr sock) 
    {
        if (ec) {
            std::cout << "conn err: " << ec << std::endl;
            return;
        }
        std::cout << "conn to: " << sock->remote_endpoint().address() << std::endl;
        sock->async_read_some(boost::asio::buffer(m_buf),
            bind(&client::read_handler, this,
                boost::asio::placeholders::error, sock));
        // 为什么上面要把sock传进去呢?
        // 因为sock是使用智能指针，如果不传递进去，在这里就会被析构掉
        // 会导致套接字被释放，从而读取的时候会报错，这个书籍里面没有提到的，是自己踩了后踩发现
    }

    void read_handler(const boost::system::error_code &ec, socket_ptr sock)
    {
        if (ec) {
            std::cout << "read err: " << ec << std::endl;
            return;
        }
        std::cout << &m_buf[0] << std::endl;

        std::cout << sock->remote_endpoint().address() << std::endl;
    }

};

int main()
{
    client c;
    c.run();
}