#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Point.h"
#include "Shell.h"
#include "SwipeShell.h"
#include "HP.h"

using namespace std;
using namespace sf;

HP hp;
int g_screen_width;
int g_screen_height;

int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

array <Texture, 8> particles{};

enum PARTICLES {
    PARTICLE_BUBBLE_1,
    PARTICLE_BUBBLE_2,
    PARTICLE_BUBBLE_3,
    PARTICLE_SWIPE_BUBBLE,
    PARTICLE_TARGET_BUBBLE,
    PARTICLE_BURSTING_BUBBLE,
    PARTICLE_HEART,
    PARTICLE_HALF_HEART,
    MAX_PARTICLES
};

class Background
{
private:
    String m_file;
    Texture m_texture;
    Sprite m_sprite;
    Point m_point_start;
    Point m_point_end;
    Point m_point;
    bool m_dir_up = true;
    float m_degrees = 0;

public:
    Background(String f) : m_file(f)
    {
        m_texture.loadFromFile("images/" + m_file);
        m_sprite.setTexture(m_texture);
        m_point_start.setPoint(0, 0);
        m_point_end.setPoint(g_screen_width, g_screen_height);
        m_sprite.setPosition(0, 0);
    }

    void rotate(float deg)
    {
        m_degrees += deg;
        m_sprite.setRotation(m_degrees);
    }

    void setRectangle(int x, int y, int x1, int y1)
    {
        m_sprite.setTextureRect(IntRect(x, y, x1, y1));
        m_point.setPoint(x1, y1);
    }

    void origin(float x, float y)
    {
        m_sprite.setOrigin(170, 170);
    }

    void setPos(int x, int y)
    {
        m_sprite.setPosition(x, y);
    }

    void move(int x, int y)
    {
        m_sprite.move(x, y);
    }

    void scale(float scale_x, float scale_y)
    {
        m_sprite.setScale(scale_x, scale_y);
    }

    void sColor() {
        m_sprite.setColor(Color(255, 255, 255, 128));
    }

    void draw(RenderWindow& window)
    {
        window.draw(m_sprite);
    }

    void changeDirUp()
    {
        if (m_dir_up)
            m_dir_up = false;
        else
            m_dir_up = true;
    }

