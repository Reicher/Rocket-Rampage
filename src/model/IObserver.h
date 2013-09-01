#include <string>

class IObserver
{
public:
	virtual ~IObserver(){}

	virtual void notify( std::string what );
};
