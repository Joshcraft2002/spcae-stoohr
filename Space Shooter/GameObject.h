#ifndef GameObject_h
#define GameObject_h

class GameObject {
public:
    Vector2D position;
    double rotation = 0.0f;
    float scale = 1.0f;

    virtual void Update() {

    }

    virtual void DrawObject() {

    }
};

//note: "virtual" here to deal with multiple inheritance

//adds vectors, speed, and movement
class Movable : virtual public GameObject {
protected:    
    Vector2D movementVector;
    float speed = 0;   
    
public: 
    //waypoints for moveTo
    class WayPoint 
    {
    private:
        vector<Vector2D*> waypoints;
        int currentWayPointIndex = 0;
    public:
        //safely clear waypoints vector
        ~WayPoint() 
        { 
            for (int i = 0; i < waypoints.size(); i++)
                delete(waypoints.at(i));
            waypoints.clear();
        }

        void addWayPoint(float x, float y) 
        {
            waypoints.push_back(new Vector2D(x, y));
        }

        //go to next waypoint, or go back to start
        void setNextWayPoint() 
        {
            if (currentWayPointIndex + 1 < waypoints.size())
                currentWayPointIndex++;
            else
                currentWayPointIndex = 0;
        }

        Vector2D* getCurrentWayPoint() 
        {
            return waypoints.at(currentWayPointIndex);
        }
    };

    void setSpeed(float speed) 
    {
        this->speed = speed;
    }

    //set vector to target coordinates
    void setMovementVectorTo(float _x, float _y) {
        movementVector.setValues(_x - position.x, _y - position.y);
        movementVector.normalize();
    }

    //just move
    void move() 
    {
        position.x += movementVector.x * speed * deltaTime;
        position.y += movementVector.y * speed * deltaTime;
    } 

    //move to specific location
    void moveTo(float x, float y) 
    {
        if (!position.matches(x, y)) //only run if not at position
        {
            setMovementVectorTo(x, y);

            if (position.x != x)
            {
                //check distance to target
                float nextMoveX = movementVector.x * speed * deltaTime;

                //set position if close enough
                if (abs(x - position.x) <= abs(nextMoveX))
                {
                    position.x = x;
                }
                else //else, just move
                {
                    position.x += nextMoveX;
                }
            }

            if (position.y != y)
            {
                //check distance to target
                float nextMoveY = movementVector.y * speed * deltaTime;

                //set position if close enough
                if (abs(y - position.y) <= abs(nextMoveY))
                {
                    position.y = y;
                }
                else //else, just move
                {
                    position.y += nextMoveY;
                }
            }
            
            /*//check distance to target
            float nextMoveX = movementVector.x * speed * deltaTime;
            float nextMoveY = movementVector.y * speed * deltaTime;

            //set position if close enough
            if (abs(x - position.x) <= abs(nextMoveX) && abs(y - position.y) <= abs(nextMoveY))
            {
                position.setValues(x, y);
            }                
            else //else, just move
            { 
                position.setValues(position.x + nextMoveX, position.y + nextMoveY);
            }*/
        }
    }

    //move to, but with Vector2D parameters
    void moveTo(Vector2D* targetPos) 
    {
        moveTo(targetPos->x, targetPos->y);
    }   

    //move thru waypoints based on given waypoint set
    void moveInWayPoints(WayPoint* waypointSet) 
    {
        Vector2D* currentWayPoint = waypointSet->getCurrentWayPoint();
        if (position.matches(currentWayPoint))
        {
            waypointSet->setNextWayPoint();            
        }           
        moveTo(currentWayPoint);
    }

    /*//move to, but to built-in moveTo coordinates
    void moveTo() {
        moveTo(moveToCoords.x, moveToCoords.y);
    }

    //set moveTo coordinates
    void setMoveTo(float x, float y) {
        moveToCoords.setValues(x, y);
    }*/
};

//for them game objects with hitboxes
class HasHitbox : virtual public GameObject {
protected:
    float hitboxRadius;
public:
    HasHitbox(float hitboxRadius) 
    {
        this->hitboxRadius = hitboxRadius;
    }

    bool checkCollision(GameObject* collision) 
    {
        Vector2D distance(collision->position.x - position.x, collision->position.y - position.y);
        return (distance.getSquaredMagnitude() < hitboxRadius* hitboxRadius) ? true : false;
    }
};

#endif