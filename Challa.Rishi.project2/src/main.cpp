#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <stdlib.h> 
#include <bitset>
#include <cstdio>
#include <sys/stat.h>
using namespace std;


typedef struct
{
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;
} Header;

typedef struct
{
	unsigned char r, g, b;
	//vector<unsigned char> pix;
} PIXEL;

//void readFile(string filename, Header &headerObj);
//prototypes
void MergeBytes(PIXEL *, unsigned char *, int);
PIXEL * multiply(PIXEL *top, PIXEL *bottom);
PIXEL * subtraction(PIXEL *top, PIXEL *bottom);
PIXEL * screen(PIXEL *top, PIXEL *bottom);
PIXEL * overlay(PIXEL *top, PIXEL *bottom);
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();
void test11();
PIXEL * check(string filename);
void writeFiles(string filename, Header &headerObj, FILE *fptr, PIXEL *pixels, const char *outputF);

void writeFiles(string filename, Header &headerObj, FILE *fptr, PIXEL *pixels, const char *outputF)
{
    if ((fptr = fopen(outputF, "w")))
    {
        putc(0, fptr);
        putc(0, fptr);
        putc(2, fptr);                         /* uncompressed rgb */
        putc(0, fptr); putc(0, fptr);
        putc(0, fptr); putc(0, fptr);
        putc(0, fptr);
        putc(0, fptr); putc(0, fptr);           /* x origin */
        putc(0, fptr); putc(0, fptr);           /* y origin */
        putc((headerObj.width & 0x00ff), fptr);
        putc((headerObj.width & 0xff00) / 256, fptr);
        putc((headerObj.height & 0x00ff), fptr);
        putc((headerObj.height & 0xff00) / 256, fptr);
        putc(24, fptr);                        /* 24 bit bitmap */
        putc(0, fptr);
        
        for (int i = 0; i < headerObj.width*headerObj.height; i++)
        {
            
            putc(pixels[i].b, fptr);
            putc(pixels[i].g, fptr);
            putc(pixels[i].r, fptr);
        }
    }
}
void MergeBytes(PIXEL *pixel, unsigned char *p, int bytes)
{
    pixel->r = p[2];
    pixel->g = p[1];
    pixel->b = p[0];
}

int tests = 0;

void test1()
{
    Header headerObj;
    string filename = "../input/layer1.tga";
    ifstream file;
    int n = 0;
    FILE *fptr;
    PIXEL *pixels;
    unsigned char p[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptr = fopen(filename.c_str(), "r")))
    {
        headerObj.idLength = getc(fptr);
        //cout << "id length: " << int(headerObj.idLength) << endl;
        headerObj.colorMapType = getc(fptr);
        //cout << "color map: " << int(headerObj.colorMapType) << endl;
        headerObj.dataTypeCode = getc(fptr);
        //out << "data type: " << int(headerObj.dataTypeCode) << endl;
        fread(&headerObj.colorMapOrigin, 2, 1, fptr);
        //cout << headerObj.colorMapOrigin << endl;
        fread(&headerObj.colorMapLength, 2, 1, fptr);
        //cout << headerObj.colorMapLength << endl;
        headerObj.colorMapDepth = getc(fptr);
        //cout << "colorMapDepth: " << int(headerObj.colorMapDepth) << endl;
        fread(&headerObj.xOrigin, 2, 1, fptr);
        //cout << headerObj.xOrigin << endl;
        fread(&headerObj.yOrigin, 2, 1, fptr);
        //cout << headerObj.yOrigin << endl;
        fread(&headerObj.width, 2, 1, fptr);
        //cout << headerObj.width << endl;
        fread(&headerObj.height, 2, 1, fptr);
        //cout << headerObj.height << endl;
        headerObj.bitsPerPixel = getc(fptr);
        //cout << "bitsPerPixel: " << int(headerObj.bitsPerPixel) << endl;
        headerObj.imageDescriptor = getc(fptr);
        //cout << "imageDescriptor: " << int(headerObj.imageDescriptor) << endl;
        
        
        
        if ((pixels = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerObj.width*headerObj.height; i++)
            {
                
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
                
            }
        }
        
        int skipover = 0;
        int bytes2read = 0;
        skipover += headerObj.idLength;
        skipover += headerObj.colorMapType * headerObj.colorMapLength;
        fseek(fptr, skipover, ios_base::cur);
        
        bytes2read = headerObj.bitsPerPixel / 8;
        while (n < headerObj.width*headerObj.height)
        {
            if (headerObj.dataTypeCode == 2)
            {
                if (fread(p, 1, bytes2read, fptr) != bytes2read)
                {
                    break;
                }
                MergeBytes(&(pixels[n]), p, bytes2read);
                n++;
            }
        }
        fclose(fptr);
    }
    //writeFiles(filename, headerObj, fptr, pixels, "output/outPut1.tga");
    
    Header headerO;
    string f = "../input/pattern1.tga";
    ifstream files;
    int j = 0;
    FILE *fptrs;
    PIXEL *pixel;
    unsigned char q[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptrs = fopen(f.c_str(), "r")))
    {
        headerO.idLength = getc(fptrs);
        //cout << "id length: " << int(headerO.idLength) << endl;
        headerO.colorMapType = getc(fptrs);
        //cout << "color map: " << int(headerO.colorMapType) << endl;
        headerO.dataTypeCode = getc(fptrs);
        //cout << "data type: " << int(headerO.dataTypeCode) << endl;
        fread(&headerO.colorMapOrigin, 2, 1, fptrs);
        //cout << headerO.colorMapOrigin << endl;
        fread(&headerO.colorMapLength, 2, 1, fptrs);
        //cout << headerO.colorMapLength << endl;
        headerO.colorMapDepth = getc(fptrs);
        //cout << "colorMapDepth: " << int(headerO.colorMapDepth) << endl;
        fread(&headerO.xOrigin, 2, 1, fptrs);
        //cout << headerO.xOrigin << endl;
        fread(&headerO.yOrigin, 2, 1, fptrs);
        //cout << headerO.yOrigin << endl;
        fread(&headerO.width, 2, 1, fptrs);
        //cout << headerO.width << endl;
        fread(&headerO.height, 2, 1, fptrs);
        //cout << headerO.height << endl;
        headerO.bitsPerPixel = getc(fptrs);
        //cout << "bitsPerPixel: " << int(headerO.bitsPerPixel) << endl;
        headerO.imageDescriptor = getc(fptrs);
        //cout << "imageDescriptor: " << int(headerO.imageDescriptor) << endl;
        
        
        
        if ((pixel = (PIXEL *)malloc(headerO.width*headerO.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerO.width*headerO.height; i++)
            {
                
                pixel[i].r = 0;
                pixel[i].g = 0;
                pixel[i].b = 0;
                
            }
        }
        
        int skipover1 = 0;
        int bytes2read1 = 0;
        skipover1 += headerO.idLength;
        skipover1 += headerO.colorMapType * headerO.colorMapLength;
        fseek(fptrs, skipover1, ios_base::cur);
        
        bytes2read1 = headerO.bitsPerPixel / 8;
        while (j < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(q, 1, bytes2read1, fptrs) != bytes2read1)
                {
                    break;
                }
                MergeBytes(&(pixel[j]), q, bytes2read1);
                j++;
            }
        }
        fclose(fptrs);
        
        //multiply
        PIXEL *comb;
        comb = multiply(pixel, pixels);
//        int k =0;
//        while (k < headerO.width*headerO.height)
//        {
//            if (headerO.dataTypeCode == 2)
//            {
//                if (fread(q, 1, bytes2read1, fptrs) != bytes2read1)
//                {
//                    break;
//                }
//                MergeBytes(&(comb[k]), q, bytes2read1);
//                k++;
//            }
//        }
        writeFiles(filename, headerObj, fptr, comb, "../output/part1.tga");
        
        PIXEL *p;
        p = (PIXEL *)malloc(headerO.width*headerO.height * sizeof(PIXEL));
        p = check("../examples/EXAMPLE_part1.tga");
        int c = 0;
        for (int i = 0; i < headerO.width*headerO.height; i++)
        {
            if(int(p[i].r) == int(comb[i].r) && int(p[i].g) == int(comb[i].g) && int(p[i].b) == int(comb[i].b))
            {
                c++;
                //cout << c << endl;
            }
            else
                break;
        }
        if(c == headerO.width*headerO.height)
        {
            cout << "Test #1...... Passed!" << endl;
            tests++;
        }
        else
            cout << "Test #1...... Failed!" << endl;
    }
} //end of test1

