#include "tests.h"

Tests::Tests()
{

}

void Tests::MatriceOperationsTiming(int number)
{
    auto started = std::chrono::high_resolution_clock::now();

    for(int i=0;i<number;i++)
        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.f)); // On crée la matrice de vue avec une translation en arrière de cinq unités

    auto done = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(done-started).count() << "us for " << number << " operations" << std::endl;
}

void Tests::TestEntity(Renderer *r, OpenGLEntity *e)
{
    std::cout << "Loading shaders" << std::endl;

    //Shaders
    GLuint fragmentID = GLUtils::LoadShader("shaders/SimpleFragmentShader.fsh", GL_FRAGMENT_SHADER);
    GLuint vertexID = GLUtils::LoadShader("shaders/MVPVSH.vsh", GL_VERTEX_SHADER);
    //GLuint vertexID = GLUtils::LoadShader("shaders/SimpleVertexShader.vsh", GL_VERTEX_SHADER);

    //Program
    GLuint programID = GLUtils::LoadShaders(vertexID,fragmentID);
    r->setProgram(programID);

    std::cout << "Initializing models" << std::endl;
    Scene *s = new Scene(60.0f,float(r->getSize().x) / float(r->getSize().y),0.1f,100.0f);
    s->setVertexShader(programID);

    r->setScene(s);
    s->setRoot(e);

    std::cout << "Running" << std::endl;
    r->start();

    while(r->isOpen())
    {
        sf::Event event;
        while (r->pollEvent(event))
        {
            // on regarde le type de l'évènement...
            switch (event.type)
            {
                // fenêtre fermée
                case sf::Event::Closed:
                    r->close();
                    break;

                // touche pressée
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) r->close();
                    break;

                // on ne traite pas les autres types d'évènements
                default:
                    break;
            }
        }
    }

    std::cout << "Exiting" << std::endl;
}
