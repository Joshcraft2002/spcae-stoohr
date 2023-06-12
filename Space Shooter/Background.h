#ifndef Background_h
#define Background_h

#define BACKGROUND_OUTER 0.0f, 0.0f, 0.0f
#define BACKGROUND_INNER 0.05f, 0.0f, 0.1f

#define STAR_COLOR 0.8f, 0.8f, 0.8f

#define ASTEROID_BASE_COLOR_DARKEST 0.03f, 0.03f, 0.03f
#define ASTEROID_BASE_COLOR_DARKER 0.05f, 0.05f, 0.05f
#define ASTEROID_BASE_COLOR 0.08f, 0.08f, 0.08f
#define ASTEROID_HIGHLIGHT_COLOR 0.12f, 0.12f, 0.12f
#define ASTEROID_HOLE_COLOR 0.06f, 0.06f, 0.06f

void updateAsteroids();

//tiles of stars (200 x 200)
class StarPanel : public Movable {
private:
    class Star {
    private:
        int x;
        int y;
        int radius;
    public:
        Star(int x, int y, int radius) {
            this->x = x;
            this->y = y;
            this->radius = radius;
        }

        //draw star, parameters take coordinates of parent tile
        void drawStar(float x, float y) {
            glPushMatrix();
            glTranslatef(this->x + x, this->y + y, 0);

            glBegin(GL_POLYGON);
            glColor3f(STAR_COLOR);
            for (int i = 0; i < 360; i+=30) {
                theta = (i / 180.0f) * 3.14159;
                glVertex2f(radius * cos(theta), radius * sin(theta));
            }
            glEnd();

            glPopMatrix();
        }
    };

    const int starCount = 100;
    const int minRadius = 1;
    const int maxRadius = 2;
    vector<Star*> stars;
public:
    StarPanel(float x, float y) {
        position.setValues(x, y);
        movementVector.setValues(0.0f, 1.0f);
        speed = 20.0f;
        generateStars();
    }

    void Update() override {
        move();
        if (position.y > SCREEN_HEIGHT) {
            position.y = -SCREEN_HEIGHT;
            regenerateStars();
        } 
        drawStars();
    }

    //draw stars
    void drawStars() {
        for (int i = 0; i < stars.size(); i++) {
            stars[i]->drawStar(position.x, position.y);
        }
    }

    //clear and generate new stars
    void regenerateStars() {
        clearStars();
        generateStars();
    }

    //generate new stars
    void generateStars() {
        for (int i = 0; i < starCount; ++i) {
            int radius = minRadius + rand() % (maxRadius - minRadius + 1);
            int x = rand() % SCREEN_WIDTH;
            int y = rand() % SCREEN_HEIGHT;
            stars.push_back(new Star(x, y, radius));
        }
    }
    
    //safely delete all stars
    void clearStars() {
        for (int i = 0; i < stars.size(); i++) {
            delete(stars.at(i));
        }
        stars.clear();
    }
};

StarPanel starPanelOne(0, -SCREEN_HEIGHT);
StarPanel starPanelTwo(0, 0);

class Asteroid : public Movable {
public:
    bool shouldDestroy = false;

    Asteroid(float positionX) {
        position.setValues(positionX, -100.0f);
        movementVector.y = 1.0f;
        speed = 75.0f;
        rotation = rand() % 360;
        scale = (float)(rand() % 7 + 5) / 10; //rand between 0.5 and 1.2
    }

    void Update() override {
        move();
        if (position.y >= SCREEN_HEIGHT + 100)
            shouldDestroy = true;
    }

    bool getShouldDestroy() {
        return shouldDestroy;
    }

    void DrawObject() override {
        glPushMatrix();
        glTranslatef(position.x, position.y, 0);
        glScalef(scale, scale, 0);
        glRotatef(rotation, 0, 0, 1);

        drawAsteroid();

        glPopMatrix();
    }

