#include <string>

class IObserver;

class IObservable
{
public:
	virtual ~IObservable(){}

	virtual void addObserver( IObserver* pObserver );
};
