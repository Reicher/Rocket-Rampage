//! Interface for all actors in the model.
class IActor
{
public:

	virtual ~IActor(){}

	virtual long getId() = 0;

	virtual double getX() = 0;

	virtual double getX() = 0;

	virtual double getRotation() = 0;
};
