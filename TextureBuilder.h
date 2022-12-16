#include <stdio.h>
#include "glew.h"
#include "glaux.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glaux.lib")

void loadPPM(GLuint *textureID, char *strFileName, int width, int height, int wrap) {
	BYTE *data;
	FILE *pFile;

	fopen_s(&pFile, strFileName, "r");
	if (pFile) {
		data = (BYTE*)malloc(width * height * 3);
		fread(data, 1, width * height * 3, pFile);
		fclose(pFile);
	} else {
		MessageBoxA(NULL, "Texture file not found!", "Error!", MB_OK);
		exit(EXIT_FAILURE);
	}

	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	free(data);
}

void loadBMP(GLuint *textureID, char *strFileName, int wrap) {
	AUX_RGBImageRec *pBitmap = NULL;
	FILE *pFile = NULL;

	fopen_s(&pFile, strFileName, "r");
	if (pFile) {
		pBitmap = auxDIBImageLoadA(strFileName);
	}
	else {
		MessageBoxA(NULL, "Texture file not found!", "Error!", MB_OK);
		exit(EXIT_FAILURE);
	}

	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitmap->sizeX, pBitmap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitmap->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP);

	if (pBitmap) {
		if (pBitmap->data) {
			free(pBitmap->data);
		}
		free(pBitmap);
	}
}