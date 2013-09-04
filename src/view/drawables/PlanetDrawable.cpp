#include "PlanetDrawable.h"
#include "../../model/IActor.h"
#include "../../model/actors/PlanetActor.h"

namespace view {

class PlanetDrawable::Impl
{
public:
	Impl( ::model::IActor* pActor,
		  Content*         pContent )
	: m_pContent( pContent )
	, m_pActor( pActor )
	, m_apSprite( )
	, m_atmosphere ()
	{
		m_apSprite.reset( new ::sf::Sprite( pContent->m_planetTex ) );

		sf::Vector2f scale;
		double size = m_pActor->getSize();

		scale.x = size / ( m_apSprite->getGlobalBounds().width / 2.0);
		scale.y = size  / ( m_apSprite->getGlobalBounds().height / 2.0);

		m_apSprite->setScale( scale );
		m_apSprite->setOrigin(0, 0);
		m_apSprite->setPosition(-m_pActor->getSize(), -m_pActor->getSize());

		//float thickness = static_cast<model::PlanetActor*>(m_pActor->getAtmosphereThickness());
		float thickness = 150; // For now

		m_atmosphere.setRadius(size + thickness);
		m_atmosphere.setOrigin(size + thickness, size + thickness);
		m_atmosphere.setFillColor(sf::Color(100, 100, 200));
		m_atmosphere.setPointCount(static_cast<int>(size) / 5);
	}

	void draw( ::sf::RenderTarget& target, ::sf::RenderStates states ) const
	{
		target.draw( m_atmosphere, states );
		target.draw( *m_apSprite, states );
	}

private:

	Content* m_pContent;

	::model::IActor* m_pActor;

	::std::auto_ptr< ::sf::Sprite > m_apSprite;

	sf::CircleShape m_atmosphere;
};

PlanetDrawable::PlanetDrawable( ::model::IActor* pActor, Content* pContent )
: m_apImpl( new Impl( pActor, pContent ) )
{
}

PlanetDrawable::~PlanetDrawable()
{
}

void PlanetDrawable::draw(::sf::RenderTarget& target, ::sf::RenderStates states) const
{
	m_apImpl->draw( target, states );
}

}

