//
//  IconAdNativeJni.cpp
//
//  Created by MaxiGundan H.Ishida.
//
//  reference: https://github.com/zaru/Cocos2DX_AdStir‎ (zaruさんの手法)
//

#include "IconAdNativeJni.h"
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"

#define  LOG_TAG    "TestIconAd"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  ADMANAGER_CLASS  "com/MyCompany/NativeIF/IconAdMgr"

typedef struct JniMethodInfo_
{
    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
} JniMethodInfo;

extern "C"
{
//-----> Jni Helper Functions

	// get env and cache it
	static JNIEnv* getJNIEnv(void)
	{
		JNIEnv *env = 0;
        
		// get jni environment
		if (cocos2d::JniHelper::getJavaVM()->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
		{
			LOGD("Failed to get the environment using GetEnv()");
		}
        
		if (cocos2d::JniHelper::getJavaVM()->AttachCurrentThread(&env, 0) < 0)
		{
			LOGD("Failed to get the environment using AttachCurrentThread()");
		}
        
		return env;
	}
    
	// get class and make it a global reference, release it at endJni().
	static jclass getClassID(JNIEnv *pEnv, const char *className)
	{
		jclass ret = pEnv->FindClass(className);
		if (! ret)
		{
			LOGD("Failed to find class of %s", className);
		}
        
		return ret;
	}
    
	static bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
    {
		jmethodID methodID = 0;
		JNIEnv *pEnv = 0;
		bool bRet = false;
        
        do
        {
			pEnv = getJNIEnv();
			if (! pEnv)
			{
				break;
			}
            
            jclass classID = getClassID(pEnv, className);
            
            methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
                LOGD("Failed to find static method id of %s", methodName);
                break;
            }
            
			methodinfo.classID = classID;
			methodinfo.env = pEnv;
			methodinfo.methodID = methodID;
            
			bRet = true;
        } while (0);
        
        return bRet;
    }

//<----- Jni Helper Functions


//------- ここから自前のJNI関数 -------
	void IconAdNative_createViewJNI(float yPos)
	{
		JniMethodInfo methodInfo;

		if (!getStaticMethodInfo(methodInfo, ADMANAGER_CLASS, "createView", "(F)V"))
		{
			return;
		}

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (jfloat)yPos);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}
	void IconAdNative_locateViewJNI(float yPos)
	{
		JniMethodInfo methodInfo;

		if (!getStaticMethodInfo(methodInfo, ADMANAGER_CLASS, "locateView", "(F)V"))
		{
			return;
		}

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, (jfloat)yPos);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}
	void IconAdNative_releaseViewJNI()
	{
		JniMethodInfo methodInfo;

		if (!getStaticMethodInfo(methodInfo, ADMANAGER_CLASS, "releaseView", "()V"))
		{
			return;
		}

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}

	void IconAdNative_pauseViewJNI()
	{
		JniMethodInfo methodInfo;

		if (!getStaticMethodInfo(methodInfo, ADMANAGER_CLASS, "pauseView", "()V"))
		{
			return;
		}

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}
	void IconAdNative_resumeViewJNI()
	{
		JniMethodInfo methodInfo;

		if (!getStaticMethodInfo(methodInfo, ADMANAGER_CLASS, "resumeView", "()V"))
		{
			return;
		}

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}
	void IconAdNative_refreshViewJNI()
	{
		JniMethodInfo methodInfo;

		if (!getStaticMethodInfo(methodInfo, ADMANAGER_CLASS, "refreshView", "()V"))
		{
			return;
		}

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}


}