void test2()
{
    Header headerObj;
    string filename = "../input/layer2.tga";
    ifstream file;
    int n = 0;
    FILE *fptr;
    PIXEL *pixels;
    unsigned char p[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptr = fopen(filename.c_str(), "r")))
    {
        headerObj.idLength = getc(fptr);
        //cout << "id length: " << int(headerObj.idLength) << endl;
        headerObj.colorMapType = getc(fptr);
        //cout << "color map: " << int(headerObj.colorMapType) << endl;
        headerObj.dataTypeCode = getc(fptr);
        //out << "data type: " << int(headerObj.dataTypeCode) << endl;
        fread(&headerObj.colorMapOrigin, 2, 1, fptr);
        //cout << headerObj.colorMapOrigin << endl;
        fread(&headerObj.colorMapLength, 2, 1, fptr);
        //cout << headerObj.colorMapLength << endl;
        headerObj.colorMapDepth = getc(fptr);
        //cout << "colorMapDepth: " << int(headerObj.colorMapDepth) << endl;
        fread(&headerObj.xOrigin, 2, 1, fptr);
        //cout << headerObj.xOrigin << endl;
        fread(&headerObj.yOrigin, 2, 1, fptr);
        //cout << headerObj.yOrigin << endl;
        fread(&headerObj.width, 2, 1, fptr);
        //cout << headerObj.width << endl;
        fread(&headerObj.height, 2, 1, fptr);
        //cout << headerObj.height << endl;
        headerObj.bitsPerPixel = getc(fptr);
        //cout << "bitsPerPixel: " << int(headerObj.bitsPerPixel) << endl;
        headerObj.imageDescriptor = getc(fptr);
        //cout << "imageDescriptor: " << int(headerObj.imageDescriptor) << endl;
        
        
        
        if ((pixels = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerObj.width*headerObj.height; i++)
            {
                
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
                
            }
        }
        
        int skipover = 0;
        int bytes2read = 0;
        skipover += headerObj.idLength;
        skipover += headerObj.colorMapType * headerObj.colorMapLength;
        fseek(fptr, skipover, ios_base::cur);
        
        bytes2read = headerObj.bitsPerPixel / 8;
        while (n < headerObj.width*headerObj.height)
        {
            if (headerObj.dataTypeCode == 2)
            {
                if (fread(p, 1, bytes2read, fptr) != bytes2read)
                {
                    break;
                }
                MergeBytes(&(pixels[n]), p, bytes2read);
                n++;
            }
        }
        fclose(fptr);
    }
    //writeFiles(filename, headerObj, fptr, pixels, "output/outPut1.tga");
    
    Header headerO;
    string f = "../input/car.tga";
    ifstream files;
    int j = 0;
    FILE *fptrs;
    PIXEL *pixel;
    unsigned char q[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptrs = fopen(f.c_str(), "r")))
    {
        headerO.idLength = getc(fptrs);
        //cout << "id length: " << int(headerO.idLength) << endl;
        headerO.colorMapType = getc(fptrs);
        //cout << "color map: " << int(headerO.colorMapType) << endl;
        headerO.dataTypeCode = getc(fptrs);
        //cout << "data type: " << int(headerO.dataTypeCode) << endl;
        fread(&headerO.colorMapOrigin, 2, 1, fptrs);
        //cout << headerO.colorMapOrigin << endl;
        fread(&headerO.colorMapLength, 2, 1, fptrs);
        //cout << headerO.colorMapLength << endl;
        headerO.colorMapDepth = getc(fptrs);
        //cout << "colorMapDepth: " << int(headerO.colorMapDepth) << endl;
        fread(&headerO.xOrigin, 2, 1, fptrs);
        //cout << headerO.xOrigin << endl;
        fread(&headerO.yOrigin, 2, 1, fptrs);
        //cout << headerO.yOrigin << endl;
        fread(&headerO.width, 2, 1, fptrs);
        //cout << headerO.width << endl;
        fread(&headerO.height, 2, 1, fptrs);
        //cout << headerO.height << endl;
        headerO.bitsPerPixel = getc(fptrs);
        //cout << "bitsPerPixel: " << int(headerO.bitsPerPixel) << endl;
        headerO.imageDescriptor = getc(fptrs);
        //cout << "imageDescriptor: " << int(headerO.imageDescriptor) << endl;
        
        
        
        if ((pixel = (PIXEL *)malloc(headerO.width*headerO.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerO.width*headerO.height; i++)
            {
                
                pixel[i].r = 0;
                pixel[i].g = 0;
                pixel[i].b = 0;
                
            }
        }
        
        int skipover1 = 0;
        int bytes2read1 = 0;
        skipover1 += headerO.idLength;
        skipover1 += headerO.colorMapType * headerO.colorMapLength;
        fseek(fptrs, skipover1, ios_base::cur);
        
        bytes2read1 = headerO.bitsPerPixel / 8;
        while (j < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(q, 1, bytes2read1, fptrs) != bytes2read1)
                {
                    break;
                }
                MergeBytes(&(pixel[j]), q, bytes2read1);
                j++;
            }
        }
        fclose(fptrs);
        
        //subtraction
        PIXEL *comb;
        comb = subtraction(pixel, pixels);
        int k =0;
        while (k < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(q, 1, bytes2read1, fptrs) != bytes2read1)
                {
                    break;
                }
                MergeBytes(&(comb[k]), q, bytes2read1);
                k++;
            }
        }
        
        writeFiles(filename, headerObj, fptr, comb, "../output/part2.tga");
        
        //check
        PIXEL *p;
        p = (PIXEL *)malloc(headerO.width*headerO.height * sizeof(PIXEL));
        p = check("../examples/EXAMPLE_part2.tga");
        int c = 0;
        for (int i = 0; i < headerO.width*headerO.height; i++)
        {
            if(int(p[i].r) == int(comb[i].r) && int(p[i].g) == int(comb[i].g) && int(p[i].b) == int(comb[i].b))
            {
                c++;
                //cout << c << endl;
            }
            else
                break;
        }
        if(c == headerO.width*headerO.height)
        {
            cout << "Test #2...... Passed!" << endl;
            tests++;
        }
        else
            cout << "Test #2...... Failed!" << endl;
    }
}//end of test2

