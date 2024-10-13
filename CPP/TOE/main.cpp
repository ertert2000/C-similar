#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>

struct Node
{
    int x, y;
    int idNode;
    std::string component;
};

struct NodeConnect
{
    int x, y;
    std::string component;
};

std::map<int, Node> gridPositions = {
    {1, {100, 100}},
    {2, {100, 200}},
    {3, {100, 300}},
    {4, {200, 100}},
    {5, {200, 200}},
    {6, {200, 300}},
    {7, {300, 100}},
    {8, {300, 200}},
    {9, {300, 300}},
    {10, {400, 100}},
    {11, {400, 200}},
    {12, {400, 300}},
};

int main() 
{
    std::vector<NodeConnect> inputData = { {3, 1, "U1"}, {1, 2, "U1"}, {3, 2, "U1"}, {3, 1, "U1"} };

    std::vector<Node> nodeData;

    for (int i = 0; i < inputData.size(); i++)
        for (int j = 0; j < inputData.size(); j++)
        {
            if ((inputData[i].x == inputData[j].x) && (inputData[i].y == inputData[j].y))
            {
                Node temp;
                nodeData.push_back(temp);
            }
        }





    bool foundNode[12]{false};

    int j = 0;
    for (int i = 0; i < inputData.size(); i++)
        for (const auto& [id, pos] : gridPositions)
        {
            if ((inputData[i].x == id or inputData[i].y == id) and foundNode[id] == false)
            {
                nodeData.push_back(pos);
                nodeData[j].idNode = id;
                j++;
                foundNode[id] = true;
            }
        }





    sf::RenderWindow window(sf::VideoMode(800, 600), "TOE");

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear(sf::Color::White);

        for (const auto& [id, pos] : gridPositions)
        {
            sf::CircleShape node(5);
            node.setPosition(pos.x, pos.y);
            node.setFillColor(sf::Color::Black);



            window.draw(node);
        }

        window.display();
    }

    return 0;
}
