namespace model {

class IManager
{
public:
	virtual ~IManager(){};
	virtual void update(double dt) = 0;
};

}// namepsace model
