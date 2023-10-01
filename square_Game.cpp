#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

int main()
{
    // Crie uma janela SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Square Game by Lucas Cruz");

    // Crie um jogador
    sf::RectangleShape player(sf::Vector2f(20, 20));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(380, 280); // Posição inicial do jogador

    // Crie um objeto para contar os pontos
    int pontos = 0;

    // Crie uma fonte que suporte caracteres especiais (UTF-8)
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) // Substitua pelo caminho correto para a fonte
    {
        std::cerr << "Erro ao carregar a fonte." << std::endl;
        return 1;
    }

    sf::Text pontuacaoText;
    pontuacaoText.setFont(font);
    pontuacaoText.setCharacterSize(24);
    pontuacaoText.setFillColor(sf::Color::White);
    pontuacaoText.setPosition(10, 10);

    // Crie um relógio para controlar o tempo
    sf::Clock clock;

    // Variáveis para controlar a aparência dos quadrados
    sf::RectangleShape quadrado;
    quadrado.setSize(sf::Vector2f(10, 10));
    quadrado.setFillColor(sf::Color::Red);
    quadrado.setPosition(100, 100); // Posição inicial do quadrado
    bool quadradoAtivo = false;

    // Defina a velocidade de movimento do jogador
    float velocidadeJogador = 1.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movimento do jogador
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y > 0)
        {
            player.move(0, -velocidadeJogador);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > 0)
        {
            player.move(-velocidadeJogador, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y < window.getSize().y - player.getSize().y)
        {
            player.move(0, velocidadeJogador);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < window.getSize().x - player.getSize().x)
        {
            player.move(velocidadeJogador, 0);
        }

        // Controle do tempo para criar quadrados
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 2.0f) // Cria um quadrado a cada 2 segundos
        {
            quadrado.setPosition(rand() % (window.getSize().x - 10), rand() % (window.getSize().y - 10));
            quadradoAtivo = true;
            clock.restart();
        }

        // Colisão com o quadrado
        if (quadradoAtivo && player.getGlobalBounds().intersects(quadrado.getGlobalBounds()))
        {
            pontos++;
            quadradoAtivo = false;
        }

        // Atualize o texto de pontuação
        pontuacaoText.setString("Score: " + std::to_string(pontos));

        window.clear();
        window.draw(player);
        if (quadradoAtivo)
        {
            window.draw(quadrado);
        }
        window.draw(pontuacaoText);
        window.display();
    }

    return 0;
}
