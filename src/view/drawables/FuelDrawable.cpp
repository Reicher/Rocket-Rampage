#include "FuelDrawable.h"
#include "../../model/IActor.h"

namespace view {

class FuelDrawable::Impl
{
public:
	Impl( ::model::IActor* pActor,
		  Content*         pContent )
	: m_pContent( pContent )
	, m_pActor( pActor )
	, m_apSprite( )
	{
		m_apSprite.reset( new ::sf::Sprite( pContent->m_fuelTex ) );
	}

	void draw( ::sf::RenderTarget& target, ::sf::RenderStates states ) const
	{
		m_apSprite->setPosition( m_pActor->getX(), m_pActor->getY() );

		target.draw( *m_apSprite, states );
	}

private:

	Content* m_pContent;

	::model::IActor* m_pActor;

	::std::auto_ptr< ::sf::Sprite > m_apSprite;
};

FuelDrawable::FuelDrawable( ::model::IActor* pActor, Content* pContent )
: m_apImpl( new Impl( pActor, pContent ) )
{
}

FuelDrawable::~FuelDrawable()
{
}

void FuelDrawable::draw(::sf::RenderTarget& target, ::sf::RenderStates states) const
{
	m_apImpl->draw( target, states );
}

}