void test3()
{
    Header headerObj;
    string filename = "../input/layer1.tga";
    ifstream file;
    int n = 0;
    FILE *fptr;
    PIXEL *pixels;
    unsigned char p[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptr = fopen(filename.c_str(), "r")))
    {
        headerObj.idLength = getc(fptr);
        //cout << "id length: " << int(headerObj.idLength) << endl;
        headerObj.colorMapType = getc(fptr);
        //cout << "color map: " << int(headerObj.colorMapType) << endl;
        headerObj.dataTypeCode = getc(fptr);
        //out << "data type: " << int(headerObj.dataTypeCode) << endl;
        fread(&headerObj.colorMapOrigin, 2, 1, fptr);
        //cout << headerObj.colorMapOrigin << endl;
        fread(&headerObj.colorMapLength, 2, 1, fptr);
        //cout << headerObj.colorMapLength << endl;
        headerObj.colorMapDepth = getc(fptr);
        //cout << "colorMapDepth: " << int(headerObj.colorMapDepth) << endl;
        fread(&headerObj.xOrigin, 2, 1, fptr);
        //cout << headerObj.xOrigin << endl;
        fread(&headerObj.yOrigin, 2, 1, fptr);
        //cout << headerObj.yOrigin << endl;
        fread(&headerObj.width, 2, 1, fptr);
        //cout << headerObj.width << endl;
        fread(&headerObj.height, 2, 1, fptr);
        //cout << headerObj.height << endl;
        headerObj.bitsPerPixel = getc(fptr);
        //cout << "bitsPerPixel: " << int(headerObj.bitsPerPixel) << endl;
        headerObj.imageDescriptor = getc(fptr);
        //cout << "imageDescriptor: " << int(headerObj.imageDescriptor) << endl;
        
        
        
        if ((pixels = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerObj.width*headerObj.height; i++)
            {
                
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
                
            }
        }
        
        int skipover = 0;
        int bytes2read = 0;
        skipover += headerObj.idLength;
        skipover += headerObj.colorMapType * headerObj.colorMapLength;
        fseek(fptr, skipover, ios_base::cur);
        
        bytes2read = headerObj.bitsPerPixel / 8;
        while (n < headerObj.width*headerObj.height)
        {
            if (headerObj.dataTypeCode == 2)
            {
                if (fread(p, 1, bytes2read, fptr) != bytes2read)
                {
                    break;
                }
                MergeBytes(&(pixels[n]), p, bytes2read);
                n++;
            }
        }
        fclose(fptr);
    }
    //writeFiles(filename, headerObj, fptr, pixels, "output/outPut1.tga");
    
    Header headerO;
    string f = "../input/pattern2.tga";
    ifstream files;
    int j = 0;
    FILE *fptrs;
    PIXEL *pixel;
    unsigned char q[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptrs = fopen(f.c_str(), "r")))
    {
        headerO.idLength = getc(fptrs);
        //cout << "id length: " << int(headerO.idLength) << endl;
        headerO.colorMapType = getc(fptrs);
        //cout << "color map: " << int(headerO.colorMapType) << endl;
        headerO.dataTypeCode = getc(fptrs);
        //cout << "data type: " << int(headerO.dataTypeCode) << endl;
        fread(&headerO.colorMapOrigin, 2, 1, fptrs);
        //cout << headerO.colorMapOrigin << endl;
        fread(&headerO.colorMapLength, 2, 1, fptrs);
        //cout << headerO.colorMapLength << endl;
        headerO.colorMapDepth = getc(fptrs);
        //cout << "colorMapDepth: " << int(headerO.colorMapDepth) << endl;
        fread(&headerO.xOrigin, 2, 1, fptrs);
        //cout << headerO.xOrigin << endl;
        fread(&headerO.yOrigin, 2, 1, fptrs);
        //cout << headerO.yOrigin << endl;
        fread(&headerO.width, 2, 1, fptrs);
        //cout << headerO.width << endl;
        fread(&headerO.height, 2, 1, fptrs);
        //cout << headerO.height << endl;
        headerO.bitsPerPixel = getc(fptrs);
        //cout << "bitsPerPixel: " << int(headerO.bitsPerPixel) << endl;
        headerO.imageDescriptor = getc(fptrs);
        //cout << "imageDescriptor: " << int(headerO.imageDescriptor) << endl;
        
        
        
        if ((pixel = (PIXEL *)malloc(headerO.width*headerO.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerO.width*headerO.height; i++)
            {
                
                pixel[i].r = 0;
                pixel[i].g = 0;
                pixel[i].b = 0;
                
            }
        }
        
        int skipover1 = 0;
        int bytes2read1 = 0;
        skipover1 += headerO.idLength;
        skipover1 += headerO.colorMapType * headerO.colorMapLength;
        fseek(fptrs, skipover1, ios_base::cur);
        
        bytes2read1 = headerO.bitsPerPixel / 8;
        while (j < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(q, 1, bytes2read1, fptrs) != bytes2read1)
                {
                    break;
                }
                MergeBytes(&(pixel[j]), q, bytes2read1);
                j++;
            }
        }
        fclose(fptrs);
    }
        Header header;
        string fi = "../input/text.tga";
        ifstream filess;
        int k = 0;
        FILE *fptrss;
        PIXEL *pixe;
        unsigned char r[5];
        ///int size = headerObj.width*headerObj.height;
        if ((fptrss = fopen(fi.c_str(), "r")))
        {
            header.idLength = getc(fptrss);
            //cout << "id length: " << int(headerO.idLength) << endl;
            header.colorMapType = getc(fptrss);
            //cout << "color map: " << int(headerO.colorMapType) << endl;
            header.dataTypeCode = getc(fptrss);
            //cout << "data type: " << int(headerO.dataTypeCode) << endl;
            fread(&header.colorMapOrigin, 2, 1, fptrss);
            //cout << headerO.colorMapOrigin << endl;
            fread(&header.colorMapLength, 2, 1, fptrss);
            //cout << headerO.colorMapLength << endl;
            header.colorMapDepth = getc(fptrss);
            //cout << "colorMapDepth: " << int(headerO.colorMapDepth) << endl;
            fread(&header.xOrigin, 2, 1, fptrss);
            //cout << headerO.xOrigin << endl;
            fread(&header.yOrigin, 2, 1, fptrss);
            //cout << headerO.yOrigin << endl;
            fread(&header.width, 2, 1, fptrss);
            //cout << headerO.width << endl;
            fread(&header.height, 2, 1, fptrss);
            //cout << headerO.height << endl;
            header.bitsPerPixel = getc(fptrss);
            //cout << "bitsPerPixel: " << int(headerO.bitsPerPixel) << endl;
            header.imageDescriptor = getc(fptrss);
            //cout << "imageDescriptor: " << int(headerO.imageDescriptor) << endl;
            
            
            
            if ((pixe = (PIXEL *)malloc(header.width*header.height * sizeof(PIXEL))))
            {
                for (int i = 0; i < header.width*header.height; i++)
                {
                    
                    pixe[i].r = 0;
                    pixe[i].g = 0;
                    pixe[i].b = 0;
                    
                }
            }
            
            int skipover1 = 0;
            int bytes2read1 = 0;
            skipover1 += header.idLength;
            skipover1 += header.colorMapType * header.colorMapLength;
            fseek(fptrss, skipover1, ios_base::cur);
            
            bytes2read1 = headerO.bitsPerPixel / 8;
            while (k < headerO.width*headerO.height)
            {
                if (headerO.dataTypeCode == 2)
                {
                    if (fread(r, 1, bytes2read1, fptrss) != bytes2read1)
                    {
                        break;
                    }
                    MergeBytes(&(pixe[k]), r, bytes2read1);
                    k++;
                }
            }
            fclose(fptrss);
        }
        //multiply
        PIXEL *comb;
        comb = multiply(pixel, pixels);
        int a =0;
        while (a < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(q, 1, 3, fptrs) != 3)
                {
                    break;
                }
                MergeBytes(&(comb[a]), q, 3);
                a++;
            }
        }
        
        //screen
        PIXEL *again;
        again = screen(pixe, comb);
        int b =0;
        while (b < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(r, 1, 3, fptrss) != 3)
                {
                    break;
                }
                MergeBytes(&(comb[b]), r, 3);
                b++;
            }
        }
    
        
        writeFiles(filename, headerObj, fptr, again, "../output/part3.tga");
    
    //check
    PIXEL *y;
    y = (PIXEL *)malloc(headerO.width*headerO.height * sizeof(PIXEL));
    y = check("../examples/EXAMPLE_part3.tga");
    int c = 0;
    for (int i = 0; i < headerO.width*headerO.height; i++)
    {
        if(int(y[i].r) == int(again[i].r) && int(y[i].g) == int(again[i].g) && int(y[i].b) == int(again[i].b))
        {
            c++;
            //cout << c << endl;
        }
        else
        {
            //cout << "hello" << endl;
            break;
        }
        
    }
//    for(int i = 0; i < 2; i++)
//    {
//        cout << "red :" << int(again[i].r) << endl;
//        cout << "green :" << int(again[i].g) << endl;
//        cout << "blue :" << int(again[i].b) << endl;
//    }

    if(c == headerO.width*headerO.height)
    {
        cout << "Test #3...... Passed!" << endl;
        tests++;
    }
    else
        cout << "Test #3...... Failed!" << endl;
} //end of test3

