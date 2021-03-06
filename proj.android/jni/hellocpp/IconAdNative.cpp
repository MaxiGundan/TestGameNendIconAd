//
//  IconAdNative.cpp
//
//  Created by MaxiGundan H.Ishida.
//
//  reference: http://d.hatena.ne.jp/okahiro_p/20130109/1357731806 (おかひろさんの手法)
//  reference: https://github.com/zaru/Cocos2DX_AdStir‎ (zaruさんの手法)
//

#include "IconAdNative.h"
#include "IconAdNativeJni.h"

namespace Cocos2dExt
{
	void IconAdNative::createView(float yPos)
	{
		IconAdNative_createViewJNI(yPos);
	}
	void IconAdNative::locateView(float yPos)
	{
		IconAdNative_locateViewJNI(yPos);
	}
	void IconAdNative::releaseView()
	{
		IconAdNative_releaseViewJNI();
	}

	void IconAdNative::pauseView()
	{
		IconAdNative_pauseViewJNI();
	}
	void IconAdNative::resumeView()
	{
		IconAdNative_resumeViewJNI();
	}
	void IconAdNative::refreshView()
	{
		IconAdNative_refreshViewJNI();
	}
}
