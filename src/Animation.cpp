#include "Animation.h"
#include "AnimationPrivate.h"
#include "AbstractAnimator.h"
#include "SideSlide/SideSlideAnimator.h"

using WAF::Animation;
using WAF::AnimationPrivate;
using WAF::AbstractAnimator;
using WAF::SideSlideAnimator;


void Animation::sideSlideIn(QWidget* _widget, WAF::ApplicationSide _side, bool _blockingMode)
{
	const bool IN = true;
	sideSlide(_widget, _side, IN, _blockingMode);
}

void Animation::sideSlideOut(QWidget* _widget, WAF::ApplicationSide _side, bool _blockingMode)
{
	const bool OUT = false;
	sideSlide(_widget, _side, OUT, _blockingMode);
}

void Animation::sideSlide(QWidget* _widget, WAF::ApplicationSide _side, bool _in, bool _blockingMode)
{
	AbstractAnimator* animator = 0;
	if (pimpl()->hasSideSlideAnimator(_widget)) {
		animator = pimpl()->sideSlideAnimator(_widget);
	} else {
		SideSlideAnimator* sideSlideAnimator = new SideSlideAnimator(_widget);
		sideSlideAnimator->setApplicationSide(_side);
		animator = sideSlideAnimator;

		pimpl()->saveSideSlideAnimator(_widget, animator);
	}

	if (_in) {
		animator->animateForward(_blockingMode);
	} else {
		animator->animateBackward(_blockingMode);
	}
}

AnimationPrivate* Animation::m_pimpl = 0;
AnimationPrivate* Animation::pimpl()
{
	if (m_pimpl == 0) {
		m_pimpl = new AnimationPrivate;
	}

	return m_pimpl;
}