void test4()
{
    Header headerObj;
    string filename = "../input/layer2.tga";
    ifstream file;
    int n = 0;
    FILE *fptr;
    PIXEL *pixels;
    unsigned char p[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptr = fopen(filename.c_str(), "r")))
    {
        headerObj.idLength = getc(fptr);
        //cout << "id length: " << int(headerObj.idLength) << endl;
        headerObj.colorMapType = getc(fptr);
        //cout << "color map: " << int(headerObj.colorMapType) << endl;
        headerObj.dataTypeCode = getc(fptr);
        //out << "data type: " << int(headerObj.dataTypeCode) << endl;
        fread(&headerObj.colorMapOrigin, 2, 1, fptr);
        //cout << headerObj.colorMapOrigin << endl;
        fread(&headerObj.colorMapLength, 2, 1, fptr);
        //cout << headerObj.colorMapLength << endl;
        headerObj.colorMapDepth = getc(fptr);
        //cout << "colorMapDepth: " << int(headerObj.colorMapDepth) << endl;
        fread(&headerObj.xOrigin, 2, 1, fptr);
        //cout << headerObj.xOrigin << endl;
        fread(&headerObj.yOrigin, 2, 1, fptr);
        //cout << headerObj.yOrigin << endl;
        fread(&headerObj.width, 2, 1, fptr);
        //cout << headerObj.width << endl;
        fread(&headerObj.height, 2, 1, fptr);
        //cout << headerObj.height << endl;
        headerObj.bitsPerPixel = getc(fptr);
        //cout << "bitsPerPixel: " << int(headerObj.bitsPerPixel) << endl;
        headerObj.imageDescriptor = getc(fptr);
        //cout << "imageDescriptor: " << int(headerObj.imageDescriptor) << endl;
        
        
        
        if ((pixels = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerObj.width*headerObj.height; i++)
            {
                
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
                
            }
        }
        
        int skipover = 0;
        int bytes2read = 0;
        skipover += headerObj.idLength;
        skipover += headerObj.colorMapType * headerObj.colorMapLength;
        fseek(fptr, skipover, ios_base::cur);
        
        bytes2read = headerObj.bitsPerPixel / 8;
        while (n < headerObj.width*headerObj.height)
        {
            if (headerObj.dataTypeCode == 2)
            {
                if (fread(p, 1, bytes2read, fptr) != bytes2read)
                {
                    break;
                }
                MergeBytes(&(pixels[n]), p, bytes2read);
                n++;
            }
        }
        fclose(fptr);
    }
    //writeFiles(filename, headerObj, fptr, pixels, "output/outPut1.tga");
    
    Header headerO;
    string f = "../input/circles.tga";
    ifstream files;
    int j = 0;
    FILE *fptrs;
    PIXEL *pixel;
    unsigned char q[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptrs = fopen(f.c_str(), "r")))
    {
        headerO.idLength = getc(fptrs);
        //cout << "id length: " << int(headerO.idLength) << endl;
        headerO.colorMapType = getc(fptrs);
        //cout << "color map: " << int(headerO.colorMapType) << endl;
        headerO.dataTypeCode = getc(fptrs);
        //cout << "data type: " << int(headerO.dataTypeCode) << endl;
        fread(&headerO.colorMapOrigin, 2, 1, fptrs);
        //cout << headerO.colorMapOrigin << endl;
        fread(&headerO.colorMapLength, 2, 1, fptrs);
        //cout << headerO.colorMapLength << endl;
        headerO.colorMapDepth = getc(fptrs);
        //cout << "colorMapDepth: " << int(headerO.colorMapDepth) << endl;
        fread(&headerO.xOrigin, 2, 1, fptrs);
        //cout << headerO.xOrigin << endl;
        fread(&headerO.yOrigin, 2, 1, fptrs);
        //cout << headerO.yOrigin << endl;
        fread(&headerO.width, 2, 1, fptrs);
        //cout << headerO.width << endl;
        fread(&headerO.height, 2, 1, fptrs);
        //cout << headerO.height << endl;
        headerO.bitsPerPixel = getc(fptrs);
        //cout << "bitsPerPixel: " << int(headerO.bitsPerPixel) << endl;
        headerO.imageDescriptor = getc(fptrs);
        //cout << "imageDescriptor: " << int(headerO.imageDescriptor) << endl;
        
        
        
        if ((pixel = (PIXEL *)malloc(headerO.width*headerO.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerO.width*headerO.height; i++)
            {
                
                pixel[i].r = 0;
                pixel[i].g = 0;
                pixel[i].b = 0;
                
            }
        }
        
        int skipover1 = 0;
        int bytes2read1 = 0;
        skipover1 += headerO.idLength;
        skipover1 += headerO.colorMapType * headerO.colorMapLength;
        fseek(fptrs, skipover1, ios_base::cur);
        
        bytes2read1 = headerO.bitsPerPixel / 8;
        while (j < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(q, 1, bytes2read1, fptrs) != bytes2read1)
                {
                    break;
                }
                MergeBytes(&(pixel[j]), q, bytes2read1);
                j++;
            }
        }
        fclose(fptrs);
    }
    Header header;
    string fi = "../input/pattern2.tga";
    ifstream filess;
    int k = 0;
    FILE *fptrss;
    PIXEL *pixe;
    unsigned char r[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptrss = fopen(fi.c_str(), "r")))
    {
        header.idLength = getc(fptrss);
        //cout << "id length: " << int(headerO.idLength) << endl;
        header.colorMapType = getc(fptrss);
        //cout << "color map: " << int(headerO.colorMapType) << endl;
        header.dataTypeCode = getc(fptrss);
        //cout << "data type: " << int(headerO.dataTypeCode) << endl;
        fread(&header.colorMapOrigin, 2, 1, fptrss);
        //cout << headerO.colorMapOrigin << endl;
        fread(&header.colorMapLength, 2, 1, fptrss);
        //cout << headerO.colorMapLength << endl;
        header.colorMapDepth = getc(fptrss);
        //cout << "colorMapDepth: " << int(headerO.colorMapDepth) << endl;
        fread(&header.xOrigin, 2, 1, fptrss);
        //cout << headerO.xOrigin << endl;
        fread(&header.yOrigin, 2, 1, fptrss);
        //cout << headerO.yOrigin << endl;
        fread(&header.width, 2, 1, fptrss);
        //cout << headerO.width << endl;
        fread(&header.height, 2, 1, fptrss);
        //cout << headerO.height << endl;
        header.bitsPerPixel = getc(fptrss);
        //cout << "bitsPerPixel: " << int(headerO.bitsPerPixel) << endl;
        header.imageDescriptor = getc(fptrss);
        //cout << "imageDescriptor: " << int(headerO.imageDescriptor) << endl;
        
        
        
        if ((pixe = (PIXEL *)malloc(header.width*header.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < header.width*header.height; i++)
            {
                
                pixe[i].r = 0;
                pixe[i].g = 0;
                pixe[i].b = 0;
                
            }
        }
        
        int skipover1 = 0;
        int bytes2read1 = 0;
        skipover1 += header.idLength;
        skipover1 += header.colorMapType * header.colorMapLength;
        fseek(fptrss, skipover1, ios_base::cur);
        
        bytes2read1 = headerO.bitsPerPixel / 8;
        while (k < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(r, 1, bytes2read1, fptrss) != bytes2read1)
                {
                    break;
                }
                MergeBytes(&(pixe[k]), r, bytes2read1);
                k++;
            }
        }
        fclose(fptrss);
    }
    
    //multiply
    PIXEL *comb;
    comb = multiply(pixel, pixels);
    int a =0;
    while (a < headerO.width*headerO.height)
    {
        if (headerO.dataTypeCode == 2)
        {
            if (fread(q, 1, 3, fptrs) != 3)
            {
                break;
            }
            MergeBytes(&(comb[a]), q, 3);
            a++;
        }
    }
    
    //subtraction
    PIXEL *again;
    again = subtraction(comb, pixe);
    int b =0;
    while (b < headerO.width*headerO.height)
    {
        if (headerO.dataTypeCode == 2)
        {
            if (fread(r, 1, 3, fptrss) != 3)
            {
                break;
            }
            MergeBytes(&(comb[b]), r, 3);
            b++;
        }
    }
    
    writeFiles(filename, headerObj, fptr, again, "../output/part4.tga");
    
    //check
    PIXEL *y;
    y = (PIXEL *)malloc(headerO.width*headerO.height * sizeof(PIXEL));
    y = check("../examples/EXAMPLE_part4.tga");
    int c = 0;
    for (int i = 0; i < headerO.width*headerO.height; i++)
    {
        if(int(y[i].r) == int(again[i].r) && int(y[i].g) == int(again[i].g) && int(y[i].b) == int(again[i].b))
        {
            c++;
            //cout << c << endl;
        }
        else
        {
            //cout << "hello" << endl;
            break;
        }
        
    }
    //    for(int i = 0; i < 2; i++)
    //    {
    //        cout << "red :" << int(again[i].r) << endl;
    //        cout << "green :" << int(again[i].g) << endl;
    //        cout << "blue :" << int(again[i].b) << endl;
    //    }
    
    if(c == headerO.width*headerO.height)
    {
        cout << "Test #4...... Passed!" << endl;
        tests++;
    }
    else
        cout << "Test #4...... Failed!" << endl;
}// end of test4

void test5()
{
    Header headerObj;
    string filename = "../input/layer1.tga";
    ifstream file;
    int n = 0;
    FILE *fptr;
    PIXEL *pixels;
    unsigned char p[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptr = fopen(filename.c_str(), "r")))
    {
        headerObj.idLength = getc(fptr);
        //cout << "id length: " << int(headerObj.idLength) << endl;
        headerObj.colorMapType = getc(fptr);
        //cout << "color map: " << int(headerObj.colorMapType) << endl;
        headerObj.dataTypeCode = getc(fptr);
        //out << "data type: " << int(headerObj.dataTypeCode) << endl;
        fread(&headerObj.colorMapOrigin, 2, 1, fptr);
        //cout << headerObj.colorMapOrigin << endl;
        fread(&headerObj.colorMapLength, 2, 1, fptr);
        //cout << headerObj.colorMapLength << endl;
        headerObj.colorMapDepth = getc(fptr);
        //cout << "colorMapDepth: " << int(headerObj.colorMapDepth) << endl;
        fread(&headerObj.xOrigin, 2, 1, fptr);
        //cout << headerObj.xOrigin << endl;
        fread(&headerObj.yOrigin, 2, 1, fptr);
        //cout << headerObj.yOrigin << endl;
        fread(&headerObj.width, 2, 1, fptr);
        //cout << headerObj.width << endl;
        fread(&headerObj.height, 2, 1, fptr);
        //cout << headerObj.height << endl;
        headerObj.bitsPerPixel = getc(fptr);
        //cout << "bitsPerPixel: " << int(headerObj.bitsPerPixel) << endl;
        headerObj.imageDescriptor = getc(fptr);
        //cout << "imageDescriptor: " << int(headerObj.imageDescriptor) << endl;
        
        
        
        if ((pixels = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerObj.width*headerObj.height; i++)
            {
                
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
                
            }
        }
        
        int skipover = 0;
        int bytes2read = 0;
        skipover += headerObj.idLength;
        skipover += headerObj.colorMapType * headerObj.colorMapLength;
        fseek(fptr, skipover, ios_base::cur);
        
        bytes2read = headerObj.bitsPerPixel / 8;
        while (n < headerObj.width*headerObj.height)
        {
            if (headerObj.dataTypeCode == 2)
            {
                if (fread(p, 1, bytes2read, fptr) != bytes2read)
                {
                    break;
                }
                MergeBytes(&(pixels[n]), p, bytes2read);
                n++;
            }
        }
        fclose(fptr);
    }
    //writeFiles(filename, headerObj, fptr, pixels, "output/outPut1.tga");
    
    Header headerO;
    string f = "../input/pattern1.tga";
    ifstream files;
    int j = 0;
    FILE *fptrs;
    PIXEL *pixel;
    unsigned char q[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptrs = fopen(f.c_str(), "r")))
    {
        headerO.idLength = getc(fptrs);
        //cout << "id length: " << int(headerO.idLength) << endl;
        headerO.colorMapType = getc(fptrs);
        //cout << "color map: " << int(headerO.colorMapType) << endl;
        headerO.dataTypeCode = getc(fptrs);
        //cout << "data type: " << int(headerO.dataTypeCode) << endl;
        fread(&headerO.colorMapOrigin, 2, 1, fptrs);
        //cout << headerO.colorMapOrigin << endl;
        fread(&headerO.colorMapLength, 2, 1, fptrs);
        //cout << headerO.colorMapLength << endl;
        headerO.colorMapDepth = getc(fptrs);
        //cout << "colorMapDepth: " << int(headerO.colorMapDepth) << endl;
        fread(&headerO.xOrigin, 2, 1, fptrs);
        //cout << headerO.xOrigin << endl;
        fread(&headerO.yOrigin, 2, 1, fptrs);
        //cout << headerO.yOrigin << endl;
        fread(&headerO.width, 2, 1, fptrs);
        //cout << headerO.width << endl;
        fread(&headerO.height, 2, 1, fptrs);
        //cout << headerO.height << endl;
        headerO.bitsPerPixel = getc(fptrs);
        //cout << "bitsPerPixel: " << int(headerO.bitsPerPixel) << endl;
        headerO.imageDescriptor = getc(fptrs);
        //cout << "imageDescriptor: " << int(headerO.imageDescriptor) << endl;
        
        
        
        if ((pixel = (PIXEL *)malloc(headerO.width*headerO.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerO.width*headerO.height; i++)
            {
                
                pixel[i].r = 0;
                pixel[i].g = 0;
                pixel[i].b = 0;
                
            }
        }
        
        int skipover1 = 0;
        int bytes2read1 = 0;
        skipover1 += headerO.idLength;
        skipover1 += headerO.colorMapType * headerO.colorMapLength;
        fseek(fptrs, skipover1, ios_base::cur);
        
        bytes2read1 = headerO.bitsPerPixel / 8;
        while (j < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(q, 1, bytes2read1, fptrs) != bytes2read1)
                {
                    break;
                }
                MergeBytes(&(pixel[j]), q, bytes2read1);
                j++;
            }
        }
        fclose(fptrs);
        
        //overlay
        PIXEL *comb;
        comb = overlay(pixel, pixels);
        int k =0;
        while (k < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(q, 1, bytes2read1, fptrs) != bytes2read1)
                {
                    break;
                }
                MergeBytes(&(comb[k]), q, bytes2read1);
                k++;
            }
        }
        
        writeFiles(filename, headerObj, fptr, comb, "../output/part5.tga");
        
        //check
        PIXEL *y;
        y = (PIXEL *)malloc(headerO.width*headerO.height * sizeof(PIXEL));
        y = check("../examples/EXAMPLE_part5.tga");
        int c = 0;
        for (int i = 0; i < headerO.width*headerO.height; i++)
        {
            if(int(y[i].r) == int(comb[i].r) && int(y[i].g) == int(comb[i].g) && int(y[i].b) == int(comb[i].b))
            {
                c++;
                //cout << c << endl;
            }
            else
            {
                //cout << "hello" << endl;
                break;
            }
            
        }
