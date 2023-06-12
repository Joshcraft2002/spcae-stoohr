#ifndef EnemyBolter_h
#define EnemyBolter_h

class EnemyBolter : public Enemy {
private:	
	GameObject* target; //gameobject to face
	Vector2D faceVector; //vector for facing
	Enemy* enemy = this;	
public:
	WayPoint wayPointSet;

		EnemyBolter(float initialX, float initialY, GameObject* target) : Enemy(12.0f, 30.0f) {
		position.setValues(initialX, initialY);
		shotCooldown = 1.5f;
		speed = 175.0f;
		this->target = target;
		healthBarHeight = 10.0f;
		healthBarWidth = 25.0f;
	}

	void Update() override {	
		moveInWayPoints(&wayPointSet);

		faceTarget();

		if (currentShotCooldown < shotCooldown)
			currentShotCooldown += deltaTime; //count up cooldown
		else
			fire();

		//update health bar location
		healthBarPosition.setValues(position.x - 12.5f, position.y - 25);
	}

	void DrawObject() override {
		glPushMatrix();
		glTranslatef(position.x, position.y, 0);
		glScalef(0.3f, 0.3f, 0);
		glRotatef(rotation, 0, 0, 1);

		drawBolter();

		glPopMatrix();
	}

	//face toward target
	void faceTarget() {
		faceVector.setValues(target->position.x - position.x, target->position.y - position.y);
		faceVector.normalize();
		//radians to degrees
		rotation = faceVector.getAngleDegrees() - 90.0f; //extra 90 to account for a weird offset
	}

	void fire() {
		currentShotCooldown = 0.0f;
		float bulletSpeed = 200.0f;
		float bulletOffset = 45.0f; //how far in front to shoot bullet
		bullets.push_back(new EnemyBullet(position.x + bulletOffset * faceVector.x, position.y + bulletOffset * faceVector.y, &faceVector, rotation, bulletSpeed, Bullet::BulletType::BOLT));
	}

	void drawBolter() {	
		/*Middle Body*/

		//lower hull
		glBegin(GL_QUADS);
		glColor3f(ENEMY_DARK_RED);
		glVertex2f(-20.0f, -40.0f);
		glColor3f(ENEMY_RED);
		glVertex2f(0.0f, -40.0f);
		glColor3f(ENEMY_DARK_RED);
		glVertex2f(20.0f, -40.0f);
		glColor3f(ENEMY_RED);
		glVertex2f(0.0f, 60.0f);
		glEnd();

		//thruster
		glBegin(GL_QUAD_STRIP);
		glColor3f(ENEMY_DARK_GRAY);
		glVertex2f(-20, -40);
		glVertex2f(-15, -65);
		glColor3f(ENEMY_GRAY);
		glVertex2f(0, -40);
		glVertex2f(0, -65);
		glColor3f(ENEMY_DARK_GRAY);
		glVertex2f(20, -40);
		glVertex2f(15, -65);
		glEnd();

		//wing "strut"
		glBegin(GL_QUAD_STRIP);
		glColor3f(ENEMY_GRAY);
		glVertex2f(-60, -20);
		glVertex2f(-60, -40);
		glColor3f(ENEMY_LIGHT_GRAY);
		glVertex2f(0, -40);
		glVertex2f(0, -60);
		glColor3f(ENEMY_GRAY);
		glVertex2f(60, -20);
		glVertex2f(60, -40);
		glEnd();

		//bow
		glBegin(GL_POLYGON);
		glColor3f(ENEMY_LIGHT_GRAY);
		glVertex2f(0, 40);		
		glVertex2f(0, -25);
		glColor3f(ENEMY_GRAY);
		glVertex2f(25, 40);	
		glColor3f(ENEMY_LIGHT_GRAY);
		glVertex2f(0, 100);
		glColor3f(ENEMY_GRAY);
		glVertex2f(-25, 40);
		glColor3f(ENEMY_LIGHT_GRAY);
		glVertex2f(0, -25);		
		glEnd();

		/*Left Wing*/

		//bottom
		glBegin(GL_TRIANGLES);
		glColor3f(ENEMY_DARK_GRAY);
		glVertex2f(-80.0f, -40.0f);
		glColor3f(ENEMY_GRAY);
		glVertex2f(-40.0f, -60.0f);
		glVertex2f(-20.0f, 120.0f);
		glEnd();

		//top
		glBegin(GL_TRIANGLES);
		glColor3f(ENEMY_LIGHT_GRAY);
		glVertex2f(-120.0f, -60.0f);
		glVertex2f(-60.0f, -50.0f);
		glVertex2f(-40.0f, 60.0f);
		glEnd();

		//inner top
		glBegin(GL_TRIANGLES);
		glColor3f(ENEMY_RED);
		glVertex2f(-108.0f, -55.0f);
		glVertex2f(-70.0f, -48.0f);
		glVertex2f(-50.0f, 37.0f);
		glEnd();


		/*Right Wing*/

		//bottom
		glBegin(GL_TRIANGLES);
		glColor3f(ENEMY_DARK_GRAY);
		glVertex2f(80.0f, -40.0f);
		glColor3f(ENEMY_GRAY);
		glVertex2f(40.0f, -60.0f);
		glVertex2f(20.0f, 120.0f);
		glEnd();

		//top
		glBegin(GL_TRIANGLES);
		glColor3f(ENEMY_LIGHT_GRAY);
		glVertex2f(120.0f, -60.0f);
		glVertex2f(60.0f, -50.0f);
		glVertex2f(40.0f, 60.0f);
		glEnd();

		//inner top
		glBegin(GL_TRIANGLES);
		glColor3f(ENEMY_RED);
		glVertex2f(108.0f, -55.0f);
		glVertex2f(70.0f, -48.0f);
		glVertex2f(50.0f, 37.0f);
		glEnd();


		/*Cockpit*/

		//cockpit		
		glBegin(GL_POLYGON);
		glColor3f(ENEMY_LIGHT_RED);
		glVertex2f(0.0f, 40.0f);
		glColor3f(ENEMY_RED);
		for (int i = 0; i <= 360; i++) {
			theta = (i / 180.0f) * 3.14159;
			glVertex2f(12.0f * cos(theta), 40.0f + 25.0f * sin(theta));
		}
		glEnd();
	}
};

#endif // !EnemyBolter