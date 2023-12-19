#include "TcpClient.h"

using boost::asio::ip::tcp;

//Establishing a connection to a server
void TcpClient::ConnectToServer(const std::string &adress)
{
  tcp::resolver resolver(ioService);
  tcp::resolver::query query(tcp::v4(),adress, std::to_string(port));
  tcp::resolver::iterator iterator = resolver.resolve(query);

  tcp::socket socket(ioService);

  socket.async_connect(*iterator, 
    [this](const boost::system::error_code &error)
    {
      if (!error)
      {
        emit Connected();
        StartRead();
      }
    });

    ioService.run();
}

//Reading data from the server
void TcpClient::StartRead()
{
  boost::asio::async_read(socket, boost::asio::buffer(buffer), 
    [this](const boost::system::error_code &error)
    {
      if (!error)
      {
        emit DataRecieved();
        StartRead();
      }
      else
        socket.close();
    });
}

//Sending a Data to Server with json template;
void TcpClient::SendData(const std::string& strUserId, const std::string& strRequestType, const std::string& strMessage)
{
    nlohmann::json jRequest;
    jRequest["UserId"] = strUserId;
    jRequest["ReqType"] = strRequestType;
    jRequest["Message"] = strMessage;

    std::string request = jRequest.dump();

    boost::asio::async_write(socket, boost::asio::buffer(request, request.size()),
    [this](const boost::system::error_code &error)
    {
      if (!error)
        emit DataSent();
    }); //Add param size_t bytes if need to know bytes transfered
}

/*
OLD TEMPLATE STILL NEED TO REFACTOR
// Возвращает строку с ответом сервера на последний запрос.
std::string ReadMessage(tcp::socket& aSocket)
{
    boost::asio::streambuf b;
    boost::asio::read_until(aSocket, b, "\0");
    std::istream is(&b);
    std::string line(std::istreambuf_iterator<char>(is), {});
    return line;
}

// "Создаём" пользователя, получаем его ID.
std::string ProcessRegistration(tcp::socket& aSocket)
{
    std::string name;
    std::cout << "Hello! Enter your name: ";
    std::cin >> name;

    // Для регистрации Id не нужен, заполним его нулём
    SendMessage(aSocket, "0", Requests::Registration, name);
    return ReadMessage(aSocket);
}

int main()
{
    try
    {
        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        tcp::resolver::query query(tcp::v4(), "127.0.0.1", std::to_string(port));
        tcp::resolver::iterator iterator = resolver.resolve(query);

        tcp::socket s(io_service);
        s.connect(*iterator);

        // Мы предполагаем, что для идентификации пользователя будет использоваться ID.
        // Тут мы "регистрируем" пользователя - отправляем на сервер имя, а сервер возвращает нам ID.
        // Этот ID далее используется при отправке запросов.
        std::string my_id = ProcessRegistration(s);

        while (true)
        {
            // Тут реализовано "бесконечное" меню.
            std::cout << "Menu:\n"
                         "1) Hello Request\n"
                         "2) Exit\n"
                         << std::endl;

            short menu_option_num;
            std::cin >> menu_option_num;
            switch (menu_option_num)
            {
                case 1:
                {
                    // Для примера того, как может выглядить взаимодействие с сервером
                    // реализован один единственный метод - Hello.
                    // Этот метод получает от сервера приветствие с именем клиента,
                    // отправляя серверу id, полученный при регистрации.
                    SendMessage(s, my_id, Requests::Hello, "");
                    std::cout << ReadMessage(s);
                    break;
                }
                case 2:
                {
                    exit(0);
                    break;
                }
                default:
                {
                    std::cout << "Unknown menu option\n" << std::endl;
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
*/