//            for(int i = 0; i < 3; i++)
//            {
//                cout << "red :" << int(comb[i].r) << endl;
//                cout << "green :" << int(comb[i].g) << endl;
//                cout << "blue :" << int(comb[i].b) << endl;
//            }
        
        if(c == headerO.width*headerO.height)
        {
            cout << "Test #5...... Passed!" << endl;
            tests++;
        }
        else
            cout << "Test #5...... Failed!" << endl;
    }
} //end of test5
void test6()
{
    Header headerObj;
    string filename = "../input/car.tga";
    ifstream file;
    int n = 0;
    FILE *fptr;
    PIXEL *pixels;
    unsigned char p[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptr = fopen(filename.c_str(), "r")))
    {
        headerObj.idLength = getc(fptr);
        //cout << "id length: " << int(headerObj.idLength) << endl;
        headerObj.colorMapType = getc(fptr);
        //cout << "color map: " << int(headerObj.colorMapType) << endl;
        headerObj.dataTypeCode = getc(fptr);
        //out << "data type: " << int(headerObj.dataTypeCode) << endl;
        fread(&headerObj.colorMapOrigin, 2, 1, fptr);
        //cout << headerObj.colorMapOrigin << endl;
        fread(&headerObj.colorMapLength, 2, 1, fptr);
        //cout << headerObj.colorMapLength << endl;
        headerObj.colorMapDepth = getc(fptr);
        //cout << "colorMapDepth: " << int(headerObj.colorMapDepth) << endl;
        fread(&headerObj.xOrigin, 2, 1, fptr);
        //cout << headerObj.xOrigin << endl;
        fread(&headerObj.yOrigin, 2, 1, fptr);
        //cout << headerObj.yOrigin << endl;
        fread(&headerObj.width, 2, 1, fptr);
        //cout << headerObj.width << endl;
        fread(&headerObj.height, 2, 1, fptr);
        //cout << headerObj.height << endl;
        headerObj.bitsPerPixel = getc(fptr);
        //cout << "bitsPerPixel: " << int(headerObj.bitsPerPixel) << endl;
        headerObj.imageDescriptor = getc(fptr);
        //cout << "imageDescriptor: " << int(headerObj.imageDescriptor) << endl;
        
        
        
        if ((pixels = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerObj.width*headerObj.height; i++)
            {
                
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
                
            }
        }
        
        int skipover = 0;
        int bytes2read = 0;
        skipover += headerObj.idLength;
        skipover += headerObj.colorMapType * headerObj.colorMapLength;
        fseek(fptr, skipover, ios_base::cur);
        
        bytes2read = headerObj.bitsPerPixel / 8;
        while (n < headerObj.width*headerObj.height)
        {
            if (headerObj.dataTypeCode == 2)
            {
                if (fread(p, 1, bytes2read, fptr) != bytes2read)
                {
                    break;
                }
                MergeBytes(&(pixels[n]), p, bytes2read);
                n++;
            }
        }
        fclose(fptr);
    }
    for (int i = 0; i < 512*512; i++)
    {
        if((pixels[i].g + 200) > 255)
            pixels[i].g = 255;
        else
            pixels[i].g = pixels[i].g + 200;
    }
    writeFiles(filename, headerObj, fptr, pixels, "../output/part6.tga");
    
    PIXEL *y;
    y = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL));
    y = check("../examples/EXAMPLE_part6.tga");
    int c = 0;
    for (int i = 0; i < headerObj.width*headerObj.height; i++)
    {
        if(int(y[i].r) == int(pixels[i].r) && int(y[i].g) == int(pixels[i].g) && int(y[i].b) == int(pixels[i].b))
        {
            c++;
            //cout << c << endl;
        }
        else
        {
            //cout << "hello" << endl;
            break;
        }
        
    }
    //            for(int i = 0; i < 3; i++)
    //            {
    //                cout << "red :" << int(comb[i].r) << endl;
    //                cout << "green :" << int(comb[i].g) << endl;
    //                cout << "blue :" << int(comb[i].b) << endl;
    //            }
    
    if(c == headerObj.width*headerObj.height)
    {
        cout << "Test #6...... Passed!" << endl;
        tests++;
    }
    else
        cout << "Test #6...... Failed!" << endl;
}
void test7()
{
    Header headerObj;
    string filename = "../input/car.tga";
    ifstream file;
    int n = 0;
    FILE *fptr;
    PIXEL *pixels;
    unsigned char p[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptr = fopen(filename.c_str(), "r")))
    {
        headerObj.idLength = getc(fptr);
        //cout << "id length: " << int(headerObj.idLength) << endl;
        headerObj.colorMapType = getc(fptr);
        //cout << "color map: " << int(headerObj.colorMapType) << endl;
        headerObj.dataTypeCode = getc(fptr);
        //out << "data type: " << int(headerObj.dataTypeCode) << endl;
        fread(&headerObj.colorMapOrigin, 2, 1, fptr);
        //cout << headerObj.colorMapOrigin << endl;
        fread(&headerObj.colorMapLength, 2, 1, fptr);
        //cout << headerObj.colorMapLength << endl;
        headerObj.colorMapDepth = getc(fptr);
        //cout << "colorMapDepth: " << int(headerObj.colorMapDepth) << endl;
        fread(&headerObj.xOrigin, 2, 1, fptr);
        //cout << headerObj.xOrigin << endl;
        fread(&headerObj.yOrigin, 2, 1, fptr);
        //cout << headerObj.yOrigin << endl;
        fread(&headerObj.width, 2, 1, fptr);
        //cout << headerObj.width << endl;
        fread(&headerObj.height, 2, 1, fptr);
        //cout << headerObj.height << endl;
        headerObj.bitsPerPixel = getc(fptr);
        //cout << "bitsPerPixel: " << int(headerObj.bitsPerPixel) << endl;
        headerObj.imageDescriptor = getc(fptr);
        //cout << "imageDescriptor: " << int(headerObj.imageDescriptor) << endl;
        
        
        
        if ((pixels = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerObj.width*headerObj.height; i++)
            {
                
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
                
            }
        }
        
        int skipover = 0;
        int bytes2read = 0;
        skipover += headerObj.idLength;
        skipover += headerObj.colorMapType * headerObj.colorMapLength;
        fseek(fptr, skipover, ios_base::cur);
        
        bytes2read = headerObj.bitsPerPixel / 8;
        while (n < headerObj.width*headerObj.height)
        {
            if (headerObj.dataTypeCode == 2)
            {
                if (fread(p, 1, bytes2read, fptr) != bytes2read)
                {
                    break;
                }
                MergeBytes(&(pixels[n]), p, bytes2read);
                n++;
            }
        }
        fclose(fptr);
    }
    for (int i = 0; i < 512*512; i++)
    {
        if((pixels[i].r * 4) > 255)
            pixels[i].r = 255;
        else
            pixels[i].r = pixels[i].r * 4;
        pixels[i].b = 0;
    }
    writeFiles(filename, headerObj, fptr, pixels, "../output/part7.tga");
    
    PIXEL *y;
    y = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL));
    y = check("../examples/EXAMPLE_part7.tga");
    int c = 0;
    for (int i = 0; i < headerObj.width*headerObj.height; i++)
    {
        if(int(y[i].r) == int(pixels[i].r) && int(y[i].g) == int(pixels[i].g) && int(y[i].b) == int(pixels[i].b))
        {
            c++;
            //cout << c << endl;
        }
        else
        {
            //cout << "hello" << endl;
            break;
        }
        
    }
    //            for(int i = 0; i < 3; i++)
    //            {
    //                cout << "red :" << int(comb[i].r) << endl;
    //                cout << "green :" << int(comb[i].g) << endl;
    //                cout << "blue :" << int(comb[i].b) << endl;
    //            }
    
    if(c == headerObj.width*headerObj.height)
    {
        cout << "Test #7...... Passed!" << endl;
        tests++;
    }
    else
        cout << "Test #7...... Failed!" << endl;

}

