#ifndef Text_h
#define Text_h

#define TEXT_WHITE 1.0f, 1.0f, 1.0f
#define TEXT_RED 1.0f, 0.0f, 0.0f
#define TEXT_GREEN 0.0f, 1.0f, 0.0f

class TextField {
private:
	float positionX, positionY;
	float scale;
	float r, g, b;
public:
	TextField(float positionX, float positionY, float scale, float r, float g, float b) {
		this->positionX = positionX;
		this->positionY = positionY;
		this->scale = scale;
		this->r = r;
		this->g = g;
		this->b = b;
	}

	void DrawTextField(string input) {
		glPushMatrix();
		glTranslatef(positionX, positionY, 0);
		glScalef(scale, scale, 1);
		glColor3f(r, g, b);

		for (int i = 0; i < input.size(); i++)
		{
			switch (input[i])
			{
			case 'A':
			case 'a':
				drawA();
				break;
			case 'B':
			case 'b':
				drawB();
				break;
			case 'C':
			case 'c':
				drawC();
				break;
			case 'D':
			case 'd':
				drawD();
				break;
			case 'E':
			case 'e':
				drawE();
				break;
			case 'F':
			case 'f':
				drawF();
				break;
			case 'G':
			case 'g':
				drawG();
				break;
			case 'H':
			case 'h':
				drawH();
				break;
			case 'I':
			case 'i':
				drawI();
				break;
			case 'J':
			case 'j':
				drawJ();
				break;
			case 'K':
			case 'k':
				drawK();
				break;
			case 'L':
			case 'l':
				drawL();
				break;
			case 'M':
			case 'm':
				drawM();
				glTranslatef(20, 0, 0); //extra shift cuz m thic
				break;
			case 'N':
			case 'n':
				drawN();
				break;
			case 'O':
			case 'o':
				drawO();
				break;
			case 'P':
			case 'p':
				drawP();
				break;
			case 'Q':
			case 'q':
				drawQ();
				break;
			case 'R':
			case 'r':
				drawR();
				break;
			case 'S':
			case 's':
				drawS();
				break;
			case 'T':
			case 't':
				drawT();
				break;
			case 'U':
			case 'u':
				drawU();
				break;
			case 'V':
			case 'v':
				drawV();
				break;
			case 'W':
			case 'w':
				drawW();
				glTranslatef(40, 0, 0); //extra shift cuz w thic
				break;
			case 'X':
			case 'x':
				drawX();
				break;
			case 'Y':
			case 'y':
				drawY();
				break;
			case 'Z':
			case 'z':
				drawZ();
				break;
			case ' ':
				glTranslatef(-40, 0, 0); //countershift for whitespace
				break;
			default:
				break;
			}

			glTranslatef(80, 0, 0);
		}

		glPopMatrix();
	}

