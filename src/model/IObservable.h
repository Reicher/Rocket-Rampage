#include <string>

namespace model {

class IObserver;

class IObservable
{
public:

	virtual ~IObservable(){}

	virtual void addObserver( IObserver* pObserver ) = 0;
};

}