void test8()
{
    Header headerObj;
    string filename = "../input/car.tga";
    ifstream file;
    int n = 0;
    FILE *fptr;
    PIXEL *pixels;
    unsigned char p[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptr = fopen(filename.c_str(), "r")))
    {
        headerObj.idLength = getc(fptr);
        //cout << "id length: " << int(headerObj.idLength) << endl;
        headerObj.colorMapType = getc(fptr);
        //cout << "color map: " << int(headerObj.colorMapType) << endl;
        headerObj.dataTypeCode = getc(fptr);
        //out << "data type: " << int(headerObj.dataTypeCode) << endl;
        fread(&headerObj.colorMapOrigin, 2, 1, fptr);
        //cout << headerObj.colorMapOrigin << endl;
        fread(&headerObj.colorMapLength, 2, 1, fptr);
        //cout << headerObj.colorMapLength << endl;
        headerObj.colorMapDepth = getc(fptr);
        //cout << "colorMapDepth: " << int(headerObj.colorMapDepth) << endl;
        fread(&headerObj.xOrigin, 2, 1, fptr);
        //cout << headerObj.xOrigin << endl;
        fread(&headerObj.yOrigin, 2, 1, fptr);
        //cout << headerObj.yOrigin << endl;
        fread(&headerObj.width, 2, 1, fptr);
        //cout << headerObj.width << endl;
        fread(&headerObj.height, 2, 1, fptr);
        //cout << headerObj.height << endl;
        headerObj.bitsPerPixel = getc(fptr);
        //cout << "bitsPerPixel: " << int(headerObj.bitsPerPixel) << endl;
        headerObj.imageDescriptor = getc(fptr);
        //cout << "imageDescriptor: " << int(headerObj.imageDescriptor) << endl;
        
        
        
        if ((pixels = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerObj.width*headerObj.height; i++)
            {
                
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
                
            }
        }
        
        int skipover = 0;
        int bytes2read = 0;
        skipover += headerObj.idLength;
        skipover += headerObj.colorMapType * headerObj.colorMapLength;
        fseek(fptr, skipover, ios_base::cur);
        
        bytes2read = headerObj.bitsPerPixel / 8;
        while (n < headerObj.width*headerObj.height)
        {
            if (headerObj.dataTypeCode == 2)
            {
                if (fread(p, 1, bytes2read, fptr) != bytes2read)
                {
                    break;
                }
                MergeBytes(&(pixels[n]), p, bytes2read);
                n++;
            }
        }
        fclose(fptr);
    }
    PIXEL *red;
    red = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL));
    PIXEL *blue;
    blue = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL));
    PIXEL *green;
    green = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL));
    for (int i = 0; i < 512*512; i++)
    {
        red[i].r = pixels[i].r;
        red[i].g = pixels[i].r;
        red[i].b = pixels[i].r;
        green[i].r = pixels[i].g;
        green[i].g = pixels[i].g;
        green[i].b = pixels[i].g;
        blue[i].r = pixels[i].b;
        blue[i].g = pixels[i].b;
        blue[i].b = pixels[i].b;
        
        
    }
    writeFiles(filename, headerObj, fptr, red, "../output/part8_r.tga");
    writeFiles(filename, headerObj, fptr, green, "../output/part8_g.tga");
    writeFiles(filename, headerObj, fptr, blue, "../output/part8_b.tga");
    
    //check
    PIXEL *y;
    y = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL));
    y = check("../examples/EXAMPLE_part8_r.tga");
    int c = 0;
    for (int i = 0; i < headerObj.width*headerObj.height; i++)
    {
        if(int(y[i].r) == int(red[i].r) && int(y[i].g) == int(red[i].g) && int(y[i].b) == int(red[i].b))
        {
            c++;
            //cout << c << endl;
        }
        else
        {
            //cout << "hello" << endl;
            break;
        }
        
    }
    //            for(int i = 0; i < 3; i++)
    //            {
    //                cout << "red :" << int(comb[i].r) << endl;
    //                cout << "green :" << int(comb[i].g) << endl;
    //                cout << "blue :" << int(comb[i].b) << endl;
    //            }
    
    if(c == headerObj.width*headerObj.height)
    {
        cout << "Test #8...... Passed!" << endl;
        tests++;
    }
    else
        cout << "Test #8...... Failed!" << endl;
    
    PIXEL *o;
    o = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL));
    o = check("../examples/EXAMPLE_part8_g.tga");
    int x = 0;
    for (int i = 0; i < headerObj.width*headerObj.height; i++)
    {
        if(int(o[i].r) == int(green[i].r) && int(o[i].g) == int(green[i].g) && int(o[i].b) == int(green[i].b))
        {
            x++;
            //cout << x << endl;
        }
        else
        {
            //cout << "hello" << endl;
            break;
        }
        
    }
    //            for(int i = 0; i < 3; i++)
    //            {
    //                cout << "red :" << int(comb[i].r) << endl;
    //                cout << "green :" << int(comb[i].g) << endl;
    //                cout << "blue :" << int(comb[i].b) << endl;
    //            }
    
    if(x == headerObj.width*headerObj.height)
    {
        cout << "Test #9...... Passed!" << endl;
        tests++;
    }
    else
        cout << "Test #9...... Failed!" << endl;
    
    PIXEL *w;
    w = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL));
    w = check("../examples/EXAMPLE_part8_b.tga");
    int z = 0;
    for (int i = 0; i < headerObj.width*headerObj.height; i++)
    {
        if(int(w[i].r) == int(blue[i].r) && int(w[i].g) == int(blue[i].g) && int(w[i].b) == int(blue[i].b))
        {
            z++;
            //cout << z << endl;
        }
        else
        {
            //cout << "hello" << endl;
            break;
        }
        
    }
    //            for(int i = 0; i < 3; i++)
    //            {
    //                cout << "red :" << int(comb[i].r) << endl;
    //                cout << "green :" << int(comb[i].g) << endl;
    //                cout << "blue :" << int(comb[i].b) << endl;
    //            }
    
    if(z == headerObj.width*headerObj.height)
    {
        cout << "Test #10...... Passed!" << endl;
        tests++;
    }
    else
        cout << "Test #10...... Failed!" << endl;
}