	void drawA() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 20);
		glVertex2f(0, 100);
		glVertex2f(20, 100);
		glVertex2f(20, 20);
		glEnd();

		//top
		glBegin(GL_QUADS);
		glVertex2f(10, 0);
		glVertex2f(10, 20);
		glVertex2f(50, 20);
		glVertex2f(50, 0);
		glEnd();

		//mid
		glBegin(GL_QUADS);
		glVertex2f(20, 50);
		glVertex2f(20, 70);
		glVertex2f(40, 70);
		glVertex2f(40, 50);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(40, 20);
		glVertex2f(40, 100);
		glVertex2f(60, 100);
		glVertex2f(60, 20);
		glEnd();
	}

	void drawB() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 100);
		glVertex2f(20, 100);
		glVertex2f(20, 0);
		glEnd();

		//top
		glBegin(GL_QUADS);
		glVertex2f(20, 0);
		glVertex2f(20, 20);
		glVertex2f(50, 20);
		glVertex2f(50, 0);
		glEnd();

		//mid
		glBegin(GL_QUADS);
		glVertex2f(20, 40);
		glVertex2f(20, 60);
		glVertex2f(50, 60);
		glVertex2f(50, 40);
		glEnd();

		//bottom
		glBegin(GL_QUADS);
		glVertex2f(20, 80);
		glVertex2f(20, 100);
		glVertex2f(50, 100);
		glVertex2f(50, 80);
		glEnd();

		//top right
		glBegin(GL_QUADS);
		glVertex2f(40, 20);
		glVertex2f(40, 40);
		glVertex2f(60, 40);
		glVertex2f(60, 20);
		glEnd();

		//bottom right
		glBegin(GL_QUADS);
		glVertex2f(40, 60);
		glVertex2f(40, 80);
		glVertex2f(60, 80);
		glVertex2f(60, 60);
		glEnd();
	}

	void drawC() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 10);
		glVertex2f(0, 90);
		glVertex2f(20, 90);
		glVertex2f(20, 10);
		glEnd();

		//top
		glBegin(GL_QUADS);
		glVertex2f(10, 0);
		glVertex2f(10, 20);
		glVertex2f(60, 20);
		glVertex2f(60, 0);
		glEnd();

		//bottom
		glBegin(GL_QUADS);
		glVertex2f(10, 80);
		glVertex2f(10, 100);
		glVertex2f(60, 100);
		glVertex2f(60, 80);
		glEnd();
	}

	void drawD() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 20);
		glVertex2f(0, 80);
		glVertex2f(20, 80);
		glVertex2f(20, 20);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(40, 10);
		glVertex2f(40, 90);
		glVertex2f(60, 90);
		glVertex2f(60, 10);
		glEnd();

		//top
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 20);
		glVertex2f(50, 20);
		glVertex2f(50, 0);
		glEnd();

		//bottom
		glBegin(GL_QUADS);
		glVertex2f(0, 80);
		glVertex2f(0, 100);
		glVertex2f(50, 100);
		glVertex2f(50, 80);
		glEnd();
	}

	void drawE() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 100);
		glVertex2f(20, 100);
		glVertex2f(20, 0);
		glEnd();

		//top
		glBegin(GL_QUADS);
		glVertex2f(20, 0);
		glVertex2f(20, 20);
		glVertex2f(60, 20);
		glVertex2f(60, 0);
		glEnd();

		//mid
		glBegin(GL_QUADS);
		glVertex2f(20, 40);
		glVertex2f(20, 60);
		glVertex2f(50, 60);
		glVertex2f(50, 40);
		glEnd();

		//bottom
		glBegin(GL_QUADS);
		glVertex2f(20, 80);
		glVertex2f(20, 100);
		glVertex2f(60, 100);
		glVertex2f(60, 80);
		glEnd();
	}

	void drawF() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 100);
		glVertex2f(20, 100);
		glVertex2f(20, 0);
		glEnd();

		//top
		glBegin(GL_QUADS);
		glVertex2f(20, 0);
		glVertex2f(20, 20);
		glVertex2f(60, 20);
		glVertex2f(60, 0);
		glEnd();

		//mid
		glBegin(GL_QUADS);
		glVertex2f(20, 40);
		glVertex2f(20, 60);
		glVertex2f(50, 60);
		glVertex2f(50, 40);
		glEnd();
	}

	void drawG() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 10);
		glVertex2f(0, 90);
		glVertex2f(20, 90);
		glVertex2f(20, 10);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(40, 60);
		glVertex2f(40, 90);
		glVertex2f(60, 90);
		glVertex2f(60, 60);
		glEnd();

		//top
		glBegin(GL_QUADS);
		glVertex2f(10, 0);
		glVertex2f(10, 20);
		glVertex2f(60, 20);
		glVertex2f(60, 0);
		glEnd();

		//bottom
		glBegin(GL_QUADS);
		glVertex2f(10, 80);
		glVertex2f(10, 100);
		glVertex2f(50, 100);
		glVertex2f(50, 80);
		glEnd();

		//lil arm
		glBegin(GL_QUADS);
		glVertex2f(30, 45);
		glVertex2f(30, 60);
		glVertex2f(60, 60);
		glVertex2f(60, 45);
		glEnd();
	}

	void drawH() {
		//mid
		glBegin(GL_QUADS);
		glVertex2f(20, 40);
		glVertex2f(20, 60);
		glVertex2f(40, 60);
		glVertex2f(40, 40);
		glEnd();

		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 100);
		glVertex2f(20, 100);
		glVertex2f(20, 0);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(40, 0);
		glVertex2f(40, 100);
		glVertex2f(60, 100);
		glVertex2f(60, 0);
		glEnd();
	}

	void drawI() {
		//top
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(60, 0);
		glVertex2f(60, 20);
		glVertex2f(0, 20);
		glEnd();

		//bottom
		glBegin(GL_QUADS);
		glVertex2f(0, 80);
		glVertex2f(60, 80);
		glVertex2f(60, 100);
		glVertex2f(0, 100);
		glEnd();

		//mid
		glBegin(GL_QUADS);
		glVertex2f(20, 20);
		glVertex2f(20, 80);
		glVertex2f(40, 80);
		glVertex2f(40, 20);
		glEnd();
	}

	void drawJ() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 50);
		glVertex2f(0, 90);
		glVertex2f(20, 90);
		glVertex2f(20, 50);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(40, 0);
		glVertex2f(40, 90);
		glVertex2f(60, 90);
		glVertex2f(60, 0);
		glEnd();

		//bottom
		glBegin(GL_QUADS);
		glVertex2f(10, 80);
		glVertex2f(10, 100);
		glVertex2f(50, 100);
		glVertex2f(50, 80);
		glEnd();
	}

	void drawK() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 100);
		glVertex2f(20, 100);
		glVertex2f(20, 0);
		glEnd();

		//upper right
		glBegin(GL_QUADS);
		glVertex2f(40, 0);
		glVertex2f(20, 40);
		glVertex2f(20, 70);
		glVertex2f(60, 0);
		glEnd();

		//lower right
		glBegin(GL_QUADS);
		glVertex2f(40, 100);
		glVertex2f(20, 50);
		glVertex2f(30, 30);
		glVertex2f(60, 100);
		glEnd();
	}

	void drawL() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 100);
		glVertex2f(20, 100);
		glVertex2f(20, 0);
		glEnd();

		//bottom
		glBegin(GL_QUADS);
		glVertex2f(20, 80);
		glVertex2f(20, 100);
		glVertex2f(60, 100);
		glVertex2f(60, 80);
		glEnd();
	}

	void drawM() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 100);
		glVertex2f(20, 100);
		glVertex2f(20, 0);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(60, 0);
		glVertex2f(60, 100);
		glVertex2f(80, 100);
		glVertex2f(80, 0);
		glEnd();

		//left line
		glBegin(GL_QUADS);
		glVertex2f(20, 0);
		glVertex2f(20, 40);
		glVertex2f(40, 100);
		glVertex2f(40, 60);
		glEnd();

		//right line
		glBegin(GL_QUADS);
		glVertex2f(60, 0);
		glVertex2f(60, 40);
		glVertex2f(40, 100);
		glVertex2f(40, 60);
		glEnd();
	}

	void drawN() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 100);
		glVertex2f(20, 100);
		glVertex2f(20, 0);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(40, 0);
		glVertex2f(40, 100);
		glVertex2f(60, 100);
		glVertex2f(60, 0);
		glEnd();

		//line
		glBegin(GL_QUADS);
		glVertex2f(20, 0);
		glVertex2f(20, 40);
		glVertex2f(40, 100);
		glVertex2f(40, 60);
		glEnd();
	}

	void drawO() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 10);
		glVertex2f(0, 90);
		glVertex2f(20, 90);
		glVertex2f(20, 10);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(40, 10);
		glVertex2f(40, 90);
		glVertex2f(60, 90);
		glVertex2f(60, 10);
		glEnd();

		//top
		glBegin(GL_QUADS);
		glVertex2f(10, 0);
		glVertex2f(10, 20);
		glVertex2f(50, 20);
		glVertex2f(50, 0);
		glEnd();

		//bottom
		glBegin(GL_QUADS);
		glVertex2f(10, 80);
		glVertex2f(10, 100);
		glVertex2f(50, 100);
		glVertex2f(50, 80);
		glEnd();
	}

	void drawP() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 100);
		glVertex2f(20, 100);
		glVertex2f(20, 0);
		glEnd();

		//top
		glBegin(GL_QUADS);
		glVertex2f(20, 0);
		glVertex2f(20, 20);
		glVertex2f(50, 20);
		glVertex2f(50, 0);
		glEnd();

		//mid
		glBegin(GL_QUADS);
		glVertex2f(20, 40);
		glVertex2f(20, 60);
		glVertex2f(50, 60);
		glVertex2f(50, 40);
		glEnd();

		//top right
		glBegin(GL_QUADS);
		glVertex2f(40, 10);
		glVertex2f(40, 50);
		glVertex2f(60, 50);
		glVertex2f(60, 10);
		glEnd();
	}

	void drawQ() {
	}

	void drawR() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 100);
		glVertex2f(20, 100);
		glVertex2f(20, 0);
		glEnd();

		//top
		glBegin(GL_QUADS);
		glVertex2f(20, 0);
		glVertex2f(20, 20);
		glVertex2f(50, 20);
		glVertex2f(50, 0);
		glEnd();

		//mid
		glBegin(GL_QUADS);
		glVertex2f(20, 40);
		glVertex2f(20, 60);
		glVertex2f(50, 60);
		glVertex2f(50, 40);
		glEnd();

		//top right
		glBegin(GL_QUADS);
		glVertex2f(40, 10);
		glVertex2f(40, 40);
		glVertex2f(60, 40);
		glVertex2f(60, 10);
		glEnd();

		//bottom right
		glBegin(GL_QUADS);
		glVertex2f(40, 60);
		glVertex2f(40, 100);
		glVertex2f(60, 100);
		glVertex2f(60, 60);
		glEnd();
	}

	void drawS() {
		//top
		glBegin(GL_QUADS);
		glVertex2f(10, 0);
		glVertex2f(10, 20);
		glVertex2f(60, 20);
		glVertex2f(60, 0);
		glEnd();

		//mid
		glBegin(GL_QUADS);
		glVertex2f(10, 40);
		glVertex2f(10, 60);
		glVertex2f(50, 60);
		glVertex2f(50, 40);
		glEnd();

		//bottom
		glBegin(GL_QUADS);
		glVertex2f(0, 80);
		glVertex2f(0, 100);
		glVertex2f(50, 100);
		glVertex2f(50, 80);
		glEnd();

		//top left
		glBegin(GL_QUADS);
		glVertex2f(0, 10);
		glVertex2f(0, 50);
		glVertex2f(20, 50);
		glVertex2f(20, 10);
		glEnd();

		//bottom right
		glBegin(GL_QUADS);
		glVertex2f(40, 50);
		glVertex2f(40, 90);
		glVertex2f(60, 90);
		glVertex2f(60, 50);
		glEnd();
	}

	void drawT() {
		//mid
		glBegin(GL_QUADS);
		glVertex2f(20, 20);
		glVertex2f(20, 100);
		glVertex2f(40, 100);
		glVertex2f(40, 20);
		glEnd();

		//top
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 20);
		glVertex2f(60, 20);
		glVertex2f(60, 0);
		glEnd();
	}

	void drawU() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 90);
		glVertex2f(20, 90);
		glVertex2f(20, 0);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(40, 0);
		glVertex2f(40, 90);
		glVertex2f(60, 90);
		glVertex2f(60, 0);
		glEnd();

		//bottom
		glBegin(GL_QUADS);
		glVertex2f(10, 80);
		glVertex2f(10, 100);
		glVertex2f(50, 100);
		glVertex2f(50, 80);
		glEnd();
	}

	void drawV() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(18, 0);
		glVertex2f(38, 100);
		glVertex2f(20, 100);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(42, 0);
		glVertex2f(60, 0);
		glVertex2f(40, 100);
		glVertex2f(22, 100);
		glEnd();
	}

	void drawW() {
		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 80);
		glVertex2f(20, 80);
		glVertex2f(20, 0);
		glEnd();

		//mid
		glBegin(GL_QUADS);
		glVertex2f(40, 20);
		glVertex2f(40, 80);
		glVertex2f(60, 80);
		glVertex2f(60, 20);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(80, 0);
		glVertex2f(80, 80);
		glVertex2f(100, 80);
		glVertex2f(100, 0);
		glEnd();

		//bottom left
		glBegin(GL_QUADS);
		glVertex2f(10, 80);
		glVertex2f(10, 100);
		glVertex2f(45, 100);
		glVertex2f(45, 80);
		glEnd();

		//bottom right
		glBegin(GL_QUADS);
		glVertex2f(55, 80);
		glVertex2f(55, 100);
		glVertex2f(90, 100);
		glVertex2f(90, 80);
		glEnd();
	}

	void drawX() {
		//left to right down
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(20, 0);
		glVertex2f(60, 100);
		glVertex2f(40, 100);
		glEnd();

		//right to right down
		glBegin(GL_QUADS);
		glVertex2f(40, 0);
		glVertex2f(60, 0);
		glVertex2f(20, 100);
		glVertex2f(0, 100);
		glEnd();
		
	}

	void drawY() {
		//stem
		glBegin(GL_QUADS);
		glVertex2f(20, 50);
		glVertex2f(40, 50);
		glVertex2f(40, 100);
		glVertex2f(20, 100);
		glEnd();

		//left
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(18, 0);
		glVertex2f(38, 50);
		glVertex2f(20, 50);
		glEnd();

		//right
		glBegin(GL_QUADS);
		glVertex2f(42, 0);
		glVertex2f(60, 0);
		glVertex2f(40, 50);
		glVertex2f(22, 50);
		glEnd();
	}

	void drawZ() {
		//top
		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 20);
		glVertex2f(60, 20);
		glVertex2f(60, 0);
		glEnd();

		//mid
		glBegin(GL_QUADS);
		glVertex2f(0, 80);
		glVertex2f(0, 100);
		glVertex2f(60, 100);
		glVertex2f(60, 80);
		glEnd();

		//line
		glBegin(GL_QUADS);
		glVertex2f(40, 20);
		glVertex2f(0, 80);
		glVertex2f(20, 80);
		glVertex2f(60, 20);
		glEnd();
	}
};

#endif // !
