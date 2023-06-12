#ifndef Enemy_h
#define Enemy_h

//colors
#define ENEMY_HEALTH 1.0f, 0.0f, 0.0f
#define ENEMY_HEALTH_OUTLINE 0.5f, 0.0f, 0.0f

#define ENEMY_LIGHT_RED 0.8f, 0.3f, 0.3f
#define ENEMY_RED 0.6f, 0.0f, 0.0f
#define ENEMY_DARK_RED 0.3f, 0.0f, 0.0f

#define ENEMY_LIGHT_GRAY 0.7f, 0.7f, 0.7f
#define ENEMY_GRAY 0.5f, 0.5f, 0.5f
#define ENEMY_DARK_GRAY 0.3f, 0.3f, 0.3f
#define ENEMY_SHADOW 0.1f, 0.1f, 0.1f

class Enemy : public Movable, public HasHitbox {
protected:
	//health
    float maxHealth, currentHealth;    

    //moving into the scene
    bool movingIn = true;

    //primary shot
    float shotCooldown = 1.0f;
    float currentShotCooldown = 0.0f;
    float attackAngle = 0; //shot direction calcs

    //secondaryshot
    float shotCooldownSecondary = 1.0f;
    float currentShotCooldownSecondary = 0.0f;
    float attackAngleSecondary = 0;

    //health bar details
    Vector2D healthBarPosition;
    float healthBarWidth = 0.0f, healthBarHeight = 0.0f;
public:
	Enemy(float health, float hitboxRadius) : HasHitbox(hitboxRadius) {
        this->maxHealth = health;
		this->currentHealth = health;
	}   

    float getMaxHealth() {
        return maxHealth;
    }

    //check if this enemy is alive
    bool isAlive() {
        return currentHealth > 0.0f;
    }

    bool isMovingIn() {
        return movingIn;
    }

    void moveCircle(float center, bool isClockwise) {
               
    }

    //damage this enemy
    void damage(float damage) {
        currentHealth -= damage;
    }

    //set current health of this enemy
	void setHealth(float health) {
		this->currentHealth = health;
	}    

    //set whether this enemy is moving in
    void setMovingIn(bool movingIn) {
        this->movingIn = movingIn;
    }

    //draw health bar
    void DrawHealthBar() {
        //bar width based on health left
        float barWidth = healthBarWidth * (currentHealth / maxHealth);

        glPushMatrix();
        glTranslatef(healthBarPosition.x, healthBarPosition.y, 0);

        //bar proper
        glBegin(GL_QUAD_STRIP);
        glColor3f(ENEMY_HEALTH_OUTLINE);
        glVertex2f(0, -healthBarHeight);
        glVertex2f(barWidth, -healthBarHeight);
        glColor3f(ENEMY_HEALTH); //inner gradient
        glVertex2f(0, -healthBarHeight / 2);
        glVertex2f(barWidth, -healthBarHeight / 2);
        glColor3f(ENEMY_HEALTH_OUTLINE);
        glVertex2f(0, 0);
        glVertex2f(barWidth, 0);

        glEnd();

        glPopMatrix();
    }
};



//vector holding all enemies
vector<Enemy*> enemies;

#endif // !Enemy_h
