#include "IActorFwd.h"
#include <string>

namespace model {

class IObserver
{
public:

	virtual ~IObserver(){}

	virtual void notify( std::string what, IActor* pActor ) = 0;
};

}

