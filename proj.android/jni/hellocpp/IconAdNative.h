//
//  IconAdNative.h
//
//  Created by MaxiGundan H.Ishida.
//
//

#ifndef __IconAdNative_H__
#define __IconAdNative_H__

#include <stddef.h>

#define ICNAD_POS_INVALID (-1000)

namespace Cocos2dExt {
	class IconAdNative
	{
	public:
		static void createView(float yPos);
		static void locateView(float yPos);
		static void releaseView();

		static void pauseView();
		static void resumeView();
		static void refreshView();
	};
}


#endif //__IconAdNative_H__
