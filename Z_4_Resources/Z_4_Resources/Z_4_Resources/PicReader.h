/******************************************************************
* ！注意！                                                         *
* 本头文件中为你封装了WinAPI中WIC底层函数，方便你进行图片读取而不必引  *
* 入或安装其他的外部库，但是我们有一定的约束条件，请你仔细阅读以下规定  *
*     本头文件中任何没有TO-DO的地方请你不要修改，若函数存在问题，      *
* 请及时联系老师或助教！                                            *
*     每一个TO-DO块以TO-DO：说明 (TO-DO) END 结束，具体可看下方代码  *
*     readPic()函数为你封装了WinAPI中的方法，可以将图片读取为RGBA的   *
* bitmap数据，但这并不代表你可以通过修改这个函数直接达到读取灰度图的   *
* 目的。                                                           *
*     getData()是你最终需要完善的函数，将读取出来的一维BYTE数组转换   *
* 成你实现的Array类。                                              *
*     testReader()是demo中提供读取数据的其中一个思路。               *
******************************************************************/
#ifndef PIC_READER_H
#define PIC_READER_H

#include <windows.h>
#include <wincodec.h>
#include <commdlg.h>
#include <vector>
#include <string>
#include "Array.h"

template <typename T>
inline void SafeRelease(T*& p) {
	if (nullptr != p) {
		p->Release();
		p = nullptr;
	}
}

class PicReader {
public:
	PicReader();
	~PicReader();

	bool readPic(LPCSTR fileName);
	bool readPic(const std::string& fileName);

	Array getData(bool asGrayScale = false);
	Array getData(int x, int y, int width, int height, bool asGrayScale = false);

	void testReader(BYTE*&, UINT&, UINT&);

	UINT getWidth() const { return imageWidth; }
	UINT getHeight() const { return imageHeight; }
	bool isLoaded() const { return m_pConvertedSourceBitmap != nullptr; }

private:
	void init();
	bool checkHR(HRESULT);
	void quitWithError(LPCSTR);
	bool copyBitmapData(BYTE*& data, UINT& x, UINT& y);

	HWND                    hWnd;
	HANDLE                  hFile;
	IWICImagingFactory* m_pIWICFactory;
	IWICFormatConverter* m_pConvertedSourceBitmap;
	UINT                   imageWidth;
	UINT                   imageHeight;

	/*TO-DO：这里可能会增加你需要的内部成员 END*/
};

PicReader::PicReader() : m_pConvertedSourceBitmap(nullptr), m_pIWICFactory(nullptr),
imageWidth(0), imageHeight(0), hFile(NULL) {
	init();
}

PicReader::~PicReader() {
	if (hFile != NULL && hFile != INVALID_HANDLE_VALUE)
		CloseHandle(hFile);
	SafeRelease(m_pConvertedSourceBitmap);
	SafeRelease(m_pIWICFactory);
	CoUninitialize();
}

bool PicReader::checkHR(HRESULT hr) {
	return FAILED(hr);
}

void PicReader::quitWithError(LPCSTR message) {
	MessageBoxA(hWnd, message, "Application Error", MB_ICONEXCLAMATION | MB_OK);
	quick_exit(0xffffffff);
}

void PicReader::init() {
	hWnd = GetForegroundWindow();

	HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

	HRESULT hr = S_OK;

	hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_pIWICFactory)
	);

	if (checkHR(hr)) { quitWithError("Init Reader Failed"); }
}

bool PicReader::readPic(LPCSTR fileName) {
	HRESULT hr = S_OK;

	SafeRelease(m_pConvertedSourceBitmap);
	imageWidth = 0;
	imageHeight = 0;

	if (hFile != NULL && hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		hFile = NULL;
	}

	hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		if (error == ERROR_FILE_NOT_FOUND) {
			quitWithError("Cannot find such file, please retry or check the access");
		}
		else {
			char errorMsg[256];
			sprintf_s(errorMsg, "Cannot open file. Error code: %lu", error);
			quitWithError(errorMsg);
		}
		return false;
	}

	IWICBitmapDecoder* pDecoder = nullptr;
	hr = m_pIWICFactory->CreateDecoderFromFileHandle((ULONG_PTR)hFile, nullptr, WICDecodeMetadataCacheOnDemand, &pDecoder);
	if (checkHR(hr)) {
		CloseHandle(hFile);
		hFile = NULL;
		quitWithError("Create Decoder Failed");
		return false;
	}

	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (checkHR(hr)) {
		SafeRelease(pDecoder);
		CloseHandle(hFile);
		hFile = NULL;
		quitWithError("Get Frame Failed");
		return false;
	}

	hr = m_pIWICFactory->CreateFormatConverter(&m_pConvertedSourceBitmap);
	if (checkHR(hr)) {
		SafeRelease(pFrame);
		SafeRelease(pDecoder);
		CloseHandle(hFile);
		hFile = NULL;
		quitWithError("Get Format Converter Failed");
		return false;
	}

	hr = m_pConvertedSourceBitmap->Initialize(pFrame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);
	if (checkHR(hr)) {
		SafeRelease(m_pConvertedSourceBitmap);
		SafeRelease(pFrame);
		SafeRelease(pDecoder);
		CloseHandle(hFile);
		hFile = NULL;
		quitWithError("Init Bitmap Failed");
		return false;
	}

	hr = m_pConvertedSourceBitmap->GetSize(&imageWidth, &imageHeight);
	if (checkHR(hr)) {
		SafeRelease(m_pConvertedSourceBitmap);
		SafeRelease(pFrame);
		SafeRelease(pDecoder);
		CloseHandle(hFile);
		hFile = NULL;
		quitWithError("Get Image Size Failed");
		return false;
	}

	SafeRelease(pDecoder);
	SafeRelease(pFrame);

	return true;
}

