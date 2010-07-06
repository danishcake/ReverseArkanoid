#include "Wall.h"
#include <cfloat>
#include <TinyXML.h>
#include "Logger.h"

using std::vector;

Wall::Wall(void) :
	mPosition((float)INITIAL_X, (float)FIXED_Y),
	mLeftEdge(0),
	mRightEdge(0),
	mBounds((float)DEFAULT_BOUNDS_W, (float)DEFAULT_BOUNDS_H),
	mTopEdge(0),
	mBottomEdge(0)
{
}

Wall::Wall(std::string filename) :
	mPosition((float)INITIAL_X, (float)FIXED_Y),
	mLeftEdge(0),
	mRightEdge(0),
	mBounds((float)DEFAULT_BOUNDS_W, (float)DEFAULT_BOUNDS_H)
{
	TiXmlDocument doc("Levels\\" + filename);
	if(doc.LoadFile())
	{
		TiXmlElement* wall = doc.FirstChildElement("Wall");
		if(wall)
		{
			TiXmlElement* brick = wall->FirstChildElement("Brick");
			while(brick)
			{
				Vector2f brick_position;
				int brick_colour = 0;
				if(brick->QueryFloatAttribute("x", &brick_position.x) == TIXML_SUCCESS &&
				   brick->QueryFloatAttribute("y", &brick_position.y) == TIXML_SUCCESS &&
				   brick->QueryIntAttribute("c", &brick_colour) == TIXML_SUCCESS)
				{
					Brick::SharedPointer brick;
					switch(brick_colour)
					{
					default:
					case 1:
						brick = Brick::SharedPointer(new Brick(BrickType::BlueBrick));
						break;
					case 2:
						brick = Brick::SharedPointer(new Brick(BrickType::RedBrick));
						break;
					case 3:
						brick = Brick::SharedPointer(new Brick(BrickType::YellowBrick));
						break;
					}
					brick->SetPosition(brick_position);
					AddBrick(brick);
					
				} else
					Logger::DiagnosticOut() << "Brick must have x, y and c attributes\n";
				brick = brick->NextSiblingElement("Brick");
			}
		} else
		{
			Logger::ErrorOut() << "Wall root element missing from " << filename << "\n";
		}
	} else
	{
		Logger::ErrorOut() << "Unable to open " << filename << "\n";
	}
}

Wall::~Wall(void)
{
}

void Wall::AddBrick(Brick::SharedPointer brick)
{
	mBricks.push_back(brick);
	RecalculateBounds();
}

void Wall::RecalculateBounds()
{
	if(mBricks.size() > 0)
	{
		mLeftEdge = FLT_MAX;
		mRightEdge = -FLT_MAX;
		mTopEdge = -FLT_MAX;
		mBottomEdge = FLT_MAX;
	} else
	{
		mLeftEdge = 0;
		mRightEdge = 0;
		mTopEdge = 0;
		mBottomEdge = 0;
	}
	for(vector<Brick::SharedPointer>::iterator it = mBricks.begin(); it != mBricks.end(); ++it)
	{
		float left = (*it)->GetPosition().x;
		float right = (*it)->GetPosition().x + (*it)->GetSize().x;
		float bottom = (*it)->GetPosition().y;
		float top = (*it)->GetPosition().y + (*it)->GetSize().y;

		if(left < mLeftEdge)
			mLeftEdge = left;
		if(right > mRightEdge)
			mRightEdge = right;
		if(top > mTopEdge)
			mTopEdge = top;
		if(bottom < mBottomEdge)
			mBottomEdge = bottom;
	}
}

void Wall::SetX(float x)
{
	if(x > mBounds.x - mRightEdge)
		mPosition.x = mBounds.x - mRightEdge;
	else if(x < -mLeftEdge)
		mPosition.x = -mLeftEdge;
	else
		mPosition.x = x;
}

void Wall::Tick()
{
	int brick_count = mBricks.size();
	mBricks.erase(std::remove_if(mBricks.begin(), mBricks.end(), Brick::IsRemovable), mBricks.end());;
	if(brick_count != mBricks.size())
		RecalculateBounds();
}