#include <memory>

//! Model for the game
class Model
{
public:
	Model();

	~Model();

	//! Starts the model
	void start();

	//! Updates the model
	void update();

private:

	class Impl;

	std::auto_ptr<Impl> m_apImpl;

};