void test9()
{
    Header headerObj;
    string filename = "../input/layer_red.tga";
    ifstream file;
    int n = 0;
    FILE *fptr;
    PIXEL *pixels;
    unsigned char p[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptr = fopen(filename.c_str(), "r")))
    {
        headerObj.idLength = getc(fptr);
        //cout << "id length: " << int(headerObj.idLength) << endl;
        headerObj.colorMapType = getc(fptr);
        //cout << "color map: " << int(headerObj.colorMapType) << endl;
        headerObj.dataTypeCode = getc(fptr);
        //out << "data type: " << int(headerObj.dataTypeCode) << endl;
        fread(&headerObj.colorMapOrigin, 2, 1, fptr);
        //cout << headerObj.colorMapOrigin << endl;
        fread(&headerObj.colorMapLength, 2, 1, fptr);
        //cout << headerObj.colorMapLength << endl;
        headerObj.colorMapDepth = getc(fptr);
        //cout << "colorMapDepth: " << int(headerObj.colorMapDepth) << endl;
        fread(&headerObj.xOrigin, 2, 1, fptr);
        //cout << headerObj.xOrigin << endl;
        fread(&headerObj.yOrigin, 2, 1, fptr);
        //cout << headerObj.yOrigin << endl;
        fread(&headerObj.width, 2, 1, fptr);
        //cout << headerObj.width << endl;
        fread(&headerObj.height, 2, 1, fptr);
        //cout << headerObj.height << endl;
        headerObj.bitsPerPixel = getc(fptr);
        //cout << "bitsPerPixel: " << int(headerObj.bitsPerPixel) << endl;
        headerObj.imageDescriptor = getc(fptr);
        //cout << "imageDescriptor: " << int(headerObj.imageDescriptor) << endl;
        
        
        
        if ((pixels = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerObj.width*headerObj.height; i++)
            {
                
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
                
            }
        }
        
        int skipover = 0;
        int bytes2read = 0;
        skipover += headerObj.idLength;
        skipover += headerObj.colorMapType * headerObj.colorMapLength;
        fseek(fptr, skipover, ios_base::cur);
        
        bytes2read = headerObj.bitsPerPixel / 8;
        while (n < headerObj.width*headerObj.height)
        {
            if (headerObj.dataTypeCode == 2)
            {
                if (fread(p, 1, bytes2read, fptr) != bytes2read)
                {
                    break;
                }
                MergeBytes(&(pixels[n]), p, bytes2read);
                n++;
            }
        }
        fclose(fptr);
    }
    //writeFiles(filename, headerObj, fptr, pixels, "output/outPut1.tga");
    
    Header headerO;
    string f = "../input/layer_green.tga";
    ifstream files;
    int j = 0;
    FILE *fptrs;
    PIXEL *pixel;
    unsigned char q[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptrs = fopen(f.c_str(), "r")))
    {
        headerO.idLength = getc(fptrs);
        //cout << "id length: " << int(headerO.idLength) << endl;
        headerO.colorMapType = getc(fptrs);
        //cout << "color map: " << int(headerO.colorMapType) << endl;
        headerO.dataTypeCode = getc(fptrs);
        //cout << "data type: " << int(headerO.dataTypeCode) << endl;
        fread(&headerO.colorMapOrigin, 2, 1, fptrs);
        //cout << headerO.colorMapOrigin << endl;
        fread(&headerO.colorMapLength, 2, 1, fptrs);
        //cout << headerO.colorMapLength << endl;
        headerO.colorMapDepth = getc(fptrs);
        //cout << "colorMapDepth: " << int(headerO.colorMapDepth) << endl;
        fread(&headerO.xOrigin, 2, 1, fptrs);
        //cout << headerO.xOrigin << endl;
        fread(&headerO.yOrigin, 2, 1, fptrs);
        //cout << headerO.yOrigin << endl;
        fread(&headerO.width, 2, 1, fptrs);
        //cout << headerO.width << endl;
        fread(&headerO.height, 2, 1, fptrs);
        //cout << headerO.height << endl;
        headerO.bitsPerPixel = getc(fptrs);
        //cout << "bitsPerPixel: " << int(headerO.bitsPerPixel) << endl;
        headerO.imageDescriptor = getc(fptrs);
        //cout << "imageDescriptor: " << int(headerO.imageDescriptor) << endl;
        
        
        
        if ((pixel = (PIXEL *)malloc(headerO.width*headerO.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerO.width*headerO.height; i++)
            {
                
                pixel[i].r = 0;
                pixel[i].g = 0;
                pixel[i].b = 0;
                
            }
        }
        
        int skipover1 = 0;
        int bytes2read1 = 0;
        skipover1 += headerO.idLength;
        skipover1 += headerO.colorMapType * headerO.colorMapLength;
        fseek(fptrs, skipover1, ios_base::cur);
        
        bytes2read1 = headerO.bitsPerPixel / 8;
        while (j < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(q, 1, bytes2read1, fptrs) != bytes2read1)
                {
                    break;
                }
                MergeBytes(&(pixel[j]), q, bytes2read1);
                j++;
            }
        }
        fclose(fptrs);
    }
    Header header;
    string fi = "../input/layer_blue.tga";
    ifstream filess;
    int k = 0;
    FILE *fptrss;
    PIXEL *pixe;
    unsigned char r[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptrss = fopen(fi.c_str(), "r")))
    {
        header.idLength = getc(fptrss);
        //cout << "id length: " << int(headerO.idLength) << endl;
        header.colorMapType = getc(fptrss);
        //cout << "color map: " << int(headerO.colorMapType) << endl;
        header.dataTypeCode = getc(fptrss);
        //cout << "data type: " << int(headerO.dataTypeCode) << endl;
        fread(&header.colorMapOrigin, 2, 1, fptrss);
        //cout << headerO.colorMapOrigin << endl;
        fread(&header.colorMapLength, 2, 1, fptrss);
        //cout << headerO.colorMapLength << endl;
        header.colorMapDepth = getc(fptrss);
        //cout << "colorMapDepth: " << int(headerO.colorMapDepth) << endl;
        fread(&header.xOrigin, 2, 1, fptrss);
        //cout << headerO.xOrigin << endl;
        fread(&header.yOrigin, 2, 1, fptrss);
        //cout << headerO.yOrigin << endl;
        fread(&header.width, 2, 1, fptrss);
        //cout << headerO.width << endl;
        fread(&header.height, 2, 1, fptrss);
        //cout << headerO.height << endl;
        header.bitsPerPixel = getc(fptrss);
        //cout << "bitsPerPixel: " << int(headerO.bitsPerPixel) << endl;
        header.imageDescriptor = getc(fptrss);
        //cout << "imageDescriptor: " << int(headerO.imageDescriptor) << endl;
        
        
        
        if ((pixe = (PIXEL *)malloc(header.width*header.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < header.width*header.height; i++)
            {
                
                pixe[i].r = 0;
                pixe[i].g = 0;
                pixe[i].b = 0;
                
            }
        }
        
        int skipover1 = 0;
        int bytes2read1 = 0;
        skipover1 += header.idLength;
        skipover1 += header.colorMapType * header.colorMapLength;
        fseek(fptrss, skipover1, ios_base::cur);
        
        bytes2read1 = headerO.bitsPerPixel / 8;
        while (k < headerO.width*headerO.height)
        {
            if (headerO.dataTypeCode == 2)
            {
                if (fread(r, 1, bytes2read1, fptrss) != bytes2read1)
                {
                    break;
                }
                MergeBytes(&(pixe[k]), r, bytes2read1);
                k++;
            }
        }
        fclose(fptrss);
    }
    
    PIXEL *comb;
    comb = (PIXEL *)malloc(512*512 * sizeof(PIXEL));
    for (int i = 0; i < 512*512; i++)
    {
        comb[i].r = pixels[i].r;
        comb[i].g = pixel[i].g;
        comb[i].b = pixe[i].b;
    }
    writeFiles(filename, headerObj, fptr, comb, "../output/part9.tga");
    
    PIXEL *y;
    y = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL));
    y = check("../examples/EXAMPLE_part9.tga");
    int c = 0;
    for (int i = 0; i < headerObj.width*headerObj.height; i++)
    {
        if(int(y[i].r) == int(comb[i].r) && int(y[i].g) == int(comb[i].g) && int(y[i].b) == int(comb[i].b))
        {
            c++;
            //cout << c << endl;
        }
        else
        {
            //cout << "hello" << endl;
            break;
        }
        
    }
    //            for(int i = 0; i < 3; i++)
    //            {
    //                cout << "red :" << int(comb[i].r) << endl;
    //                cout << "green :" << int(comb[i].g) << endl;
    //                cout << "blue :" << int(comb[i].b) << endl;
    //            }
    
    if(c == headerObj.width*headerObj.height)
    {
        cout << "Test #11...... Passed!" << endl;
        tests++;
    }
    else
        cout << "Test #11...... Failed!" << endl;
}

void test10()
{
    Header headerObj;
    string filename = "../input/text2.tga";
    ifstream file;
    int n = 0;
    FILE *fptr;
    PIXEL *pixels;
    unsigned char p[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptr = fopen(filename.c_str(), "r")))
    {
        headerObj.idLength = getc(fptr);
        //cout << "id length: " << int(headerObj.idLength) << endl;
        headerObj.colorMapType = getc(fptr);
        //cout << "color map: " << int(headerObj.colorMapType) << endl;
        headerObj.dataTypeCode = getc(fptr);
        //out << "data type: " << int(headerObj.dataTypeCode) << endl;
        fread(&headerObj.colorMapOrigin, 2, 1, fptr);
        //cout << headerObj.colorMapOrigin << endl;
        fread(&headerObj.colorMapLength, 2, 1, fptr);
        //cout << headerObj.colorMapLength << endl;
        headerObj.colorMapDepth = getc(fptr);
        //cout << "colorMapDepth: " << int(headerObj.colorMapDepth) << endl;
        fread(&headerObj.xOrigin, 2, 1, fptr);
        //cout << headerObj.xOrigin << endl;
        fread(&headerObj.yOrigin, 2, 1, fptr);
        //cout << headerObj.yOrigin << endl;
        fread(&headerObj.width, 2, 1, fptr);
        //cout << headerObj.width << endl;
        fread(&headerObj.height, 2, 1, fptr);
        //cout << headerObj.height << endl;
        headerObj.bitsPerPixel = getc(fptr);
        //cout << "bitsPerPixel: " << int(headerObj.bitsPerPixel) << endl;
        headerObj.imageDescriptor = getc(fptr);
        //cout << "imageDescriptor: " << int(headerObj.imageDescriptor) << endl;
        
        
        
        if ((pixels = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerObj.width*headerObj.height; i++)
            {
                
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
                
            }
        }
        
        int skipover = 0;
        int bytes2read = 0;
        skipover += headerObj.idLength;
        skipover += headerObj.colorMapType * headerObj.colorMapLength;
        fseek(fptr, skipover, ios_base::cur);
        
        bytes2read = headerObj.bitsPerPixel / 8;
        while (n < headerObj.width*headerObj.height)
        {
            if (headerObj.dataTypeCode == 2)
            {
                if (fread(p, 1, bytes2read, fptr) != bytes2read)
                {
                    break;
                }
                MergeBytes(&(pixels[n]), p, bytes2read);
                n++;
            }
        }
        fclose(fptr);
    }
    //180 rotation
    if ((fptr = fopen("../output/part10", "w")))
    {
        putc(0, fptr);
        putc(0, fptr);
        putc(2, fptr);                         /* uncompressed rgb */
        putc(0, fptr); putc(0, fptr);
        putc(0, fptr); putc(0, fptr);
        putc(0, fptr);
        putc(0, fptr); putc(0, fptr);           /* x origin */
        putc(0, fptr); putc(0, fptr);           /* y origin */
        putc((headerObj.width & 0x00ff), fptr);
        putc((headerObj.width & 0xff00) / 256, fptr);
        putc((headerObj.height & 0x00ff), fptr);
        putc((headerObj.height & 0xff00) / 256, fptr);
        putc(24, fptr);                        /* 24 bit bitmap */
        putc(0, fptr);
        
        for (int i = headerObj.width*headerObj.height-1; i >= 0; i--)
        {
            
            putc(pixels[i].b, fptr);
            putc(pixels[i].g, fptr);
            putc(pixels[i].r, fptr);
        }
    }
    
    PIXEL *y;
    y = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL));
    y = check("../examples/EXAMPLE_part10.tga");
    int c = 0;
    int m = 0;
    for (int i = headerObj.width*headerObj.height-1; i >= 0; i--)
    {
        if(int(y[i].r) == int(pixels[m].r) && int(y[i].g) == int(pixels[m].g) && int(y[i].b) == int(pixels[m].b))
        {
            c++;
            m++;
            //cout << c << endl;
        }
        else
        {
            //cout << "hello" << endl;
            break;
        }
        
    }
