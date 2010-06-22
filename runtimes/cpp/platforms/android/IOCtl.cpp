/* Copyright (C) 2010 MoSync AB

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
*/

#include "IOCtl.h"

#include <helpers/cpp_defs.h>

namespace Base
{

	int _maFrameBufferGetInfo(MAFrameBufferInfo *info)
	{	
		int size = maGetScrSize();
		int width = (size&0xffff0000) >> 16;
		int height = size&0x0000ffff;
	
		char* b = (char*)malloc(200);
		sprintf(b,"Framebuffer width: %i height: %i", width, height);
		__android_log_write(ANDROID_LOG_INFO,"JNI",b);
		free(b);
	
		info->bitsPerPixel = 24;//backBuffer->bitsPerPixel;
		info->bytesPerPixel = 4;//backBuffer->bytesPerPixel;
		info->redMask = 0x00ff0000; //backBuffer->redMask;
		info->greenMask = 0x0000ff00;// backBuffer->greenMask;
		info->blueMask = 0x0000000ff; //backBuffer->blueMask;
		info->sizeInBytes = width * height * 4; //backBuffer->pitch*backBuffer->height;
		info->width = width; //backBuffer->width;
		info->height = height; // backBuffer->height;
		info->pitch = width*4; //backBuffer->pitch;
		info->redShift = 16; //backBuffer->redShift;
		info->greenShift = 9; //backBuffer->greenShift;
		info->blueShift = 0; //backBuffer->blueShift;
		info->redBits = 8;// backBuffer->redBits;
		info->greenBits = 8;// backBuffer->greenBits;
		info->blueBits = 8; //backBuffer->blueBits;
		info->supportsGfxSyscalls = 0;

		return 1;
	}

	int _maFrameBufferInit(void *data, int memStart, JNIEnv* jNIEnv, jobject jThis)
	{
	/*
		if(sInternalBackBuffer!=NULL) return 0;
		sInternalBackBuffer = backBuffer;
		backBuffer = new Image((unsigned char*)data, NULL, backBuffer->width, backBuffer->height, backBuffer->pitch, backBuffer->pixelFormat, false, false);
		currentDrawSurface = backBuffer;
		return 1;
	*/
	
		int rdata = (int)data - memStart;
	
		char* b = (char*)malloc(200);
		sprintf(b,"Framebuffer data: %i", rdata);
		__android_log_write(ANDROID_LOG_INFO,"JNI",b);
		free(b);
	
		jclass cls = jNIEnv->GetObjectClass(jThis);
		jmethodID methodID = jNIEnv->GetMethodID(cls, "_enableFramebuffer", "(I)V");
		if (methodID == 0) return 0;
		jNIEnv->CallVoidMethod(jThis, methodID, rdata);
		
		jNIEnv->DeleteLocalRef(cls);
	
		return 1;
	}

	int _maFrameBufferClose(JNIEnv* jNIEnv, jobject jThis)
	{
	/*
		if(sInternalBackBuffer==NULL) return 0;
		delete backBuffer;
		backBuffer = sInternalBackBuffer;
		sInternalBackBuffer = NULL;
		currentDrawSurface = backBuffer;
		return 1;
	*/
		jclass cls = jNIEnv->GetObjectClass(jThis);
		jmethodID methodID = jNIEnv->GetMethodID(cls, "_disableFramebuffer", "()V");
		if (methodID == 0) return 0;
		jNIEnv->CallVoidMethod(jThis, methodID);
		
		jNIEnv->DeleteLocalRef(cls);
		
		return 1;
	}
	
	
}