    bool getDirUp()
    {
        return m_dir_up;
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    rand();

    ContextSettings settings;
    settings.antialiasingLevel = 8;

    RenderWindow window(VideoMode(1920, 1080), "My window", Style::Fullscreen, settings);

    Vector2u size = window.getSize();
    g_screen_width = size.x;
    g_screen_height = size.y;

    bool game = true;

    Event event;

    Background main_background_1("main_background1.png");
    Background main_background_1_1("main_background1.1.png");
    Background main_background_1_2("main_background1.2.png");
    Background main_background_1_3("main_background1.3.png");
    Background main_background_2("main_background2.png");
    Background ship("ship.png");
    ship.setPos(0, -300);
    Background storm("shtorm.png");
    storm.setPos(0, -300);
    Background water("water.png");
    water.sColor();
    Background bottom("bottom.png");
    Background star("star.png");
    star.setRectangle(70, 10, 340, 340);
    star.origin(170, 170);
    star.setPos((g_screen_width / 2), (g_screen_height / 2));
    star.scale(4, 4);
    Background shark("Shark.png");
    shark.setRectangle(0, 0, 600, 360);
    shark.origin(300, 180);
    shark.setPos((g_screen_width / 2 - 300), (g_screen_height / 2));
    shark.scale(2, 2);
    Background karakaken("karakaken.png");
    karakaken.setRectangle(550, 200, 850, 700);
    karakaken.origin(425, 350);
    karakaken.setPos((g_screen_width / 2 - 325), (g_screen_height / 2 - 200));
    karakaken.scale(1.5, 1.5);
    Background dialog("dialog.png");
    dialog.setPos(0, g_screen_height - 360);
    Background shop("shop.png");
    Background oldman("pers.png");
    oldman.setRectangle(0, 0, 40, 50);
    oldman.setPos(1100, 100);
    oldman.scale(20, 20);
    Background oldman1("pers.png");
    oldman1.setRectangle(40, 0, 40, 50);
    oldman1.setPos(1100, 100);
    oldman1.scale(20, 20);
    Background gg("pers.png");
    gg.setRectangle(0, 150, 40, 50);
    gg.setPos(1100, 100);
    gg.scale(20, 20);
    Background gg1("pers.png");
    gg1.setRectangle(40, 150, 40, 50);
    gg1.setPos(1100, 100);
    gg1.scale(20, 20);
    Background sany("pers.png");
    sany.setRectangle(0, 50, 40, 50);
    sany.setPos(1100, 100);
    sany.scale(20, 20);
    Background sany1("pers.png");
    sany1.setRectangle(40, 50, 40, 50);
    sany1.setPos(1100, 100);
    sany1.scale(20, 20);
    Background kristof("pers.png");
    kristof.setRectangle(0, 200, 40, 50);
    kristof.setPos(1100, 100);
    kristof.scale(20, 20);
    Background kristof1("pers.png");
    kristof1.setRectangle(40, 200, 40, 50);
    kristof1.setPos(1100, 100);
    kristof1.scale(20, 20);
    Background bela("pers.png");
    bela.setRectangle(0, 100, 40, 50);
    bela.setPos(1100, 100);
    bela.scale(20, 20);
    Background bela1("pers.png");
    bela1.setRectangle(40, 100, 40, 50);
    bela1.setPos(1100, 100);
    bela1.scale(20, 20);

    particles[PARTICLE_BUBBLE_1].loadFromFile("images/particles.png", sf::IntRect(0, 0, 10, 10));
    particles[PARTICLE_BUBBLE_2].loadFromFile("images/particles.png", sf::IntRect(10, 0, 10, 10));
    particles[PARTICLE_BUBBLE_3].loadFromFile("images/particles.png", sf::IntRect(20, 0, 10, 10));
    particles[PARTICLE_SWIPE_BUBBLE].loadFromFile("images/particles.png", sf::IntRect(0, 10, 10, 10));
    particles[PARTICLE_TARGET_BUBBLE].loadFromFile("images/particles.png", sf::IntRect(10, 10, 10, 10));
    particles[PARTICLE_BURSTING_BUBBLE].loadFromFile("images/particles.png", sf::IntRect(20, 10, 10, 10));
    particles[PARTICLE_HEART].loadFromFile("images/particles.png", sf::IntRect(0, 20, 13, 11));
    particles[PARTICLE_HALF_HEART].loadFromFile("images/particles.png", sf::IntRect(13, 20, 13, 11));

    vector <Shell> shells{ Shell(80, 0.15) };
    vector <SwipeShell> swipeShells;

    Font font;
    font.loadFromFile("CyrilicOld.ttf");
    Text nameD("Джек", font, 30);
    Text nameR("Рыбак", font, 30);
    Text nameK("Кристоф", font, 30);
    Text nameL("Лилия", font, 30);
    Text nameS("Саня", font, 30);
    Text replika("Мася впиши реплики!", font, 50);
    Text replika1("Мася впиши реплики!", font, 50);
    Text akt("Акт I: 'Незабываемое путешествие'", font, 100);
    nameD.setPosition(100, 1080 - 355);
    nameR.setPosition(100, 1080 - 355);
    nameK.setPosition(100, 1080 - 355);
    nameL.setPosition(100, 1080 - 355);
    nameS.setPosition(100, 1080 - 355);
    akt.setPosition(200, 300);
    replika.setPosition(50, 1080 - 280);
    replika1.setPosition(50, 1080 - 200);
    nameD.setOutlineColor(Color::Red);
    nameD.setFillColor(Color::Red);
    nameR.setOutlineColor(Color::Yellow);
    nameR.setFillColor(Color::Yellow);
    nameK.setOutlineColor(Color::Green);
    nameK.setFillColor(Color::Green);
    nameS.setOutlineColor(Color::Blue);
    nameS.setFillColor(Color::Blue);
    nameL.setOutlineColor(Color(255, 79, 105));
    nameL.setFillColor(Color(255, 79, 105));

    //=================================== Заставочный экран ==========================================
    Clock c_menu;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Space) and game == true)
            {
                game = false;
                c_menu.restart();
            }
        }

        if (game == true)
            main_background_1.draw(window);

        else
        {
            Int32 time = c_menu.getElapsedTime().asMilliseconds();

            if (time < 250)  main_background_1_1.draw(window);
            else if (time < 500) main_background_1_2.draw(window);
            else if (time < 750) main_background_1_3.draw(window);
            else if (time < 850) window.clear(Color(250, 220, 100, 0));
            else if (time < 2000) main_background_2.draw(window);
            else
            {
                c_menu.restart();
                break;
            }
        }

        window.display();
    }

    //================================== Диалог с рыбаком ========================================
    int click = 0;

    window.clear();
    window.display();

    click = -1;

    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {
            window.clear();
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed and event.key.code == Mouse::Left)
            {
                click++;
            }
        }

        switch (click)
        {
            case -1:
                window.draw(akt);
                replika.setString("             *Подсказка: нажимайте левую кнопку мыши, чтобы листать диалоги*");
                window.draw(replika);
                break;
            case 0:
                shop.draw(window);
                dialog.draw(window);
                replika.setString("Мы зашли в магазин под названием 'Рыболовные снасти'.");
                replika1.setString("Нас встретил хмурый дед, хозяин заведения.");
                window.draw(replika);
                window.draw(replika1);
                break;
            case 1:
                shop.draw(window);
                gg.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("Здравствуйте, мы хотели бы лодку в аренду взять.");
                window.draw(replika);
                break;
            case 2:
                shop.draw(window);
                oldman.draw(window);
                dialog.draw(window);
                window.draw(nameR);
                replika.setString("*Пытаясь недовольно прищуриться*");
                window.draw(replika);
                replika1.setString("Сегодня никак, суставы болят, значит погода плохая будет.");
                window.draw(replika1);
                break;
            case 3:
                shop.draw(window);
                gg1.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("Да ладно вам, небо чистое, ни одного облачка.");
                window.draw(replika);
                break;
            case 4:
                shop.draw(window);
                dialog.draw(window);
                replika.setString("*В магазин зашла Лили, и слегка приобняла меня*");
                window.draw(replika);
                break;
            case 5:
                shop.draw(window);
                bela.draw(window);
                dialog.draw(window);
                window.draw(nameL);
                replika.setString("*Легким шепотом* Ну что? Получилось?");
                window.draw(replika);
                break;
            case 6:
                shop.draw(window);
                gg.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("*с пафосом* Сейчас все будет)");
                window.draw(replika);
                break;
            case 7:
                shop.draw(window);
                oldman.draw(window);
                dialog.draw(window);
                window.draw(nameR);
                replika.setString("*С ухмылкой* Нет не будет.");
                window.draw(replika);
                break;
            case 8:
                shop.draw(window);
                gg1.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("А если мы заплатим сверху?)");
                window.draw(replika);
                break;
            case 9:
                shop.draw(window);
                oldman1.draw(window);
                dialog.draw(window);
                window.draw(nameR);
                replika.setString("Тройную стоимость и при условии, что вы вернетесь до обеда.");
                window.draw(replika);
                break;
            case 10:
                shop.draw(window);
                bela1.draw(window);
                dialog.draw(window);
                window.draw(nameL);
                replika.setString("А не жирно ли???");
                window.draw(replika);
                break;
            case 11:
                shop.draw(window);
                gg.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("*Как бы дед ещё цену не поднял*");
                window.draw(replika);
                replika1.setString("Мы согласны!");
                window.draw(replika1);
                break;
            case 12:
                shop.draw(window);
                oldman.draw(window);
                dialog.draw(window);
                window.draw(nameR);
                replika.setString("Но будьте всегда начеку, море хранит свои секреты)");
                window.draw(replika);
                break;
            case 13:
                shop.draw(window);
                bela1.draw(window);
                dialog.draw(window);
                window.draw(nameL);
                replika.setString("Эм, ну ладно.");
                window.draw(replika);
                break;
            case 14:
                shop.draw(window);
                oldman1.draw(window);
                dialog.draw(window);
                window.draw(nameR);
                replika.setString("Вот вам ключи и рация, все остальное уже на корабле.");
                window.draw(replika);
                replika1.setString("И чтобы до обеда вернулись.");
                window.draw(replika1);
                break;
            case 15:
                shop.draw(window);
                dialog.draw(window);
                replika.setString("*В магазин, разговаривая, зашли Санёк и Крис*");
                window.draw(replika);
                break;
            case 16:
                shop.draw(window);
                sany.draw(window);
                dialog.draw(window);
                window.draw(nameS);
                replika.setString("Разве это корабль, вот у нас в России...");
                window.draw(replika);
                break;
            case 17:
                shop.draw(window);
                kristof.draw(window);
                dialog.draw(window);
                window.draw(nameK);
                replika.setString("Тише ты!");
                window.draw(replika);
                break;
            case 18:
                shop.draw(window);
                gg1.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("*Дед сделал вид что не услышал этих <<грязных>> слов*");
                window.draw(replika);
                break;
            case 19:
                shop.draw(window);
                kristof1.draw(window);
                dialog.draw(window);
                window.draw(nameK);
                replika.setString("Ребята, а вы точно хотите этого, а то у меня плохое предчувствие.");
                window.draw(replika);
                break;
            case 20:
                shop.draw(window);
                gg.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("Не ссы, у нас лучший рулевой России-Матушки.");
                window.draw(replika);
                break;
            case 21:
                shop.draw(window);
                sany1.draw(window);
                dialog.draw(window);
                window.draw(nameS);
                replika.setString("Скажешь тоже)");
                window.draw(replika);
                break;
            case 22:
                shop.draw(window);
                kristof.draw(window);
                dialog.draw(window);
                window.draw(nameK);
                replika.setString("В этот раз точно без твоих <<приколов>>?");
                window.draw(replika);
                break;
            case 23:
                shop.draw(window);
                sany.draw(window);
                dialog.draw(window);
                window.draw(nameS);
                replika.setString("Все хорошо, я с собой взял <<Трибоцинопанол>>. Кстати, Крис, зачем ты");
                window.draw(replika);
                replika1.setString("взял ещё две бочки топлива? Тебе деньги некуда девать?");
                window.draw(replika1);
                break;
            case 24:
                shop.draw(window);
                kristof1.draw(window);
                dialog.draw(window);
                window.draw(nameK);
                replika.setString("На всякий случай.");
                window.draw(replika);
                break;
            case 25:
                shop.draw(window);
                bela.draw(window);
                dialog.draw(window);
                window.draw(nameL);
                replika.setString("Мальчики, хватит болтать, взяли руки в ноги и поплыли)");
                window.draw(replika);
                break;
            case 26:
                shop.draw(window);
                gg1.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("*Я приобнял её за талию*");
                window.draw(replika);
                replika1.setString("За твою торопливость я тебя и люблю.");
                window.draw(replika1);
                break;
        }

        if (click == 27) break;
        window.display();
    }