    void drawAsteroid() {

        /*Body*/

        //bac       
        glBegin(GL_POLYGON);
        glColor3f(ASTEROID_BASE_COLOR);
        glVertex2f(0.0f, 0.0f);
        glColor3f(ASTEROID_BASE_COLOR_DARKEST);
        for (int i = 0; i <= 360; i += 70) {
            theta = (i / 180.0f) * 3.14159;
            glVertex2f(100 * cos(theta), 90 * sin(theta));
        }
        glVertex2f(100.0f, 0.0f);
        glEnd();

        //mid
        glBegin(GL_POLYGON);
        glColor3f(ASTEROID_BASE_COLOR);
        glVertex2f(0.0f, 0.0f);
        glColor3f(ASTEROID_BASE_COLOR_DARKER);
        for (int i = 0; i <= 360; i += 40) {
            theta = ((i + 45)/ 180.0f) * 3.14159;
            glVertex2f(95 * cos(theta), 85 * sin(theta));
        }
        glVertex2f(90.0f, 0.0f);
        glEnd();

        //fron
        glBegin(GL_POLYGON);
        glColor3f(ASTEROID_HIGHLIGHT_COLOR);
        glVertex2f(0.0f, 0.0f);
        glColor3f(ASTEROID_BASE_COLOR);
        for (int i = 0; i <= 360; i += 52) {
            theta = (i / 180.0f) * 3.14159;
            glVertex2f(93 * cos(theta), 83 * sin(theta));
        }
        glVertex2f(88.0f, 0.0f);
        glEnd();


        /*Holes*/

        //check out these holes ;)
        drawAsteroidHole(10.0f, 25.0f, 20.0f);
        drawAsteroidHole(50.0f, 50.0f, 15.0f);
        drawAsteroidHole(50.0f, -50.0f, 17.0f);
        drawAsteroidHole(-60.0f, -20.0f, 22.0f);
        drawAsteroidHole(-10.0f, -40.0f, 18.0f);
    }

    //asteroid holes
    void drawAsteroidHole(float x, float y, float radius) {
        glBegin(GL_POLYGON);
        glColor3f(ASTEROID_BASE_COLOR);
        glVertex2f(x, y);
        glColor3f(ASTEROID_HOLE_COLOR);
        for (int i = 0; i <= 360; i += 45) {
            theta = (i / 180.0f) * 3.14159;
            glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
        }
        glEnd();
    }
};

void drawSpaceBackground() {
    //background black, just in case
    glBegin(GL_QUADS);
    glColor3f(BACKGROUND_OUTER);
    glVertex2f(300, 400);
    glVertex2f(600, 0);
    glVertex2f(600, 800);
    glVertex2f(0, 800);
    glVertex2f(0, 0);
    glVertex2f(600, 0);
    glEnd();

    //inner circle
    glBegin(GL_POLYGON);
    glColor3f(BACKGROUND_INNER);
    glVertex2f(300, 400);
    glColor3f(BACKGROUND_OUTER);
    for (int i = 0; i <= 360; i++) {
        theta = (i / 180.0f) * 3.14159;
        glVertex2f(300.0f + 275.0f * cos(theta), 400 + 375.0f * sin(theta));
    }
    glEnd();

    //update star panels
    starPanelOne.Update();
    starPanelTwo.Update();

    updateAsteroids();
}

vector<Asteroid*> asteroids;
float asteroidSpawnCooldown = 7.0f;
float currentAsteroidSpawnCooldown = asteroidSpawnCooldown;

void updateAsteroids() {

    //spawn cooldown
    if (currentAsteroidSpawnCooldown < asteroidSpawnCooldown)
        currentAsteroidSpawnCooldown += deltaTime;
    else
    {
        currentAsteroidSpawnCooldown = rand() % 3;
        asteroids.push_back(new Asteroid(rand() % SCREEN_WIDTH));
    }

    //update each
    for (int i = 0; i < asteroids.size(); i++) {
        asteroids.at(i)->Update();
        asteroids.at(i)->DrawObject();
        if (asteroids.at(i)->getShouldDestroy()) { //safe deletion
            delete(asteroids.at(i));
            asteroids.erase(asteroids.begin() + i);
        }
    }
}

#endif // !Background_h

