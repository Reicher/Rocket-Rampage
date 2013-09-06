#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Content;

namespace model {
class ScoreActor;
}

namespace view {

class ScoreDrawable : public sf::Drawable
{
public:

	ScoreDrawable( ::model::ScoreActor* pScoreActor, Content* pContent );

	~ScoreDrawable();

	void draw( ::sf::RenderTarget& target, ::sf::RenderStates states ) const;

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;

};

}