//================================== Диалог на корабле ========================================
    window.clear();
    window.display();
    click = 0;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            window.clear();
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed and event.key.code == Mouse::Left) click++;
        }
       
       switch (click)
       {
           case 0:
                akt.setString("     II Акт.  Легкая беззаботность");
                window.draw(akt);
                replika.setString("             *Подсказка: нажимайте левую кнопку мыши, чтобы листать диалоги*");
                window.draw(replika);
                break;
           case 1:
                ship.draw(window);
                dialog.draw(window);
                replika.setString("Мы плавали уже где-то 3 часа, погода всё ещё была спокойной");
                window.draw(replika);
                replika1.setString("Саша стоял за штурвалом, Кристоф рядом изучал карту, а мы пили лимонад");
                window.draw(replika1);
                break;
           case 2:
                ship.draw(window);
                kristof.draw(window);
                dialog.draw(window);
                window.draw(nameK);
                replika.setString("Ну и жара. Куда я трачу свой отпуск?");
                window.draw(replika);
                break;
           case 3:
                ship.draw(window);
                sany.draw(window);
                dialog.draw(window);
                window.draw(nameS);
                replika.setString("Да ладно тебе, лучше, чем в Сибири, вот я бы сейчас в баню сходил.");
                window.draw(replika);
                break;
           case 4:
                ship.draw(window);
                kristof1.draw(window);
                dialog.draw(window);
                window.draw(nameK);
                replika.setString("*слегка улыбаясь*  А потом бы ещё горячего чая выпил. Странные вы люди русские.");
                window.draw(replika);
                break;
           case 5:
                ship.draw(window);
                sany1.draw(window);
                dialog.draw(window);
                window.draw(nameS);
                replika.setString("Имеем право, с нами Бог.");
                window.draw(replika);
                break;
           case 6:
                ship.draw(window);
                kristof.draw(window);
                dialog.draw(window);
                window.draw(nameK);
                replika.setString("Существование бога или иных высших сил научно не доказано.");
                window.draw(replika);
                break;
           case 7:
                ship.draw(window);
                sany.draw(window);
                dialog.draw(window);
                window.draw(nameS);
                replika.setString("*нахмурив брови* Давно по шее не получал?");
                window.draw(replika);
                break;
           case 8:
                ship.draw(window);
                gg.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("Сань, сбавь обороты, он не хотел тебя оскорбить.");
                window.draw(replika);
                break;
           case 9:
                ship.draw(window);
                bela.draw(window);
                dialog.draw(window);
                window.draw(nameL);
                replika.setString("Крис, а ты веришь в местные легенды? Бермудский треугольник, всё такое)");
                window.draw(replika);
                replika1.setString("Не боишься потеряться?)");
                window.draw(replika1);
                break;
           case 10:
                ship.draw(window);
                dialog.draw(window);
                replika.setString("*Кристоф проглотил слюну и пытаясь не показать свои эмоции сказал:*");
                window.draw(replika);
                break;
           case 11:
                ship.draw(window);
                sany.draw(window);
                dialog.draw(window);
                window.draw(nameS);
                replika.setString("Волшебные свойства Бермудов не доказаны, как и...");
                window.draw(replika);
                break;
           case 12:
                ship.draw(window);
                dialog.draw(window);
                replika.setString("*Саня прописал смачный подзатыльник Кристофу*");
                window.draw(replika);
                break;
           case 13:
                ship.draw(window);
                gg.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("О, сверхъестественные силы!");
                window.draw(replika);
                break;
           case 14:
                ship.draw(window);
                dialog.draw(window);
                replika.setString("*Все посмеялись, как ни странно Кристоф тоже* ");
                window.draw(replika);
                break;
           case 15:
                ship.draw(window);
                dialog.draw(window);
                replika.setString("*Вдруг, задребезжала рация");
                window.draw(replika);
                break;
           case 16:
                ship.draw(window);
                oldman.draw(window);
                dialog.draw(window);
                window.draw(nameR);
                replika.setString("РАЦИЯ:: Ну гдеыыы вы там, даваЙте возврашаЙтесь.");
                window.draw(replika);
                break;
           case 17:
                ship.draw(window);
                dialog.draw(window);
                replika.setString("*Дед походу уже накатил, значит можно не торопиться)");
                window.draw(replika);
                break;
           case 18:
                ship.draw(window);
                gg1.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("РАЦИЯ:: Да да, хорошо");
                window.draw(replika);
                break;
        }

        if (click ==19) break;
        window.display();
    }

