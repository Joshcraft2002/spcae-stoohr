#ifndef EnemyBoss_h
#define EnemyBoss_h

//colors

#define BOSS_CRYSTAL_INNER 1.0f, 0.6f, 0.0f
#define BOSS_CRYSTAL_OUTER 0.7f, 0.3f, 0.0f

class EnemyBoss : public Enemy {
private:  
    //current pattern
    enum class BossAttack {
        SPIRAL,
        OUTWARD_CIRCLE
    };

    //extra attacks during patterns
    enum class BossAttackMod {
        NONE,
        LINEBEAM_ROTATION,
        DISCS
    };

    //set default boss states
    int phase = 1;
    BossAttack currentAttack = BossAttack::SPIRAL;
    BossAttackMod currentAttackMod = BossAttackMod::NONE;

    //basic movement waypoint
    WayPoint basicMovement;
public:
    EnemyBoss() : Enemy(500.0f, 90.0f) {
        speed = 200.0f;
        position.setValues(300.0f, -100.0f);

        //fixed health bar location
        healthBarPosition.setValues(50.0f, 40.0f);
        healthBarWidth = 500;
        healthBarHeight = 20;

        //fill in basic movement waypoint set
        basicMovement.addWayPoint(200.0f, 180.0f);
        basicMovement.addWayPoint(400.0f, 180.0f);
    }

    void Update() override {
        //set phases
        if (currentHealth > (maxHealth * 0.75)) {
            if (phase != 1) {
                phase = 1;
                speed = 20.0f;
                currentAttack = BossAttack::SPIRAL;
                currentAttackMod = BossAttackMod::NONE;
            }            
        }            
        else if (currentHealth > (maxHealth * 0.5)) {
            if (phase != 2) {
                phase = 2;
                speed = 50.0f;
                currentAttack = BossAttack::OUTWARD_CIRCLE;
                currentAttackMod = BossAttackMod::NONE;
            }
        }
        else if (currentHealth > (maxHealth * 0.25)) {
            if (phase != 3) {
                phase = 3;
                speed = 75.0f;
                currentAttack = BossAttack::SPIRAL;
                currentAttackMod = BossAttackMod::LINEBEAM_ROTATION;
            }
        }
        else {
            if (phase != 4) {
                phase = 4;
                currentAttack = BossAttack::OUTWARD_CIRCLE;
                currentAttackMod = BossAttackMod::DISCS;
            }
        }           

        //primary shot
        if (currentShotCooldown < shotCooldown)
            currentShotCooldown += deltaTime; //count up cooldown
        else
        {
            switch (currentAttack)
            {
            case BossAttack::SPIRAL:
                spiralAttack();
                break;
            case BossAttack::OUTWARD_CIRCLE:
                outwardCircleAttack();
                break;
            }
            currentShotCooldown = 0.0f; //reset cooldown
        }

        //secondary shot
        if (currentShotCooldownSecondary < shotCooldownSecondary)
            currentShotCooldownSecondary += deltaTime; //count up cooldown
        else
        {
            switch (currentAttackMod)
            {
            case BossAttackMod::LINEBEAM_ROTATION:
                linebeamRotationAttack();
                break;
            case BossAttackMod::DISCS:
                discsAttack();
                break;
            }
            currentShotCooldownSecondary = 0.0f; //reset cooldown
        }

        //movement
        switch (phase)
        {
        case 1:
        case 2:
            moveInWayPoints(&basicMovement);
            break;
        case 3:
            moveTo(300, 300);
            break;
        case 4:
            moveTo(300, 200);
            break;
        }

        //reset attack angle if exceed 360
        if (attackAngle >= 360.0f)
            attackAngle -= 360.0f;
        //reset secondary attack angle if exceed 60
        if (attackAngleSecondary >= 360.0f)
            attackAngleSecondary -= 360.0f;
                   
    }  

    //spiral attack pattern
    void spiralAttack() {
        shotCooldown = 0.3f; //set shot cooldown
        float bulletSpeed = 170.0f; //set bullet speed

        for (float i = attackAngle; i <= 720; i += 90) //attack in 4 directions, 720deg to account for going over 360
        {
            float attackRadians = (attackAngle + i / 180.0f) * 3.14159; //attack direction
            bullets.push_back(new EnemyBullet(position.x, position.y, cos(attackRadians), sin(attackRadians), bulletSpeed, Bullet::BulletType::BALL));
        }
        attackAngle+=17;
    }

    //outward circle attack pattern
    void outwardCircleAttack() {
        shotCooldown = 0.35f; //set shot cooldown
        float bulletSpeed = 350.0f;

        for (int i = 0; i < 360; i+=20) {
            float attackRadians = ((i + attackAngle) / 180.0f) * 3.14159; //attack direction
            bullets.push_back(new EnemyBullet(position.x, position.y, cos(attackRadians), sin(attackRadians), bulletSpeed, Bullet::BulletType::BALL));
        }

        attackAngle+=11;
    }

