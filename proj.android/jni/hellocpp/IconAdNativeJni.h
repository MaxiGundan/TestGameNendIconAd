//
//  IconAdNativeJni.h
//
//  Created by MaxiGundan H.Ishida.
//
//

#ifndef __IconAdNativeJni_H__
#define __IconAdNativeJni_H__

#include <jni.h>

extern "C"
{
	extern void IconAdNative_createViewJNI(float yPos);
	extern void IconAdNative_locateViewJNI(float yPos);
	extern void IconAdNative_releaseViewJNI();

	extern void IconAdNative_pauseViewJNI();
	extern void IconAdNative_resumeViewJNI();
	extern void IconAdNative_refreshViewJNI();
}

#endif //__IconAdNativeJni_H__