//========================================= Шторм =============================================
    window.clear();
    window.display();
    click = 0;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            window.clear();

            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed and event.key.code == Mouse::Left)
            {
                click++;
            }
        }

        switch (click)
        {
            case 0:
                akt.setString("           III Акт: первые проблемы");
                window.draw(akt);
                replika.setString("             *Подсказка: нажимайте левую кнопку мыши, чтобы листать диалоги*");
                window.draw(replika);
                break;
            case 1:
                ship.draw(window);
                dialog.draw(window);
                replika.setString("Мы продолжали плыть. Был легкий туман, но солнце все равно светило сквозь него");
                window.draw(replika);
                break;
            case 2:
                ship.draw(window);
                kristof.draw(window);
                dialog.draw(window);
                window.draw(nameK);
                replika.setString("Ребят мы же должны вернуться к обеду, пора разворачиваться.");
                window.draw(replika);
                break;
            case 3:
                ship.draw(window);
                bela.draw(window);
                dialog.draw(window);
                window.draw(nameL);
                replika.setString("Этот дед взял с нас кучу денег, ничего, подождёт.");
                window.draw(replika);
                break;
            case 4:
                ship.draw(window);
                kristof1.draw(window);
                dialog.draw(window);
                window.draw(nameK);
                replika.setString("А погода? Вы видите, какой туман! А если потеряемся?");
                window.draw(replika);
                break;
            case 5:
                ship.draw(window);
                gg.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("Что скажет капитан нашего судна?");
                window.draw(replika);
                break;
            case 6:
                ship.draw(window);
                sany.draw(window);
                dialog.draw(window);
                window.draw(nameS);
                replika.setString("Вроде бы погода нормальна...");
                window.draw(replika);
                break;
            case 7:
                window.clear(Color(255, 255, 255));
                break;
            case 8:
                storm.draw(window);
                dialog.draw(window);
                replika.setString("*Вдруг удар молнии ослепил всех, раздался гром, подул сильный ветер*");
                window.draw(replika);
                replika1.setString("*Начался тропический дождь, волны качали корабль из стороны в сторону*");
                window.draw(replika1);
                break;
            case 9:
                storm.draw(window);
                dialog.draw(window);
                replika.setString("*Все начали паниковать, только Саня ругался на старославянском*");
                window.draw(replika);
                break;
            case 10:
                storm.draw(window);
                sany1.draw(window);
                dialog.draw(window);
                window.draw(nameS);
                replika.setString("Джек, убери паруса и руби форт мачту Лили-проверь переборки, Крис. . .");
                window.draw(replika);
                break;
            case 11:
                storm.draw(window);
                dialog.draw(window);
                replika.setString("*Крис забился в угол и сквозь слезы и паниковал*");
                window.draw(replika);
                break;
            case 12:
                storm.draw(window);
                kristof1.draw(window);
                dialog.draw(window);
                window.draw(nameK);
                replika.setString("МАМА, Я НЕ ХОЧУ УМИРАТЬ.");
                window.draw(replika);
                break;
            case 13:
                akt.setString("                  *Прошло 2 часа*");
                window.draw(akt);
                break;
            case 14:
                storm.draw(window);
                dialog.draw(window);
                replika.setString("*Шторм утих, небо окрасилось в устрашающий зелёный цвет*");
                window.draw(replika);
                break;
            case 15:
                storm.draw(window);
                sany1.draw(window);
                dialog.draw(window);
                window.draw(nameS);
                replika.setString("Все живы?");
                window.draw(replika);
                replika1.setString("Етижи-пассатижи, Крис, ну как так-то.");
                window.draw(replika1);
                break;
            case 16:
                storm.draw(window);
                dialog.draw(window);
                replika.setString("Кристофер лежал без сознания");
                window.draw(replika);
                break;
            case 17:
                storm.draw(window);
                gg1.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("попробую связаться с дедом.");
                window.draw(replika);
                replika1.setString("РАЦИЯ:: Прием, нам нужна помощь с движком, вы можете нам помочь?");
                window.draw(replika1);
                break;
            case 18:
                storm.draw(window);
                oldman.draw(window);
                dialog.draw(window);
                window.draw(nameR);
                replika.setString("РАЦИЯ:: Вы…….те…сь о…. д….а  …….с.. ….о……но…. слы…..те…..  м……ня…..");
                window.draw(replika);
                break;
            case 19:
                storm.draw(window);
                gg.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("Чёрт, связи нет.");
                window.draw(replika);
                break;
            case 20:
                storm.draw(window);
                dialog.draw(window);
                replika.setString("*Раздался глухой звон*");
                window.draw(replika);
                break;
            case 21:
                storm.draw(window);
                bela.draw(window);
                dialog.draw(window);
                window.draw(nameL);
                replika.setString("Что это было?");
                window.draw(replika);
                break;
            case 22:
                storm.draw(window);
                dialog.draw(window);
                replika.setString("*Мы перебежали на правый борт корабля, к нему присосалась огромная морская звезда*");
                window.draw(replika);
                break;
            case 23:
                storm.draw(window);
                dialog.draw(window);
                replika.setString("Сказать, что все были в шоке это ничего не сказать");
                window.draw(replika);
                break;
            case 24:
                storm.draw(window);
                sany.draw(window);
                dialog.draw(window);
                window.draw(nameS);
                replika.setString("Мне кажется или эта штуковина пытается сожрать наш корабль?");
                window.draw(replika);
                break;
            case 25:
                storm.draw(window);
                bela1.draw(window);
                dialog.draw(window);
                window.draw(nameL);
                replika.setString("Нет, Саня ты чего, оно к нам на чаепитие пришло)");
                window.draw(replika);
                replika1.setString("КОНЕЧНО СОЖРАТЬ, НЕ ТУПИ");
                window.draw(replika1);
                break;
            case 26:
                storm.draw(window);
                gg.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("Хватайте что-нибудь потяжелее и бейте её");
                window.draw(replika);
                break;
            case 27:
                replika.setString("                                    Ваша задача: Лопнуть 25 пузыриков");
                window.draw(replika);
                replika1.setString("                          Подсказка: Зелёный шарик надо доставить в серый");
                window.draw(replika1);
                break;
        }

        if (click == 28)
        {
            break;
        }

        window.display();
    }

