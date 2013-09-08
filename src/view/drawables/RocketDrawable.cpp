#include "RocketDrawable.h"
#include "../../model/IActor.h"
#include "../../model/actors/RocketActor.h"
#include "../../Content.h"

namespace view {

class RocketDrawable::Impl
{
public:
	Impl( ::model::RocketActor* pActor,
		  Content*         pContent,
		  ::sf::View* 		pView)
	: m_pContent( pContent )
	, m_pActor( pActor )
	, m_apSprite( )
	, m_pView( pView )
	{
		m_apSprite.reset( new ::sf::Sprite( pContent->m_rocketTex ) );

		Vector2 middle;
		middle.x =  m_apSprite->getGlobalBounds().width / 2.0;
		middle.y =  m_apSprite->getGlobalBounds().height / 2.0;

		m_apSprite->setOrigin(middle.x, middle.y);
		m_apSprite->setPosition(m_pActor->getX(), m_pActor->getY());

	}

	void draw( ::sf::RenderTarget& target, ::sf::RenderStates states ) const
	{
		target.draw( *m_apSprite, states );
		m_pView->setCenter(m_pActor->getX(), m_pActor->getY());
	}

private:

	Content* m_pContent;

	::model::RocketActor* m_pActor;

	::std::auto_ptr< ::sf::Sprite > m_apSprite;

	::sf::View* m_pView;

};

RocketDrawable::RocketDrawable( ::model::RocketActor* pActor, Content* pContent, ::sf::View* pView)
: m_apImpl( new Impl( pActor, pContent, pView ) )
{
}

RocketDrawable::~RocketDrawable()
{
}

void RocketDrawable::draw(::sf::RenderTarget& target, ::sf::RenderStates states) const
{
	m_apImpl->draw( target, states );
}

}