bool PicReader::readPic(const std::string& fileName) {
	return readPic(fileName.c_str());
}

bool PicReader::copyBitmapData(BYTE*& data, UINT& x, UINT& y) {
	if (!m_pConvertedSourceBitmap) {
		return false;
	}

	HRESULT hr = S_OK;

	hr = m_pConvertedSourceBitmap->GetSize(&x, &y);
	if (checkHR(hr)) {
		quitWithError("Check Bitmap Size Failed");
		return false;
	}

	data = new BYTE[x * y * 4];
	memset(data, 0, x * y * 4);

	UINT stride = x * 4;
	hr = m_pConvertedSourceBitmap->CopyPixels(nullptr, stride, x * y * 4, data);
	if (checkHR(hr)) {
		delete[] data;
		data = nullptr;
		quitWithError("Copy Pixels Failed");
		return false;
	}

	return true;
}

Array PicReader::getData(bool asGrayScale) {
	if (!m_pConvertedSourceBitmap) {
		throw std::runtime_error("No image loaded. Call readPic() first.");
	}

	BYTE* data = nullptr;
	UINT x = 0, y = 0;

	if (!copyBitmapData(data, x, y)) {
		throw std::runtime_error("Failed to copy bitmap data");
	}

	/******************************************************************
	*  TO-DO:                                                         *
	*                                                                 *
	*  实现一个Array类，并将上面的data转存至你的Array内                  *
	*                                                                 *
	*  数据说明：从Bitmap Copy出来的数据，每4个为一组代表一个像素         *
	*           数据为一个长度为图像的(长*宽*4)的一维数组                *
	*           即数据排布为 R G B A R G B A R G B A.....              *
	*                                                                 *
	*  ！注意！  你仅可以只改动从此开始到下一个TO-DO END位置的代码！       *
	******************************************************************/

	// 1. 创建Array对象，大小为x*y*4
	Array result(x, y, 4);

	// 2. 将BYTE数据复制到Array中
	for (UINT i = 0; i < y; i++) {
		for (UINT j = 0; j < x; j++) {
			UINT dataIndex = (i * x + j) * 4;
			for (int k = 0; k < 4; k++) {
				result.at(j, i, k) = static_cast<int>(data[dataIndex + k]);
			}
		}
	}

	// 3. 如果需要灰度图，转换为单通道
	if (asGrayScale) {
		Array grayResult(x, y, 1);
		for (UINT i = 0; i < y; i++) {
			for (UINT j = 0; j < x; j++) {
				int r = result.at(j, i, 0);
				int g = result.at(j, i, 1);
				int b = result.at(j, i, 2);
				// 使用标准灰度转换公式
				int gray = (r * 299 + g * 587 + b * 114 + 500) / 1000;
				grayResult.at2D(j, i) = gray;
			}
		}
		delete[] data;
		return grayResult;
	}

	// 4. 删除临时数据
	delete[] data;

	/******************************************************************
	*  TO-DO END                                                      *
	******************************************************************/

	if (hFile != NULL && hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		hFile = NULL;
	}

	return result;
}

Array PicReader::getData(int startX, int startY, int width, int height, bool asGrayScale) {
	if (!m_pConvertedSourceBitmap) {
		throw std::runtime_error("No image loaded. Call readPic() first.");
	}

	if (startX < 0 || startY < 0 || width <= 0 || height <= 0 ||
		startX + width >(int)imageWidth || startY + height >(int)imageHeight) {
		throw std::out_of_range("Invalid subimage coordinates");
	}

	Array fullImage = getData(asGrayScale);

	if (asGrayScale) {
		Array subImage(width, height, 1);
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				subImage.at2D(x, y) = fullImage.at2D(startX + x, startY + y);
			}
		}
		return subImage;
	}
	else {
		Array subImage(width, height, 4);
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				for (int c = 0; c < 4; c++) {
					subImage.at(x, y, c) = fullImage.at(startX + x, startY + y, c);
				}
			}
		}
		return subImage;
	}
}

void PicReader::testReader(BYTE*& _out, UINT& _x, UINT& _y) {
	if (!m_pConvertedSourceBitmap) {
		throw std::runtime_error("No image loaded. Call readPic() first.");
	}

	if (!copyBitmapData(_out, _x, _y)) {
		throw std::runtime_error("Failed to copy bitmap data");
	}

	if (hFile != NULL && hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		hFile = NULL;
	}
}

#endif