//================================= Первый босс ======================================
    Clock c_between;
    Clock c_new;
    Clock c_monster;

    int bubbles_amount = 25;

    while (window.isOpen())
    {
        if (hp.check() == 0)
        {
            while (window.isOpen())
            {
                window.clear();
                akt.setString("                      Game over!");
                replika.setString("                                  *Вы умерли окончательно и бесповоротно!*");
                replika1.setString("                                   *Нажмите ПРОБЕЛ, чтобы закрыть игру*");
                window.draw(akt);
                window.draw(replika);
                window.draw(replika1);
                Event event;
                while (window.pollEvent(event))
                {
                    if (Keyboard::isKeyPressed(Keyboard::Escape) or Keyboard::isKeyPressed(Keyboard::Space))
                    {
                        window.close();
                    }
                }
                window.display();
            }
        }

        Point mousePosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

        Event event;
        while (window.pollEvent(event))
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape) or event.type == Event::Closed) window.close();

            if (event.type == Event::MouseButtonPressed and event.key.code == Mouse::Left)
            {
                for (int idx = 0; idx < shells.size(); ++idx)
                {
                    if (shells[idx].inclusion(mousePosition))
                    {
                        if (shells[idx].getHp() > 1)
                        {
                            shells[idx].decreaseHp();
                        }
                        else
                        {
                            shells.erase(shells.begin() + idx);
                            --bubbles_amount;
                        }
                    }
                }

                for (SwipeShell& sw : swipeShells)
                {
                    if (sw.inclusion(mousePosition))
                    {
                        sw.active = true;
                    }
                }
            }

            for (int idx = 0; idx < swipeShells.size(); ++idx)
            {
                if (event.type == Event::MouseButtonReleased and event.key.code == Mouse::Left and swipeShells[idx].active)
                {
                    swipeShells[idx].active = false;
                    if (swipeShells[idx].inclusion_end(mousePosition))
                    {
                        swipeShells.erase(swipeShells.begin() + idx);
                        --bubbles_amount;
                    }
                }
            }
        }

        window.clear(Color(14, 61, 112, 0));

        if (!bubbles_amount)
        {
            break;
        }

        for (SwipeShell& sw : swipeShells)
        {
            if (sw.active)
            {
                sw.follow(mousePosition);
            }
        }

        if (c_between.getElapsedTime().asMilliseconds() > 10)
        {
            for (int idx = 0; idx < shells.size(); ++idx)
            {
                shells[idx].increase(shells, idx);
            }

            for (int idx = 0; idx < swipeShells.size(); ++idx)
            {
                swipeShells[idx].increase(swipeShells, idx);
            }

            star.rotate(0.5);

            c_between.restart();
        }

        if (c_new.getElapsedTime().asMilliseconds() > 600)
        {
            int received = getRandomNumber(0, 10);
            if (received <= 9)
            {
                shells.push_back(Shell(80, 0.15));
            }
            else
            {
                swipeShells.push_back(SwipeShell(60, 0.07));
            }

            c_new.restart();
        }

        bottom.draw(window);
        star.draw(window);
        water.draw(window);

        for (Shell& s : shells)
        {
            s.draw(window);
        }

        for (SwipeShell& sw : swipeShells)
        {
            sw.draw(window);
        }

        hp.draw_empty_hp(window);
        hp.draw_half_hp(window);
        hp.draw_full_hp(window);

        window.display();
    }

