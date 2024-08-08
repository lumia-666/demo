#include "pch.h"
#include "NativeTest.h"
#include <string>

jstring str2jstring(JNIEnv* env, const char* pat)
{
	//����java String�� strClass
	jclass strClass = (env)->FindClass("Ljava/lang/String;");
	//��ȡString(byte[],String)�Ĺ�����,���ڽ�����byte[]����ת��Ϊһ����String
	jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	//����byte����
	jbyteArray bytes = (env)->NewByteArray(strlen(pat));
	//��char* ת��Ϊbyte����
	(env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
	// ����String, ������������,����byte����ת����Stringʱ�Ĳ���
	jstring encoding = (env)->NewStringUTF("GB2312");
	//��byte����ת��Ϊjava String,�����
	return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
}


std::string jstring2str(JNIEnv* env, jstring jstr)
{
	char*   rtn = NULL;
	jclass   clsstring = env->FindClass("java/lang/String");
	jstring   strencode = env->NewStringUTF("GB2312");
	jmethodID   mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray   barr = (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize   alen = env->GetArrayLength(barr);
	jbyte*   ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0)
	{
		rtn = (char*)malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	std::string stemp(rtn);
	free(rtn);
	return   stemp;
}

JNIEXPORT jstring JNICALL Java_NativeTest_hello(JNIEnv * env, jobject obj, jstring jStr)
{
	auto str = jstring2str(env, jStr);
	str += "is handsome";
	return str2jstring(env, str.c_str());
}
