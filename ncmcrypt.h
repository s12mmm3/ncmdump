#pragma once

#include "aes.h"
#include "cJSON.h"

#include <iostream>
#include <fstream>

#include <filesystem>

class NeteaseMusicMetadata {

private:
	std::string mAlbum;
	std::string mArtist;
	std::string mFormat;
	std::string mName;
	int mDuration;
	int mBitrate;

private:
	cJSON* mRaw;

public:
	NeteaseMusicMetadata(cJSON*);
	~NeteaseMusicMetadata();
    const std::string& name() const { return mName; }
    const std::string& album() const { return mAlbum; }
    const std::string& artist() const { return mArtist; }
    const std::string& format() const { return mFormat; }
    const int duration() const { return mDuration; }
    const int bitrate() const { return mBitrate; }

};

class NeteaseCrypt {

private:
	static const unsigned char sCoreKey[17];
	static const unsigned char sModifyKey[17];
	static const unsigned char mPng[8];
	enum NcmFormat { MP3, FLAC };

private:
	std::filesystem::path mFilepath;
	std::filesystem::path mDumpFilepath;
	NcmFormat mFormat;
	std::string mImageData;
	std::ifstream mFile;
	unsigned char mKeyBox[256];
	NeteaseMusicMetadata* mMetaData;

private:
	bool isNcmFile();
    bool openFile(std::filesystem::path const);
	int read(char *s, std::streamsize n);
	void buildKeyBox(unsigned char *key, int keyLen);
    std::string mimeType(std::string data);

public:
    const std::filesystem::path filepath() const { return mFilepath; }
    const std::filesystem::path dumpFilepath() const { return mDumpFilepath; }

public:
    NeteaseCrypt(std::filesystem::path);
	~NeteaseCrypt();

public:
	void Dump();
	void FixMetadata();
};