//================================== Смерть Сани ========================================
    window.clear();
    window.display();
        
    click = 0;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            window.clear();
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed and event.key.code == Mouse::Left) click++;
        }

        switch (click)
        {
            case 0:
                storm.draw(window);
                dialog.draw(window);
                replika.setString("Саня хватает перочинный ножик и со словами: “МОЧИ ГУКОВ” прыгает и режет чудовище,");
                replika1.setString("оно бурчит уходит на дно вместе с шизоидом");
                window.draw(replika);
                window.draw(replika1);
                break;
            case 1:
                storm.draw(window);
                gg.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("САНЯ, НЕЕЕЕТ");
                window.draw(replika);
                break;
            case 2:
                storm.draw(window);
                oldman.draw(window);
                dialog.draw(window);
                window.draw(nameL);
                replika.setString("*Пытаясь сдержать слёзы*");
                window.draw(replika);
                replika1.setString("Это его собственный выбор.");
                window.draw(replika1);
                break;
            case 3:
                storm.draw(window);
                gg1.draw(window);
                dialog.draw(window);
                window.draw(nameD);
                replika.setString("Надо чинить корабль и уплывать на хрен отсюда.");
                window.draw(replika);
                break;
           
        }

        if (click == 4) break;
        window.display();
    }

 //==================================IV АКТ ====================================
    window.clear();
    window.display();
        
    click = 0;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            window.clear();
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed and event.key.code == Mouse::Left) click++;
        }

        switch (click)
        {
        case 0:
            akt.setString("           IV Акт:  Финальный бой");
            window.draw(akt);
            replika.setString("             *Подсказка: нажимайте левую кнопку мыши, чтобы листать диалоги*");
            window.draw(replika);
            break;
        case 1:
            replika.setString("*Вдруг на нас напал мегаладон*");
            window.draw(replika);

            break;
        }
        if (click == 2) break;
        window.display();
    }