    //line that rotates around
    void linebeamRotationAttack() {
        shotCooldownSecondary = 0.05f;
        float bulletSpeed = 500.0f;

        float attackRadians = -(attackAngleSecondary / 180.0f) * 3.14159; //attack direction, negative to go anticlockwise
        bullets.push_back(new EnemyBullet(position.x, position.y, cos(attackRadians), sin(attackRadians), bulletSpeed, Bullet::BulletType::BALL));
        attackRadians = -((attackAngleSecondary + 180) / 180.0f) * 3.14159;
        bullets.push_back(new EnemyBullet(position.x, position.y, cos(attackRadians), sin(attackRadians), bulletSpeed, Bullet::BulletType::BALL));

        attackAngleSecondary++;
    }

    void discsAttack() {
        shotCooldownSecondary = 0.8f; 
        float discRadius = 40.0f; //radius of each disc
        float bulletSpeed = 170.0f;

        for (float i = attackAngle; i <= 720; i += 90) //attack in 4 directions, 720deg to account for going over 360
        {
            float attackRadians = - (attackAngleSecondary + i/ 180.0f) * 3.14159; //attack direction, negative to go anticlockwise
            for (int i = 0; i < 360; i += 30) {
                float positionRadians = (i / 180.0f) * 3.14159; //for bullet position in disc
                //this should've been its own bullet type but agh I need to finish this for submission lol
                bullets.push_back(new EnemyBullet(position.x + discRadius * cos(positionRadians), position.y + discRadius * sin(positionRadians), cos(attackRadians), sin(attackRadians), bulletSpeed, Bullet::BulletType::BALL));
            }
        }
        attackAngleSecondary += 77;
    }

    void DrawObject() override {
        glPushMatrix();
        glTranslatef(position.x, position.y, 0);
        glScalef(0.6, 0.6, 1);

        drawBoss();

        glPopMatrix();
    }    