//    cout << "red :" << int(pixels[c].r) << endl;
//    cout << "green :" << int(pixels[c].g) << endl;
//    cout << "blue :" << int(pixels[c].b) << endl;
//    cout << "EXAMPLE :" << endl;
//    cout << "red :" << int(y[c].r) << endl;
//    cout << "green :" << int(y[c].g) << endl;
//    cout << "blue :" << int(y[c].b) << endl;
    
    if(c == headerObj.width*headerObj.height)
    {
        cout << "Test #12...... Passed!" << endl;
        
        tests++;
        cout << "Test Results: " << tests << "/12" << endl;
    }
    else
    {
        cout << "Test #12...... Failed!" << endl;
        cout << "Test Results: " << tests << "/12" << endl;
    }
}


PIXEL * overlay(PIXEL *top, PIXEL *bottom)
{
    PIXEL *comb;
    
    if ((comb = (PIXEL *)malloc(512*512 * sizeof(PIXEL))))
    {
        for (int i = 0; i < 512*512; i++)
        {
            if((top[i].r + top[i].g + top[i].b)/(3) <= 127)
            {
                //cout << int(((2*((float(top[i].r)/255) * (float(bottom[i].r)/255)))*255)+.5f) << endl;
                if(int(((2*((float(top[i].r)/255) * (float(bottom[i].r)/255)))*255)+.5f) > 255)
                    comb[i].r = 255;
                else
                    comb[i].r = int(((2*((float(top[i].r)/255) * (float(bottom[i].r)/255)))*255)+.5f);
                if(int(((2*((float(top[i].g)/255) * (float(bottom[i].g)/255)))*255)+.5f) > 255)
                    comb[i].g = 255;
                else
                    comb[i].g = int(((2*((float(top[i].g)/255) * (float(bottom[i].g)/255)))*255)+.5f);
                if(int(((2*((float(top[i].b)/255) * (float(bottom[i].b)/255)))*255)+.5f) > 255)
                    comb[i].b = 255;
                else
                    comb[i].b = int(((2*((float(top[i].b)/255) * (float(bottom[i].b)/255)))*255)+.5f);
            }
            else if((top[i].r + top[i].g + top[i].b)/(3) > 127)
            {
                //cout << ((1-(2*(1-(float(top[i].g)/255))*(1-(float(bottom[i].g)/255))))*255)+.5f << endl;
                if(int(((1-(2*(1-(float(top[i].r)/255))*(1-(float(bottom[i].r)/255))))*255)+.5f) < 0)
                {
                    //cout << "black" << endl;
                    //cout << i <<"here" << endl;
                    comb[i].r = 0;
                }
                else
                {
                    //cout << i <<"here" << endl;
                    comb[i].r = int(((1-(2*(1-(float(top[i].r)/255))*(1-(float(bottom[i].r)/255))))*255)+.5f);
                }
                if(int(((1-(2*(1-(float(top[i].g)/255))*(1-(float(bottom[i].g)/255))))*255)+.5f) < 0)
                    comb[i].g = 0;
                else
                    comb[i].g = int(((1-(2*(1-(float(top[i].g)/255))*(1-(float(bottom[i].g)/255))))*255)+.5f);
                if(int(((1-(2*(1-(float(top[i].b)/255))*(1-(float(bottom[i].b)/255))))*255)+.5f) < 0)
                    comb[i].b = 0;
                else
                    comb[i].b = int(((1-(2*(1-(float(top[i].b)/255))*(1-(float(bottom[i].b)/255))))*255)+.5f);
            }
        }
    }
    
    return comb;
}
PIXEL * multiply(PIXEL *top, PIXEL *bottom)
{
    PIXEL *comb;
    
    if ((comb = (PIXEL *)malloc(512*512 * sizeof(PIXEL))))
    {
        for (int i = 0; i < 512*512; i++)
        {
            comb[i].r = int((((float(top[i].r)/255) * (float(bottom[i].r)/255))*255)+.5f);
            //cout << int((((float(top[i].r)/255) * (float(bottom[i].r)/255))*255)+.5f) << endl;
            comb[i].g = int((((float(top[i].g)/255) * (float(bottom[i].g)/255))*255)+.5f);
            comb[i].b = int((((float(top[i].b)/255) * (float(bottom[i].b)/255))*255)+.5f);
            
        }
    }
    
    return comb;
}
    
PIXEL * subtraction(PIXEL *top, PIXEL *bottom)
{
    PIXEL *comb;
    
    if ((comb = (PIXEL *)malloc(512*512 * sizeof(PIXEL))))
    {
        for (int i = 0; i < 512*512; i++)
        {
            
            if((top[i].r - bottom[i].r) < 0)
            {
                comb[i].r = 0;
            }
            else
            {
                comb[i].r = (top[i].r - bottom[i].r);
            }

            if((top[i].g - bottom[i].g) < 0)
            {
                comb[i].g = 0;
            }
            else
            {
                comb[i].g = (top[i].g - bottom[i].g);
            }

            if((top[i].b - bottom[i].b) < 0)
            {
                comb[i].b = 0;
            }
            else
            {
                comb[i].b = (top[i].b - bottom[i].b);
            }
            
        }
    }
    return comb;
}

PIXEL * screen(PIXEL *top, PIXEL *bottom)
{
    PIXEL *comb;
    
    if ((comb = (PIXEL *)malloc(512*512 * sizeof(PIXEL))))
    {
        for (int i = 0; i < 512*512; i++)
        {
            comb[i].r = int(((1-((1-(float(top[i].r)/255))*(1-(float(bottom[i].r)/255))))*255)+.5f);
            //cout << (float(bottom[i].r)/255) << endl;
            comb[i].g = int(((1-((1-(float(top[i].g)/255))*(1-(float(bottom[i].g)/255))))*255)+.5f);
            //cout << int(((1-((1-(float(top[i].g)/255))*(1-(float(bottom[i].g)/255))))*255)+.5f) << endl;
            comb[i].b = int(((1-((1-(float(top[i].b)/255))*(1-(float(bottom[i].b)/255))))*255)+.5f);
            //cout << int(comb[i].b) << endl;
            
        }
    }
    
    return comb;
}
int main()
{
    //int size;
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    //test11();
    return 0;
}

PIXEL * check(string filename)
{
    Header headerObj;
    //string filename = "input/layer1.tga";
    ifstream file;
    int n = 0;
    FILE *fptr;
    PIXEL *pixels;
    unsigned char p[5];
    ///int size = headerObj.width*headerObj.height;
    if ((fptr = fopen(filename.c_str(), "r")))
    {
        headerObj.idLength = getc(fptr);
        //cout << "id length: " << int(headerObj.idLength) << endl;
        headerObj.colorMapType = getc(fptr);
        //cout << "color map: " << int(headerObj.colorMapType) << endl;
        headerObj.dataTypeCode = getc(fptr);
        //out << "data type: " << int(headerObj.dataTypeCode) << endl;
        fread(&headerObj.colorMapOrigin, 2, 1, fptr);
        //cout << headerObj.colorMapOrigin << endl;
        fread(&headerObj.colorMapLength, 2, 1, fptr);
        //cout << headerObj.colorMapLength << endl;
        headerObj.colorMapDepth = getc(fptr);
        //cout << "colorMapDepth: " << int(headerObj.colorMapDepth) << endl;
        fread(&headerObj.xOrigin, 2, 1, fptr);
        //cout << headerObj.xOrigin << endl;
        fread(&headerObj.yOrigin, 2, 1, fptr);
        //cout << headerObj.yOrigin << endl;
        fread(&headerObj.width, 2, 1, fptr);
        //cout << headerObj.width << endl;
        fread(&headerObj.height, 2, 1, fptr);
        //cout << headerObj.height << endl;
        headerObj.bitsPerPixel = getc(fptr);
        //cout << "bitsPerPixel: " << int(headerObj.bitsPerPixel) << endl;
        headerObj.imageDescriptor = getc(fptr);
        //cout << "imageDescriptor: " << int(headerObj.imageDescriptor) << endl;
        
        
        
        if ((pixels = (PIXEL *)malloc(headerObj.width*headerObj.height * sizeof(PIXEL))))
        {
            for (int i = 0; i < headerObj.width*headerObj.height; i++)
            {
                
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
                
            }
        }
        
        int skipover = 0;
        int bytes2read = 0;
        skipover += headerObj.idLength;
        skipover += headerObj.colorMapType * headerObj.colorMapLength;
        fseek(fptr, skipover, ios_base::cur);
        
        bytes2read = headerObj.bitsPerPixel / 8;
        while (n < headerObj.width*headerObj.height)
        {
            if (headerObj.dataTypeCode == 2)
            {
                if (fread(p, 1, bytes2read, fptr) != bytes2read)
                {
                    break;
                }
                MergeBytes(&(pixels[n]), p, bytes2read);
                n++;
            }
        }
        fclose(fptr);
    }
//    cout << "example: " << endl;
//    for(int i = 0; i < 3; i++)
//    {
//        cout << "red :" << int(pixels[i].r) << endl;
//        cout << "green :" << int(pixels[i].g) << endl;
//        cout << "blue :" << int(pixels[i].b) << endl;
//    }
    return pixels;
}
