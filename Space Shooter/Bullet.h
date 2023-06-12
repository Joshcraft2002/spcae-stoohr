#ifndef Bullet_h
#define Bullet_h

//colors
#define PLAYER_BULLET_AURA 0.0f, 0.0f, 1.0f
#define ENEMY_BULLET_AURA 1.0f, 0.0f, 0.0f
#define BULLET_CORE 1.0f, 1.0f, 1.0f

class Bullet : public Movable {
private:
    bool hit = false;
    //for bullet color
    float auraR = 1.0f, auraG = 1.0f, auraB = 1.0f;

protected:
    bool friendly = false;
    float damage = 1.0f;

public:
    enum class BulletType {
        BALL,
        BOLT
    };

    BulletType bulletType;

    //initialize bullet
    Bullet(float positionX, float positionY, float vectorX, float vectorY, float speed, BulletType bulletType, float r, float g, float b) {
        position.setValues(positionX, positionY);
        movementVector.setValues(vectorX, vectorY);
        this->speed = speed;
        this->bulletType = bulletType;
        auraR = r;
        auraG = g;
        auraB = b;
    }

    //bullet, but passing a movement vector
    Bullet(float positionX, float positionY, Vector2D* movementVector, float speed, BulletType bulletType, float r, float g, float b) : Bullet(positionX, positionY, movementVector->x, movementVector->y, speed, bulletType, r, g, b) {
    
    }

    void Update() override {       
        move();      
        outOfBoundsCheck();
    }

    void DrawObject() override {
        glPushMatrix();
        glTranslatef(position.x, position.y, 0);
        glRotatef(rotation, 0, 0, 1);

        switch (bulletType) {
        case BulletType::BALL:
            drawBall();
            break;
        case BulletType::BOLT:
            drawBolt();
            break;
        }

        glPopMatrix();        
    }   

    //get bullet damage
    float getDamage() {
        return damage;
    }

    //check if bullet hit
    bool hasHit() {
        return hit;
    }

    //make bullet hit
    void callHit() {
        hit = true;
    }

    //check sus level of bullet
    bool isFriendly() {
        return friendly;
    }

    //check if bullet out of bounds
    void outOfBoundsCheck() {
        if (position.x < -10.0f || position.x > SCREEN_WIDTH + 10 || position.y < -10.0f || position.y > SCREEN_HEIGHT + 10)
            hit = true;
    }

    void drawBall() {
        //aura
        glBegin(GL_POLYGON);
        glColor3f(auraR, auraG, auraB);
        for (int i = 0; i < 360; i++) {
            theta = (i / 180.0f) * 3.14159;
            glVertex2f(10.0f * cos(theta), 10 * sin(theta));
        }
        glEnd();

        //core
        glBegin(GL_POLYGON);
        glColor3f(BULLET_CORE);
        for (int i = 0; i < 360; i++) {
            theta = (i / 180.0f) * 3.14159;
            glVertex2f(7.0f * cos(theta), 7 * sin(theta));
        }
        glEnd();
    }

    void drawBolt() {       
        //aura      
        glBegin(GL_POLYGON);
        glColor3f(auraR, auraG, auraB);
        glVertex2f(-5.0f, 15.0f);
        glVertex2f(0.0f, 20.0f);
        glVertex2f(5.0f, 15.0f);
        glVertex2f(5.0f, -15.0f);
        glVertex2f(0.0f, -20.0f);
        glVertex2f(-5.0f, -15.0f);
        glEnd();

        //core
        glBegin(GL_QUADS);
        glColor3f(BULLET_CORE);
        glVertex2f(-2.0f, 15.0f);
        glVertex2f(2.0f, 15.0f);
        glVertex2f(2.0f, -15.0f);
        glVertex2f(-2.0f, -15.0f);
        glEnd();        
    }
};

class EnemyBullet : public Bullet {
public:
    //enemy bullet
    EnemyBullet(float positionX, float positionY, float vectorX, float vectorY, float speed, BulletType bulletType) : Bullet(positionX, positionY, vectorX, vectorY, speed, bulletType, ENEMY_BULLET_AURA) {

    }

    //enemy bullet, but with movement vector passed (normalize first!)
    EnemyBullet(float positionX, float positionY, Vector2D* movementVector, float speed, BulletType bulletType) : Bullet(positionX, positionY, movementVector, speed, bulletType, ENEMY_BULLET_AURA) {

    }
    
    //with set rotation
    EnemyBullet(float positionX, float positionY, float vectorX, float vectorY, float rotation, float speed, BulletType bulletType) : Bullet(positionX, positionY, vectorX, vectorY, speed, bulletType, ENEMY_BULLET_AURA) {
        this->rotation = rotation;
    }

    //with set rotation, but with movement vector passed (normalize first!)
    EnemyBullet(float positionX, float positionY, Vector2D* movementVector, float rotation, float speed, BulletType bulletType) : Bullet(positionX, positionY, movementVector, speed, bulletType, ENEMY_BULLET_AURA) {
        this->rotation = rotation;
    }
};

class PlayerBullet : public Bullet {

public:
    PlayerBullet(float positionX, float positionY, float speed, float damage, BulletType bulletType) : Bullet(positionX, positionY, 0, -1, speed, bulletType, PLAYER_BULLET_AURA) {
        friendly = true;
        this->damage = damage;
    }    
};

//vector holding all bullets
vector<Bullet*> bullets;

#endif