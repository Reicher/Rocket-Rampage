#include <memory>
#include "IObservable.h"

//! Model for the game
class Model : public IObservable
{
public:
	Model();

	~Model();

	//! Starts the model
	void start();

	//! Updates the model
	void update();

	void addObserver( IObserver* pObserver );

private:

	class Impl;

	std::auto_ptr<Impl> m_apImpl;

};
