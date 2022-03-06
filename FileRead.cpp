#include <jni.h>     
#include <fstream>
#include "FileRead.h"
#include <cstdlib>
#include <iostream>
#include <filesystem>

#include <string>
#include <vector>

using namespace std;
std::string toString(JNIEnv* env, jstring jStr);
void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);
void tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}
std::string toString(JNIEnv* env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray)env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t)env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char*)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

JNIEXPORT jboolean JNICALL Java_FileRead_addRow
(JNIEnv *env, jobject thisObject, jstring row, jstring s1, jstring s2, jstring s3, jstring s4) {
    string name = toString(env, s1);
    string age = toString(env, s2);
    string dob = toString(env, s3);
    string city = toString(env, s4);
	string r = toString(env, row);
	fstream myfile;

    myfile.open("C:\\Users\\soory\\OneDrive\\Desktop\\data.txt", std::ios_base::app | std::ios_base::in);
    if (myfile.is_open())
    {
        myfile << r + "," + name + "," + age + "," + dob + "," + city+"\n";
        myfile.close();
    }
    else cout << "Unable to open file";
    return true;
}

/*
 * Class:     FileRead
 * Method:    removeRow
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_FileRead_removeRow
(JNIEnv* env, jobject thisObject, jstring s1) {
    const char delim = ',';
    string row = toString(env,s1);
    string line;
    string path = "C:\\Users\\soory\\OneDrive\\Desktop\\data.txt";
	char tempName[] = "C:\\Users\\soory\\OneDrive\\Desktop\\temp.txt";
	char pathName[] = "C:\\Users\\soory\\OneDrive\\Desktop\\data.txt";
    ifstream myfile(path);
    std::ofstream temp;
    string tempPath = "C:\\Users\\soory\\OneDrive\\Desktop\\temp.txt";
	
    temp.open(tempPath);
     cout << "Inside c++: check 1"<< endl;
        while (getline(myfile, line))
        {
            std::vector<std::string> out;
            tokenize(line, delim, out);
            string check = out[0];
                if (check != row) {
                    temp << line << std::endl;
                }
                 
        }
        myfile.close();
		
        temp.close();
		remove(pathName);
		
        std::filesystem::copy(tempPath, path);
		remove(tempName);
        return true;

}

/*
 * Class:     FileRead
 * Method:    updateRow
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_FileRead_updateRow
(JNIEnv* env, jobject thisObject, jstring r, jstring c, jstring d) {
    string row = toString(env, r);
    string col= toString(env, c);
    string data = toString(env, d);
    const char delim = ',';
    string line;
	char pathName[] = "C:\\Users\\soory\\OneDrive\\Desktop\\data.txt";
	char tempName[] = "C:\\Users\\soory\\OneDrive\\Desktop\\temp.txt";
    string path = "C:\\Users\\soory\\OneDrive\\Desktop\\data.txt";
    ifstream myfile(path);
    std::ofstream temp;
    string tempPath = "C:\\Users\\soory\\OneDrive\\Desktop\\temp.txt";
    temp.open(tempPath);

    int j = stoi(col);
    while (getline(myfile, line))
    {
        std::vector<std::string> out;
        tokenize(line, delim, out);
        int i = 0;

        if (out[0] == row) {
            out[j-1] = data;
            temp << out[0] + "," + out[1] + "," + out[2] + "," + out[3] << std::endl;
        }
        else {
            temp << line << std::endl;
        }


    }
    myfile.close();
    temp.close();
	remove(pathName);
    std::filesystem::copy(tempPath, path);
	remove(tempName);
    return true;

}

/*
 * Class:     FileRead
 * Method:    searchRow
 * Signature: (I)[Ljava/lang/String;
 */
JNIEXPORT jboolean JNICALL Java_FileRead_searchRow
(JNIEnv *env, jobject thisObject, jstring c, jstring d) {
	string col= toString(env, c);
	string data= toString(env, d);
	const char delim = ',';
	 string path = "C:\\Users\\soory\\OneDrive\\Desktop\\data.txt";
	 ifstream myfile(path);
	 int j = stoi(col);
	 string line;
	  while (getline(myfile, line))
    {
        std::vector<std::string> out;
        tokenize(line, delim, out);

        if (out[j-1] == data) {
            return true;
        }
        


    }
    return false;
}