//================================= Второй босс ======================================
    hp.setHP(7);

    bubbles_amount = 75;

    shells.clear();
    shells.push_back(Shell(80, 0.2));
    swipeShells.clear();

    c_between.restart();
    c_new.restart();
    c_monster.restart();

    while (window.isOpen())
    {
        if (hp.check() == 0)
        {
            while (window.isOpen())
            {
                window.clear();
                akt.setString("                      Game over!");
                replika.setString("                                  *Вы умерли окончательно и бесповоротно!*");
                replika1.setString("                                   *Нажмите ПРОБЕЛ, чтобы закрыть игру*");
                window.draw(akt);
                window.draw(replika);
                window.draw(replika1);
                Event event;
                while (window.pollEvent(event))
                {
                    if (Keyboard::isKeyPressed(Keyboard::Escape) or Keyboard::isKeyPressed(Keyboard::Space)) window.close();
                }
                window.display();
            }
        }
        
        Point mousePosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

        Event event;
        while (window.pollEvent(event))
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape) or event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed and event.key.code == Mouse::Left)
            {
                for (int idx = 0; idx < shells.size(); ++idx)
                {
                    if (shells[idx].inclusion(mousePosition))
                    {
                        if (shells[idx].getHp() > 1)
                        {
                            shells[idx].decreaseHp();
                        }
                        else
                        {
                            shells.erase(shells.begin() + idx);
                            --bubbles_amount;
                        }
                    }
                }

                for (SwipeShell& sw : swipeShells)
                {
                    if (sw.inclusion(mousePosition))
                        sw.active = true;
                }
            }

            for (int idx = 0; idx < swipeShells.size(); ++idx)
            {
                if (event.type == Event::MouseButtonReleased and event.key.code == Mouse::Left and swipeShells[idx].active)
                {
                    swipeShells[idx].active = false;
                    if (swipeShells[idx].inclusion_end(mousePosition))
                    {
                        swipeShells.erase(swipeShells.begin() + idx);
                        --bubbles_amount;
                    }
                }
            }
        }

        window.clear(Color(14, 61, 112, 0));

        if (!bubbles_amount)
        {
            break;
        }

        for (SwipeShell& sw : swipeShells)
        {
            if (sw.active)
            {
                sw.follow(mousePosition);
            }
        }

        if (c_between.getElapsedTime().asMilliseconds() > 10)
        {
            for (int idx = 0; idx < shells.size(); ++idx)
            {
                shells[idx].increase(shells, idx);
            }

            for (int idx = 0; idx < swipeShells.size(); ++idx)
            {
                swipeShells[idx].increase(swipeShells, idx);
            }

            if (shark.getDirUp() == true)
            {
                shark.move(0, -2);
            }
            else
            {
                shark.move(0, 2);
            }

            c_between.restart();
        }

        if (c_monster.getElapsedTime().asMilliseconds() > 1500)
        {
            shark.changeDirUp();
            c_monster.restart();
        }

        if (c_new.getElapsedTime().asMilliseconds() > 600)
        {
            int received = getRandomNumber(0, 10);
            if (received <= 9)
            {
                shells.push_back(Shell(80, 0.2));
            }
            else
            {
                swipeShells.push_back(SwipeShell(60, 0.1));
            }

            c_new.restart();
        }

        bottom.draw(window);
        shark.draw(window);
        water.draw(window);

        for (Shell& s : shells)
        {
            s.draw(window);
        }

        for (SwipeShell& sw : swipeShells)
        {
            sw.draw(window);
        }

        hp.draw_empty_hp(window);
        hp.draw_half_hp(window);
        hp.draw_full_hp(window);

        window.display();
    }