    void drawBoss()
    {
        /*Hull*/

        //hull
        glBegin(GL_QUAD_STRIP);
        glColor3f(ENEMY_SHADOW);
        glVertex2f(-40, -40);
        glVertex2f(-50, 80);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(-30, -40);
        glVertex2f(-40, 80);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(30, -40);
        glVertex2f(40, 80);
        glColor3f(ENEMY_SHADOW);
        glVertex2f(40, -40);
        glVertex2f(50, 80);     
        glEnd();

        //hull stripe
        glBegin(GL_QUADS);
        glColor3f(ENEMY_RED);
        glVertex2f(-20, -40);
        glVertex2f(20, -40);
        glVertex2f(20, 40);
        glVertex2f(-20, 40);
        glEnd();


        /*Bow*/

        //bow gradient
        glBegin(GL_QUAD_STRIP);
        glColor3f(ENEMY_LIGHT_GRAY);
        glVertex2f(0, 20);
        glColor3f(ENEMY_GRAY);
        glVertex2f(0, 0);
        glColor3f(ENEMY_LIGHT_GRAY);
        glVertex2f(60, 80);
        glColor3f(ENEMY_GRAY);
        glVertex2f(80, 80);
        glColor3f(ENEMY_LIGHT_GRAY);
        glVertex2f(0, 140);
        glColor3f(ENEMY_GRAY);
        glVertex2f(0, 160);
        glColor3f(ENEMY_LIGHT_GRAY);
        glVertex2f(-60, 80);
        glColor3f(ENEMY_GRAY);
        glVertex2f(-80, 80);
        glColor3f(ENEMY_LIGHT_GRAY);
        glVertex2f(0, 20);
        glColor3f(ENEMY_GRAY);
        glVertex2f(0, 0);
        glEnd();
        
        //bow
        glBegin(GL_QUADS);
        glColor3f(ENEMY_LIGHT_GRAY);
        glVertex2f(0, 20);
        glVertex2f(60, 80);
        glVertex2f(0, 140);
        glVertex2f(-60, 80);
        glEnd();


        /*Pods*/

        //left pod outer
        glBegin(GL_QUAD_STRIP);
        glColor3f(ENEMY_SHADOW);
        glVertex2f(-60, -140);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(-70, -120);
        glColor3f(ENEMY_SHADOW);
        glVertex2f(-100, 120);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(-100, 80);
        glColor3f(ENEMY_SHADOW);
        glVertex2f(-140, 0);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(-130, -20);
        glEnd();

        //left pod inner
        glBegin(GL_POLYGON);
        glColor3f(ENEMY_LIGHT_GRAY);
        glVertex2f(-100, -30);
        glColor3f(ENEMY_GRAY);
        glVertex2f(-70, -120);
        glVertex2f(-130, -20);
        glVertex2f(-100, 80);
        glVertex2f(-70, -120);
        glEnd();

        //right pod outer
        glBegin(GL_QUAD_STRIP);
        glColor3f(ENEMY_SHADOW);
        glVertex2f(60, -140);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(70, -120);
        glColor3f(ENEMY_SHADOW);
        glVertex2f(100, 120);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(100, 80);
        glColor3f(ENEMY_SHADOW);
        glVertex2f(140, 0);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(130, -20);
        glEnd();

        //right pod inner
        glBegin(GL_POLYGON);
        glColor3f(ENEMY_LIGHT_GRAY);
        glVertex2f(100, -30);
        glColor3f(ENEMY_GRAY);
        glVertex2f(70, -120);
        glVertex2f(130, -20);
        glVertex2f(100, 80);
        glVertex2f(70, -120);
        glEnd();


        /*Thrusters*/
      
        //small thruster left
        glBegin(GL_QUAD_STRIP);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(-30, -80);
        glVertex2f(-25, -110);
        glColor3f(ENEMY_GRAY);
        glVertex2f(-15, -80);
        glVertex2f(-15, -110);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(0, -80);
        glVertex2f(-5, -110);
        glEnd();

        //small thruster right
        glBegin(GL_QUAD_STRIP);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(30, -80);
        glVertex2f(25, -110);
        glColor3f(ENEMY_GRAY);
        glVertex2f(15, -80);
        glVertex2f(15, -110);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(0, -80);
        glVertex2f(5, -110);
        glEnd();

        //big thruster
        glBegin(GL_QUAD_STRIP);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(-18, -80);
        glVertex2f(-12, -120);
        glColor3f(ENEMY_GRAY);
        glVertex2f(0, -80);
        glVertex2f(0, -120);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(18, -80);
        glVertex2f(12, -120);
        glEnd();


        /*Wings*/
        
        //lower wing
        glBegin(GL_QUADS);
        glColor3f(ENEMY_GRAY);
        glVertex2f(-100, -30);
        glVertex2f(-100, -60);
        glVertex2f(100, -60);
        glVertex2f(100, -30);
        glEnd();

        //rear wings
        glBegin(GL_POLYGON);
        glColor3f(ENEMY_GRAY);
        
        glVertex2f(0, -80);
        glVertex2f(120, -120);
        glVertex2f(100, -80);
        glVertex2f(-100, -80);
        glVertex2f(-120, -120);
        glEnd();

        //upper wing 
        glBegin(GL_QUAD_STRIP);
        glColor3f(ENEMY_DARK_GRAY);
        glVertex2f(-140, -20);
        glVertex2f(-120, -80);
        glVertex2f(0, -40);
        glVertex2f(0, -100);
        glVertex2f(140, -20);
        glVertex2f(120, -80);
        glEnd();

        //upper wing stripe
        glBegin(GL_QUAD_STRIP);
        glColor3f(ENEMY_RED);
        glVertex2f(-130, -30);
        glVertex2f(-115, -70);
        glVertex2f(0, -50);
        glVertex2f(0, -90);
        glVertex2f(130, -30);
        glVertex2f(115, -70);
        glEnd();


        /*Bridge*/

        //bridge extension outline
        glBegin(GL_QUADS);
        glColor3f(ENEMY_GRAY);
        glVertex2f(-22, -50);
        glVertex2f(-18, -100);
        glVertex2f(18, -100);
        glVertex2f(22, -50);
        glEnd();

        //bridge extension
        glBegin(GL_QUADS);
        glColor3f(ENEMY_LIGHT_GRAY);
        glVertex2f(-16, -50);
        glVertex2f(-12, -100);
        glVertex2f(12, -100);
        glVertex2f(16, -50);
        glEnd();

        //bridge outline
        glBegin(GL_POLYGON);
        glColor3f(ENEMY_GRAY);
        glVertex2f(-30, -10);
        glVertex2f(-30, -50);
        glVertex2f(0, -70);
        glVertex2f(30, -50);
        glVertex2f(30, -10);
        glEnd();

        //bridge
        glBegin(GL_POLYGON);
        glColor3f(ENEMY_LIGHT_GRAY);
        glVertex2f(-25, -15);
        glVertex2f(-25, -45);
        glVertex2f(0, -60);
        glVertex2f(25, -45);
        glVertex2f(25, -15);
        glEnd();


        /*Crystal*/

        //crystalthing
        glBegin(GL_POLYGON);
        glColor3f(BOSS_CRYSTAL_INNER);
        glVertex2f(0.0f, 80.0f);
        glColor3f(BOSS_CRYSTAL_OUTER);
        for (int i = 0; i <= 360; i++) {
            theta = (i / 180.0f) * 3.14159;
            glVertex2f(30.0f * cos(theta), 80 + 30.0f * sin(theta));
        }
        glEnd();
    }
};

#endif