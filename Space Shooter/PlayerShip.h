#ifndef PlayerShip_h
#define PlayerShip_h

#define PLAYER_BODY 1.0f, 1.0f, 1.0f
#define PLAYER_BODY_OUTLINE 0.6f, 0.6f, 0.6f

#define PLAYER_THRUSTER 0.3f, 0.3f, 0.3f
#define PLAYER_THRUSTER_HIGHLIGHT 0.5f, 0.5f, 0.5f

#define PLAYER_WING 0.9f, 0.9f, 0.0f
#define PLAYER_POD 0.1f, 0.3f, 1.0f
#define PLAYER_POD_HIGHLIGHT 0.2f, 0.4f, 1.0f

#define PLAYER_COCKPIT_HIGHLIGHT 0.3f, 0.8f, 1.0f
#define PLAYER_COCKPIT 0.0f, 0.6f, 0.8f

class PlayerShip : public Movable, public HasHitbox {
private:
    float shotCooldown = 0.2f;
    float currentShotCooldown = 0.0f;
public:
    PlayerShip() : HasHitbox(15.0f) {
        this->speed = 400.0f;
        position.setValues(300.0f, 700.0f);
    }

    void Update() override {
        setMoveVectors();
        move();

        if (currentShotCooldown < shotCooldown)
            currentShotCooldown += deltaTime;
        else if (keys[GLFW_KEY_Z] == true)
            fire();       
    }

    void DrawObject() override {
        glPushMatrix();
        glTranslatef(position.x, position.y, 0);
        glScalef(0.3f, 0.3f, 0);
        drawShip();
        glPopMatrix();
    }

    //override so player don't go off map
    void move() {
        float newPositionX = position.x + movementVector.x * speed * deltaTime;
        float newPositionY = position.y + movementVector.y * speed * deltaTime;

        //bounds check
        bool inBoundsX = newPositionX - hitboxRadius >= 0 && newPositionX + hitboxRadius <= SCREEN_WIDTH;
        bool inBoundsY = newPositionY - hitboxRadius >= 0 && newPositionY + hitboxRadius <= SCREEN_HEIGHT;

        if (inBoundsX && inBoundsY)
            position.setValues(newPositionX, newPositionY);
    }

    //set move vectors based on key input
    void setMoveVectors() {
        //get input vectors
        int vectorX = (keys[GLFW_KEY_RIGHT] ? 1.0f : 0.0f) - (keys[GLFW_KEY_LEFT] ? 1.0f : 0.0f);
        int vectorY = (keys[GLFW_KEY_DOWN] ? 1.0f : 0.0f) - (keys[GLFW_KEY_UP] ? 1.0f : 0.0f);
        movementVector.setValues(vectorX, vectorY);
        movementVector.normalize();
    }

    //fire off a shot
    void fire() {
        currentShotCooldown = 0.0f;
        //bullet offset
        float bulletOffsetX = 7.0f;
        float bulletOffsetY = -40.0f;
        //mah boi only knows how to fire bolts
        bullets.push_back(new PlayerBullet(position.x + bulletOffsetX, position.y + bulletOffsetY, 600, 1, Bullet::BulletType::BOLT));
        bullets.push_back(new PlayerBullet(position.x - bulletOffsetX, position.y + bulletOffsetY, 600, 1, Bullet::BulletType::BOLT));
    }

    //check if firing
    bool isFiring() {
        return keys[GLFW_KEY_Z];
    }

    //render le ship
    void drawShip()
    {       
        //left wing
        glColor3f(PLAYER_WING);
        glBegin(GL_QUADS);
        glVertex2f(-60.0f, 0.0f);
        glVertex2f(-60.0f, 20.0f);
        glVertex2f(0.0f, 10.0f);
        glVertex2f(0.0f, -30.0f);
        glEnd();

        //right wing
        glColor3f(PLAYER_WING);
        glBegin(GL_QUADS);
        glVertex2f(60.0f, 0.0f);
        glVertex2f(60.0f, 20.0f);
        glVertex2f(0.0f, 10.0f);
        glVertex2f(0.0f, -30.0f);
        glEnd();

        //thruster       
        glBegin(GL_QUAD_STRIP);       
        glColor3f(PLAYER_THRUSTER);
        glVertex2f(-20.0f, 20.0f);
        glVertex2f(-13.0f, 48.0f);
        glColor3f(PLAYER_THRUSTER_HIGHLIGHT);
        glVertex2f(0.0f, 20.0f);
        glVertex2f(0.0f, 48.0f);
        glColor3f(PLAYER_THRUSTER);
        glVertex2f(20.0f, 20.0f);
        glVertex2f(13.0f, 48.0f);        
        glEnd();

        //body      
        glBegin(GL_POLYGON);
        glColor3f(PLAYER_BODY);
        glVertex2f(0.0f, 0.0f);
        glColor3f(PLAYER_BODY_OUTLINE);
        glVertex2f(-40.0f, 0.0f);
        glColor3f(PLAYER_BODY);
        glVertex2f(0.0f, -100.0f);
        glColor3f(PLAYER_BODY_OUTLINE);
        glVertex2f(40.0f, 0.0f);
        glColor3f(PLAYER_BODY);
        glVertex2f(0.0f, 40.0f);
        glColor3f(PLAYER_BODY_OUTLINE);
        glVertex2f(-40.0f, 0.0f);
        glEnd();

        //cockpit        
        glBegin(GL_POLYGON);
        glColor3f(PLAYER_COCKPIT_HIGHLIGHT);
        glVertex2f(0.0f, -10.0f);
        glColor3f(PLAYER_COCKPIT);
        for (int i = 0; i < 360; i++) {
            theta = (i / 180.0f) * 3.14159;
            glVertex2f(15.0f * cos(theta), -10.0f + 30.0f * sin(theta));
        }
        glEnd();

        //left pod    
        glBegin(GL_POLYGON);
        glColor3f(PLAYER_POD_HIGHLIGHT);
        glVertex2f(-60.0f, 0.0f);
        glColor3f(PLAYER_POD);
        for (int i = 135; i < 225; i++) {
            theta = (i / 180.0f) * 3.14159;
            glVertex2f(-10 + 70.0f * cos(theta), 70.0f * sin(theta));
        }
        glEnd();

        //right pod       
        glBegin(GL_POLYGON);
        glColor3f(PLAYER_POD_HIGHLIGHT);
        glVertex2f(60.0f, 0.0f);
        glColor3f(PLAYER_POD);
        for (int i = -45; i < 45; i++) {
            theta = (i / 180.0f) * 3.14159;
            glVertex2f(10 + 70.0f * cos(theta), 70.0f * sin(theta));
        }
        glEnd();
    }
};

//define a player ship
PlayerShip alphaShip;

#endif