//================================== Смерть Сани =====================================

//================================= Третий босс ======================================
    hp.setHP(10);

    bubbles_amount = 125;

    shells.clear();
    shells.push_back(Shell(80, 0.25));
    swipeShells.clear();

    c_between.restart();
    c_new.restart();
    c_monster.restart();

    while (window.isOpen())
    {
        if (hp.check() == 0)
        {
            while (window.isOpen())
            {
                window.clear();
                akt.setString("                      Game over!");
                replika.setString("                                  *Вы умерли окончательно и бесповоротно!*");
                replika1.setString("                                   *Нажмите ПРОБЕЛ, чтобы закрыть игру*");
                window.draw(akt);
                window.draw(replika);
                window.draw(replika1);
                Event event;
                while (window.pollEvent(event))
                {
                    if (Keyboard::isKeyPressed(Keyboard::Escape) or Keyboard::isKeyPressed(Keyboard::Space))
                    {
                        window.close();
                    }
                }
                window.display();
            }
        }

        Point mousePosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

        Event event;
        while (window.pollEvent(event))
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape) or event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed and event.key.code == Mouse::Left)
            {
                for (int idx = 0; idx < shells.size(); ++idx)
                {
                    if (shells[idx].inclusion(mousePosition))
                    {
                        if (shells[idx].getHp() > 1)
                        {
                            shells[idx].decreaseHp();
                        }
                        else
                        {
                            shells.erase(shells.begin() + idx);
                            --bubbles_amount;
                        }
                    }
                }

                for (SwipeShell& sw : swipeShells)
                {
                    if (sw.inclusion(mousePosition))
                    {
                        sw.active = true;
                    }
                }
            }

            for (int idx = 0; idx < swipeShells.size(); ++idx)
            {
                if (event.type == Event::MouseButtonReleased and event.key.code == Mouse::Left and swipeShells[idx].active)
                {
                    swipeShells[idx].active = false;
                    if (swipeShells[idx].inclusion_end(mousePosition))
                    {
                        swipeShells.erase(swipeShells.begin() + idx);
                        --bubbles_amount;
                    }
                }
            }
        }

        window.clear(Color(14, 61, 112, 0));

        if (!bubbles_amount)
        {
            break;
        }

        for (SwipeShell& sw : swipeShells)
        {
            if (sw.active)
                sw.follow(mousePosition);
        }

        if (c_between.getElapsedTime().asMilliseconds() > 10)
        {
            for (int idx = 0; idx < shells.size(); ++idx)
            {
                shells[idx].increase(shells, idx);
            }

            for (int idx = 0; idx < swipeShells.size(); ++idx)
            {
                swipeShells[idx].increase(swipeShells, idx);
            }

            if (karakaken.getDirUp() == true)
            {
                karakaken.move(-5, -0);
            }
            else
            {
                karakaken.move(5, 0);
            }

            c_between.restart();
        }

        if (c_monster.getElapsedTime().asMilliseconds() > 2000)
        {
            karakaken.changeDirUp();
            c_monster.restart();
        }

        if (c_new.getElapsedTime().asMilliseconds() > 600)
        {
            int received = getRandomNumber(0, 10);
            if (received <= 9)
            {
                shells.push_back(Shell(80, 0.25));
            }
            else
            {
                swipeShells.push_back(SwipeShell(60, 0.13));
            }

            c_new.restart();
        }

        bottom.draw(window);
        karakaken.draw(window);
        water.draw(window);

        for (Shell& s : shells)
        {
            s.draw(window);
        }

        for (SwipeShell& sw : swipeShells)
        {
            sw.draw(window);
        }

        hp.draw_empty_hp(window);
        hp.draw_half_hp(window);
        hp.draw_full_hp(window);

        window.display();
    } 

//================================== Смерть Белы ========================================


//================================= Четвертый босс ======================================


//================================== Прыжок в глаз ======================================

    while (window.isOpen())
            {
                window.clear();
                akt.setString("                      Вы победили!");
                replika.setString("                                  *Ваш корабль уцелел в этом нещедящем шторме!*");
                replika1.setString("                                   *Нажмите ПРОБЕЛ, чтобы закрыть игру*");
                window.draw(akt);
                window.draw(replika);
                window.draw(replika1);
                Event event;
                while (window.pollEvent(event))
                {
                    if (Keyboard::isKeyPressed(Keyboard::Escape) or Keyboard::isKeyPressed(Keyboard::Space))
                    {
                        window.close();
                    }
                }
                window.display();
            }
    
    return 0;
}