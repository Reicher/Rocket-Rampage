#include "ScoreDrawable.h"
#include "../../Content.h"
#include "../../model/actors/ScoreActor.h"
#include "SFML/Graphics/Text.hpp"

namespace view {

class ScoreDrawable::Impl
{
public:

	Impl( ::model::ScoreActor* pScoreActor, Content* pContent )
	: m_pScoreActor( pScoreActor )
	, m_apScoreText( new sf::Text( "123", pContent->m_standardFont, 30 ) )
	{
		m_apScoreText->setColor(sf::Color::White);
	}

	void draw( sf::RenderTarget& target, sf::RenderStates states ) const
	{
		m_apScoreText->setPosition( m_pScoreActor->getPosition().x, m_pScoreActor->getPosition().y );
		target.draw(*m_apScoreText, states);
	}

private:

	::model::ScoreActor* m_pScoreActor;

	::std::auto_ptr<sf::Text> m_apScoreText;

};

ScoreDrawable::ScoreDrawable( ::model::ScoreActor* pScoreActor, Content* pContent )
: m_apImpl( new Impl( pScoreActor, pContent ) )
{
}

ScoreDrawable::~ScoreDrawable()
{
}

void ScoreDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	m_apImpl->draw( target, states );
}

}
